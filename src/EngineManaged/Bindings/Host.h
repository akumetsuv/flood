/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Core/Network/Host.h>

namespace Flood
{
    ref class Host;
    value struct HostConnectionDetails;
    ref class HostClient;
    ref class HostServer;
}

namespace Flood
{
    public ref class Host : ICppInstance
    {
    public:

        property ::Host* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        Host(::Host* native);
        Host(System::IntPtr native);
        Host();

        bool DestroySocket();

        void ProcessEvents(unsigned int timeout);

        bool HasContext();

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };

    public value struct HostConnectionDetails
    {
    public:

        HostConnectionDetails(::HostConnectionDetails* native);
        HostConnectionDetails(System::IntPtr native);
        unsigned short Port;
        unsigned char ChannelCount;
    };

    public ref class HostClient : Flood::Host
    {
    public:

        HostClient(::HostClient* native);
        HostClient(System::IntPtr native);
        HostClient();

        bool Connect(Flood::HostConnectionDetails _0);

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };

    public ref class HostServer : Flood::Host
    {
    public:

        HostServer(::HostServer* native);
        HostServer(System::IntPtr native);
        HostServer();

        bool CreateSocket(Flood::HostConnectionDetails _0);

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
