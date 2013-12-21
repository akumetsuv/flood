/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Engine/Input/Mouse.h>
#include "Device.h"

namespace Flood
{
    ref class MouseInfo;
    ref class InputDevice;
    ref class MouseMoveEvent;
    ref class MouseDragEvent;
    ref class MouseButtonEvent;
    ref class MouseWheelEvent;
    enum struct InputDeviceType;
    ref class InputEvent;
    enum struct MouseButton : unsigned char;
}

namespace Flood
{
    /// <summary>
    /// Holds the mouse state.
    /// </summary>
    public ref class MouseInfo : ICppInstance
    {
    public:

        property ::MouseInfo* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        MouseInfo(::MouseInfo* native);
        MouseInfo(System::IntPtr native);
        MouseInfo();

        property short X
        {
            short get();
            void set(short);
        }
        property short Y
        {
            short get();
            void set(short);
        }
        property bool InsideWindow
        {
            bool get();
            void set(bool);
        }
        property bool LeftButton
        {
            bool get();
            void set(bool);
        }
        property bool RightButton
        {
            bool get();
            void set(bool);
        }
        property bool MiddleButton
        {
            bool get();
            void set(bool);
        }
        property bool Aux1Button
        {
            bool get();
            void set(bool);
        }
        property bool Aux2Button
        {
            bool get();
            void set(bool);
        }
        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
