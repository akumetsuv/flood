/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Graphics/RenderTarget.h>

namespace Flood
{
    ref class RenderView;
    value struct Settings;
    value struct Vector2i;
    ref class RenderContext;
    ref class RenderTarget;
}

namespace Flood
{
    public value struct Settings
    {
    public:

        Settings(::Settings* native);
        Settings(System::IntPtr native);
        Settings(unsigned short width, unsigned short height);

        unsigned short Width;
        unsigned short Height;
        property Flood::Vector2i Size
        {
            Flood::Vector2i get();
        }
    };

    public ref class RenderTarget : ICppInstance
    {
    public:

        property ::RenderTarget* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        RenderTarget(::RenderTarget* native);
        RenderTarget(System::IntPtr native);
        RenderTarget();

        property Flood::Settings Settings
        {
            Flood::Settings get();
        }
        property Flood::RenderContext^ Context
        {
            Flood::RenderContext^ get();
            void set(Flood::RenderContext^);
        }
        property System::IntPtr UserData
        {
            System::IntPtr get();
            void set(System::IntPtr);
        }
        property Flood::RenderContext^ Context1
        {
            Flood::RenderContext^ get();
            void set(Flood::RenderContext^);
        }
    private:
        delegate void _TargetResizeDelegate(const ::Settings& _0);
        _TargetResizeDelegate^ _TargetResizeDelegateInstance;
        void _TargetResizeRaise(const ::Settings& _0);
        System::Action<Flood::Settings>^ _TargetResize;
    public:
        event System::Action<Flood::Settings>^ TargetResize
        {
            void add(System::Action<Flood::Settings>^ evt);
            void remove(System::Action<Flood::Settings>^ evt);
            void raise(Flood::Settings _0);
        }
        Flood::RenderView^ CreateView();

        void RemoveViews();

        virtual void MakeCurrent();

        virtual void Update();

        void HandleResize();

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
