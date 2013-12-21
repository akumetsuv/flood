/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Core/Network/Packet.h>

namespace Flood
{
    enum struct PacketFlags : unsigned char;
}

namespace Flood
{
    [System::Flags]
    public enum struct PacketFlags : unsigned char
    {
        Binary = 1,
        Encrypted = 2,
        Compressed = 4,
        Reliable = 8,
        Signed = 16
    };
}
