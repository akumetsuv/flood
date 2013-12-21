/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "FileWatcher.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::FileWatchEvent::FileWatchEvent(::FileWatchEvent* native)
{
    Action = (Flood::FileWatchEventKind)native->action;
    WatchId = native->watchId;
    Userdata = IntPtr(native->userdata);
}

Flood::FileWatchEvent::FileWatchEvent(System::IntPtr native)
{
    auto __native = (::FileWatchEvent*)native.ToPointer();
    Action = (Flood::FileWatchEventKind)__native->action;
    WatchId = __native->watchId;
    Userdata = IntPtr(__native->userdata);
}

Flood::FileWatcher::FileWatcher(::FileWatcher* native)
{
    NativePtr = native;
}

Flood::FileWatcher::FileWatcher(System::IntPtr native)
{
    auto __native = (::FileWatcher*)native.ToPointer();
    NativePtr = __native;
}

Flood::FileWatcher::FileWatcher()
{
}

void Flood::FileWatcher::RemoveWatch(unsigned int FileWatchId)
{
    auto arg0 = (::FileWatchId)(::uint32)(::uint32_t)FileWatchId;
    ((::FileWatcher*)NativePtr)->removeWatch(arg0);
}

void Flood::FileWatcher::Update()
{
    ((::FileWatcher*)NativePtr)->update();
}

bool Flood::FileWatcher::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<FileWatcher^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::FileWatcher::GetHashCode()
{
    return (int)NativePtr;
}

System::IntPtr Flood::FileWatcher::Instance::get()
{
    return System::IntPtr(NativePtr);
}

void Flood::FileWatcher::Instance::set(System::IntPtr object)
{
    NativePtr = (::FileWatcher*)object.ToPointer();
}
void Flood::FileWatcher::FileWatchEvent::add(System::Action<Flood::FileWatchEvent>^ evt)
{
    if (!_FileWatchEventDelegateInstance)
    {
        _FileWatchEventDelegateInstance = gcnew _FileWatchEventDelegate(this, &Flood::FileWatcher::_FileWatchEventRaise);
        auto _fptr = (void (*)(const ::FileWatchEvent&))Marshal::GetFunctionPointerForDelegate(_FileWatchEventDelegateInstance).ToPointer();
        ((::FileWatcher*)NativePtr)->onFileWatchEvent.Connect(_fptr);
    }
    _FileWatchEvent = static_cast<System::Action<Flood::FileWatchEvent>^>(System::Delegate::Combine(_FileWatchEvent, evt));
}

void Flood::FileWatcher::FileWatchEvent::remove(System::Action<Flood::FileWatchEvent>^ evt)
{
    _FileWatchEvent = static_cast<System::Action<Flood::FileWatchEvent>^>(System::Delegate::Remove(_FileWatchEvent, evt));
}

void Flood::FileWatcher::FileWatchEvent::raise(Flood::FileWatchEvent _0)
{
    _FileWatchEvent(_0);
}

void Flood::FileWatcher::_FileWatchEventRaise(const ::FileWatchEvent& _0)
{
    FileWatchEvent::raise(Flood::FileWatchEvent((::FileWatchEvent*)&_0));
}

