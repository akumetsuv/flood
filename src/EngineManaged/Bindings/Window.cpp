/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "_Marshal.h"
#include "Window.h"
#include "RenderContext.h"
#include "RenderTarget.h"
#include "Color.h"
#include "Vector.h"
#include "InputManager.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace clix;

Flood::WindowSettings::WindowSettings(::WindowSettings* native)
{
    Title = marshalString<E_UTF8>(native->title);
    FullScreen = native->fullScreen;
    Handle = IntPtr(native->handle);
    Styles = (Flood::WindowStyles)native->styles;
}

Flood::WindowSettings::WindowSettings(System::IntPtr native)
{
    auto __native = (::WindowSettings*)native.ToPointer();
    Title = marshalString<E_UTF8>(__native->title);
    FullScreen = __native->fullScreen;
    Handle = IntPtr(__native->handle);
    Styles = (Flood::WindowStyles)__native->styles;
}

Flood::WindowSettings::WindowSettings(unsigned short width, unsigned short height, System::String^ title, bool fullscreen)
{
}

Flood::Window::Window(::Window* native)
    : RenderTarget(native)
{
}

Flood::Window::Window(System::IntPtr native)
    : RenderTarget(native)
{
    auto __native = (::Window*)native.ToPointer();
}

Flood::Window::Window(Flood::WindowSettings settings)
    : RenderTarget(nullptr)
{
}

Flood::RenderContext^ Flood::Window::CreateContext(Flood::RenderContextSettings^ _224)
{
    auto &arg0 = *(::RenderContextSettings*)_224->NativePtr;
    auto ret = ((::Window*)NativePtr)->createContext(arg0);
    return gcnew Flood::RenderContext((::RenderContext*)ret);
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
    auto ret = ((::Window*)NativePtr)->pumpEvents();
    return ret;
}

void Flood::Window::SetTitle(System::String^ title)
{
    auto arg0 = marshalString<E_UTF8>(title);
    ((::Window*)NativePtr)->setTitle(arg0);
}

void Flood::Window::SetCursorVisible(bool state)
{
    ((::Window*)NativePtr)->setCursorVisible(state);
}

bool Flood::Window::IsCursorVisible()
{
    auto ret = ((::Window*)NativePtr)->isCursorVisible();
    return ret;
}

void Flood::Window::SetCursorCapture(bool state)
{
    ((::Window*)NativePtr)->setCursorCapture(state);
}

Flood::Vector2i Flood::Window::GetCursorPosition()
{
    auto ret = ((::Window*)NativePtr)->getCursorPosition();
    return Flood::Vector2i((::Vector2i*)&ret);
}

void Flood::Window::SetCursorPosition(int x, int y)
{
    ((::Window*)NativePtr)->setCursorPosition(x, y);
}

bool Flood::Window::HasFocus()
{
    auto ret = ((::Window*)NativePtr)->hasFocus();
    return ret;
}

Flood::InputManager^ Flood::Window::GetInput()
{
    auto ret = ((::Window*)NativePtr)->getInput();
    return gcnew Flood::InputManager((::InputManager*)ret);
}

Flood::Settings Flood::Window::GetSettings()
{
    auto ret = &((::Window*)NativePtr)->getSettings();
    return Flood::Settings((::Settings*)&ret);
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
