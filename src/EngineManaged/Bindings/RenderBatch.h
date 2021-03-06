/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include <Graphics/RenderBatch.h>
#include "Memory.h"

namespace Flood
{
    enum struct PrimitiveType : unsigned char;
    enum struct PrimitiveRasterMode : unsigned char;
    enum struct RenderLayer : unsigned char;
    ref class RenderBatch;
    ref class Delegate2;
    ref class ClosurePtr;
    ref class GenericClass;
    ref class DelegateMemento;
    ref class RenderBatchRange;
    ref class RefPtr;
    ref class Handle;
    ref class Allocator;
    ref class RenderView;
    ref class RenderState;

    /// <summary>
    /// Type of primitive of the RenderBatch.
    /// </summary>
    public enum struct PrimitiveType : unsigned char
    {
        Points = 0,
        Lines = 1,
        LineLoop = 2,
        LineStrip = 3,
        Triangles = 4,
        TriangleStrip = 5,
        TriangleFan = 6,
        Quads = 7,
        QuadStrip = 8,
        Polygon = 9
    };

    /// <summary>
    /// Type of rendering mode of the RenderBatch.
    /// </summary>
    public enum struct PrimitiveRasterMode : unsigned char
    {
        Solid = 0,
        Wireframe = 1,
        Point = 2
    };

    /// <summary>
    /// Use these different kinds of render groups to signal to the renderer how
    /// you want your RenderBatchs to be sorted by the render device. Lower numbers
    /// render before higher numbers.
    /// </summary>
    public enum struct RenderLayer : unsigned char
    {
        Normal = 0,
        Transparency = 5,
        PostTransparency = 7,
        Overlays = 10
    };

    /// <summary>
    /// The range of indices in the render batch
    /// </summary>
    public ref class RenderBatchRange
    {
    public:
        property ::RenderBatchRange* NativePtr;

        RenderBatchRange(::RenderBatchRange* native);
        RenderBatchRange(System::IntPtr native);
        property unsigned short Start;
        property unsigned short End;
        RenderBatchRange();
    };

    public ref class RenderBatch
    {
    public:
        property ::RenderBatch* NativePtr;

        RenderBatch(::RenderBatch* native);
        RenderBatch(System::IntPtr native);
        property Flood::RenderBatchRange^ Range;
        property Flood::RenderLayer Stage;
        property int Priority;
        property Flood::PrimitiveType Type;
        property Flood::PrimitiveRasterMode Mode;
        RenderBatch();
        Flood::RenderLayer GetRenderLayer();
        void SetRenderLayer(Flood::RenderLayer v);
        int GetRenderPriority();
        void SetRenderPriority(int v);
        Flood::PrimitiveRasterMode GetPrimitiveRasterMode();
        void SetPrimitiveRasterMode(Flood::PrimitiveRasterMode v);
        Flood::PrimitiveType GetPrimitiveType();
        void SetPrimitiveType(Flood::PrimitiveType v);
    };

    public ref class FloodRenderBatch
    {
    public:
        static Flood::RenderBatch^ RenderBatchCreate(Flood::Allocator^ _217);
    };
}
