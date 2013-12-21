/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Geometry.h"
#include "RenderBatch.h"
#include "RenderQueue.h"
#include "Transform.h"
#include "Vector.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::Geometry::Geometry(::Geometry* native)
    : Flood::Component((::Component*)native)
{
}

Flood::Geometry::Geometry(System::IntPtr native)
    : Flood::Component(native)
{
    auto __native = (::Geometry*)native.ToPointer();
}

Flood::Geometry::Geometry()
    : Flood::Component((::Component*)nullptr)
{
    NativePtr = new ::Geometry();
}

void Flood::Geometry::AddRenderable(Flood::RenderBatch^ renderable)
{
    auto arg0 = (::RenderBatch*)renderable->NativePtr;
    ((::Geometry*)NativePtr)->addRenderable(arg0);
}

void Flood::Geometry::UpdateBounds()
{
    ((::Geometry*)NativePtr)->updateBounds();
}

void Flood::Geometry::Update(float delta)
{
    ((::Geometry*)NativePtr)->update(delta);
}

void Flood::Geometry::RebuildBoundingBox()
{
    ((::Geometry*)NativePtr)->rebuildBoundingBox();
}

void Flood::Geometry::NotifiesTransform()
{
    ((::Geometry*)NativePtr)->notifiesTransform();
}

bool Flood::Geometry::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<Geometry^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::Geometry::GetHashCode()
{
    return (int)NativePtr;
}

Flood::BoundingBox Flood::Geometry::BoundingVolume::get()
{
    auto &__ret = ((::Geometry*)NativePtr)->getBoundingVolume();
    return Flood::BoundingBox((::BoundingBox*)&__ret);
}

Flood::BoundingBox Flood::Geometry::WorldBoundingVolume::get()
{
    auto __ret = ((::Geometry*)NativePtr)->getWorldBoundingVolume();
    return Flood::BoundingBox((::BoundingBox*)&__ret);
}

Flood::BoundingBox Flood::Geometry::Bounds::get()
{
    return Flood::BoundingBox((::BoundingBox*)&((::Geometry*)NativePtr)->bounds);
}

void Flood::Geometry::Bounds::set(Flood::BoundingBox value)
{
    auto _marshal0 = ::BoundingBox();
    auto _marshal1 = ::Vector3();
    _marshal1.x = value.Min.X;
    _marshal1.y = value.Min.Y;
    _marshal1.z = value.Min.Z;
    _marshal0.min = _marshal1;
    auto _marshal2 = ::Vector3();
    _marshal2.x = value.Max.X;
    _marshal2.y = value.Max.Y;
    _marshal2.z = value.Max.Z;
    _marshal0.max = _marshal2;
    ((::Geometry*)NativePtr)->bounds = _marshal0;
}

bool Flood::Geometry::NeedsBoundsRebuild::get()
{
    return ((::Geometry*)NativePtr)->needsBoundsRebuild;
}

void Flood::Geometry::NeedsBoundsRebuild::set(bool value)
{
    ((::Geometry*)NativePtr)->needsBoundsRebuild = value;
}

