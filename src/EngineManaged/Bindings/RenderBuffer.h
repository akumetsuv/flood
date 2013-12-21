/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Graphics/RenderBuffer.h>
#include "RenderTarget.h"

namespace Flood
{
    ref class RenderBuffer;
    ref class RenderTarget;
    value struct Settings;
    ref class Image;
    enum struct RenderBufferType : unsigned char;
    ref class Texture;
}

namespace Flood
{
    [System::Flags]
    public enum struct RenderBufferType : unsigned char
    {
        Color = 1,
        Depth = 2,
        Stencil = 4
    };

    /// <summary>
    /// Render buffers are offscreen render targets that you can render into. There
    /// are 2 types of render targets attachments that you can use with render
    /// buffers: textures (also known as render-to-textures or RTTs), and render
    /// buffers. The attachments can have different types, so you need to specify
    /// the type of attachments that you need. You can render color, depth or even
    /// use them as stencil buffer. There is also another technique called MRTs
    /// (multiple render targets) which allows you to render into multiple buffers
    /// at the same time.
    /// </summary>
    public ref class RenderBuffer : Flood::RenderTarget
    {
    public:

        RenderBuffer(::RenderBuffer* native);
        RenderBuffer(System::IntPtr native);
        RenderBuffer(Flood::Settings settings);

        property Flood::Settings Settings
        {
            Flood::Settings get();
        }
        property Flood::Settings Settings1
        {
            Flood::Settings get();
            void set(Flood::Settings);
        }
        virtual void MakeCurrent() override;

        virtual void Bind();

        virtual void Unbind();

        virtual bool Check();

        virtual void Update() override;

        virtual Flood::Image^ ReadImage(char attachment);

        virtual void CreateRenderBuffer(Flood::RenderBufferType _0);

        virtual Flood::Texture^ CreateRenderTexture(Flood::RenderBufferType _1);

        virtual void AttachRenderTexture(Flood::Texture^ tex);

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
