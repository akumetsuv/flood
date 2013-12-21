/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Engine/Scene/Group.h>

namespace Flood
{
    ref class Group;
    ref class Component;
}

namespace Flood
{
    /// <summary>
    /// Groups are nodes that have the special property of being able to be
    /// attached to each other. If you attach a node to another node, they will be
    /// in a hierarchical relationship and the parent node will influence the child
    /// node transformations.
    /// </summary>
    public ref class Group : ICppInstance
    {
    public:

        property ::Group* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        Group(::Group* native);
        Group(System::IntPtr native);
        Group();

    private:
        delegate void _EntityComponentAddedDelegate(const ::ComponentPtr& _2);
        _EntityComponentAddedDelegate^ _EntityComponentAddedDelegateInstance;
        void _EntityComponentAddedRaise(const ::ComponentPtr& _2);
        System::Action<Flood::Component^>^ _EntityComponentAdded;
    public:
        event System::Action<Flood::Component^>^ EntityComponentAdded
        {
            void add(System::Action<Flood::Component^>^ evt);
            void remove(System::Action<Flood::Component^>^ evt);
            void raise(Flood::Component^ _2);
        }
    private:
        delegate void _EntityComponentRemovedDelegate(const ::ComponentPtr& _3);
        _EntityComponentRemovedDelegate^ _EntityComponentRemovedDelegateInstance;
        void _EntityComponentRemovedRaise(const ::ComponentPtr& _3);
        System::Action<Flood::Component^>^ _EntityComponentRemoved;
    public:
        event System::Action<Flood::Component^>^ EntityComponentRemoved
        {
            void add(System::Action<Flood::Component^>^ evt);
            void remove(System::Action<Flood::Component^>^ evt);
            void raise(Flood::Component^ _3);
        }
    private:
        delegate void _EntityChangedDelegate();
        _EntityChangedDelegate^ _EntityChangedDelegateInstance;
        void _EntityChangedRaise();
        System::Action^ _EntityChanged;
    public:
        event System::Action^ EntityChanged
        {
            void add(System::Action^ evt);
            void remove(System::Action^ evt);
            void raise();
        }
        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
