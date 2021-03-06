/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "Core/Math/Color.h"
#include "Core/Math/Vector.h"
#include "Core/Math/Matrix4x3.h"
#include "Core/Math/Matrix4x4.h"

NAMESPACE_GRAPHICS_BEGIN

//-----------------------------------//

class RenderTarget;

/**
 * A view is a region in a render target that can be rendered into.
 * It has an associated renderer that will render into the view.
 */

class API_GRAPHICS RenderView
{
	DECLARE_UNCOPYABLE(RenderView)

public:

	RenderView();
	~RenderView();

	// Gets/sets the render target of the view.
	ACCESSOR(RenderTarget, RenderTarget*, target)

	// Gets/sets the origin of the view.
	ACCESSOR(Origin, Vector2i, origin)

	// Gets/sets the size of the view.
	ACCESSOR(Size, Vector2i, size)

	// Gets/sets the clear color of the view.
	ACCESSOR(ClearColor, const Color&, clearColor)

	// Gets/sets the depth (Z-order) priority of the view.
	ACCESSOR(DepthPriority, int, depthPriority)

	// Gets the aspect ratio of the view.
	float getAspectRatio() const;

	// Returns if a view has more priority than another.
	bool operator < (RenderView& view);

	// Handles render target resize.
	void handleRenderTargetResize();

public:

	// Origin of the view.
	Vector2i origin;

	// Size of the view.
	Vector2i size;

	// Render target.
	RenderTarget* target;

	// Background color.
	Color clearColor;

	// Depth priority.
	int depthPriority;

	// Projection matrix.
	Matrix4x4 projectionMatrix;

	// View matrix.
	Matrix4x3 viewMatrix;
};

//-----------------------------------//

NAMESPACE_GRAPHICS_END