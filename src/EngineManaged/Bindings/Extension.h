/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Core/Extension.h>

namespace Flood
{
    ref class Extension;
    value struct ExtensionMetadata;

    public value struct ExtensionMetadata
    {
    public:
        ExtensionMetadata(::ExtensionMetadata* native);
        ExtensionMetadata(System::IntPtr native);
        System::String^ Name;
        System::String^ Description;
        int Priority;
    };

    public ref class Extension : ICppInstance
    {
    public:
        property ::Extension* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        Extension(::Extension* native);
        Extension(System::IntPtr native);
        Extension();
        property Flood::ExtensionMetadata Metadata
        {
            Flood::ExtensionMetadata get();
        }
        void OnInit();
        void OnCleanup();
        virtual bool Equals(System::Object^ object) override;
        virtual int GetHashCode() override;
    };
}
