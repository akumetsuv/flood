// This code is in the public domain -- Ignacio Casta�o <castano@gmail.com>

#pragma once
#ifndef NV_CORE_UTILS_H
#define NV_CORE_UTILS_H

#include "Debug.h" // nvDebugCheck

#include <new> // for placement new


// Just in case. Grrr.
#undef min
#undef max

#define NV_INT8_MIN    (-128)
#define NV_INT8_MAX    127
#define NV_UINT8_MAX    255
#define NV_INT16_MIN    (-32767-1)
#define NV_INT16_MAX    32767
#define NV_UINT16_MAX   0xffff
#define NV_INT32_MIN    (-2147483647-1)
#define NV_INT32_MAX    2147483647
#define NV_UINT32_MAX   0xffffffff
#define NV_INT64_MAX    POSH_I64(9223372036854775807)
#define NV_INT64_MIN    (-POSH_I64(9223372036854775808))
#define NV_UINT64_MAX   POSH_U64(0xffffffffffffffff)

#define NV_HALF_MAX     65504.0F
#define NV_FLOAT_MAX    3.402823466e+38F


namespace nv
{
    // Less error prone than casting. From CB:
    // http://cbloomrants.blogspot.com/2011/06/06-17-11-c-casting-is-devil.html

    // uint32 casts:
    template <typename T> inline uint32 toU32(T x) { return x; }
    template <> inline uint32 toU32<uint64>(uint64 x) { nvDebugCheck(x <= NV_UINT32_MAX); return (uint32)x; }
    template <> inline uint32 toU32<int64>(int64 x) { nvDebugCheck(x >= 0 && x <= NV_UINT32_MAX); return (uint32)x; }
    //template <> inline uint32 toU32<uint32>(uint32 x) { return x; }
    template <> inline uint32 toU32<int32>(int32 x) { nvDebugCheck(x >= 0); return (uint32)x; }
    //template <> inline uint32 toU32<uint16>(uint16 x) { return x; }
    template <> inline uint32 toU32<int16>(int16 x) { nvDebugCheck(x >= 0); return (uint32)x; }
    //template <> inline uint32 toU32<uint8>(uint8 x) { return x; }
    template <> inline uint32 toU32<int8>(int8 x) { nvDebugCheck(x >= 0); return (uint32)x; }

    // int32 casts:
    template <typename T> inline int32 toI32(T x) { return x; }
    template <> inline int32 toI32<uint64>(uint64 x) { nvDebugCheck(x <= NV_INT32_MAX); return (int32)x; }
    template <> inline int32 toI32<int64>(int64 x) { nvDebugCheck(x >= NV_INT32_MIN && x <= NV_UINT32_MAX); return (int32)x; }
    template <> inline int32 toI32<uint32>(uint32 x) { nvDebugCheck(x <= NV_INT32_MAX); return (int32)x; }
    //template <> inline int32 toI32<int32>(int32 x) { return x; }
    //template <> inline int32 toI32<uint16>(uint16 x) { return x; }
    //template <> inline int32 toI32<int16>(int16 x) { return x; }
    //template <> inline int32 toI32<uint8>(uint8 x) { return x; }
    //template <> inline int32 toI32<int8>(int8 x) { return x; }

    // uint16 casts:
    template <typename T> inline uint16 toU16(T x) { return x; }
    template <> inline uint16 toU16<uint64>(uint64 x) { nvDebugCheck(x <= NV_UINT16_MAX); return (uint16)x; }
    template <> inline uint16 toU16<int64>(int64 x) { nvDebugCheck(x >= 0 && x <= NV_UINT16_MAX); return (uint16)x; }
    template <> inline uint16 toU16<uint32>(uint32 x) { nvDebugCheck(x <= NV_UINT16_MAX); return (uint16)x; }
    template <> inline uint16 toU16<int32>(int32 x) { nvDebugCheck(x >= 0 && x <= NV_UINT16_MAX); return (uint16)x; }
    //template <> inline uint16 toU16<uint16>(uint16 x) { return x; }
    template <> inline uint16 toU16<int16>(int16 x) { nvDebugCheck(x >= 0); return (uint16)x; }
    //template <> inline uint16 toU16<uint8>(uint8 x) { return x; }
    template <> inline uint16 toU16<int8>(int8 x) { nvDebugCheck(x >= 0); return (uint16)x; }

    // int16 casts:
    template <typename T> inline int16 toI16(T x) { return x; }
    template <> inline int16 toI16<uint64>(uint64 x) { nvDebugCheck(x <= NV_INT16_MAX); return (int16)x; }
    template <> inline int16 toI16<int64>(int64 x) { nvDebugCheck(x >= NV_INT16_MIN && x <= NV_UINT16_MAX); return (int16)x; }
    template <> inline int16 toI16<uint32>(uint32 x) { nvDebugCheck(x <= NV_INT16_MAX); return (int16)x; }
    template <> inline int16 toI16<int32>(int32 x) { nvDebugCheck(x >= NV_INT16_MIN && x <= NV_UINT16_MAX); return (int16)x; }
    template <> inline int16 toI16<uint16>(uint16 x) { nvDebugCheck(x <= NV_INT16_MAX); return (int16)x; }
    //template <> inline int16 toI16<int16>(int16 x) { return x; }
    //template <> inline int16 toI16<uint8>(uint8 x) { return x; }
    //template <> inline int16 toI16<int8>(int8 x) { return x; }

    // uint8 casts:
    template <typename T> inline uint8 toU8(T x) { return x; }
    template <> inline uint8 toU8<uint64>(uint64 x) { nvDebugCheck(x <= NV_UINT8_MAX); return (uint8)x; }
    template <> inline uint8 toU8<int64>(int64 x) { nvDebugCheck(x >= 0 && x <= NV_UINT8_MAX); return (uint8)x; }
    template <> inline uint8 toU8<uint32>(uint32 x) { nvDebugCheck(x <= NV_UINT8_MAX); return (uint8)x; }
    template <> inline uint8 toU8<int32>(int32 x) { nvDebugCheck(x >= 0 && x <= NV_UINT8_MAX); return (uint8)x; }
    template <> inline uint8 toU8<uint16>(uint16 x) { nvDebugCheck(x <= NV_UINT8_MAX); return (uint8)x; }
    template <> inline uint8 toU8<int16>(int16 x) { nvDebugCheck(x >= 0 && x <= NV_UINT8_MAX); return (uint8)x; }
    //template <> inline uint8 toU8<uint8>(uint8 x) { return x; }
    template <> inline uint8 toU8<int8>(int8 x) { nvDebugCheck(x >= 0); return (uint8)x; }

    // int8 casts:
    template <typename T> inline int8 toI8(T x) { return x; }
    template <> inline int8 toI8<uint64>(uint64 x) { nvDebugCheck(x <= NV_INT8_MAX); return (int8)x; }
    template <> inline int8 toI8<int64>(int64 x) { nvDebugCheck(x >= NV_INT8_MIN && x <= NV_UINT8_MAX); return (int8)x; }
    template <> inline int8 toI8<uint32>(uint32 x) { nvDebugCheck(x <= NV_INT8_MAX); return (int8)x; }
    template <> inline int8 toI8<int32>(int32 x) { nvDebugCheck(x >= NV_INT8_MIN && x <= NV_UINT8_MAX); return (int8)x; }
    template <> inline int8 toI8<uint16>(uint16 x) { nvDebugCheck(x <= NV_INT8_MAX); return (int8)x; }
    template <> inline int8 toI8<int16>(int16 x) { nvDebugCheck(x >= NV_INT8_MIN && x <= NV_UINT8_MAX); return (int8)x; }
    template <> inline int8 toI8<uint8>(uint8 x) { nvDebugCheck(x <= NV_INT8_MAX); return (int8)x; }
    //template <> inline int8 toI8<int8>(int8 x) { return x; }
    
    /// Swap two values.
    template <typename T> 
    inline void swap(T & a, T & b)
    {
        T temp(a);
        a = b; 
        b = temp;
    }

    /// Return the maximum of the two arguments. For floating point values, it returns the second value if the first is NaN.
    template <typename T> 
    inline const T & max(const T & a, const T & b)
    {
        return (b < a) ? a : b;
    }

    /// Return the maximum of the three arguments.
    template <typename T> 
    inline const T & max(const T & a, const T & b, const T & c)
    {
        return max(a, max(b, c));
    }

    /// Return the minimum of two values.
    template <typename T> 
    inline const T & min(const T & a, const T & b)
    {
        return (a < b) ? a : b;
    }

    /// Return the maximum of the three arguments.
    template <typename T> 
    inline const T & min(const T & a, const T & b, const T & c)
    {
        return min(a, min(b, c));
    }

    /// Clamp between two values.
    template <typename T> 
    inline const T & clamp(const T & x, const T & a, const T & b)
    {
        return min(max(x, a), b);
    }

    /** Return the next power of two. 
    * @see http://graphics.stanford.edu/~seander/bithacks.html
    * @warning Behaviour for 0 is undefined.
    * @note isPowerOfTwo(x) == true -> nextPowerOfTwo(x) == x
    * @note nextPowerOfTwo(x) = 2 << log2(x-1)
    */
    inline uint nextPowerOfTwo( uint x )
    {
        nvDebugCheck( x != 0 );
#if 1	// On modern CPUs this is supposed to be as fast as using the bsr instruction.
        x--;
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return x+1;	
#else
        uint p = 1;
        while( x > p ) {
            p += p;
        }
        return p;
#endif
    }

    /// Return true if @a n is a power of two.
    inline bool isPowerOfTwo( uint n )
    {
        return (n & (n-1)) == 0;
    }


    // @@ Move this to utils?
    /// Delete all the elements of a container.
    template <typename T>
    void deleteAll(T & container)
    {
        for (typename T::PseudoIndex i = container.start(); !container.isDone(i); container.advance(i))
        {
            delete container[i];
        }
    }



    // @@ Specialize these methods for numeric, pointer, and pod types.

    template <typename T>
    void construct_range(T * restrict ptr, uint new_size, uint old_size) {
        for (uint i = old_size; i < new_size; i++) {
            new(ptr+i) T; // placement new
        }
    }

    template <typename T>
    void construct_range(T * restrict ptr, uint new_size, uint old_size, const T & elem) {
        for (uint i = old_size; i < new_size; i++) {
            new(ptr+i) T(elem); // placement new
        }
    }

    template <typename T>
    void destroy_range(T * restrict ptr, uint new_size, uint old_size) {
        for (uint i = new_size; i < old_size; i++) {
            (ptr+i)->~T(); // Explicit call to the destructor
        }
    }

    template <typename T>
    void fill(T * restrict dst, uint count, const T & value) {
        for (uint i = 0; i < count; i++) {
            dst[i] = value;
        }
    }

    template <typename T>
    void copy(T * restrict dst, const T * restrict src, uint count) {
        for (uint i = 0; i < count; i++) {
            dst[i] = src[i];
        }
    }

    template <typename T>
    bool find(const T & element, const T * restrict ptr, uint begin, uint end, uint * index) {
        for (uint i = begin; i < end; i++) {
            if (ptr[i] == element) {
                if (index != NULL) *index = i;
                return true;
            }
        }
        return false;
    }

} // nv namespace

#endif // NV_CORE_UTILS_H
