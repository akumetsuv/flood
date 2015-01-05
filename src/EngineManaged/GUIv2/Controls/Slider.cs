﻿using Flood.GUIv2.ControlInternal;
using Flood.GUIv2.Input;
using System;
using Flood.GUIv2.Panels.Layout;

namespace Flood.GUIv2.Controls
{
    /// <summary>
    /// Base slider.
    /// </summary>
    public class Slider : Control
    {
        protected readonly SliderBar m_SliderBar;
        protected bool m_SnapToNotches;
        protected int m_NotchCount;
        protected float m_Value;
        protected float m_Min;
        protected float m_Max;

        /// <summary>
        /// Number of notches on the slider axis.
        /// </summary>
        public int NotchCount { get { return m_NotchCount; } set { m_NotchCount = value; } }

        /// <summary>
        /// Determines whether the slider should snap to notches.
        /// </summary>
        public bool SnapToNotches { get { return m_SnapToNotches; } set { m_SnapToNotches = value; } }

        /// <summary>
        /// Minimum value.
        /// </summary>
        public float Min { get { return m_Min; } set { SetRange(value, m_Max); } }

        /// <summary>
        /// Maximum value.
        /// </summary>
        public float Max { get { return m_Max; } set { SetRange(m_Min, value); } }

        /// <summary>
        /// Current value.
        /// </summary>
        public float Value
        {
            get { return m_Min + (m_Value * (m_Max - m_Min)); }
            set
            {
                if (value < m_Min) value = m_Min;
                if (value > m_Max) value = m_Max;
                // Normalize Value
                value = (value - m_Min) / (m_Max - m_Min);
                SetValueInternal(value);
                Redraw();
            }
        }

        /// <summary>
        /// Invoked when the value has been changed.
        /// </summary>
        public event GwenEventHandler ValueChanged;

        /// <summary>
        /// Initializes a new instance of the <see cref="Slider"/> class.
        /// </summary>
        /// <param name="parent">Parent control.</param>
        protected Slider(Control parent)
        {
            SetBounds(new Rectangle(0, 0, 32, 128));

            m_SliderBar = new SliderBar(this);
            m_SliderBar.Dragged += OnMoved;

            m_Min = 0.0f;
            m_Max = 1.0f;

            m_SnapToNotches = false;
            m_NotchCount = 5;
            m_Value = 0.0f;

            KeyboardInputEnabled = true;
            IsTabable = true;
        }

        /// <summary>
        /// Handler for Right Arrow keyboard event.
        /// </summary>
        /// <param name="down">Indicates whether the key was pressed or released.</param>
        /// <returns>
        /// True if handled.
        /// </returns>
        public override bool OnKeyRight(bool down)
        {
            throw new NotImplementedException();

            if (down)
                Value = Value + 1;
            return true;
        }

        /// <summary>
        /// Handler for Up Arrow keyboard event.
        /// </summary>
        /// <param name="down">Indicates whether the key was pressed or released.</param>
        /// <returns>
        /// True if handled.
        /// </returns>
        public override bool OnKeyUp(bool down)
        {
            throw new NotImplementedException();

            if (down)
                Value = Value + 1;
            return true;
        }

        /// <summary>
        /// Handler for Left Arrow keyboard event.
        /// </summary>
        /// <param name="down">Indicates whether the key was pressed or released.</param>
        /// <returns>
        /// True if handled.
        /// </returns>
        public override bool OnKeyLeft(bool down)
        {
            throw new NotImplementedException();

            if (down)
                Value = Value - 1;
            return true;
        }

        /// <summary>
        /// Handler for Down Arrow keyboard event.
        /// </summary>
        /// <param name="down">Indicates whether the key was pressed or released.</param>
        /// <returns>
        /// True if handled.
        /// </returns>
        public override bool OnKeyDown(bool down)
        {
            throw new NotImplementedException();

            if (down)
                Value = Value - 1;
            return true;
        }

        /// <summary>
        /// Handler for Home keyboard event.
        /// </summary>
        /// <param name="down">Indicates whether the key was pressed or released.</param>
        /// <returns>
        /// True if handled.
        /// </returns>
        public override bool OnKeyHome(bool down)
        {
            throw new NotImplementedException();

            if (down)
                Value = m_Min;
            return true;
        }

        /// <summary>
        /// Handler for End keyboard event.
        /// </summary>
        /// <param name="down">Indicates whether the key was pressed or released.</param>
        /// <returns>
        /// True if handled.
        /// </returns>
        public override bool OnKeyEnd(bool down)
        {
            throw new NotImplementedException();

            if (down)
                Value = m_Max;
            return true;
        }

        protected virtual void OnMoved(IControl control)
        {
            SetValueInternal(CalculateValue());
        }

        protected virtual float CalculateValue()
        {
            return 0;
        }

        protected virtual void UpdateBarFromValue()
        {
            
        }

        protected virtual void SetValueInternal(float val)
        {
            if (m_SnapToNotches)
            {
                val = (float)Math.Floor((val * m_NotchCount) + 0.5f);
                val /= m_NotchCount;
            }

            if (m_Value != val)
            {
                m_Value = val;
                if (ValueChanged != null)
                    ValueChanged.Invoke(this);
            }

            UpdateBarFromValue();
        }

        /// <summary>
        /// Sets the value range.
        /// </summary>
        /// <param name="min">Minimum value.</param>
        /// <param name="max">Maximum value.</param>
        public void SetRange(float min, float max)
        {
            m_Min = min;
            m_Max = max;
        }

        /// <summary>
        /// Renders the focus overlay.
        /// </summary>
        /// <param name="skin">Skin to use.</param>
        public override void RenderFocus(Skins.Skin skin)
        {
            throw new NotImplementedException();

            if (InputHandler.KeyboardFocus != this) return;
            if (!IsTabable) return;
            
            skin.DrawKeyboardHighlight(this, RenderBounds, 0);
        }
    }
}