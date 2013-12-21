/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Mouse.h"
#include "Device.h"
#include "MouseEvents.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::MouseInfo::MouseInfo(::MouseInfo* native)
{
    NativePtr = native;
}

Flood::MouseInfo::MouseInfo(System::IntPtr native)
{
    auto __native = (::MouseInfo*)native.ToPointer();
    NativePtr = __native;
}

Flood::MouseInfo::MouseInfo()
{
    NativePtr = new ::MouseInfo();
}

bool Flood::MouseInfo::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<MouseInfo^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::MouseInfo::GetHashCode()
{
    return (int)NativePtr;
}

System::IntPtr Flood::MouseInfo::Instance::get()
{
    return System::IntPtr(NativePtr);
}

void Flood::MouseInfo::Instance::set(System::IntPtr object)
{
    NativePtr = (::MouseInfo*)object.ToPointer();
}

short Flood::MouseInfo::X::get()
{
    return ((::MouseInfo*)NativePtr)->x;
}

void Flood::MouseInfo::X::set(short value)
{
    ((::MouseInfo*)NativePtr)->x = value;
}

short Flood::MouseInfo::Y::get()
{
    return ((::MouseInfo*)NativePtr)->y;
}

void Flood::MouseInfo::Y::set(short value)
{
    ((::MouseInfo*)NativePtr)->y = value;
}

bool Flood::MouseInfo::InsideWindow::get()
{
    return ((::MouseInfo*)NativePtr)->insideWindow;
}

void Flood::MouseInfo::InsideWindow::set(bool value)
{
    ((::MouseInfo*)NativePtr)->insideWindow = value;
}

bool Flood::MouseInfo::LeftButton::get()
{
    return ((::MouseInfo*)NativePtr)->leftButton;
}

void Flood::MouseInfo::LeftButton::set(bool value)
{
    ((::MouseInfo*)NativePtr)->leftButton = value;
}

bool Flood::MouseInfo::RightButton::get()
{
    return ((::MouseInfo*)NativePtr)->rightButton;
}

void Flood::MouseInfo::RightButton::set(bool value)
{
    ((::MouseInfo*)NativePtr)->rightButton = value;
}

bool Flood::MouseInfo::MiddleButton::get()
{
    return ((::MouseInfo*)NativePtr)->middleButton;
}

void Flood::MouseInfo::MiddleButton::set(bool value)
{
    ((::MouseInfo*)NativePtr)->middleButton = value;
}

bool Flood::MouseInfo::Aux1Button::get()
{
    return ((::MouseInfo*)NativePtr)->aux1Button;
}

void Flood::MouseInfo::Aux1Button::set(bool value)
{
    ((::MouseInfo*)NativePtr)->aux1Button = value;
}

bool Flood::MouseInfo::Aux2Button::get()
{
    return ((::MouseInfo*)NativePtr)->aux2Button;
}

void Flood::MouseInfo::Aux2Button::set(bool value)
{
    ((::MouseInfo*)NativePtr)->aux2Button = value;
}

