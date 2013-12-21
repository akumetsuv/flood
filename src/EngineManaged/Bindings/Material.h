/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Graphics/Resources/Material.h>
#include "Image.h"
#include "Resource.h"
#include "ResourceHandle.h"
#include "ShaderMaterial.h"
#include "Vector.h"

namespace Flood
{
    ref class Material;
    ref class Resource;
    ref class TextureUnit;
    ref class ShaderMaterial;
    enum struct DepthCompare;
    value struct Vector2;
    enum struct BlendSource;
    enum struct BlendDestination;
    enum struct ResourceGroup;
    ref class Image;
}

namespace Flood
{
    public enum struct BlendSource
    {
        Zero = 0,
        One = 1,
        DestinationColor = 2,
        InverseDestinationColor = 3,
        SourceAlpha = 4,
        InverseSourceAlpha = 5,
        DestinationAlpha = 6,
        InverseDestinationAlpha = 7,
        SourceAlphaSaturate = 8
    };

    public enum struct BlendDestination
    {
        Zero = 0,
        One = 1,
        SourceColor = 2,
        InverseSourceColor = 3,
        SourceAlpha = 4,
        InverseSourceAlpha = 5,
        DestinationAlpha = 6,
        InverseDestinationAlpha = 7
    };

    public enum struct DepthCompare
    {
        Never = 0,
        Less = 1,
        Equal = 2,
        LessOrEqual = 3,
        Greater = 4,
        NotEqual = 5,
        GreaterOrEqual = 6,
        Always = 7
    };

    public ref class Material : Flood::Resource
    {
    public:

        Material(::Material* native);
        Material(System::IntPtr native);
        Material();

        property Flood::ResourceGroup ResourceGroup
        {
            Flood::ResourceGroup get();
        }
        property Flood::ResourceHandle<Flood::ShaderMaterial^> Shader
        {
            Flood::ResourceHandle<Flood::ShaderMaterial^> get();
            void set(Flood::ResourceHandle<Flood::ShaderMaterial^>);
        }
        property bool DepthWrite
        {
            bool get();
            void set(bool);
        }
        property bool DepthTest
        {
            bool get();
            void set(bool);
        }
        property Flood::DepthCompare DepthCompare
        {
            Flood::DepthCompare get();
            void set(Flood::DepthCompare);
        }
        property Flood::Vector2 DepthRange
        {
            Flood::Vector2 get();
            void set(Flood::Vector2);
        }
        property Flood::Vector2 DepthOffset
        {
            Flood::Vector2 get();
            void set(Flood::Vector2);
        }
        property bool AlphaTest
        {
            bool get();
            void set(bool);
        }
        property float LineWidth
        {
            float get();
            void set(float);
        }
        property bool LineSmoothing
        {
            bool get();
            void set(bool);
        }
        property bool BackfaceCulling
        {
            bool get();
            void set(bool);
        }
        property Flood::BlendSource BlendSource
        {
            Flood::BlendSource get();
        }
        property Flood::BlendDestination BlendDestination
        {
            Flood::BlendDestination get();
        }
        property Flood::ResourceHandle<Flood::ShaderMaterial^> Shader1
        {
            Flood::ResourceHandle<Flood::ShaderMaterial^> get();
            void set(Flood::ResourceHandle<Flood::ShaderMaterial^>);
        }
        property bool CullBackfaces
        {
            bool get();
            void set(bool);
        }
        property bool LineSmooth
        {
            bool get();
            void set(bool);
        }
        property Flood::BlendSource Source
        {
            Flood::BlendSource get();
            void set(Flood::BlendSource);
        }
        property Flood::BlendDestination Destination
        {
            Flood::BlendDestination get();
            void set(Flood::BlendDestination);
        }
        property bool _isBlendingEnabled
        {
            bool get();
            void set(bool);
        }
        bool IsBlendingEnabled();

        void SetBlending(Flood::BlendSource _0, Flood::BlendDestination _1);

        void SetTexture(unsigned char unit, Flood::ResourceHandle<Flood::Image^> image);

        Flood::ResourceHandle<Flood::Image^> GetTexture(unsigned char unit);

        Flood::TextureUnit^ GetTextureUnit(unsigned char unit);

        void Init();

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

        static property float DefaultLineWidth
        {
            float get();
            void set(float);
        }
    };
}
