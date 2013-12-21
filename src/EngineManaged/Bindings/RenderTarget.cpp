/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "RenderTarget.h"
#include "RenderContext.h"
#include "RenderView.h"
#include "Vector.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::Settings::Settings(::Settings* native)
{
    Width = native->width;
    Height = native->height;
}

Flood::Settings::Settings(System::IntPtr native)
{
    auto __native = (::Settings*)native.ToPointer();
    Width = __native->width;
    Height = __native->height;
}

Flood::Settings::Settings(unsigned short width, unsigned short height)
{
    ::Settings _native((::uint16)(::uint16_t)width, (::uint16)(::uint16_t)height);
    this->Width = _native.width;
    this->Height = _native.height;
}

Flood::Vector2i Flood::Settings::Size::get()
{
    auto _this0 = ::Settings();
    _this0.width = (::uint16)(::uint16_t)(*this).Width;
    _this0.height = (::uint16)(::uint16_t)(*this).Height;
    auto __ret = _this0.getSize();
    Width = _this0.width;
    Height = _this0.height;
    return Flood::Vector2i((::Vector2i*)&__ret);
}

Flood::RenderTarget::RenderTarget(::RenderTarget* native)
{
    NativePtr = native;
}

Flood::RenderTarget::RenderTarget(System::IntPtr native)
{
    auto __native = (::RenderTarget*)native.ToPointer();
    NativePtr = __native;
}

Flood::RenderTarget::RenderTarget()
{
}

Flood::RenderView^ Flood::RenderTarget::CreateView()
{
    auto __ret = ((::RenderTarget*)NativePtr)->createView();
    if (__ret == nullptr) return nullptr;
    return gcnew Flood::RenderView((::RenderView*)__ret);
}

void Flood::RenderTarget::RemoveViews()
{
    ((::RenderTarget*)NativePtr)->removeViews();
}

void Flood::RenderTarget::MakeCurrent()
{
    ((::RenderTarget*)NativePtr)->makeCurrent();
}

void Flood::RenderTarget::Update()
{
    ((::RenderTarget*)NativePtr)->update();
}

void Flood::RenderTarget::HandleResize()
{
    ((::RenderTarget*)NativePtr)->handleResize();
}

bool Flood::RenderTarget::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<RenderTarget^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::RenderTarget::GetHashCode()
{
    return (int)NativePtr;
}

System::IntPtr Flood::RenderTarget::Instance::get()
{
    return System::IntPtr(NativePtr);
}

void Flood::RenderTarget::Instance::set(System::IntPtr object)
{
    NativePtr = (::RenderTarget*)object.ToPointer();
}

Flood::Settings Flood::RenderTarget::Settings::get()
{
    auto &__ret = ((::RenderTarget*)NativePtr)->getSettings();
    return Flood::Settings((::Settings*)&__ret);
}

Flood::RenderContext^ Flood::RenderTarget::Context::get()
{
    auto __ret = ((::RenderTarget*)NativePtr)->getContext();
    if (__ret == nullptr) return nullptr;
    return gcnew Flood::RenderContext((::RenderContext*)__ret);
}

void Flood::RenderTarget::Context::set(Flood::RenderContext^ value)
{
    auto context = value;
    auto arg0 = (::RenderContext*)context->NativePtr;
    ((::RenderTarget*)NativePtr)->setContext(arg0);
}

System::IntPtr Flood::RenderTarget::UserData::get()
{
    auto __ret = ((::RenderTarget*)NativePtr)->getUserData();
    if (__ret == nullptr) return System::IntPtr();
    return IntPtr(__ret);
}

void Flood::RenderTarget::UserData::set(System::IntPtr value)
{
    auto v = value;
    auto arg0 = (void*)v.ToPointer();
    ((::RenderTarget*)NativePtr)->setUserData(arg0);
}

Flood::RenderContext^ Flood::RenderTarget::Context1::get()
{
    return gcnew Flood::RenderContext((::RenderContext*)((::RenderTarget*)NativePtr)->context.get());
}

void Flood::RenderTarget::Context1::set(Flood::RenderContext^ value)
{
    ((::RenderTarget*)NativePtr)->context = (::RenderContext*)value->NativePtr;
}

void Flood::RenderTarget::TargetResize::add(System::Action<Flood::Settings>^ evt)
{
    if (!_TargetResizeDelegateInstance)
    {
        _TargetResizeDelegateInstance = gcnew _TargetResizeDelegate(this, &Flood::RenderTarget::_TargetResizeRaise);
        auto _fptr = (void (*)(const ::Settings&))Marshal::GetFunctionPointerForDelegate(_TargetResizeDelegateInstance).ToPointer();
        ((::RenderTarget*)NativePtr)->onTargetResize.Connect(_fptr);
    }
    _TargetResize = static_cast<System::Action<Flood::Settings>^>(System::Delegate::Combine(_TargetResize, evt));
}

void Flood::RenderTarget::TargetResize::remove(System::Action<Flood::Settings>^ evt)
{
    _TargetResize = static_cast<System::Action<Flood::Settings>^>(System::Delegate::Remove(_TargetResize, evt));
}

void Flood::RenderTarget::TargetResize::raise(Flood::Settings _0)
{
    _TargetResize(_0);
}

void Flood::RenderTarget::_TargetResizeRaise(const ::Settings& _0)
{
    TargetResize::raise(Flood::Settings((::Settings*)&_0));
}

