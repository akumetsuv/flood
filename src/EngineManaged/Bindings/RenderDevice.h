/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Graphics/RenderDevice.h>

namespace Flood
{
    ref class Texture;
    ref class RenderBuffer;
    ref class RenderContext;
    ref class RenderBackend;
    ref class RenderBatch;
    ref class RenderDevice;
    enum struct RenderPipeline;
    ref class RenderTarget;
    ref class RenderView;
    value struct RenderState;
    ref class RenderBlock;
    ref class Material;
}

namespace Flood
{
    public enum struct RenderPipeline
    {
        Fixed = 0,
        ShaderForward = 1,
        ShaderDeferred = 2
    };

    public ref class RenderDevice : ICppInstance
    {
    public:

        property ::RenderDevice* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        RenderDevice(::RenderDevice* native);
        RenderDevice(System::IntPtr native);
        RenderDevice();

        property Flood::RenderPipeline Pipeline
        {
            Flood::RenderPipeline get();
            void set(Flood::RenderPipeline);
        }
        property Flood::RenderBackend^ Backend
        {
            Flood::RenderBackend^ get();
            void set(Flood::RenderBackend^);
        }
        property Flood::RenderTarget^ RenderTarget
        {
            Flood::RenderTarget^ get();
            void set(Flood::RenderTarget^);
        }
        property Flood::RenderContext^ ActiveContext
        {
            Flood::RenderContext^ get();
            void set(Flood::RenderContext^);
        }
        property Flood::RenderView^ ActiveView
        {
            Flood::RenderView^ get();
            void set(Flood::RenderView^);
        }
        property Flood::RenderTarget^ ActiveTarget
        {
            Flood::RenderTarget^ get();
            void set(Flood::RenderTarget^);
        }
        property Flood::RenderBackend^ RenderBackend
        {
            Flood::RenderBackend^ get();
            void set(Flood::RenderBackend^);
        }
        void Render(Flood::RenderBlock^ queue);

        void UpdateRenderTargets();

        void ClearView();

        bool IsFixedPipeline();

        bool SetupRenderStateMatrix(Flood::RenderState state);

        bool SetupRenderStateOverlay(Flood::RenderState _0);

        void BindTextureUnits(Flood::RenderState state, bool bindUniforms);

        void UnbindTextureUnits(Flood::Material^ material);

        bool BindBuffers(Flood::RenderBatch^ _0);

        bool UnbindBuffers(Flood::RenderBatch^ _0);

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

        static Flood::RenderDevice^ GetRenderDevice();

    };
}
