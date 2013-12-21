/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Memory.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::PoolAllocator::PoolAllocator(::PoolAllocator* native)
{
    NativePtr = native;
}

Flood::PoolAllocator::PoolAllocator(System::IntPtr native)
{
    auto __native = (::PoolAllocator*)native.ToPointer();
    NativePtr = __native;
}

Flood::PoolAllocator::PoolAllocator()
{
    NativePtr = new ::PoolAllocator();
}

bool Flood::PoolAllocator::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<PoolAllocator^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::PoolAllocator::GetHashCode()
{
    return (int)NativePtr;
}

System::IntPtr Flood::PoolAllocator::Instance::get()
{
    return System::IntPtr(NativePtr);
}

void Flood::PoolAllocator::Instance::set(System::IntPtr object)
{
    NativePtr = (::PoolAllocator*)object.ToPointer();
}

System::IntPtr Flood::PoolAllocator::Current::get()
{
    return IntPtr(((::PoolAllocator*)NativePtr)->current);
}

void Flood::PoolAllocator::Current::set(System::IntPtr value)
{
    ((::PoolAllocator*)NativePtr)->current = (::uint8*)value.ToPointer();
}

Flood::BumpAllocator::BumpAllocator(::BumpAllocator* native)
{
    NativePtr = native;
}

Flood::BumpAllocator::BumpAllocator(System::IntPtr native)
{
    auto __native = (::BumpAllocator*)native.ToPointer();
    NativePtr = __native;
}

Flood::BumpAllocator::BumpAllocator()
{
    NativePtr = new ::BumpAllocator();
}

bool Flood::BumpAllocator::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<BumpAllocator^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::BumpAllocator::GetHashCode()
{
    return (int)NativePtr;
}

System::IntPtr Flood::BumpAllocator::Instance::get()
{
    return System::IntPtr(NativePtr);
}

void Flood::BumpAllocator::Instance::set(System::IntPtr object)
{
    NativePtr = (::BumpAllocator*)object.ToPointer();
}

System::IntPtr Flood::BumpAllocator::Start::get()
{
    return IntPtr(((::BumpAllocator*)NativePtr)->start);
}

void Flood::BumpAllocator::Start::set(System::IntPtr value)
{
    ((::BumpAllocator*)NativePtr)->start = (::uint8*)value.ToPointer();
}

System::IntPtr Flood::BumpAllocator::Current::get()
{
    return IntPtr(((::BumpAllocator*)NativePtr)->current);
}

void Flood::BumpAllocator::Current::set(System::IntPtr value)
{
    ((::BumpAllocator*)NativePtr)->current = (::uint8*)value.ToPointer();
}

unsigned int Flood::BumpAllocator::Size::get()
{
    return ((::BumpAllocator*)NativePtr)->size;
}

void Flood::BumpAllocator::Size::set(unsigned int value)
{
    ((::BumpAllocator*)NativePtr)->size = (::uint32)(::uint32_t)value;
}

Flood::HeapAllocator::HeapAllocator(::HeapAllocator* native)
{
    NativePtr = native;
}

Flood::HeapAllocator::HeapAllocator(System::IntPtr native)
{
    auto __native = (::HeapAllocator*)native.ToPointer();
    NativePtr = __native;
}

Flood::HeapAllocator::HeapAllocator()
{
    NativePtr = new ::HeapAllocator();
}

bool Flood::HeapAllocator::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<HeapAllocator^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::HeapAllocator::GetHashCode()
{
    return (int)NativePtr;
}

System::IntPtr Flood::HeapAllocator::Instance::get()
{
    return System::IntPtr(NativePtr);
}

void Flood::HeapAllocator::Instance::set(System::IntPtr object)
{
    NativePtr = (::HeapAllocator*)object.ToPointer();
}

System::IntPtr Flood::HeapAllocator::Space::get()
{
    return IntPtr(((::HeapAllocator*)NativePtr)->space);
}

void Flood::HeapAllocator::Space::set(System::IntPtr value)
{
    ((::HeapAllocator*)NativePtr)->space = (void*)value.ToPointer();
}

