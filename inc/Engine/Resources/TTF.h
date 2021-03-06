/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#ifdef ENABLE_FONT_FREETYPE2

#include "Engine/Resources/Font.h"

NAMESPACE_ENGINE_BEGIN

//-----------------------------------//

/**
 * Represents a TTF (TrueType) font resource. Loads a TTF font using the
 * cross-platform FreeType library. Parses all the font glyphs of a size,
 * and packs them all into a big texture (texture atlas) for rendering.
 */

class TTF : public Font
{
public:

	TTF(const String& font);
	~TTF();

private:

};

//-----------------------------------//

NAMESPACE_ENGINE_END

#endif

