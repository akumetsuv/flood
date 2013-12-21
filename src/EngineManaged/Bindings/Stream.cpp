/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Stream.h"
#include "Vector.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::WebStream::WebStream(::WebStream* native)
{
    NativePtr = native;
}

Flood::WebStream::WebStream(System::IntPtr native)
{
    auto __native = (::WebStream*)native.ToPointer();
    NativePtr = __native;
}

Flood::WebStream::WebStream(System::String^ URL, Flood::StreamOpenMode mode)
{
    auto arg0 = StringMarshaller::marshalUTF8String(URL);
    auto arg1 = (::StreamOpenMode)mode;
    NativePtr = new ::WebStream(arg0, arg1);
}

bool Flood::WebStream::Perform()
{
    auto __ret = ((::WebStream*)NativePtr)->perform();
    return __ret;
}

bool Flood::WebStream::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<WebStream^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::WebStream::GetHashCode()
{
    return (int)NativePtr;
}

System::IntPtr Flood::WebStream::Instance::get()
{
    return System::IntPtr(NativePtr);
}

void Flood::WebStream::Instance::set(System::IntPtr object)
{
    NativePtr = (::WebStream*)object.ToPointer();
}

System::IntPtr Flood::WebStream::Handle::get()
{
    return IntPtr(((::WebStream*)NativePtr)->handle);
}

void Flood::WebStream::Handle::set(System::IntPtr value)
{
    ((::WebStream*)NativePtr)->handle = (::CURL*)value.ToPointer();
}

bool Flood::WebStream::IsPerformDone::get()
{
    return ((::WebStream*)NativePtr)->isPerformDone;
}

void Flood::WebStream::IsPerformDone::set(bool value)
{
    ((::WebStream*)NativePtr)->isPerformDone = value;
}

Flood::ZipStream::ZipStream(::ZipStream* native)
{
    NativePtr = native;
}

Flood::ZipStream::ZipStream(System::IntPtr native)
{
    auto __native = (::ZipStream*)native.ToPointer();
    NativePtr = __native;
}

bool Flood::ZipStream::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<ZipStream^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::ZipStream::GetHashCode()
{
    return (int)NativePtr;
}

System::IntPtr Flood::ZipStream::Instance::get()
{
    return System::IntPtr(NativePtr);
}

void Flood::ZipStream::Instance::set(System::IntPtr object)
{
    NativePtr = (::ZipStream*)object.ToPointer();
}

unsigned long long Flood::ZipStream::Position::get()
{
    auto __ret = ((::ZipStream*)NativePtr)->getPosition();
    return __ret;
}

