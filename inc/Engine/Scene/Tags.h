/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

NAMESPACE_ENGINE_BEGIN

//-----------------------------------//

/**
 * We define some default tags that we need and/or find useful.
 * Note that position 24 and beyond are reserved for internal engine use.
 */

namespace Tags
{
	enum Bitfield
	{
		NonPickable				= 1 << 24,
		NonTransformable		= 1 << 25,
		NonCollidable			= 1 << 26,
		NonCulled				= 1 << 27,
		UpdateTransformsOnly	= 1 << 28,
	};
}

//-----------------------------------//

NAMESPACE_ENGINE_END