﻿
using System;

namespace Flood.GUIv2.Controls
{
    /// <summary>
    /// Group box (container).
    /// </summary>
    /// <remarks>Don't use autosize with docking.</remarks>
    public class GroupBox : Label
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="GroupBox"/> class.
        /// </summary>
        /// <param name="parent">Parent control.</param>
        public GroupBox(Control parent)
        {
            throw new NotImplementedException();
            //// Set to true, because it's likely that our  
            //// children will want mouse input, and they
            //// can't get it without us..
            //MouseInputEnabled = true;
            //KeyboardInputEnabled = true;

            //TextMargin = new Padding(10, 0, 10, 0);
            //TextAlignment = Pos.Top | Pos.Left;
            //Invalidate();

            //m_InnerPanel = new Control(this);
            //m_InnerPanel.Dock = Pos.Fill;
            //m_InnerPanel.Margin = new Margin(5, TextHeight+5, 5, 5);
            ////Margin = new Margin(5, 5, 5, 5);
        }

        /// <summary>
        /// Lays out the control's interior according to alignment, padding, dock etc.
        /// </summary>
        /// <param name="skin">Skin to use.</param>
        public override void PreLayout(Skins.Skin skin)
        {
            throw new NotImplementedException();

            base.PreLayout(skin);
            if (AutoSizeToContents)
            {
                DoSizeToContents();
            }
        }

        /// <summary>
        /// Renders the control using specified skin.
        /// </summary>
        /// <param name="skin">Skin to use.</param>
        //public override void Render(Skins.Skin skin)
        //{
        //    throw new NotImplementedException();

        //    skin.DrawGroupBox(this, TextX, TextHeight, TextWidth);
        //}

        /// <summary>
        /// Sizes to contents.
        /// </summary>
        public override void SizeToContents()
        {
            // we inherit from Label and shouldn't use its method.
            DoSizeToContents();
        }

        protected virtual void DoSizeToContents()
        {
            throw new NotImplementedException();
            //m_InnerPanel.SizeToChildren();
            //SizeToChildren();
            //if (Width < TextWidth + TextMargin.Right + TextMargin.Left)
            //    Width = TextWidth + TextMargin.Right + TextMargin.Left;
        }
    }
}