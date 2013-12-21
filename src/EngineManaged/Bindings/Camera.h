/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Engine/Scene/Camera.h>
#include "Component.h"
#include "Frustum.h"
#include "Matrix4x3.h"
#include "Vector.h"

namespace Flood
{
    ref class Transform;
    ref class Scene;
    ref class RenderView;
    ref class RenderDevice;
    ref class RenderBlock;
    ref class Camera;
    ref class Component;
    ref class DebugDrawer;
    value struct Frustum;
    value struct Vector3;
    value struct Matrix4x3;
    ref class Entity;
    enum struct DebugDrawFlags : unsigned char;
}

namespace Flood
{
    /// <summary>
    /// Represents a view from a specific point in the world. Has an associated
    /// projection type, like ortographic or perspective and also holds a frustum
    /// that will be used for performing viewing frustum culling. Culling helps
    /// speed up the rendering by cutting nodes that are outside the view range.
    /// </summary>
    public ref class Camera : Flood::Component
    {
    public:

        Camera(::Camera* native);
        Camera(System::IntPtr native);
        Camera();

        property Flood::Vector3 LookAtVector
        {
            Flood::Vector3 get();
        }
        property Flood::Matrix4x3 ViewMatrix
        {
            Flood::Matrix4x3 get();
        }
        property Flood::RenderView^ View
        {
            Flood::RenderView^ get();
            void set(Flood::RenderView^);
        }
        property Flood::Frustum Frustum
        {
            Flood::Frustum get();
        }
        property Flood::Frustum Frustum1
        {
            Flood::Frustum get();
        }
        property Flood::DebugDrawer^ Drawer
        {
            Flood::DebugDrawer^ get();
            void set(Flood::DebugDrawer^);
        }
        property Flood::Frustum Frustum2
        {
            Flood::Frustum get();
            void set(Flood::Frustum);
        }
        property bool FrustumCulling
        {
            bool get();
            void set(bool);
        }
        property Flood::Vector3 LookAtVector1
        {
            Flood::Vector3 get();
            void set(Flood::Vector3);
        }
        property Flood::Matrix4x3 ViewMatrix1
        {
            Flood::Matrix4x3 get();
            void set(Flood::Matrix4x3);
        }
        property Flood::Transform^ Transform
        {
            Flood::Transform^ get();
            void set(Flood::Transform^);
        }
        property Flood::RenderView^ ActiveView
        {
            Flood::RenderView^ get();
            void set(Flood::RenderView^);
        }
        void Render(Flood::Scene^ scene);

        void Render(Flood::RenderBlock^ block, bool clearView);

        Flood::Frustum GetVolume(float screenLeft, float screenRight, float screenTop, float screenBottom);

        virtual void Update(float delta) override;

        void UpdateFrustum();

        void UpdateViewTransform();

        void OnTransformed();

        virtual void OnDebugDraw(Flood::DebugDrawer^ _0, Flood::DebugDrawFlags _1) override;

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
