/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Engine/Window/WindowManager.h>

namespace Flood
{
    ref class Window;
    ref class WindowManager;
    value struct WindowSettings;
    enum struct FileDialogFlags;
    enum struct DirectoryDialogFlags;
}

namespace Flood
{
    [System::Flags]
    public enum struct FileDialogFlags
    {
        Open = 2,
        Save = 4,
        AllowMultipleFiles = 8
    };

    public enum struct DirectoryDialogFlags
    {
        MustExist = 2
    };

    /// <summary>
    /// Window manager is responsible for managing the native windows in the
    /// platform. It also provides support for platform-specific dialogs.
    /// </summary>
    public ref class WindowManager : ICppInstance
    {
    public:

        property ::WindowManager* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        WindowManager(::WindowManager* native);
        WindowManager(System::IntPtr native);
        WindowManager();

        /// <summary>
        /// Creates a new window.
        /// </summary>
        virtual Flood::Window^ CreateWindow(Flood::WindowSettings settings);

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
