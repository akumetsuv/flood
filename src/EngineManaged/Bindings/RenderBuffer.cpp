/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "RenderBuffer.h"
#include "Image.h"
#include "Texture.h"
#include "Vector.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::RenderBuffer::RenderBuffer(::RenderBuffer* native)
    : Flood::RenderTarget((::RenderTarget*)native)
{
}

Flood::RenderBuffer::RenderBuffer(System::IntPtr native)
    : Flood::RenderTarget(native)
{
    auto __native = (::RenderBuffer*)native.ToPointer();
}

void Flood::RenderBuffer::MakeCurrent()
{
    ((::RenderBuffer*)NativePtr)->makeCurrent();
}

void Flood::RenderBuffer::Bind()
{
    ((::RenderBuffer*)NativePtr)->bind();
}

void Flood::RenderBuffer::Unbind()
{
    ((::RenderBuffer*)NativePtr)->unbind();
}

bool Flood::RenderBuffer::Check()
{
    auto __ret = ((::RenderBuffer*)NativePtr)->check();
    return __ret;
}

void Flood::RenderBuffer::Update()
{
    ((::RenderBuffer*)NativePtr)->update();
}

Flood::Image^ Flood::RenderBuffer::ReadImage(char attachment)
{
    auto arg0 = (::int8)(::int8_t)attachment;
    auto __ret = ((::RenderBuffer*)NativePtr)->readImage(arg0);
    if (__ret == nullptr) return nullptr;
    return gcnew Flood::Image((::Image*)__ret);
}

void Flood::RenderBuffer::CreateRenderBuffer(Flood::RenderBufferType _0)
{
    auto arg0 = (::RenderBufferType)_0;
    ((::RenderBuffer*)NativePtr)->createRenderBuffer(arg0);
}

Flood::Texture^ Flood::RenderBuffer::CreateRenderTexture(Flood::RenderBufferType _1)
{
    auto arg0 = (::RenderBufferType)_1;
    auto __ret = ((::RenderBuffer*)NativePtr)->createRenderTexture(arg0);
    return gcnew Flood::Texture((::Texture*)__ret.get());
}

void Flood::RenderBuffer::AttachRenderTexture(Flood::Texture^ tex)
{
    auto arg0 = (::Texture*)tex->NativePtr;
    ((::RenderBuffer*)NativePtr)->attachRenderTexture(arg0);
}

Flood::RenderBuffer::RenderBuffer(Flood::Settings settings)
    : Flood::RenderTarget((::RenderTarget*)nullptr)
{
}

bool Flood::RenderBuffer::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<RenderBuffer^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::RenderBuffer::GetHashCode()
{
    return (int)NativePtr;
}

Flood::Settings Flood::RenderBuffer::Settings::get()
{
    auto &__ret = ((::RenderBuffer*)NativePtr)->getSettings();
    return Flood::Settings((::Settings*)&__ret);
}

Flood::Settings Flood::RenderBuffer::Settings1::get()
{
    return Flood::Settings((::Settings*)&((::RenderBuffer*)NativePtr)->settings);
}

void Flood::RenderBuffer::Settings1::set(Flood::Settings value)
{
    auto _marshal0 = ::Settings();
    _marshal0.width = (::uint16)(::uint16_t)value.Width;
    _marshal0.height = (::uint16)(::uint16_t)value.Height;
    ((::RenderBuffer*)NativePtr)->settings = _marshal0;
}

