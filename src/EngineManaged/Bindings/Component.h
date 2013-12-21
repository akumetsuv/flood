/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Engine/Scene/Component.h>

namespace Flood
{
    ref class RenderBatch;
    ref class Camera;
    ref class DebugDrawer;
    ref class Component;
    enum struct DebugDrawFlags : unsigned char;
    enum struct DebugDrawFlags : unsigned char;
}

namespace Flood
{
    /// <summary>
    /// Represents a component, a specific piece of functionality that can be added
    /// to each entity in the scene. A component will tipically hold a piece of
    /// data and update it's state each frame if it needs to do it. A component
    /// will also be able to register methods for scripting.
    /// </summary>
    public ref class Component : ICppInstance
    {
    public:

        property ::Component* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        Component(::Component* native);
        Component(System::IntPtr native);
        Component();

        property bool DebugRenderableVisible
        {
            void set(bool);
        }
        property bool DebugInheritsTransform
        {
            bool get();
            void set(bool);
        }
        property bool DebugVisible
        {
            bool get();
            void set(bool);
        }
        property Flood::RenderBatch^ DebugRenderable
        {
            Flood::RenderBatch^ get();
            void set(Flood::RenderBatch^);
        }
        virtual void Update(float delta);

        virtual void OnPreRender(Flood::Camera^ camera);

        virtual bool IsDebugRenderableVisible();

        virtual void OnPreRender1(Flood::Camera^ camera);

        virtual bool IsDebugRenderableVisible1();

        virtual void OnDebugDraw(Flood::DebugDrawer^ _0, Flood::DebugDrawFlags _1);

        virtual void OnPreRender2(Flood::Camera^ camera);

        virtual bool IsDebugRenderableVisible2();

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
