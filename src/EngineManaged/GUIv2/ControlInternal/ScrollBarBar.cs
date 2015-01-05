﻿using Flood.GUIv2.Controls;

namespace Flood.GUIv2.ControlInternal
{
    /// <summary>
    /// Scrollbar bar.
    /// </summary>
    public class ScrollBarBar : Dragger
    {
        private bool m_Horizontal;

        /// <summary>
        /// Indicates whether the bar is horizontal.
        /// </summary>
        public bool IsHorizontal { get { return m_Horizontal; } set { m_Horizontal = value; } }

        /// <summary>
        /// Indicates whether the bar is vertical.
        /// </summary>
        public bool IsVertical { get { return !m_Horizontal; } set { m_Horizontal = !value; } }

        /// <summary>
        /// Initializes a new instance of the <see cref="ScrollBarBar"/> class.
        /// </summary>
        /// <param name="parent">Parent control.</param>
        public ScrollBarBar(Control parent)
        {
            RestrictToParent = true;
            Target = this;
        }

        /// <summary>
        /// Renders the control using specified skin.
        /// </summary>
        /// <param name="skin">Skin to use.</param>
        public override void Render(Skins.Skin skin)
        {
            skin.DrawScrollBarBar(this, m_Held, IsHovered, m_Horizontal);
            base.Render(skin);
        }

        /// <summary>
        /// Handler invoked on mouse moved event.
        /// </summary>
        /// <param name="x">X coordinate.</param>
        /// <param name="y">Y coordinate.</param>
        /// <param name="dx">X change.</param>
        /// <param name="dy">Y change.</param>
        public override void OnMouseMoved(int x, int y, int dx, int dy)
        {
            base.OnMouseMoved(x, y, dx, dy);
            if (!m_Held)
                return;

            InvalidateParent();
        }

        /// <summary>
        /// Handler invoked on mouse click (left) event.
        /// </summary>
        /// <param name="x">X coordinate.</param>
        /// <param name="y">Y coordinate.</param>
        /// <param name="down">If set to <c>true</c> mouse button is down.</param>
        public override void OnMouseClickedLeft(int x, int y, bool down)
        {
            base.OnMouseClickedLeft(x, y, down);
            InvalidateParent();
        }

        ///// <summary>
        ///// Lays out the control's interior according to alignment, padding, dock etc.
        ///// </summary>
        ///// <param name="skin">Skin to use.</param>
        //public override void Layout(Skins.Skin skin)
        //{
        //    if (null == Parent)
        //        return;

        //    //Move to our current position to force clamping - is this a hack?
        //    MoveTo(X, Y);
        //}
    }
}