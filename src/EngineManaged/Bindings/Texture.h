/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Graphics/Texture.h>
#include "Image.h"
#include "ResourceHandle.h"

namespace Flood
{
    ref class Texture;
    enum struct TextureTarget;
    enum struct PixelFormat;
    ref class Image;
    value struct Vector2i;
    ref class TextureUnit;
    enum struct TextureFilterMode;
    enum struct TextureMipMode;
    enum struct TextureWrapMode;
}

namespace Flood
{
    public enum struct TextureFilterMode
    {
        Nearest = 0,
        Linear = 1
    };

    public enum struct TextureMipMode
    {
        Nearest = 0,
        Linear = 1
    };

    public enum struct TextureWrapMode
    {
        Repeat = 0,
        Clamp = 1,
        ClampToBorder = 2,
        ClampToEdge = 3
    };

    public enum struct TextureTarget
    {
        Target2D = 0,
        Target3D = 1
    };

    public ref class Texture : ICppInstance
    {
    public:

        property ::Texture* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        Texture(::Texture* native);
        Texture(System::IntPtr native);
        Texture();

        property unsigned int Id
        {
            unsigned int get();
        }
        property Flood::PixelFormat PixelFormat
        {
            Flood::PixelFormat get();
        }
        property Flood::ResourceHandle<Flood::Image^> Image
        {
            Flood::ResourceHandle<Flood::Image^> get();
            void set(Flood::ResourceHandle<Flood::Image^>);
        }
        property unsigned int ExpectedSize
        {
            unsigned int get();
        }
        property Flood::TextureTarget Target
        {
            Flood::TextureTarget get();
            void set(Flood::TextureTarget);
        }
        property unsigned int Width
        {
            unsigned int get();
            void set(unsigned int);
        }
        property unsigned int Height
        {
            unsigned int get();
            void set(unsigned int);
        }
        property Flood::PixelFormat Format
        {
            Flood::PixelFormat get();
            void set(Flood::PixelFormat);
        }
        property float AnisotropicFilter
        {
            float get();
            void set(float);
        }
        void Alloc(Flood::Vector2i size, Flood::PixelFormat _0);

        Flood::Image^ ReadImage();

        bool IsUploaded();

        void SetUploaded();

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };

    public ref class TextureUnit : ICppInstance
    {
    public:

        property ::TextureUnit* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        TextureUnit(::TextureUnit* native);
        TextureUnit(System::IntPtr native);
        TextureUnit();

        property Flood::TextureFilterMode FilterMode
        {
            Flood::TextureFilterMode get();
            void set(Flood::TextureFilterMode);
        }
        property Flood::TextureMipMode MipMode
        {
            Flood::TextureMipMode get();
            void set(Flood::TextureMipMode);
        }
        property Flood::TextureWrapMode WrapMode
        {
            Flood::TextureWrapMode get();
            void set(Flood::TextureWrapMode);
        }
        property unsigned char Unit
        {
            unsigned char get();
            void set(unsigned char);
        }
        property Flood::ResourceHandle<Flood::Image^> Image
        {
            Flood::ResourceHandle<Flood::Image^> get();
            void set(Flood::ResourceHandle<Flood::Image^>);
        }
        property bool OverrideModes
        {
            bool get();
            void set(bool);
        }
        property Flood::TextureFilterMode Filter
        {
            Flood::TextureFilterMode get();
            void set(Flood::TextureFilterMode);
        }
        property Flood::TextureMipMode Mip
        {
            Flood::TextureMipMode get();
            void set(Flood::TextureMipMode);
        }
        property Flood::TextureWrapMode Wrap
        {
            Flood::TextureWrapMode get();
            void set(Flood::TextureWrapMode);
        }
        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
