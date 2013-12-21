/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Core/Network/Session.h>

namespace Flood
{
    enum struct SessionState;
}

namespace Flood
{
    public enum struct SessionState
    {
        Closed = 0,
        Open = 1
    };
}
