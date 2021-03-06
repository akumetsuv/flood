/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Editor/API.h"
#include "Editor.h"
#include "EditorIcons.h"
#include "EditorTags.h"
#include "EditorSettings.h"

#include "Core/PluginManager.h"
#include "Core/Utilities.h"

#include "DocumentManager.h"
#include "EventManager.h"

#include "Extensions/Project/ProjectPlugin.h"
#include "Extensions/Mono/MonoPlugin.h"

#include <wx/webview.h>
#include <wx/debugrpt.h>

FL_INSTANTIATE_TEMPLATES()

#ifdef BUILD_DEBUG
wxIMPLEMENT_WXWIN_MAIN_CONSOLE
#else
wxIMPLEMENT_WXWIN_MAIN
#endif

wxIMPLEMENT_APP_NO_MAIN(EditorApp);

int main(int argc, char **argv)
{
    wxDISABLE_DEBUG_SUPPORT();
    return wxEntry(argc, argv);
}

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

bool EditorApp::OnInit()
{
	if( !wxApp::OnInit() ) return false;

	wxImage::AddHandler( new wxPNGHandler() );

	mainFrame = new EditorFrame(VAPOR_EDITOR_NAME);
	mainFrame->SetSize(900, 550);
	mainFrame->SetIcon( wxIcon("iconEditor") );

	SetTopWindow(mainFrame);
	mainFrame->Show(true);

	return true;
}

//-----------------------------------//

static EditorFrame* gs_EditorInstance = nullptr;;
EditorFrame& GetEditor() { return *gs_EditorInstance; }

EditorFrame::EditorFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title)
	, paneCtrl(nullptr)
	, toolbarCtrl(nullptr)
	, statusCtrl(nullptr)
	, notebookCtrl(nullptr)
	, eventManager(nullptr)
	, pluginManager(nullptr)
	, documentManager(nullptr)
	, engine(nullptr)
	, archive(nullptr)
	, input(nullptr)
{
	gs_EditorInstance = this;

	CoreInitialize();

#ifdef EDITOR_OLD_UI
	documentManager = AllocateThis(DocumentManager);
	documentManager->onDocumentAdded.Connect(this, &EditorFrame::onDocumentAdded);
	documentManager->onDocumentRemoved.Connect(this, &EditorFrame::onDocumentRemoved);
	documentManager->onDocumentRenamed.Connect(this, &EditorFrame::onDocumentRenamed);
#endif

	createPlugins();

#ifdef EDITOR_OLD_UI
	createUI();
#endif

	createEngine();
	eventManager = AllocateThis(EventManager);

#ifdef ENABLE_PLUGIN_MONO
	Plugin* monoPlugin = pluginManager->getPluginFromClass( ReflectionGetType(MonoPlugin) );
	pluginManager->enablePlugin(monoPlugin);
#endif

#ifdef EDITOR_OLD_UI
	enablePlugins();
	createToolbar();
	createLastUI();
#endif

	Bind(wxEVT_IDLE, &EditorFrame::OnIdle, this);
	Bind(wxEVT_CLOSE_WINDOW, &EditorFrame::OnClose, this);

    auto projectPlugin = GetPlugin<ProjectPlugin>();
    projectPlugin->createDocument();
}

//-----------------------------------//

EditorFrame::~EditorFrame()
{
#ifdef EDITOR_OLD_UI
	Deallocate(documentManager);

	eventManager->disconnectPluginListeners();
#endif

	ArchiveDestroy(archive);

	pluginManager->disablePlugins();
	Deallocate(pluginManager);

	Deallocate(eventManager);
	Deallocate(input);

#ifdef EDITOR_OLD_UI
	if(notebookCtrl)
	{
		notebookCtrl->Destroy();
		paneCtrl->DetachPane(notebookCtrl);
	}
	
	if(paneCtrl)
	{
		paneCtrl->UnInit();
		delete paneCtrl;
	}
#endif

	Deallocate(engine);

	CoreDeinitialize();
}

//-----------------------------------//

void EditorFrame::OnIdle(wxIdleEvent& event)
{
	GetEngine()->update();

	const std::vector<Plugin*> plugins = pluginManager->getPlugins();
	
	for( size_t i = 0; i < plugins.size(); ++i )
	{
		EditorPlugin* plugin = (EditorPlugin*) plugins[i];
		if( !plugin->isEnabled() ) continue;

		plugin->onPluginUpdate();
	}
}

//-----------------------------------//

void EditorFrame::OnClose(wxCloseEvent& event)
{
	// Hide the window in advance so the ugly destroy is not seen.
	Hide();

	// Skip the event so the window frame is destroyed.
	event.Skip();
}

//-----------------------------------//

void EditorFrame::createPlugins()
{
	pluginManager = AllocateThis(PluginManager);

	// Find and instantiate plugins.
	std::vector<Plugin*> plugins;
	ClassCreateChilds(ReflectionGetType(EditorPlugin), AllocatorGetThis(), plugins);
	
	PluginsSortByPriority(plugins);
	pluginManager->registerPlugins(plugins);

	// Notify plugins that they have been registered.
	for( size_t i = 0; i < plugins.size(); i++ )
	{
		EditorPlugin* plugin = (EditorPlugin*) plugins[i];
		plugin->onPluginRegistered();
	}
}

//-----------------------------------//

void EditorFrame::enablePlugins()
{
	const std::vector<Plugin*>& plugins = pluginManager->getPlugins();
	
	for( size_t i = 0; i < plugins.size(); i++ )
	{
		EditorPlugin* plugin = (EditorPlugin*) plugins[i];
		
		if(plugin->getMetadata().startEnabled)
			pluginManager->enablePlugin(plugin);
	}
}

//-----------------------------------//

void EditorFrame::createEngine()
{
	engine = AllocateThis(Engine);
	engine->init();

	// Setup the input manager.
	input = AllocateThis(InputManager);
	input->createDefaultDevices();
	engine->setInputManager(input);

	// Mount the default assets path.
	ResourceManager* res = engine->getResourceManager();
	
	// Get the mount paths from the editor preferences.
	archive = ArchiveCreateVirtual( GetResourcesAllocator() );
	ArchiveMountDirectories(archive, MediaFolder, GetResourcesAllocator());
	
	res->setArchive(archive);
}

//-----------------------------------//

void EditorFrame::createUI()
{
	paneCtrl = new wxAuiManager();
	paneCtrl->SetManagedWindow(this);

	// Create notebook
	notebookCtrl = new wxAuiNotebook(this);
	notebookCtrl->Bind(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, &EditorFrame::onNotebookPageChanged, this);
	notebookCtrl->Bind(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, &EditorFrame::onNotebookPageClose, this);
	
	wxAuiPaneInfo pane;
	pane.CenterPane().PaneBorder(false);
	paneCtrl->AddPane(notebookCtrl, pane);

	// Create menus
	createMenus();

	// Create toolbar
	int style = wxAUI_TB_DEFAULT_STYLE /*| wxAUI_TB_OVERFLOW*/;
	toolbarCtrl = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, style);
	toolbarCtrl->SetGripperVisible(false);
	//toolbarCtrl->GetArtProvider()->SetElementSize(wxAUI_TBART_GRIPPER_SIZE, 0);
	toolbarCtrl->Bind(wxEVT_COMMAND_MENU_SELECTED, &EditorFrame::OnToolbarButtonClick, this);
	
	// Create status-bar.
	statusCtrl = CreateStatusBar();
}

//-----------------------------------//

void EditorFrame::createToolbar()
{
	if(!toolbarCtrl) return;

	toolbarCtrl->AddTool( Toolbar_ToogleGrid, "Grid", wxMEMORY_BITMAP(grid_icon), "Show/hide the editor grid", wxITEM_CHECK );
	//toolbarCtrl->AddTool( Toolbar_TooglePhysicsDebug, "Physics", wxMEMORY_BITMAP(grid_icon), "Show/hide the physics debug", wxITEM_CHECK );
	toolbarCtrl->ToggleTool( Toolbar_ToogleGrid, true );
	toolbarCtrl->AddTool( Toolbar_TooglePlay, "Play", wxMEMORY_BITMAP(resultset_next), "Enable/disable Play mode", wxITEM_CHECK );
	
	toolbarCtrl->AddSeparator();

	toolbarCtrl->AddTool( Toolbar_ToogleViewport, "Toogles maximize view", wxMEMORY_BITMAP(application_split), "Toogles maximize view" );
	toolbarCtrl->AddTool( Toolbar_ToogleSidebar, "Shows/hides the sidebar", wxMEMORY_BITMAP(application_side_tree_right), "Shows/hides the sidebar" );

	wxAuiPaneInfo toolPane;
	const char* name = "Toolbar";
	toolPane.ToolbarPane().Name(name).Caption(name).Top().PaneBorder(false);
	paneCtrl->AddPane(toolbarCtrl, toolPane);
}

//-----------------------------------//

Document* EditorFrame::getDocumentFromPage(int selection)
{
	if( selection < 0 ) return nullptr;
	if( (size_t)selection >= notebookCtrl->GetPageCount() ) return nullptr;

	wxWindow* window = notebookCtrl->GetPage(selection);

	const DocumentsVector& documents = documentManager->getDocuments();

	for( size_t i = 0; i < documents.size(); i++ )
	{
		Document* document = documents[i];
		wxWindow* documentWindow = (wxWindow*) document->getWindow();

		if( documentWindow == window ) return document;
	}

	return nullptr;
}

//-----------------------------------//

void EditorFrame::onNotebookPageChanged(wxAuiNotebookEvent& event)
{
	Document* oldDocument = getDocumentFromPage( event.GetOldSelection() );
	Document* newDocument = getDocumentFromPage( event.GetSelection() );

	if(oldDocument)
	{
		oldDocument->onDocumentUnselect();
		eventManager->onDocumentUnselect(*oldDocument);
		documentManager->currentDocument = nullptr;
	}

	if(newDocument)
	{
		documentManager->currentDocument = newDocument;
		newDocument->onDocumentSelect();
		eventManager->onDocumentSelect(*newDocument);
	}
}

//-----------------------------------//

void EditorFrame::onNotebookPageClose(wxAuiNotebookEvent& event)
{
	Document* document = getDocumentFromPage( event.GetSelection() );
	if( !document ) return;

	documentManager->removeDocument(document);

	// We veto the default wxWidgets closed event because we
	// already delete the notebook page when a document is removed.

	event.Veto();
}

//-----------------------------------//

Document* EditorFrame::getDocument() const
{
	if( !documentManager ) return nullptr;
	return documentManager->currentDocument;
}

//-----------------------------------//

void EditorFrame::onDocumentAdded(Document* document)
{
	if( !document ) return;

	eventManager->onDocumentCreate(*document);

	wxWindow* window = (wxWindow*) document->getWindow();

	if( !window )
	{
		LogDebug("Invalid window in document");
		return;
	}

	String name = PathGetFile( document->getPath() );
	if( name.empty() ) name = "untitled";
	
	getNotebook()->AddPage(window, name, true, document->getBitmap());

	getAUI()->Update();
}

//-----------------------------------//

void EditorFrame::onDocumentRemoved(Document* document)
{
	if( !document ) return;

	eventManager->onDocumentDestroy(*document);
	
	wxWindow* window = (wxWindow*) document->getWindow();
	int index = notebookCtrl->GetPageIndex(window);

	if( index != wxID_INVALID )
		notebookCtrl->DeletePage(index);
}

//-----------------------------------//

void EditorFrame::onDocumentRenamed(Document* document)
{
	if( !document ) return;

	String name = PathGetFile( document->getPath() );
	if( name.empty() ) name = "untitled";

	if( document->getUnsavedChanges() )
		name += "*";

	wxWindow* window = (wxWindow*) document->getWindow();
	size_t index = notebookCtrl->GetPageIndex(window);

	notebookCtrl->SetPageText(index, name);
}

//-----------------------------------//

void EditorFrame::OnToolbarButtonClick(wxCommandEvent& event)
{
	const int id = event.GetId();

	switch(id) 
	{
	//-----------------------------------//
	case Toolbar_ToogleViewport:
	{
#if 0
		int curExpansion = viewSplitter->GetExpanded();

		if( curExpansion >= 0 )
			viewSplitter->SetExpanded(-1);
		else
			viewSplitter->SetExpanded(0);
#endif
		break;
	}
	//-----------------------------------//
	case Toolbar_ToogleSidebar:
	{
#if 0
		if( !mainSplitter->GetWindow2() )
			mainSplitter->SplitVertically(viewSplitter, notebookCtrl, -220);
		else
			mainSplitter->Unsplit();

		break;
#endif
	} }
}

//-----------------------------------//

NAMESPACE_EDITOR_END