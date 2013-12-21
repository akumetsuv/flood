/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Core/FileWatcher.h>

namespace Flood
{
    value struct FileWatchEvent;
    enum struct FileWatchEventKind;
    ref class FileWatcher;
}

namespace Flood
{
    public enum struct FileWatchEventKind
    {
        Added = 0,
        Deleted = 1,
        Modified = 2,
        Renamed = 3
    };

    public value struct FileWatchEvent
    {
    public:

        FileWatchEvent(::FileWatchEvent* native);
        FileWatchEvent(System::IntPtr native);
        Flood::FileWatchEventKind Action;
        unsigned int WatchId;
        System::IntPtr Userdata;
    };

    /// <summary>
    /// Listens to files and directories and dispatches events to notify the parent
    /// program of the changes.
    /// </summary>
    public ref class FileWatcher : ICppInstance
    {
    public:

        property ::FileWatcher* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        FileWatcher(::FileWatcher* native);
        FileWatcher(System::IntPtr native);
        FileWatcher();

    private:
        delegate void _FileWatchEventDelegate(const ::FileWatchEvent& _0);
        _FileWatchEventDelegate^ _FileWatchEventDelegateInstance;
        void _FileWatchEventRaise(const ::FileWatchEvent& _0);
        System::Action<Flood::FileWatchEvent>^ _FileWatchEvent;
    public:
        event System::Action<Flood::FileWatchEvent>^ FileWatchEvent
        {
            void add(System::Action<Flood::FileWatchEvent>^ evt);
            void remove(System::Action<Flood::FileWatchEvent>^ evt);
            void raise(Flood::FileWatchEvent _0);
        }
        virtual void RemoveWatch(unsigned int FileWatchId);

        virtual void Update();

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
