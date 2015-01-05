﻿using Flood.GUIv2.Controls;
using Flood.GUIv2.Input;
using Flood.GUIv2.Renderers;
using System;
using System.Collections.Generic;

namespace Flood.GUIv2
{
    class ZCounter
    {
        float zcount;
        
        public void Reset()
        {
            zcount = -99;
        }

        public void Increment()
        {
            zcount += 0.001f;
        }

        public float Value
        {
            get { return zcount; }
        }
    }

    class GUIGeometryBuffer : ManagedGeometryBuffer
    {
        struct Vertex
        {
            public Vector3 Position;
            public Vector2 UV;
            public Color Color;
            public float shift;
        };

        private ZCounter zCounter;

        public GUIGeometryBuffer(ZCounter zCounter)
        {
            this.zCounter = zCounter;
        }

        protected override GeometryBuffer CreateGeometryBuffer()
        {
            var gb = new GeometryBuffer();
            gb.Declarations.Add(new VertexElement(VertexAttribute.Position, VertexDataType.Float, 3));
            gb.Declarations.Add(new VertexElement(VertexAttribute.TexCoord0, VertexDataType.Float, 2));
            gb.Declarations.Add(new VertexElement(VertexAttribute.Color, VertexDataType.Byte, 4));
            gb.Declarations.Add(new VertexElement(VertexAttribute.Normal, VertexDataType.Float, 1));
            gb.Declarations.CalculateStrides();
            return gb;
        }

        protected override ResourceHandle<Material> CreateMaterial(ResourceHandle<Image> imageHandle)
        {
            var materialHandle = Material.Create(Allocator.GetHeap(), "GwenGui");
            var mat = materialHandle.Resolve();
            mat.BackfaceCulling = false;
            mat.SetBlending(BlendSource.SourceAlpha, BlendDestination.InverseSourceAlpha);

            if (imageHandle.Id == ResourceHandle<Image>.Invalid)
            {
                mat.SetShader("VertexColor");
            }
            else
            {
                mat.SetShader("TexColor");
                mat.SetTexture(0, imageHandle);
                mat.GetTextureUnit(0).WrapMode = TextureWrapMode.Clamp;
            }

            return materialHandle;
        }

        public void AddRectangle(RectangleF rect, Color color)
        {
            ResourceHandle<Image> imageHandle;
            imageHandle.Id = ResourceHandle<Image>.Invalid;

            AddRectangle(rect,Vector2.Zero,Vector2.Zero,Vector2.Zero,Vector2.Zero, GetCreateMaterial(imageHandle), color);
        }

        //public void AddRectangle(RectangleF rect, 
        //    Vector2 topLeftUV, Vector2 topRightUV, Vector2 bottomRightUV, Vector2 bottomLeftUV,
        //    ResourceHandle<Image> imageHandle, Color color)
        //{
        //    Vertex v1, v2, v3, v4;

        //    InitVetexes(out v1, out v2, out v3, out v4,
        //                rect, color,
        //                topLeftUV, topRightUV, bottomRightUV, bottomLeftUV);

        //     unsafe
        //     {
        //         AddQuad(new IntPtr(&v1),new IntPtr(&v2),new IntPtr(&v3),new IntPtr(&v4), (uint)sizeof(Vertex), imageHandle);
        //     }
        // }

        public void AddRectangle(RectangleF rect, 
            Vector2 topLeftUV, Vector2 topRightUV, Vector2 bottomRightUV, Vector2 bottomLeftUV,
            ResourceHandle<Material> materialHandle, Color color)
        {
            Vertex v1, v2, v3, v4;

            InitVetexes(out v1, out v2, out v3, out v4,
                        rect, color,
                        topLeftUV, topRightUV, bottomRightUV, bottomLeftUV);

             unsafe
             {
                 AddQuad(new IntPtr(&v1),new IntPtr(&v2),new IntPtr(&v3),new IntPtr(&v4), (uint)sizeof(Vertex), materialHandle);
             }
        }

        private void InitVetexes(out Vertex v1, out Vertex v2, out Vertex v3, out Vertex v4,
            RectangleF rect , Color color,
            Vector2 topLeftUV, Vector2 topRightUV, Vector2 bottomRightUV, Vector2 bottomLeftUV)
        {

            var top = Math.Max(rect.GetBottom(), rect.GetTop());
            var bottom = Math.Min(rect.GetBottom(), rect.GetTop());
            var left = rect.GetLeft();
            var right = rect.GetRight();

            v1.Position = new Vector3(left, bottom, zCounter.Value);
            v2.Position = new Vector3(right, bottom, zCounter.Value);
            v3.Position = new Vector3(right, top, zCounter.Value);
            v4.Position = new Vector3(left, top, zCounter.Value);

            zCounter.Increment();

            v1.shift = left  - ((int)left);
            v2.shift = right - ((int)right);
            v3.shift = right - ((int)right);
            v4.shift = left  - ((int)left);

            v1.Color = color;
            v2.Color = color;
            v3.Color = color;
            v4.Color = color;

            v1.UV = topLeftUV;
            v2.UV = topRightUV;
            v3.UV = bottomRightUV;
            v4.UV = bottomLeftUV;
        }
    }

    abstract class ManagedGeometryBuffer
    {
        struct BatchInfo
        {
            public RenderBatch Batch;
            public List<int> Ranges;
        };

        readonly GeometryBuffer gb;
        readonly Dictionary<uint, BatchInfo> batches;
        readonly Dictionary<uint, ResourceHandle<Material>> materials;

        protected ManagedGeometryBuffer()
        {
            gb = CreateGeometryBuffer();

            batches = new Dictionary<uint, BatchInfo>();
            materials = new Dictionary<uint, ResourceHandle<Material>>();
        }

        protected abstract GeometryBuffer CreateGeometryBuffer();
        protected abstract ResourceHandle<Material> CreateMaterial(ResourceHandle<Image> imageHandle);

        protected void AddQuad(IntPtr v1, IntPtr v2, IntPtr v3, IntPtr v4, uint structSize, ResourceHandle<Image> imageHandle)
        {
            var materialHandle = GetCreateMaterial(imageHandle);
            AddQuad(v1, v2, v3, v4, structSize, materialHandle);
        }

        protected unsafe void AddQuad(IntPtr v1, IntPtr v2, IntPtr v3, IntPtr v4, uint structSize, ResourceHandle<Material> materialHandle)
        {
            var batchInfo = GetCreateBatchInfo(materialHandle);
            batchInfo.Ranges.Add((int) gb.NumVertices);

            gb.Add((byte*)v1.ToPointer(), structSize);
            gb.Add((byte*)v2.ToPointer(), structSize);
            gb.Add((byte*)v3.ToPointer(), structSize);
            gb.Add((byte*)v4.ToPointer(), structSize);
        }

        public void Render(RenderBlock rb)
        {
            foreach (var batch in batches.Values)
            {
                if (batch.Ranges.Count > 0)
                {
                    var newRange = new RenderBatchRange();
                    newRange.Start = (ushort)gb.NumIndices;

                    foreach (var range in batch.Ranges)
                    {
                        var vertexIndex = (ushort)range;
                        gb.AddIndex(vertexIndex++);
                        gb.AddIndex(vertexIndex++);
                        gb.AddIndex(vertexIndex++);
                        gb.AddIndex(vertexIndex);
                    }

                    newRange.End = (ushort)gb.NumIndices;
                    batch.Batch.Range = newRange;

                    var state = new RenderState(batch.Batch);
                    rb.AddState(state);
                }
            }
        }

        public void Clear()
        {
            foreach(var batch in batches.Values)
            {
                batch.Ranges.Clear();
            }

            gb.Clear();
            gb.ClearIndexes();
        }

        public ResourceHandle<Material> GetCreateMaterial(ResourceHandle<Image> imageHandle)
        {
            var id = imageHandle.Id;

            if (!materials.ContainsKey(id))
            {
                var materialHandle = CreateMaterial(imageHandle);

                materials.Add(id, materialHandle);
            }

            return materials[id];
        }

        BatchInfo GetCreateBatchInfo(ResourceHandle<Material> materialHandle)
        {
            if (!batches.ContainsKey(materialHandle.Id))
            {
                var batch = new RenderBatch
                {
                    GeometryBuffer = gb,
                    RenderLayer = RenderLayer.Overlays,
                    PrimitiveType = PrimitiveType.Quads,
                    Material = materialHandle
                };

                var batchInfo = new BatchInfo {Batch = batch, Ranges = new List<int>()};
                batches[materialHandle.Id] = batchInfo;
            }

            return batches[materialHandle.Id];
        }

    };
    
    public class TextRenderer
    {
        private static readonly GlyphManager glyphManager;

        static TextRenderer()
        {
            glyphManager = new GlyphManager();
        }

        public static Vector2 MeasureText(System.String text, Font font)
        {
            float curX = 0;
            float curY = font.Size;
            for(var i = 0; i < text.Length; i++)
            {
                var c = text[i];

                Glyph glyph;
                if (!glyphManager.TryGetGlyphInfo(font, c, out glyph))
                {
                    Log.Warn("Glyph not found for character " + c);
                    continue;
                }

                curX += glyph.Advance;
                if(i < text.Length - 1) 
                    curX += glyphManager.GetKerning(font, text[i], text[i + 1]).X;

                curY = Math.Max(curY, glyph.Height + glyph.BaseLineOffset);

            }

            return new Vector2(curX, curY);
        }

        public static bool GetPositionTextIndex(string text, Font font, float x, out int index)
        {
            float curX = 0;

            for(var i = 0; i < text.Length; i++)
            {
                var c = text[i];

                Glyph glyph;
                if (!glyphManager.TryGetGlyphInfo(font, c, out glyph))
                {
                    Log.Warn("Glyph not found for character " + c);
                    continue;
                }

                curX += glyph.Advance;
                if(i < text.Length - 1) 
                   curX += glyphManager.GetKerning(font, text[i], text[i + 1]).X;

                if(curX >= x)
                {
                    index = i;
                    return true;
                }
            }

            index = 0;
            return false;
        }

        //internal static void DrawText(GUIGeometryBuffer geometryBuffer, Font font, Vector2 position, String text, Color color)
        //{
        //    for (var i = 0; i < text.Length; i++)
        //    {
        //        char c = text[i];

        //        Glyph glyph;
        //        if (!glyphManager.TryGetGlyphInfo(font, c, out glyph))
        //        {
        //            Log.Warn("Glyph not found for character " + c);
        //            continue;
        //        }

        //        SubTexture subTexture;
        //        ResourceHandle<Material> material;

        //        if (glyphManager.TryGetGlyphImage(font, c, out subTexture, out material))
        //        {
        //            var renderRect = new RectangleF(
        //                position.X + glyph.XOffset,
        //                position.Y + glyph.BaseLineOffset,
        //                glyph.Width,
        //                glyph.Height);

        //            geometryBuffer.AddRectangle(renderRect,
        //                subTexture.LeftTopUV, subTexture.RightTopUV,
        //                subTexture.RightBottomUV, subTexture.LeftBottomUV,
        //                material, color);
        //        }

        //        if (i < text.Length - 1)
        //        {
        //            var kern = glyphManager.GetKerning(font, text[i], text[i + 1]);
        //            position.X += glyph.Advance + kern.X;
        //            position.Y += kern.Y;
        //        }
        //    }
        //}
        //todo: use this version of the method above to have text clipping when it's fixed
        internal static void DrawText(Renderer renderer, Font font, Vector2 position, String text, Color color)
        {
            for (var i = 0; i < text.Length; i++)
            {
                char c = text[i];

                Glyph glyph;
                if (!glyphManager.TryGetGlyphInfo(font, c, out glyph))
                {
                    Log.Warn("Glyph not found for character " + c);
                    continue;
                }

                SubTexture subTexture;
                ResourceHandle<Material> material;

                if (glyphManager.TryGetGlyphImage(font, c, out subTexture, out material))
                {
                    var renderRect = new RectangleF(
                        position.X + glyph.XOffset,
                        position.Y + glyph.BaseLineOffset,
                        glyph.Width,
                        glyph.Height);

                    renderer.DrawText(material, renderRect,
                        subTexture.LeftTopUV, subTexture.RightTopUV,
                        subTexture.RightBottomUV, subTexture.LeftBottomUV);
                }

                if (i < text.Length - 1)
                {
                    var kern = glyphManager.GetKerning(font, text[i], text[i + 1]);
                    position.X += glyph.Advance + kern.X;
                    position.Y += kern.Y;
                }
            }
        }
    };

    public class GwenRenderer : Renderer
    {
        private readonly ZCounter zCounter;
        private readonly GUIGeometryBuffer _guiBuffer;

        public GwenRenderer()
        {
            zCounter = new ZCounter();
            _guiBuffer = new GUIGeometryBuffer(zCounter);
        }

        public void Render(RenderBlock rb)
        {
            _guiBuffer.Render(rb);
        }

        public void Clear()
        {
            _guiBuffer.Clear();
            zCounter.Reset();
        }

        public override void DrawFilledRect(Rectangle rect) 
        {
            rect = Translate(rect);
            rect = ClampToClipRegion(rect);
            _guiBuffer.AddRectangle(rect.ToRectangleF(), DrawColor);
        }

        private Rectangle ClampToClipRegion(Rectangle rectangle)
        {
            var x = Math.Min(Math.Max(rectangle.X, ClipRegion.GetLeft()), ClipRegion.GetRight());
            var y = Math.Min(Math.Max(rectangle.Y, ClipRegion.GetTop()), ClipRegion.GetBottom());
            var width = Math.Min(rectangle.Width, ClipRegion.GetRight() - x);
            var height = Math.Min(rectangle.Height, ClipRegion.GetBottom() - y);

            return new Rectangle(x, y, width, height);
        }

        private RectangleF ClampToClipRegion(RectangleF rectangle)
        {
            var x = Math.Min(Math.Max(rectangle.X, ClipRegion.GetLeft()), ClipRegion.GetRight());
            var y = Math.Min(Math.Max(rectangle.Y, ClipRegion.GetTop()), ClipRegion.GetBottom());
            var width = Math.Min(rectangle.Width, ClipRegion.GetRight() - x);
            var height = Math.Min(rectangle.Height, ClipRegion.GetBottom() - y);

            return new RectangleF(x, y, width, height);
        }
        public override Color DrawColor { get; set; }

        public override void DrawTexturedRect(ResourceHandle<Image> imageHandle, Rectangle rect, float u1, float v1, float u2, float v2)
        {
            DrawTexturedRect(_guiBuffer.GetCreateMaterial(imageHandle), rect.ToRectangleF(), u1, v1, u2, v2);
        }

        public override void DrawTexturedRect(ResourceHandle<Material> materialHandle, Rectangle rect, float u1, float v1, float u2, float v2)
        {
            DrawTexturedRect(materialHandle, rect.ToRectangleF(), u1, v1, u2, v2);
        }

        public override void DrawTexturedRect(ResourceHandle<Image> imageHandle, RectangleF rect, float u1, float v1, float u2, float v2)
        {
            DrawTexturedRect(_guiBuffer.GetCreateMaterial(imageHandle), rect, u1, v1, u2, v2);
        }

        public override void DrawTexturedRect(ResourceHandle<Material> materialHandle, RectangleF rect, float u1, float v1, float u2, float v2)
        {
            rect = Translate(rect);
            var rect2 = ClampToClipRegion(rect);
            var horizontalRatio = (u2 - u1)/rect.Width;
            var verticalRatio = (v2 - v1)/rect.Height;

            u1 = u1 + (rect2.GetLeft() - rect.GetLeft()) * horizontalRatio;
            u2 = u1 + (rect2.GetRight() - rect.GetLeft()) * horizontalRatio;
            v1 = v1 + (rect2.GetTop() - rect.GetTop()) * verticalRatio;
            v2 = v1 + (rect2.GetBottom() - rect.GetTop()) * verticalRatio;

            _guiBuffer.AddRectangle(rect2, new Vector2(u1,v1), new Vector2(u2,v1), new Vector2(u2,v2), new Vector2(u1,v2), materialHandle, DrawColor);
        }

        public override void DrawText(ResourceHandle<Material> materialHandle, RectangleF rect, Vector2 leftTop, Vector2 rightTop, Vector2 rightBottom, Vector2 leftBottom)
        {
            rect = Translate(rect);
            var rect2 = ClampToClipRegion(rect);

            var horizontalRatio = 1 - (rect2.GetRight() - rect2.GetLeft())/(rect.GetRight() - rect.GetLeft());
            var verticalRatio = 1 - (rect2.GetBottom() - rect2.GetTop())/(rect.GetBottom() - rect.GetTop());
            var tr = rightTop - (rightTop - leftTop) * horizontalRatio;
            var br = rightBottom - (rightBottom - leftBottom) * horizontalRatio;
            var bl = leftBottom - (leftBottom - leftTop) * verticalRatio;
            br -= (br - tr) * verticalRatio;

            _guiBuffer.AddRectangle(rect2, leftTop, tr, br, bl, materialHandle, DrawColor);
        }

        public override Vector2 MeasureText(Font font, string text) 
        {
            return TextRenderer.MeasureText(text,font);
        }

        public override void RenderText(Font font, Vector2i position, string text)
        {
            //position = Translate(position);
            //TextRenderer.DrawText(_guiBuffer, font, new Vector2(position.X, position.Y), text, DrawColor);

            TextRenderer.DrawText(this, font, new Vector2(position.X, position.Y), text, DrawColor);
        }

        public override Color PixelColor(ResourceHandle<Image> imageHandle, uint x, uint y, Color defaultColor)
        {
            var image = imageHandle.Resolve();
            if(image == null || image.Width == 0)
                return defaultColor;

            var offset = (int)(4 * (x + y * image.Width));
            var data = image.Buffer;

            var pixel = new Color(data[offset + 0],
                data[offset + 1], data[offset + 2], data[offset + 3]);
        
            return pixel;
        }

    };

    public sealed class GwenInput : IDisposable
    {
        readonly InputManager inputManager;
        readonly Mouse mouse;
        readonly Keyboard keyboard;

        Canvas canvas;

        int mouseX;
        int mouseY;

        bool m_AltGr;

        public GwenInput(InputManager inputManager)
        {
            this.inputManager = inputManager;
            
            canvas = null;
            mouseX = 0;
            mouseY = 0;
            m_AltGr = false;

            mouse = inputManager.Mouse;
            if (mouse != null)
            {
                mouse.MouseMove += ProcessMouseMove;
                mouse.MouseDrag += ProcessMouseDrag;
                mouse.MouseButtonPress += ProcessMouseButtonPressed;
                mouse.MouseButtonRelease += ProcessMouseButtonReleased;
                mouse.MouseWheelMove += ProcessMouseWheel;
            }

            keyboard = inputManager.Keyboard;
            if (keyboard != null)
            {
                keyboard.KeyPress += ProcessKeyDown;
                keyboard.KeyRelease += ProcessKeyUp;
                keyboard.KeyText += ProcessText;
            }
        }

        ~GwenInput()
        {
            
        }

        public void Dispose()
        {
            Log.Info("Disposing GwenInput");

            if (mouse != null)
            {
                mouse.MouseMove -= ProcessMouseMove;
                mouse.MouseDrag -= ProcessMouseDrag;
                mouse.MouseButtonPress -= ProcessMouseButtonPressed;
                mouse.MouseButtonRelease -= ProcessMouseButtonReleased;
                mouse.MouseWheelMove -= ProcessMouseWheel;
            }

            if (keyboard != null)
            {
                keyboard.KeyPress -= ProcessKeyDown;
                keyboard.KeyRelease -= ProcessKeyUp;
                keyboard.KeyText -= ProcessText;
            }

            GC.SuppressFinalize(this);
        }

        public void Initialize(Canvas c)
        {
            canvas = c;
        }

        static char TranslateChar(Keys key)
        {
            if (key >= Keys.A && key <= Keys.Z)
                return (char)('a' + ((int)key - (int) Keys.A));
            return ' ';
        }

        void ProcessMouseMove(MouseMoveEvent mouseMoveEvent)
        {
            var dx = mouseMoveEvent.X - mouseX;
            var dy = mouseMoveEvent.Y - mouseY;

            mouseX = mouseMoveEvent.X;
            mouseY = mouseMoveEvent.Y;

            canvas.Input_MouseMoved(mouseX, mouseY, dx, dy);
        }

        void ProcessMouseDrag(MouseDragEvent mouseDragEvent)
        {
            int dx = mouseDragEvent.X - mouseX;
            int dy = mouseDragEvent.Y - mouseY;

            mouseX = mouseDragEvent.X;
            mouseY = mouseDragEvent.Y;

            canvas.Input_MouseMoved(mouseX, mouseY, dx, dy);
        }

        void ProcessMouseButtonPressed(MouseButtonEvent mouseButtonEvent)
        {
            canvas.Input_MouseButton((int) mouseButtonEvent.Button, true);
        }

        void ProcessMouseButtonReleased(MouseButtonEvent mouseButtonEvent)
        {
            canvas.Input_MouseButton((int) mouseButtonEvent.Button, false);
        }

        void ProcessMouseWheel(MouseWheelEvent mouseWheelEvent)
        {
            canvas.Input_MouseWheel(mouseWheelEvent.Delta*60);
        }

        void ProcessKeyDown(KeyEvent keyEvent)
        {
            var ch = TranslateChar(keyEvent.KeyCode);

            if (InputHandler.DoSpecialKeys(canvas, ch))
                return;
        
            canvas.Input_Key(keyEvent.KeyCode, true);
        }

        void ProcessKeyUp(KeyEvent keyEvent)
        {
            canvas.Input_Key(keyEvent.KeyCode, false);
        }

        void ProcessText(KeyEvent keyEvent)
        {
            var ch =  (char)keyEvent.Unicode;
            canvas.Input_Character(ch);
        }
    }
}