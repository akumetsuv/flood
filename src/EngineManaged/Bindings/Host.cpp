/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Host.h"
#include "Vector.h"

using namespace System;
using namespace System::Runtime::InteropServices;

Flood::Host::Host(::Host* native)
{
    NativePtr = native;
}

Flood::Host::Host(System::IntPtr native)
{
    auto __native = (::Host*)native.ToPointer();
    NativePtr = __native;
}

bool Flood::Host::DestroySocket()
{
    auto __ret = ((::Host*)NativePtr)->destroySocket();
    return __ret;
}

void Flood::Host::ProcessEvents(unsigned int timeout)
{
    auto arg0 = (::uint32)(::uint32_t)timeout;
    ((::Host*)NativePtr)->processEvents(arg0);
}

bool Flood::Host::HasContext()
{
    auto __ret = ((::Host*)NativePtr)->hasContext();
    return __ret;
}

Flood::Host::Host()
{
    NativePtr = new ::Host();
}

bool Flood::Host::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<Host^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::Host::GetHashCode()
{
    return (int)NativePtr;
}

System::IntPtr Flood::Host::Instance::get()
{
    return System::IntPtr(NativePtr);
}

void Flood::Host::Instance::set(System::IntPtr object)
{
    NativePtr = (::Host*)object.ToPointer();
}
Flood::HostConnectionDetails::HostConnectionDetails(::HostConnectionDetails* native)
{
    Port = native->port;
    ChannelCount = native->channelCount;
}

Flood::HostConnectionDetails::HostConnectionDetails(System::IntPtr native)
{
    auto __native = (::HostConnectionDetails*)native.ToPointer();
    Port = __native->port;
    ChannelCount = __native->channelCount;
}

Flood::HostClient::HostClient(::HostClient* native)
    : Flood::Host((::Host*)native)
{
}

Flood::HostClient::HostClient(System::IntPtr native)
    : Flood::Host(native)
{
    auto __native = (::HostClient*)native.ToPointer();
}

Flood::HostClient::HostClient()
    : Flood::Host((::Host*)nullptr)
{
    NativePtr = new ::HostClient();
}

bool Flood::HostClient::Connect(Flood::HostConnectionDetails _0)
{
    auto _marshal0 = ::HostConnectionDetails();
    _marshal0.port = (::uint16)(::uint16_t)_0.Port;
    _marshal0.channelCount = (::uint8)(::uint8_t)_0.ChannelCount;
    auto arg0 = _marshal0;
    auto __ret = ((::HostClient*)NativePtr)->connect(arg0);
    return __ret;
}

bool Flood::HostClient::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<HostClient^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::HostClient::GetHashCode()
{
    return (int)NativePtr;
}

Flood::HostServer::HostServer(::HostServer* native)
    : Flood::Host((::Host*)native)
{
}

Flood::HostServer::HostServer(System::IntPtr native)
    : Flood::Host(native)
{
    auto __native = (::HostServer*)native.ToPointer();
}

bool Flood::HostServer::CreateSocket(Flood::HostConnectionDetails _0)
{
    auto _marshal0 = ::HostConnectionDetails();
    _marshal0.port = (::uint16)(::uint16_t)_0.Port;
    _marshal0.channelCount = (::uint8)(::uint8_t)_0.ChannelCount;
    auto arg0 = _marshal0;
    auto __ret = ((::HostServer*)NativePtr)->createSocket(arg0);
    return __ret;
}

Flood::HostServer::HostServer()
    : Flood::Host((::Host*)nullptr)
{
    NativePtr = new ::HostServer();
}

bool Flood::HostServer::Equals(System::Object^ object)
{
    if (!object) return false;
    auto obj = dynamic_cast<HostServer^>(object);

    if (!obj) return false;
    return Instance == obj->Instance;
}

int Flood::HostServer::GetHashCode()
{
    return (int)NativePtr;
}

