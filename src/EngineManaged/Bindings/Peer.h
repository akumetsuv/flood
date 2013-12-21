/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Core/Network/Peer.h>

namespace Flood
{
    ref class Host;
    enum struct PeerState;
}

namespace Flood
{
    public enum struct PeerState
    {
        Disconnected = 0,
        Connected = 1,
        Disconnecting = 2
    };
}
