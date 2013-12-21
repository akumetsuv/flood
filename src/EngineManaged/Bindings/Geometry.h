/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Engine/Scene/Geometry.h>
#include "BoundingBox.h"
#include "Component.h"

namespace Flood
{
    ref class Geometry;
    ref class Component;
    ref class RenderBatch;
    value struct BoundingBox;
    value struct RenderState;
    ref class Transform;
}

namespace Flood
{
    /// <summary>
    /// This component holds geometry data for rendering. It can hold multiple
    /// renderable objects, each with different materials. When the camera node
    /// traverses the scene graph, Geometry nodes are picked and passed to the
    /// rendering device for rendering.
    /// </summary>
    public ref class Geometry : Flood::Component
    {
    public:

        Geometry(::Geometry* native);
        Geometry(System::IntPtr native);
        Geometry();

        property Flood::BoundingBox BoundingVolume
        {
            Flood::BoundingBox get();
        }
        property Flood::BoundingBox WorldBoundingVolume
        {
            Flood::BoundingBox get();
        }
        property Flood::BoundingBox Bounds
        {
            Flood::BoundingBox get();
            void set(Flood::BoundingBox);
        }
        property bool NeedsBoundsRebuild
        {
            bool get();
            void set(bool);
        }
        void AddRenderable(Flood::RenderBatch^ renderable);

        virtual void UpdateBounds();

        virtual void Update(float delta) override;

        void RebuildBoundingBox();

        void NotifiesTransform();

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
