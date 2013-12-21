/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Core/Memory.h>

namespace Flood
{
    ref class PoolAllocator;
    ref class BumpAllocator;
    ref class HeapAllocator;
}

namespace Flood
{
    /// <summary>
    /// Manages memory allocation using a fixed-size object pool. When a new
    /// allocation is requested, we search for the first free object available and
    /// return it.
    /// </summary>
    public ref class PoolAllocator : ICppInstance
    {
    public:

        property ::PoolAllocator* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        PoolAllocator(::PoolAllocator* native);
        PoolAllocator(System::IntPtr native);
        PoolAllocator();

        property System::IntPtr Current
        {
            System::IntPtr get();
            void set(System::IntPtr);
        }
        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };

    /// <summary>
    /// Manages memory allocations using a fixed-size buffer that can provide
    /// allocations and deallocations in O(1). The allocated space in the buffer is
    /// not re-used until the whole buffer is reset.
    /// </summary>
    public ref class BumpAllocator : ICppInstance
    {
    public:

        property ::BumpAllocator* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        BumpAllocator(::BumpAllocator* native);
        BumpAllocator(System::IntPtr native);
        BumpAllocator();

        property System::IntPtr Start
        {
            System::IntPtr get();
            void set(System::IntPtr);
        }
        property System::IntPtr Current
        {
            System::IntPtr get();
            void set(System::IntPtr);
        }
        property unsigned int Size
        {
            unsigned int get();
            void set(unsigned int);
        }
        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };

    /// <summary>
    /// Manages memory allocation using Doug Lea's malloc implementation. This is a
    /// boundary-tag allocator that manages memory by keeping track of the
    /// used/free memory blocks.
    /// </summary>
    public ref class HeapAllocator : ICppInstance
    {
    public:

        property ::HeapAllocator* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        HeapAllocator(::HeapAllocator* native);
        HeapAllocator(System::IntPtr native);
        HeapAllocator();

        property System::IntPtr Space
        {
            System::IntPtr get();
            void set(System::IntPtr);
        }
        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
