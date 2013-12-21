/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "String.h"
#include "str.h"
#include "Vector.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::StringHash::StringHash(::StringHash* native)
{
    Hash = native->hash;
}

Flood::StringHash::StringHash(System::IntPtr native)
{
    auto __native = (::StringHash*)native.ToPointer();
    Hash = __native->hash;
}

Flood::StringHash::StringHash(System::String^ str, unsigned int size)
{
    auto _str = clix::marshalString<clix::E_UTF8>(str);
    ::StringHash _native(_str.c_str(), (::size_t)size);
    this->Hash = _native.hash;
}

