/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "RenderDevice.h"
#include "HashMap.h"
#include "Material.h"
#include "RenderBackend.h"
#include "RenderBatch.h"
#include "RenderBuffer.h"
#include "RenderContext.h"
#include "RenderQueue.h"
#include "RenderTarget.h"
#include "RenderView.h"
#include "Texture.h"
#include "Vector.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::RenderDevice::RenderDevice(::RenderDevice* native)
{
    NativePtr = native;
}

Flood::RenderDevice::RenderDevice(System::IntPtr native)
{
    auto __native = (::RenderDevice*)native.ToPointer();
    NativePtr = __native;
}

Flood::RenderDevice::RenderDevice()
{
    NativePtr = new ::RenderDevice();
}

void Flood::RenderDevice::Render(Flood::RenderBlock^ queue)
{
    auto &arg0 = *(::RenderBlock*)queue->NativePtr;
    ((::RenderDevice*)NativePtr)->render(arg0);
}

void Flood::RenderDevice::UpdateRenderTargets()
{
    ((::RenderDevice*)NativePtr)->updateRenderTargets();
}

void Flood::RenderDevice::ClearView()
{
    ((::RenderDevice*)NativePtr)->clearView();
}

bool Flood::RenderDevice::IsFixedPipeline()
{
    auto __ret = ((::RenderDevice*)NativePtr)->isFixedPipeline();
    return __ret;
}

bool Flood::RenderDevice::SetupRenderStateMatrix(Flood::RenderState state)
{
    auto _marshal0 = ::RenderState();
    if (state.Renderable != nullptr)
        _marshal0.renderable = (::RenderBatch*)state.Renderable->NativePtr;
    if (state.Material != nullptr)
        _marshal0.material = (::Material*)state.Material->NativePtr;
    auto _marshal1 = ::Matrix4x3();
    _marshal1.m11 = state.ModelMatrix.M11;
    _marshal1.m12 = state.ModelMatrix.M12;
    _marshal1.m13 = state.ModelMatrix.M13;
    _marshal1.m21 = state.ModelMatrix.M21;
    _marshal1.m22 = state.ModelMatrix.M22;
    _marshal1.m23 = state.ModelMatrix.M23;
    _marshal1.m31 = state.ModelMatrix.M31;
    _marshal1.m32 = state.ModelMatrix.M32;
    _marshal1.m33 = state.ModelMatrix.M33;
    _marshal1.tx = state.ModelMatrix.Tx;
    _marshal1.ty = state.ModelMatrix.Ty;
    _marshal1.tz = state.ModelMatrix.Tz;
    _marshal0.modelMatrix = _marshal1;
    _marshal0.priority = (::int32)(::int32_t)state.Priority;
    auto arg0 = _marshal0;
    auto __ret = ((::RenderDevice*)NativePtr)->setupRenderStateMatrix(arg0);
    return __ret;
}

bool Flood::RenderDevice::SetupRenderStateOverlay(Flood::RenderState _0)
{
    auto _marshal0 = ::RenderState();
    if (_0.Renderable != nullptr)
        _marshal0.renderable = (::RenderBatch*)_0.Renderable->NativePtr;
    if (_0.Material != nullptr)
        _marshal0.material = (::Material*)_0.Material->NativePtr;
    auto _marshal1 = ::Matrix4x3();
    _marshal1.m11 = _0.ModelMatrix.M11;
    _marshal1.m12 = _0.ModelMatrix.M12;
    _marshal1.m13 = _0.ModelMatrix.M13;
    _marshal1.m21 = _0.ModelMatrix.M21;
    _marshal1.m22 = _0.ModelMatrix.M22;
    _marshal1.m23 = _0.ModelMatrix.M23;
    _marshal1.m31 = _0.ModelMatrix.M31;
    _marshal1.m32 = _0.ModelMatrix.M32;
    _marshal1.m33 = _0.ModelMatrix.M33;
    _marshal1.tx = _0.ModelMatrix.Tx;
    _marshal1.ty = _0.ModelMatrix.Ty;
    _marshal1.tz = _0.ModelMatrix.Tz;
    _marshal0.modelMatrix = _marshal1;
    _marshal0.priority = (::int32)(::int32_t)_0.Priority;
    auto arg0 = _marshal0;
    auto __ret = ((::RenderDevice*)NativePtr)->setupRenderStateOverlay(arg0);
    return __ret;
}

void Flood::RenderDevice::BindTextureUnits(Flood::RenderState state, bool bindUniforms)
{
    auto _marshal0 = ::RenderState();
    if (state.Renderable != nullptr)
        _marshal0.renderable = (::RenderBatch*)state.Renderable->NativePtr;
    if (state.Material != nullptr)
        _marshal0.material = (::Material*)state.Material->NativePtr;
    auto _marshal1 = ::Matrix4x3();
    _marshal1.m11 = state.ModelMatrix.M11;
    _marshal1.m12 = state.ModelMatrix.M12;
    _marshal1.m13 = state.ModelMatrix.M13;
    _marshal1.m21 = state.ModelMatrix.M21;
    _marshal1.m22 = state.ModelMatrix.M22;
    _marshal1.m23 = state.ModelMatrix.M23;
    _marshal1.m31 = state.ModelMatrix.M31;
    _marshal1.m32 = state.ModelMatrix.M32;
    _marshal1.m33 = state.ModelMatrix.M33;
    _marshal1.tx = state.ModelMatrix.Tx;
    _marshal1.ty = state.ModelMatrix.Ty;
    _marshal1.tz = state.ModelMatrix.Tz;
    _marshal0.modelMatrix = _marshal1;
    _marshal0.priority = (::int32)(::int32_t)state.Priority;
    auto arg0 = _marshal0;
    ((::RenderDevice*)NativePtr)->bindTextureUnits(arg0, bindUniforms);
}

void Flood::RenderDevice::UnbindTextureUnits(Flood::Material^ material)
{
    auto arg0 = (::Material*)material->NativePtr;
    ((::RenderDevice*)NativePtr)->unbindTextureUnits(arg0);
}

bool Flood::RenderDevice::BindBuffers(Flood::RenderBatch^ _0)
{
    auto arg0 = (::RenderBatch*)_0->NativePtr;
    auto __ret = ((::RenderDevice*)NativePtr)->bindBuffers(arg0);
    return __ret;
}

bool Flood::RenderDevice::UnbindBuffers(Flood::RenderBatch^ _0)
{
    auto arg0 = (::RenderBatch*)_0->NativePtr;
    auto __ret = ((::RenderDevice*)NativePtr)->unbindBuffers(arg0);
    return __ret;
}

bool Flood::RenderDevice::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<RenderDevice^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::RenderDevice::GetHashCode()
{
    return (int)NativePtr;
}

Flood::RenderDevice^ Flood::RenderDevice::GetRenderDevice()
{
    auto __ret = ::GetRenderDevice();
    if (__ret == nullptr) return nullptr;
    return gcnew Flood::RenderDevice((::RenderDevice*)__ret);
}

System::IntPtr Flood::RenderDevice::Instance::get()
{
    return System::IntPtr(NativePtr);
}

void Flood::RenderDevice::Instance::set(System::IntPtr object)
{
    NativePtr = (::RenderDevice*)object.ToPointer();
}

Flood::RenderPipeline Flood::RenderDevice::Pipeline::get()
{
    auto __ret = ((::RenderDevice*)NativePtr)->getPipeline();
    return (Flood::RenderPipeline)__ret;
}

void Flood::RenderDevice::Pipeline::set(Flood::RenderPipeline value)
{
    auto v = value;
    auto arg0 = (::RenderPipeline)v;
    ((::RenderDevice*)NativePtr)->setPipeline(arg0);
}

Flood::RenderBackend^ Flood::RenderDevice::Backend::get()
{
    auto __ret = ((::RenderDevice*)NativePtr)->getBackend();
    if (__ret == nullptr) return nullptr;
    return gcnew Flood::RenderBackend((::RenderBackend*)__ret);
}

void Flood::RenderDevice::Backend::set(Flood::RenderBackend^ value)
{
    auto v = value;
    auto arg0 = (::RenderBackend*)v->NativePtr;
    ((::RenderDevice*)NativePtr)->setBackend(arg0);
}

Flood::RenderTarget^ Flood::RenderDevice::RenderTarget::get()
{
    auto __ret = ((::RenderDevice*)NativePtr)->getRenderTarget();
    if (__ret == nullptr) return nullptr;
    return gcnew Flood::RenderTarget((::RenderTarget*)__ret);
}

void Flood::RenderDevice::RenderTarget::set(Flood::RenderTarget^ value)
{
    auto target = value;
    auto arg0 = (::RenderTarget*)target->NativePtr;
    ((::RenderDevice*)NativePtr)->setRenderTarget(arg0);
}

Flood::RenderContext^ Flood::RenderDevice::ActiveContext::get()
{
    auto __ret = ((::RenderDevice*)NativePtr)->getActiveContext();
    if (__ret == nullptr) return nullptr;
    return gcnew Flood::RenderContext((::RenderContext*)__ret);
}

void Flood::RenderDevice::ActiveContext::set(Flood::RenderContext^ value)
{
    auto v = value;
    auto arg0 = (::RenderContext*)v->NativePtr;
    ((::RenderDevice*)NativePtr)->setActiveContext(arg0);
}

Flood::RenderView^ Flood::RenderDevice::ActiveView::get()
{
    auto __ret = ((::RenderDevice*)NativePtr)->getActiveView();
    if (__ret == nullptr) return nullptr;
    return gcnew Flood::RenderView((::RenderView*)__ret);
}

void Flood::RenderDevice::ActiveView::set(Flood::RenderView^ value)
{
    auto view = value;
    auto arg0 = (::RenderView*)view->NativePtr;
    ((::RenderDevice*)NativePtr)->setActiveView(arg0);
}

Flood::RenderTarget^ Flood::RenderDevice::ActiveTarget::get()
{
    return gcnew Flood::RenderTarget((::RenderTarget*)((::RenderDevice*)NativePtr)->activeTarget);
}

void Flood::RenderDevice::ActiveTarget::set(Flood::RenderTarget^ value)
{
    ((::RenderDevice*)NativePtr)->activeTarget = (::RenderTarget*)value->NativePtr;
}

Flood::RenderBackend^ Flood::RenderDevice::RenderBackend::get()
{
    return gcnew Flood::RenderBackend((::RenderBackend*)((::RenderDevice*)NativePtr)->renderBackend);
}

void Flood::RenderDevice::RenderBackend::set(Flood::RenderBackend^ value)
{
    ((::RenderDevice*)NativePtr)->renderBackend = (::RenderBackend*)value->NativePtr;
}

