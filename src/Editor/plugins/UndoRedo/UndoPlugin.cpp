/************************************************************************
*
* vapor3D Editor � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#include "PCH.h"
#include "UndoPlugin.h"
#include "Editor.h"
#include "UndoManager.h"
#include "EditorIcons.h"

namespace vapor { namespace editor {

//-----------------------------------//

UndoPlugin::UndoPlugin( EditorFrame* frame )
	: Plugin(frame)
{
	undoManager = editor->getUndoManager();
	assert( undoManager != nullptr );
}

//-----------------------------------//

PluginMetadata UndoPlugin::getMetadata()
{
	PluginMetadata metadata;
	
	metadata.name = "Undo/Redo";
	metadata.description = "Provides undo and redo functionality";
	metadata.author = "triton";
	metadata.version = "1.0";

	return metadata;
}

//-----------------------------------//

void UndoPlugin::onPluginEnable()
{
	wxAuiToolBar* toolBar = editor->getToolbar();
	
	if(toolBar)
	{
		addTool( toolBar->AddSeparator() );

		wxBitmap iconUndo = wxMEMORY_BITMAP(arrow_undo);
		undoButton = toolBar->AddTool( wxID_UNDO, "Undo", iconUndo, "Undo" );
		addTool(undoButton);

		wxBitmap iconRedo = wxMEMORY_BITMAP(arrow_redo);
		redoButton = toolBar->AddTool( wxID_REDO, "Redo", iconRedo, "Redo" );
		addTool(redoButton);

		toolBar->Bind( wxEVT_COMMAND_TOOL_CLICKED, &UndoPlugin::onUndoButtonClick, this, undoButton->GetId() );
		toolBar->Bind( wxEVT_COMMAND_TOOL_CLICKED, &UndoPlugin::onRedoButtonClick, this, redoButton->GetId() );
	}

	wxMenu* menu = editor->editMenu;
	undoItem = menu->Append(undoButton->GetId(), undoButton->GetLabel() + "\tCtrl-Z");
	redoItem = menu->Append(redoButton->GetId(), redoButton->GetLabel() + "\tCtrl-Y");

	editor->Bind( wxEVT_COMMAND_TOOL_CLICKED, &UndoPlugin::onUndoButtonClick, this, undoButton->GetId() );
	editor->Bind( wxEVT_COMMAND_TOOL_CLICKED, &UndoPlugin::onRedoButtonClick, this, redoButton->GetId() );

	// Connect to undo/redo events.
	undoManager->onUndoRedoEvent.Connect(this, &UndoPlugin::onUndoEvent);

	// Updates the state of the buttons.
	updateButtons();
}

//-----------------------------------//

void UndoPlugin::onPluginDisable()
{
	// Disconnect to undo/redo events.
	undoManager->onUndoRedoEvent.Disconnect(this, &UndoPlugin::onUndoEvent);
}

//-----------------------------------//

void UndoPlugin::onUndoEvent()
{
	updateButtons();
	editor->redrawView();
}

//-----------------------------------//

void UndoPlugin::updateButtons()
{
	const Operations& undoOperations = undoManager->getUndoOperations();
	bool undoEmpty = undoOperations.empty();

	const Operations& redoOperations = undoManager->getRedoOperations();
	bool redoEmpty = redoOperations.empty();

	wxAuiToolBar* toolBar = editor->getToolbar();

	if(toolBar)
	{
		toolBar->EnableTool( undoButton->GetId(), !undoEmpty );
		toolBar->EnableTool( redoButton->GetId(), !redoEmpty );
		toolBar->Refresh();

		undoItem->Enable( !undoEmpty );
		redoItem->Enable( !redoEmpty );
	}
}

//-----------------------------------//

void UndoPlugin::onUndoButtonClick(wxCommandEvent& event)
{
	undoManager->undoOperation();
}

//-----------------------------------//

void UndoPlugin::onRedoButtonClick(wxCommandEvent& event)
{
	undoManager->redoOperation();
}

//-----------------------------------//

} } // end namespaces