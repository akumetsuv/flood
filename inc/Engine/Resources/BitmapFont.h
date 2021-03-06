/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "Engine/Resources/Font.h"

#ifdef ENABLE_FONT_BITMAP

NAMESPACE_ENGINE_BEGIN

//-----------------------------------//

/**
 * Represents a bitmap font resource. A bitmap font is a pre-rendered
 * texture, with all the glyphs packed (usually in a grid) and also
 * normally a binary file with all the glyphs coords (UVs).
 */

class BitmapFont : public Font
{
public:

	// Gets the size information of a glyph.
	virtual const Vector2 getGlyphSize() const;

	// Gets/sets the font image.
	ACCESSOR(Image, const ImageHandle&, image)

	// Gets/sets the font glyphs.
	ACCESSOR(Glyphs, const std::vector<Glyph>&, glyphs)

private:

	ImageHandle image;
	std::vector<Glyph> glyphs;
};

//-----------------------------------//

NAMESPACE_ENGINE_END

#endif

