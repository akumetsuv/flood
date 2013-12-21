/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "TrueTypeFont.h"
#include "Font.h"
#include "Vector.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::TrueTypeFont::TrueTypeFont(::TrueTypeFont* native)
    : Flood::Font((::Font*)native)
{
}

Flood::TrueTypeFont::TrueTypeFont(System::IntPtr native)
    : Flood::Font(native)
{
    auto __native = (::TrueTypeFont*)native.ToPointer();
}

Flood::TrueTypeFont::TrueTypeFont()
    : Flood::Font((::Font*)nullptr)
{
    NativePtr = new ::TrueTypeFont();
}

void Flood::TrueTypeFont::Init()
{
    ((::TrueTypeFont*)NativePtr)->init();
}

bool Flood::TrueTypeFont::GetGlyphInfo(int codepoint, int size, [System::Runtime::InteropServices::Out] Flood::Glyph% glyph)
{
    ::Glyph arg2;
    auto __ret = ((::TrueTypeFont*)NativePtr)->getGlyphInfo(codepoint, size, arg2);
    glyph = Flood::Glyph((::Glyph*)&arg2);
    return __ret;
}

Flood::ResourceHandle<Flood::Image^> Flood::TrueTypeFont::CreateGlyphImage(int codepoint, int size)
{
    auto __ret = ((::TrueTypeFont*)NativePtr)->createGlyphImage(codepoint, size);
    return Flood::ResourceHandle<Flood::Image^>(__ret.id);
}

Flood::Vector2 Flood::TrueTypeFont::GetKerning(int codepoint1, int codepoint2, int fontSize)
{
    auto __ret = ((::TrueTypeFont*)NativePtr)->getKerning(codepoint1, codepoint2, fontSize);
    return Flood::Vector2((::Vector2*)&__ret);
}

bool Flood::TrueTypeFont::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<TrueTypeFont^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::TrueTypeFont::GetHashCode()
{
    return (int)NativePtr;
}

