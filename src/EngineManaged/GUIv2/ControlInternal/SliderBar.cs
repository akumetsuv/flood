﻿using Flood.GUIv2.Controls;

namespace Flood.GUIv2.ControlInternal
{
    /// <summary>
    /// Slider bar.
    /// </summary>
    public class SliderBar : Dragger
    {
        private bool m_bHorizontal;

        /// <summary>
        /// Indicates whether the bar is horizontal.
        /// </summary>
        public bool IsHorizontal { get { return m_bHorizontal; } set { m_bHorizontal = value; } }

        /// <summary>
        /// Initializes a new instance of the <see cref="SliderBar"/> class.
        /// </summary>
        /// <param name="parent">Parent control.</param>
        public SliderBar(Control parent)
        {
            Target = this;
            RestrictToParent = true;
        }

        /// <summary>
        /// Renders the control using specified skin.
        /// </summary>
        /// <param name="skin">Skin to use.</param>
        public override void Render(Skins.Skin skin)
        {
            skin.DrawSliderButton(this, IsHeld, IsHorizontal);
        }
    }
}
