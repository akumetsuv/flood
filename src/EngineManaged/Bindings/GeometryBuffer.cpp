/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "_Marshal.h"
#include "GeometryBuffer.h"
#include "Buffer.h"
#include "VertexBuffer.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace clix;

Flood::GeometryBuffer::GeometryBuffer(::GeometryBuffer* native)
{
    NativePtr = native;
}

Flood::GeometryBuffer::GeometryBuffer(System::IntPtr native)
{
    NativePtr = (::GeometryBuffer*)native.ToPointer();
}

Flood::GeometryBuffer::GeometryBuffer()
{
    NativePtr = new ::GeometryBuffer();
}

Flood::GeometryBuffer::GeometryBuffer(Flood::BufferUsage _180, Flood::BufferAccess _181)
{
    auto arg0 = (::BufferUsage)_180;
    auto arg1 = (::BufferAccess)_181;
    NativePtr = new ::GeometryBuffer(arg0, arg1);
}

Flood::BufferUsage Flood::GeometryBuffer::GetBufferUsage()
{
    auto ret = NativePtr->getBufferUsage();
    return (Flood::BufferUsage)ret;
}

void Flood::GeometryBuffer::SetBufferUsage(Flood::BufferUsage v)
{
    auto arg0 = (::BufferUsage)v;
    NativePtr->setBufferUsage(arg0);
}

Flood::BufferAccess Flood::GeometryBuffer::GetBufferAccess()
{
    auto ret = NativePtr->getBufferAccess();
    return (Flood::BufferAccess)ret;
}

void Flood::GeometryBuffer::SetBufferAccess(Flood::BufferAccess v)
{
    auto arg0 = (::BufferAccess)v;
    NativePtr->setBufferAccess(arg0);
}

void Flood::GeometryBuffer::ForceRebuild()
{
    NativePtr->forceRebuild();
}

void Flood::GeometryBuffer::Clear()
{
    NativePtr->clear();
}

void Flood::GeometryBuffer::Set(Flood::VertexAttribute _182, System::IntPtr data, unsigned int size)
{
    auto arg0 = (::VertexAttribute)_182;
    auto arg1 = (uint8*)data.ToPointer();
    auto arg2 = (uint32)size;
    NativePtr->set(arg0, arg1, arg2);
}

void Flood::GeometryBuffer::Set(System::IntPtr data, unsigned int size)
{
    auto arg0 = (uint8*)data.ToPointer();
    auto arg1 = (uint32)size;
    NativePtr->set(arg0, arg1);
}

void Flood::GeometryBuffer::Add(System::IntPtr data, unsigned int size)
{
    auto arg0 = (uint8*)data.ToPointer();
    auto arg1 = (uint32)size;
    NativePtr->add(arg0, arg1);
}

void Flood::GeometryBuffer::SetIndex(System::IntPtr data, unsigned int size)
{
    auto arg0 = (uint8*)data.ToPointer();
    auto arg1 = (uint32)size;
    NativePtr->setIndex(arg0, arg1);
}

void Flood::GeometryBuffer::AddIndex(System::IntPtr data, unsigned int size)
{
    auto arg0 = (uint8*)data.ToPointer();
    auto arg1 = (uint32)size;
    NativePtr->addIndex(arg0, arg1);
}

void Flood::GeometryBuffer::AddIndex(unsigned short index)
{
    auto arg0 = (uint16)index;
    NativePtr->addIndex(arg0);
}

bool Flood::GeometryBuffer::IsIndexed()
{
    auto ret = NativePtr->isIndexed();
    return ret;
}

float Flood::GeometryBuffer::GetAttribute(Flood::VertexAttribute _183, unsigned int i)
{
    auto arg0 = (::VertexAttribute)_183;
    auto arg1 = (uint32)i;
    auto ret = NativePtr->getAttribute(arg0, arg1);
    return *ret;
}

char Flood::GeometryBuffer::GetAttributeStride(Flood::VertexAttribute _184)
{
    auto arg0 = (::VertexAttribute)_184;
    auto ret = NativePtr->getAttributeStride(arg0);
    return ret;
}

unsigned int Flood::GeometryBuffer::GetNumVertices()
{
    auto ret = NativePtr->getNumVertices();
    return ret;
}

unsigned int Flood::GeometryBuffer::GetNumIndices()
{
    auto ret = NativePtr->getNumIndices();
    return ret;
}

