/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Camera.h"
#include "DebugGeometry.h"
#include "RenderDevice.h"
#include "RenderQueue.h"
#include "RenderView.h"
#include "Scene.h"
#include "Transform.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::Camera::Camera(::Camera* native)
    : Flood::Component((::Component*)native)
{
}

Flood::Camera::Camera(System::IntPtr native)
    : Flood::Component(native)
{
    auto __native = (::Camera*)native.ToPointer();
}

Flood::Camera::Camera()
    : Flood::Component((::Component*)nullptr)
{
    NativePtr = new ::Camera();
}

void Flood::Camera::Render(Flood::Scene^ scene)
{
    auto arg0 = (::Scene*)scene->NativePtr;
    ((::Camera*)NativePtr)->render(arg0);
}

void Flood::Camera::Render(Flood::RenderBlock^ block, bool clearView)
{
    auto &arg0 = *(::RenderBlock*)block->NativePtr;
    ((::Camera*)NativePtr)->render(arg0, clearView);
}

Flood::Frustum Flood::Camera::GetVolume(float screenLeft, float screenRight, float screenTop, float screenBottom)
{
    auto __ret = ((::Camera*)NativePtr)->getVolume(screenLeft, screenRight, screenTop, screenBottom);
    return Flood::Frustum((::Frustum*)&__ret);
}

void Flood::Camera::Update(float delta)
{
    ((::Camera*)NativePtr)->update(delta);
}

void Flood::Camera::UpdateFrustum()
{
    ((::Camera*)NativePtr)->updateFrustum();
}

void Flood::Camera::UpdateViewTransform()
{
    ((::Camera*)NativePtr)->updateViewTransform();
}

void Flood::Camera::OnTransformed()
{
    ((::Camera*)NativePtr)->onTransformed();
}

void Flood::Camera::OnDebugDraw(Flood::DebugDrawer^ _0, Flood::DebugDrawFlags _1)
{
    auto &arg0 = *(::DebugDrawer*)_0->NativePtr;
    auto arg1 = (::DebugDrawFlags)_1;
    ((::Camera*)NativePtr)->onDebugDraw(arg0, arg1);
}

bool Flood::Camera::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<Camera^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::Camera::GetHashCode()
{
    return (int)NativePtr;
}

Flood::Vector3 Flood::Camera::LookAtVector::get()
{
    auto &__ret = ((::Camera*)NativePtr)->getLookAtVector();
    return Flood::Vector3((::Vector3*)&__ret);
}

Flood::Matrix4x3 Flood::Camera::ViewMatrix::get()
{
    auto &__ret = ((::Camera*)NativePtr)->getViewMatrix();
    return Flood::Matrix4x3((::Matrix4x3*)&__ret);
}

Flood::RenderView^ Flood::Camera::View::get()
{
    auto __ret = ((::Camera*)NativePtr)->getView();
    if (__ret == nullptr) return nullptr;
    return gcnew Flood::RenderView((::RenderView*)__ret);
}

void Flood::Camera::View::set(Flood::RenderView^ value)
{
    auto view = value;
    auto arg0 = (::RenderView*)view->NativePtr;
    ((::Camera*)NativePtr)->setView(arg0);
}

Flood::Frustum Flood::Camera::Frustum::get()
{
    auto &__ret = ((::Camera*)NativePtr)->getFrustum();
    return Flood::Frustum((::Frustum*)&__ret);
}

Flood::Frustum Flood::Camera::Frustum1::get()
{
    auto &__ret = ((::Camera*)NativePtr)->getFrustum();
    return Flood::Frustum((::Frustum*)&__ret);
}

Flood::DebugDrawer^ Flood::Camera::Drawer::get()
{
    return gcnew Flood::DebugDrawer((::DebugDrawer*)&((::Camera*)NativePtr)->drawer);
}

void Flood::Camera::Drawer::set(Flood::DebugDrawer^ value)
{
    ((::Camera*)NativePtr)->drawer = *(::DebugDrawer*)value->NativePtr;
}

Flood::Frustum Flood::Camera::Frustum2::get()
{
    return Flood::Frustum((::Frustum*)&((::Camera*)NativePtr)->frustum);
}

void Flood::Camera::Frustum2::set(Flood::Frustum value)
{
    auto _marshal0 = ::Frustum();
    _marshal0.projection = (::FrustumProjection)value.Projection;
    auto _marshal1 = ::Matrix4x4();
    _marshal1.m11 = value.MatProjection.M11;
    _marshal1.m12 = value.MatProjection.M12;
    _marshal1.m13 = value.MatProjection.M13;
    _marshal1.m14 = value.MatProjection.M14;
    _marshal1.m21 = value.MatProjection.M21;
    _marshal1.m22 = value.MatProjection.M22;
    _marshal1.m23 = value.MatProjection.M23;
    _marshal1.m24 = value.MatProjection.M24;
    _marshal1.m31 = value.MatProjection.M31;
    _marshal1.m32 = value.MatProjection.M32;
    _marshal1.m33 = value.MatProjection.M33;
    _marshal1.m34 = value.MatProjection.M34;
    _marshal1.tx = value.MatProjection.Tx;
    _marshal1.ty = value.MatProjection.Ty;
    _marshal1.tz = value.MatProjection.Tz;
    _marshal1.tw = value.MatProjection.Tw;
    _marshal0.matProjection = _marshal1;
    _marshal0.fieldOfView = value.FieldOfView;
    _marshal0.nearPlane = value.NearPlane;
    _marshal0.farPlane = value.FarPlane;
    _marshal0.aspectRatio = value.AspectRatio;
    auto _marshal2 = ::Vector3();
    _marshal2.x = value.OrthoSize.X;
    _marshal2.y = value.OrthoSize.Y;
    _marshal2.z = value.OrthoSize.Z;
    _marshal0.orthoSize = _marshal2;
    ((::Camera*)NativePtr)->frustum = _marshal0;
}

bool Flood::Camera::FrustumCulling::get()
{
    return ((::Camera*)NativePtr)->frustumCulling;
}

void Flood::Camera::FrustumCulling::set(bool value)
{
    ((::Camera*)NativePtr)->frustumCulling = value;
}

Flood::Vector3 Flood::Camera::LookAtVector1::get()
{
    return Flood::Vector3((::Vector3*)&((::Camera*)NativePtr)->lookAtVector);
}

void Flood::Camera::LookAtVector1::set(Flood::Vector3 value)
{
    auto _marshal0 = ::Vector3();
    _marshal0.x = value.X;
    _marshal0.y = value.Y;
    _marshal0.z = value.Z;
    ((::Camera*)NativePtr)->lookAtVector = _marshal0;
}

Flood::Matrix4x3 Flood::Camera::ViewMatrix1::get()
{
    return Flood::Matrix4x3((::Matrix4x3*)&((::Camera*)NativePtr)->viewMatrix);
}

void Flood::Camera::ViewMatrix1::set(Flood::Matrix4x3 value)
{
    auto _marshal0 = ::Matrix4x3();
    _marshal0.m11 = value.M11;
    _marshal0.m12 = value.M12;
    _marshal0.m13 = value.M13;
    _marshal0.m21 = value.M21;
    _marshal0.m22 = value.M22;
    _marshal0.m23 = value.M23;
    _marshal0.m31 = value.M31;
    _marshal0.m32 = value.M32;
    _marshal0.m33 = value.M33;
    _marshal0.tx = value.Tx;
    _marshal0.ty = value.Ty;
    _marshal0.tz = value.Tz;
    ((::Camera*)NativePtr)->viewMatrix = _marshal0;
}

Flood::Transform^ Flood::Camera::Transform::get()
{
    return gcnew Flood::Transform((::Transform*)((::Camera*)NativePtr)->transform);
}

void Flood::Camera::Transform::set(Flood::Transform^ value)
{
    ((::Camera*)NativePtr)->transform = (::Transform*)value->NativePtr;
}

Flood::RenderView^ Flood::Camera::ActiveView::get()
{
    return gcnew Flood::RenderView((::RenderView*)((::Camera*)NativePtr)->activeView);
}

void Flood::Camera::ActiveView::set(Flood::RenderView^ value)
{
    ((::Camera*)NativePtr)->activeView = (::RenderView*)value->NativePtr;
}

