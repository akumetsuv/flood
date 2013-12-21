/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Core/Stream.h>

namespace Flood
{
    enum struct StreamOpenMode;
    enum struct StreamSeekMode;
    ref class WebStream;
    ref class ZipStream;
}

namespace Flood
{
    public enum struct StreamOpenMode
    {
        Read = 0,
        Write = 1,
        Append = 2,
        Default = 3
    };

    public enum struct StreamSeekMode
    {
        Absolute = 0,
        Relative = 1,
        RelativeEnd = 2
    };

    public ref class WebStream : ICppInstance
    {
    public:

        property ::WebStream* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        WebStream(::WebStream* native);
        WebStream(System::IntPtr native);
        /// <summary>
        /// Creates Web stream.
        /// </summary>
        WebStream(System::String^ URL, Flood::StreamOpenMode mode);

        property System::IntPtr Handle
        {
            System::IntPtr get();
            void set(System::IntPtr);
        }
        property bool IsPerformDone
        {
            bool get();
            void set(bool);
        }
        /// <summary>
        /// Update memory stream from current url content.
        /// </summary>
        bool Perform();

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };

    public ref class ZipStream : ICppInstance
    {
    public:

        property ::ZipStream* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        ZipStream(::ZipStream* native);
        ZipStream(System::IntPtr native);
        property unsigned long long Position
        {
            unsigned long long get();
        }
        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
