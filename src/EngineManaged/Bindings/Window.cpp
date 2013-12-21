/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Window.h"
#include "InputManager.h"
#include "RenderContext.h"
#include "Vector.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::WindowSettings::WindowSettings(::WindowSettings* native)
{
    Width = native->width;
    Height = native->height;
    Handle = IntPtr(native->handle);
    Styles = (Flood::WindowStyles)native->styles;
}

Flood::WindowSettings::WindowSettings(System::IntPtr native)
{
    auto __native = (::WindowSettings*)native.ToPointer();
    Width = __native->width;
    Height = __native->height;
    Handle = IntPtr(__native->handle);
    Styles = (Flood::WindowStyles)__native->styles;
}

Flood::Window::Window(::Window* native)
    : Flood::RenderTarget((::RenderTarget*)native)
{
}

Flood::Window::Window(System::IntPtr native)
    : Flood::RenderTarget(native)
{
    auto __native = (::Window*)native.ToPointer();
}

Flood::Window::Window(Flood::WindowSettings settings)
    : Flood::RenderTarget((::RenderTarget*)nullptr)
{
}

Flood::RenderContext^ Flood::Window::CreateContext(Flood::RenderContextSettings _1)
{
    auto _marshal0 = ::RenderContextSettings();
    _marshal0.bitsPerPixel = (::uint16)(::uint16_t)_1.BitsPerPixel;
    _marshal0.depthBits = (::uint16)(::uint16_t)_1.DepthBits;
    _marshal0.stencilBits = (::uint16)(::uint16_t)_1.StencilBits;
    _marshal0.antialiasLevel = (::uint16)(::uint16_t)_1.AntialiasLevel;
    auto arg0 = _marshal0;
    auto __ret = ((::Window*)NativePtr)->createContext(arg0);
    if (__ret == nullptr) return nullptr;
    return gcnew Flood::RenderContext((::RenderContext*)__ret);
}

void Flood::Window::Update()
{
    ((::Window*)NativePtr)->update();
}

void Flood::Window::MakeCurrent()
{
    ((::Window*)NativePtr)->makeCurrent();
}

void Flood::Window::Show(bool visible)
{
    ((::Window*)NativePtr)->show(visible);
}

bool Flood::Window::PumpEvents()
{
    auto __ret = ((::Window*)NativePtr)->pumpEvents();
    return __ret;
}

bool Flood::Window::IsCursorVisible()
{
    auto __ret = ((::Window*)NativePtr)->isCursorVisible();
    return __ret;
}

void Flood::Window::SetCursorPosition(int x, int y)
{
    ((::Window*)NativePtr)->setCursorPosition(x, y);
}

bool Flood::Window::HasFocus()
{
    auto __ret = ((::Window*)NativePtr)->hasFocus();
    return __ret;
}

void Flood::Window::HandleWindowResize()
{
    ((::Window*)NativePtr)->handleWindowResize();
}

void Flood::Window::HandleWindowClose()
{
    ((::Window*)NativePtr)->handleWindowClose();
}

void Flood::Window::HandleWindowFocus(bool focusLost)
{
    ((::Window*)NativePtr)->handleWindowFocus(focusLost);
}

bool Flood::Window::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<Window^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::Window::GetHashCode()
{
    return (int)NativePtr;
}

void Flood::Window::CursorVisible::set(bool value)
{
    auto state = value;
    ((::Window*)NativePtr)->setCursorVisible(state);
}

void Flood::Window::CursorCapture::set(bool value)
{
    auto state = value;
    ((::Window*)NativePtr)->setCursorCapture(state);
}

Flood::Vector2i Flood::Window::CursorPosition::get()
{
    auto __ret = ((::Window*)NativePtr)->getCursorPosition();
    return Flood::Vector2i((::Vector2i*)&__ret);
}

Flood::InputManager^ Flood::Window::Input::get()
{
    auto __ret = ((::Window*)NativePtr)->getInput();
    if (__ret == nullptr) return nullptr;
    return gcnew Flood::InputManager((::InputManager*)__ret);
}

Flood::Settings Flood::Window::Settings::get()
{
    auto &__ret = ((::Window*)NativePtr)->getSettings();
    return Flood::Settings((::Settings*)&__ret);
}

Flood::WindowSettings Flood::Window::Settings1::get()
{
    return Flood::WindowSettings((::WindowSettings*)&((::Window*)NativePtr)->settings);
}

void Flood::Window::Settings1::set(Flood::WindowSettings value)
{
    auto _marshal0 = ::WindowSettings();
    _marshal0.width = (::uint16)(::uint16_t)value.Width;
    _marshal0.height = (::uint16)(::uint16_t)value.Height;
    _marshal0.handle = (void*)value.Handle.ToPointer();
    _marshal0.styles = (::WindowStyles)value.Styles;
    ((::Window*)NativePtr)->settings = _marshal0;
}

Flood::RenderContext^ Flood::Window::RenderContext::get()
{
    return gcnew Flood::RenderContext((::RenderContext*)((::Window*)NativePtr)->renderContext.get());
}

void Flood::Window::RenderContext::set(Flood::RenderContext^ value)
{
    ((::Window*)NativePtr)->renderContext = (::RenderContext*)value->NativePtr;
}

void Flood::Window::Idle::add(System::Action^ evt)
{
    if (!_IdleDelegateInstance)
    {
        _IdleDelegateInstance = gcnew _IdleDelegate(this, &Flood::Window::_IdleRaise);
        auto _fptr = (void (*)())Marshal::GetFunctionPointerForDelegate(_IdleDelegateInstance).ToPointer();
        ((::Window*)NativePtr)->onIdle.Connect(_fptr);
    }
    _Idle = static_cast<System::Action^>(System::Delegate::Combine(_Idle, evt));
}

void Flood::Window::Idle::remove(System::Action^ evt)
{
    _Idle = static_cast<System::Action^>(System::Delegate::Remove(_Idle, evt));
}

void Flood::Window::Idle::raise()
{
    _Idle();
}

void Flood::Window::_IdleRaise()
{
    Idle::raise();
}

void Flood::Window::Render::add(System::Action^ evt)
{
    if (!_RenderDelegateInstance)
    {
        _RenderDelegateInstance = gcnew _RenderDelegate(this, &Flood::Window::_RenderRaise);
        auto _fptr = (void (*)())Marshal::GetFunctionPointerForDelegate(_RenderDelegateInstance).ToPointer();
        ((::Window*)NativePtr)->onRender.Connect(_fptr);
    }
    _Render = static_cast<System::Action^>(System::Delegate::Combine(_Render, evt));
}

void Flood::Window::Render::remove(System::Action^ evt)
{
    _Render = static_cast<System::Action^>(System::Delegate::Remove(_Render, evt));
}

void Flood::Window::Render::raise()
{
    _Render();
}

void Flood::Window::_RenderRaise()
{
    Render::raise();
}

void Flood::Window::WindowClose::add(System::Action^ evt)
{
    if (!_WindowCloseDelegateInstance)
    {
        _WindowCloseDelegateInstance = gcnew _WindowCloseDelegate(this, &Flood::Window::_WindowCloseRaise);
        auto _fptr = (void (*)())Marshal::GetFunctionPointerForDelegate(_WindowCloseDelegateInstance).ToPointer();
        ((::Window*)NativePtr)->onWindowClose.Connect(_fptr);
    }
    _WindowClose = static_cast<System::Action^>(System::Delegate::Combine(_WindowClose, evt));
}

void Flood::Window::WindowClose::remove(System::Action^ evt)
{
    _WindowClose = static_cast<System::Action^>(System::Delegate::Remove(_WindowClose, evt));
}

void Flood::Window::WindowClose::raise()
{
    _WindowClose();
}

void Flood::Window::_WindowCloseRaise()
{
    WindowClose::raise();
}

void Flood::Window::WindowFocusChange::add(System::Action<bool>^ evt)
{
    if (!_WindowFocusChangeDelegateInstance)
    {
        _WindowFocusChangeDelegateInstance = gcnew _WindowFocusChangeDelegate(this, &Flood::Window::_WindowFocusChangeRaise);
        auto _fptr = (void (*)(bool))Marshal::GetFunctionPointerForDelegate(_WindowFocusChangeDelegateInstance).ToPointer();
        ((::Window*)NativePtr)->onWindowFocusChange.Connect(_fptr);
    }
    _WindowFocusChange = static_cast<System::Action<bool>^>(System::Delegate::Combine(_WindowFocusChange, evt));
}

void Flood::Window::WindowFocusChange::remove(System::Action<bool>^ evt)
{
    _WindowFocusChange = static_cast<System::Action<bool>^>(System::Delegate::Remove(_WindowFocusChange, evt));
}

void Flood::Window::WindowFocusChange::raise(bool _0)
{
    _WindowFocusChange(_0);
}

void Flood::Window::_WindowFocusChangeRaise(bool _0)
{
    WindowFocusChange::raise(_0);
}

