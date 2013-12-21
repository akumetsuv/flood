/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Resource.h"
#include "ResourceLoader.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::Resource::Resource(::Resource* native)
{
    NativePtr = native;
}

Flood::Resource::Resource(System::IntPtr native)
{
    auto __native = (::Resource*)native.ToPointer();
    NativePtr = __native;
}

bool Flood::Resource::IsLoaded()
{
    auto __ret = ((::Resource*)NativePtr)->isLoaded();
    return __ret;
}

Flood::Resource::Resource()
{
}

bool Flood::Resource::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<Resource^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::Resource::GetHashCode()
{
    return (int)NativePtr;
}

Flood::ResourceHandle<Flood::Resource^> Flood::Resource::HandleCreate()
{
    auto arg0 = (::Resource*)NativePtr;
    auto __ret = ::ResourceHandleCreate(arg0);
    return Flood::ResourceHandle<Flood::Resource^>(__ret.id);
}

System::IntPtr Flood::Resource::Instance::get()
{
    return System::IntPtr(NativePtr);
}

void Flood::Resource::Instance::set(System::IntPtr object)
{
    NativePtr = (::Resource*)object.ToPointer();
}

System::String^ Flood::Resource::Path::get()
{
    auto &__ret = ((::Resource*)NativePtr)->getPath();
    return gcnew Flood::UTF8String((::UTF8String*)&__ret);
}

void Flood::Resource::Path::set(System::String^ value)
{
    auto v = value;
    auto arg0 = StringMarshaller::marshalUTF8String(v);
    ((::Resource*)NativePtr)->setPath(arg0);
}

Flood::ResourceStatus Flood::Resource::Status::get()
{
    auto __ret = ((::Resource*)NativePtr)->getStatus();
    return (Flood::ResourceStatus)__ret;
}

void Flood::Resource::Status::set(Flood::ResourceStatus value)
{
    auto v = value;
    auto arg0 = (::ResourceStatus)v;
    ((::Resource*)NativePtr)->setStatus(arg0);
}

Flood::ResourceGroup Flood::Resource::ResourceGroup::get()
{
    auto __ret = ((::Resource*)NativePtr)->getResourceGroup();
    return (Flood::ResourceGroup)__ret;
}

System::String^ Flood::Resource::Path1::get()
{
    return StringMarshaller::marshalString(((::Resource*)NativePtr)->path);
}

void Flood::Resource::Path1::set(System::String^ value)
{
    ((::Resource*)NativePtr)->path = StringMarshaller::marshalUTF8String(value);
}

Flood::ResourceStream^ Flood::Resource::Stream::get()
{
    return gcnew Flood::ResourceStream((::ResourceStream*)((::Resource*)NativePtr)->stream);
}

void Flood::Resource::Stream::set(Flood::ResourceStream^ value)
{
    ((::Resource*)NativePtr)->stream = (::ResourceStream*)value->NativePtr;
}

