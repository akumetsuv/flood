/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Engine/Input/InputManager.h>

namespace Flood
{
    ref class InputDevice;
    ref class InputEvent;
    ref class Window;
    ref class InputManager;
}

namespace Flood
{
    /// <summary>
    /// Manages a set of input devices.
    /// </summary>
    public ref class InputManager : ICppInstance
    {
    public:

        property ::InputManager* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        InputManager(::InputManager* native);
        InputManager(System::IntPtr native);
        InputManager();

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

        static void InputInitialize();

        static void InputDeinitialize();

        static Flood::InputManager^ GetInputManager();

    };
}
