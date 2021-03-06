/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Editor/API.h"
#include "CameraPlugin.h"
#include "CameraControls.h"
#include "Editor.h"
#include "DocumentWindow.h"
#include "EventManager.h"
#include "Engine/Scene/Scene.h"

#ifdef ALL_PLUGINS

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

REFLECT_CHILD_CLASS(CameraPlugin, EditorPlugin)
REFLECT_CLASS_END()

//-----------------------------------//

CameraPlugin::CameraPlugin()
	: Plugin()
	, cameraControls(nullptr)
{ }

//-----------------------------------//

PluginMetadata CameraPlugin::getMetadata()
{
	static PluginMetadata metadata;
	
	metadata.name = "Camera Controls";
	metadata.description = "Provides advanced camera control";
	metadata.author = "triton";
	metadata.version = "1.0";

	return metadata;
}

//-----------------------------------//

void CameraPlugin::onPluginEnable()
{
	Viewframe* viewframe = editor->getMainViewframe();
	cameraControls = new CameraControls(editor, viewframe);

	wxSizerFlags sizerFlags(0);
	sizerFlags.Expand().Border(wxTOP, 2);

	wxSizer* viewSizer = viewframe->getSizer();
	viewSizer->Add( cameraControls, sizerFlags );
	viewSizer->Layout();

	// Subscribe as an event listener.
	EventManager* events = editor->getEventManager();
	events->addEventListener(this);
}

//-----------------------------------//

void CameraPlugin::onPluginDisable()
{
	Viewframe* viewframe = editor->getMainViewframe();
	viewframe->RemoveChild(cameraControls);

	wxSizer* viewSizer = viewframe->getSizer();
	bool found = viewSizer->Detach(cameraControls);
	assert( found == true );
	viewSizer->Layout();
		
	cameraControls->Destroy();
}

//-----------------------------------//

void CameraPlugin::onSceneLoad( const ScenePtr& scene )
{
	const ScenePtr& editorScene = editor->getEditorScene();
	editorScene->onEntityChanged.Connect( this, &CameraPlugin::onEntityChange );
	scene->onEntityChanged.Connect( this, &CameraPlugin::onEntityChange );
	
	cameraControls->updateCameraSelection();
}

//-----------------------------------//

void CameraPlugin::onSceneUnload( const ScenePtr& scene )
{
	const ScenePtr& editorScene = editor->getEditorScene();
	editorScene->onEntityChanged.Disconnect( this, &CameraPlugin::onEntityChange );
	scene->onEntityChanged.Disconnect( this, &CameraPlugin::onEntityChange );
	
	cameraControls->updateCameraSelection();
}

//-----------------------------------//

void CameraPlugin::onEntityChange()
{
	cameraControls->updateCameraSelection();
}

//-----------------------------------//
#if 0
CameraPtr CameraPlugin::getPlayerCamera() const
{
	ScenePtr scene = engine->getSceneManager();
	CameraPtr camera;
	
	const std::vector<EntityPtr> entities = scene->getEntities();
	
	for( size_t i = 0; i < entities.size(); i++ )
	{
		const EntityPtr& node = entities[i];
		camera = node->getComponent<Camera>();

		if( camera ) break;
	}

	return camera;
}

//-----------------------------------//

void CameraPlugin::switchPlayMode(bool switchToPlay)
{
	CameraPtr camera = getPlayerCamera();
	EntityPtr nodeCamera;
	ControllerPtr controller;

	if( camera )
		nodeCamera = camera->getEntity()->getShared();

	if( !nodeCamera )
		return;

	if( controller )
		controller = nodeCamera->getComponentFromFamily<Controller>();

	if( switchToPlay )
	{
		// Change the active camera.
		RenderView* view = viewframe->getView();

		if( controller )
			controller->setEnabled(true);

		if( camera )
			view->setCamera(camera);
	}
	else
	{
		if( controller )
			controller->setEnabled(false);

		viewframe->switchToDefaultCamera();
	}
}
#endif

//-----------------------------------//

NAMESPACE_EDITOR_END

#endif