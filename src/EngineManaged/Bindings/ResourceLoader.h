/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Resources/ResourceLoader.h>
#include "Extension.h"

namespace Flood
{
    value struct ResourceLoadOption;
    value struct ResourceLoadOptions;
    ref class Resource;
    enum struct ResourceGroup;
    ref class ResourceStream;
    ref class ResourceLoader;
    ref class Extension;
    value struct ExtensionMetadata;
}

namespace Flood
{
    public value struct ResourceLoadOption
    {
    public:

        ResourceLoadOption(::ResourceLoadOption* native);
        ResourceLoadOption(System::IntPtr native);
        int Key;
        int Value;
    };

    public value struct ResourceLoadOptions
    {
    public:

        ResourceLoadOptions(::ResourceLoadOptions* native);
        ResourceLoadOptions(System::IntPtr native);
        Flood::Resource^ Resource;
        Flood::ResourceGroup Group;
        bool IsHighPriority;
        bool SendLoadEvent;
        bool AsynchronousLoad;
        bool KeepStreamOpen;
        Flood::ResourceLoadOption Option;
        void AddOption(int key, int value);

    };

    public ref class ResourceStream : ICppInstance
    {
    public:

        property ::ResourceStream* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        ResourceStream(::ResourceStream* native);
        ResourceStream(System::IntPtr native);
        ResourceStream();

        property Flood::ResourceLoader^ Loader
        {
            Flood::ResourceLoader^ get();
            void set(Flood::ResourceLoader^);
        }
        virtual int Decode(System::IntPtr buffer, unsigned int size);

        virtual void Reset();

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };

    /// <summary>
    /// Resource loaders decode resource data into a proper resource. This is an
    /// interface that should be implemented to provide the resource codec services
    /// for the formats handled by the loader. The loader also provides the
    /// extensions of those formats.
    /// </summary>
    public ref class ResourceLoader : Flood::Extension
    {
    public:

        ResourceLoader(::ResourceLoader* native);
        ResourceLoader(System::IntPtr native);
        ResourceLoader();

        property Flood::ExtensionMetadata Metadata
        {
            Flood::ExtensionMetadata get();
        }
        property Flood::ResourceGroup ResourceGroup
        {
            Flood::ResourceGroup get();
        }
        virtual Flood::Resource^ Prepare(Flood::ResourceLoadOptions _1);

        virtual bool Decode(Flood::ResourceLoadOptions _2);

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
