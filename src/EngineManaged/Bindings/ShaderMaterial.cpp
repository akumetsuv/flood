/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "_Marshal.h"
#include "ShaderMaterial.h"
#include "Reflection.h"
#include "Memory.h"
#include "Serialization.h"
#include "Resource.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace clix;

Flood::ShaderMaterial::ShaderMaterial(::ShaderMaterial* native)
{
    NativePtr = native;
}

Flood::ShaderMaterial::ShaderMaterial(System::IntPtr native)
{
    NativePtr = (::ShaderMaterial*)native.ToPointer();
}

Flood::Class^ Flood::ShaderMaterial::GetType()
{
    auto ret = NativePtr->getType();
    return gcnew Flood::Class((::Class*)ret);
}

Flood::Class^ Flood::ShaderMaterial::GetStaticType()
{
    auto ret = NativePtr->getStaticType();
    return gcnew Flood::Class((::Class*)ret);
}

System::String^ Flood::ShaderMaterial::GetVertexSource()
{
    auto ret = NativePtr->getVertexSource();
    return clix::marshalString<clix::E_UTF8>(ret);
}

System::String^ Flood::ShaderMaterial::GetFragmentSource()
{
    auto ret = NativePtr->getFragmentSource();
    return clix::marshalString<clix::E_UTF8>(ret);
}

Flood::ResourceGroup Flood::ShaderMaterial::GetResourceGroup()
{
    auto ret = NativePtr->getResourceGroup();
    return (Flood::ResourceGroup)ret;
}

