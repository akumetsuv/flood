/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "Resources/ResourceDatabase.h"

class ResourceIndexer;

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

class ResourceThumbnailer
{
public:

	ResourceThumbnailer();

	// Sets the resource indexer.
	void setIndexer(ResourceIndexer*);

	// Updates the thumbnailer.
	void update();

	// Generate thumbnail of mesh.
	ImagePtr generateMesh(const MeshHandle& mesh);

	// Generates the thumbnail.
	void generateThumbnail();

	Event1<const ResourceMetadata&> onResourceThumbnailed;

protected:

	void onResourceIndexed(const ResourceMetadata&);

	// Sets up the render buffers.
	bool setupRender();

	ResourceIndexer* indexer;

	ScenePtr scene;
	EntityPtr entityCamera;
	CameraPtr camera;
	RenderView* renderView;

	//TexturePtr colorTexture;
	RenderBuffer* renderBuffer;

	ConcurrentQueue<ResourceMetadata> resourcesIndexed;
};

//-----------------------------------//

NAMESPACE_EDITOR_END