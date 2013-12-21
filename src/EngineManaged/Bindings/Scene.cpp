/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Scene.h"
#include "Frustum.h"
#include "Geometry.h"
#include "Group.h"
#include "RenderBatch.h"
#include "Resource.h"
#include "Vector.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::RayQueryResult::RayQueryResult(::RayQueryResult* native)
{
    NativePtr = native;
}

Flood::RayQueryResult::RayQueryResult(System::IntPtr native)
{
    auto __native = (::RayQueryResult*)native.ToPointer();
    NativePtr = __native;
}

Flood::RayQueryResult::RayQueryResult()
{
    NativePtr = new ::RayQueryResult();
}

bool Flood::RayQueryResult::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<RayQueryResult^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::RayQueryResult::GetHashCode()
{
    return (int)NativePtr;
}

System::IntPtr Flood::RayQueryResult::Instance::get()
{
    return System::IntPtr(NativePtr);
}

void Flood::RayQueryResult::Instance::set(System::IntPtr object)
{
    NativePtr = (::RayQueryResult*)object.ToPointer();
}

float Flood::RayQueryResult::Distance::get()
{
    return ((::RayQueryResult*)NativePtr)->distance;
}

void Flood::RayQueryResult::Distance::set(float value)
{
    ((::RayQueryResult*)NativePtr)->distance = value;
}

Flood::RayTriangleQueryResult::RayTriangleQueryResult(::RayTriangleQueryResult* native)
    : Flood::RayQueryResult((::RayQueryResult*)native)
{
}

Flood::RayTriangleQueryResult::RayTriangleQueryResult(System::IntPtr native)
    : Flood::RayQueryResult(native)
{
    auto __native = (::RayTriangleQueryResult*)native.ToPointer();
}

Flood::RayTriangleQueryResult::RayTriangleQueryResult()
    : Flood::RayQueryResult((::RayQueryResult*)nullptr)
{
    NativePtr = new ::RayTriangleQueryResult();
}

bool Flood::RayTriangleQueryResult::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<RayTriangleQueryResult^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::RayTriangleQueryResult::GetHashCode()
{
    return (int)NativePtr;
}

Flood::Geometry^ Flood::RayTriangleQueryResult::Geometry::get()
{
    return gcnew Flood::Geometry((::Geometry*)((::RayTriangleQueryResult*)NativePtr)->geometry);
}

void Flood::RayTriangleQueryResult::Geometry::set(Flood::Geometry^ value)
{
    ((::RayTriangleQueryResult*)NativePtr)->geometry = (::Geometry*)value->NativePtr;
}

Flood::RenderBatch^ Flood::RayTriangleQueryResult::Renderable::get()
{
    return gcnew Flood::RenderBatch((::RenderBatch*)((::RayTriangleQueryResult*)NativePtr)->renderable);
}

void Flood::RayTriangleQueryResult::Renderable::set(Flood::RenderBatch^ value)
{
    ((::RayTriangleQueryResult*)NativePtr)->renderable = (::RenderBatch*)value->NativePtr;
}

Flood::Vector3 Flood::RayTriangleQueryResult::IntersectionLocal::get()
{
    return Flood::Vector3((::Vector3*)&((::RayTriangleQueryResult*)NativePtr)->intersectionLocal);
}

void Flood::RayTriangleQueryResult::IntersectionLocal::set(Flood::Vector3 value)
{
    auto _marshal0 = ::Vector3();
    _marshal0.x = value.X;
    _marshal0.y = value.Y;
    _marshal0.z = value.Z;
    ((::RayTriangleQueryResult*)NativePtr)->intersectionLocal = _marshal0;
}

Flood::Vector3 Flood::RayTriangleQueryResult::IntersectionWorld::get()
{
    return Flood::Vector3((::Vector3*)&((::RayTriangleQueryResult*)NativePtr)->intersectionWorld);
}

void Flood::RayTriangleQueryResult::IntersectionWorld::set(Flood::Vector3 value)
{
    auto _marshal0 = ::Vector3();
    _marshal0.x = value.X;
    _marshal0.y = value.Y;
    _marshal0.z = value.Z;
    ((::RayTriangleQueryResult*)NativePtr)->intersectionWorld = _marshal0;
}

Flood::Vector3 Flood::RayTriangleQueryResult::IntersectionUV::get()
{
    return Flood::Vector3((::Vector3*)&((::RayTriangleQueryResult*)NativePtr)->intersectionUV);
}

void Flood::RayTriangleQueryResult::IntersectionUV::set(Flood::Vector3 value)
{
    auto _marshal0 = ::Vector3();
    _marshal0.x = value.X;
    _marshal0.y = value.Y;
    _marshal0.z = value.Z;
    ((::RayTriangleQueryResult*)NativePtr)->intersectionUV = _marshal0;
}

Flood::Scene::Scene(::Scene* native)
    : Flood::Resource((::Resource*)native)
{
}

Flood::Scene::Scene(System::IntPtr native)
    : Flood::Resource(native)
{
    auto __native = (::Scene*)native.ToPointer();
}

Flood::Scene::Scene()
    : Flood::Resource((::Resource*)nullptr)
{
    NativePtr = new ::Scene();
}

void Flood::Scene::Update(float delta)
{
    ((::Scene*)NativePtr)->update(delta);
}

bool Flood::Scene::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<Scene^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::Scene::GetHashCode()
{
    return (int)NativePtr;
}

Flood::ResourceGroup Flood::Scene::ResourceGroup::get()
{
    auto __ret = ((::Scene*)NativePtr)->getResourceGroup();
    return (Flood::ResourceGroup)__ret;
}

Flood::Group^ Flood::Scene::Entities::get()
{
    return gcnew Flood::Group((::Group*)&((::Scene*)NativePtr)->entities);
}

void Flood::Scene::Entities::set(Flood::Group^ value)
{
    ((::Scene*)NativePtr)->entities = *(::Group*)value->NativePtr;
}

