/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Group.h"
#include "Component.h"
#include "Entity.h"
#include "Vector.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::Group::Group(::Group* native)
{
    NativePtr = native;
}

Flood::Group::Group(System::IntPtr native)
{
    auto __native = (::Group*)native.ToPointer();
    NativePtr = __native;
}

Flood::Group::Group()
{
    NativePtr = new ::Group();
}

bool Flood::Group::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<Group^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::Group::GetHashCode()
{
    return (int)NativePtr;
}

System::IntPtr Flood::Group::Instance::get()
{
    return System::IntPtr(NativePtr);
}

void Flood::Group::Instance::set(System::IntPtr object)
{
    NativePtr = (::Group*)object.ToPointer();
}
void Flood::Group::EntityComponentAdded::add(System::Action<Flood::Component^>^ evt)
{
    if (!_EntityComponentAddedDelegateInstance)
    {
        _EntityComponentAddedDelegateInstance = gcnew _EntityComponentAddedDelegate(this, &Flood::Group::_EntityComponentAddedRaise);
        auto _fptr = (void (*)(const ::ComponentPtr&))Marshal::GetFunctionPointerForDelegate(_EntityComponentAddedDelegateInstance).ToPointer();
        ((::Group*)NativePtr)->onEntityComponentAdded.Connect(_fptr);
    }
    _EntityComponentAdded = static_cast<System::Action<Flood::Component^>^>(System::Delegate::Combine(_EntityComponentAdded, evt));
}

void Flood::Group::EntityComponentAdded::remove(System::Action<Flood::Component^>^ evt)
{
    _EntityComponentAdded = static_cast<System::Action<Flood::Component^>^>(System::Delegate::Remove(_EntityComponentAdded, evt));
}

void Flood::Group::EntityComponentAdded::raise(Flood::Component^ _2)
{
    _EntityComponentAdded(_2);
}

void Flood::Group::_EntityComponentAddedRaise(const ::ComponentPtr& _2)
{
    EntityComponentAdded::raise(gcnew Flood::Component((::Component*)_2.get()));
}

void Flood::Group::EntityComponentRemoved::add(System::Action<Flood::Component^>^ evt)
{
    if (!_EntityComponentRemovedDelegateInstance)
    {
        _EntityComponentRemovedDelegateInstance = gcnew _EntityComponentRemovedDelegate(this, &Flood::Group::_EntityComponentRemovedRaise);
        auto _fptr = (void (*)(const ::ComponentPtr&))Marshal::GetFunctionPointerForDelegate(_EntityComponentRemovedDelegateInstance).ToPointer();
        ((::Group*)NativePtr)->onEntityComponentRemoved.Connect(_fptr);
    }
    _EntityComponentRemoved = static_cast<System::Action<Flood::Component^>^>(System::Delegate::Combine(_EntityComponentRemoved, evt));
}

void Flood::Group::EntityComponentRemoved::remove(System::Action<Flood::Component^>^ evt)
{
    _EntityComponentRemoved = static_cast<System::Action<Flood::Component^>^>(System::Delegate::Remove(_EntityComponentRemoved, evt));
}

void Flood::Group::EntityComponentRemoved::raise(Flood::Component^ _3)
{
    _EntityComponentRemoved(_3);
}

void Flood::Group::_EntityComponentRemovedRaise(const ::ComponentPtr& _3)
{
    EntityComponentRemoved::raise(gcnew Flood::Component((::Component*)_3.get()));
}

void Flood::Group::EntityChanged::add(System::Action^ evt)
{
    if (!_EntityChangedDelegateInstance)
    {
        _EntityChangedDelegateInstance = gcnew _EntityChangedDelegate(this, &Flood::Group::_EntityChangedRaise);
        auto _fptr = (void (*)())Marshal::GetFunctionPointerForDelegate(_EntityChangedDelegateInstance).ToPointer();
        ((::Group*)NativePtr)->onEntityChanged.Connect(_fptr);
    }
    _EntityChanged = static_cast<System::Action^>(System::Delegate::Combine(_EntityChanged, evt));
}

void Flood::Group::EntityChanged::remove(System::Action^ evt)
{
    _EntityChanged = static_cast<System::Action^>(System::Delegate::Remove(_EntityChanged, evt));
}

void Flood::Group::EntityChanged::raise()
{
    _EntityChanged();
}

void Flood::Group::_EntityChangedRaise()
{
    EntityChanged::raise();
}

