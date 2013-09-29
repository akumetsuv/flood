﻿using System;
using GUI.Controls;

namespace GUI.ControlInternal
{
    /// <summary>
    /// Properties node.
    /// </summary>
    public class PropertyTreeNode : TreeNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="PropertyTreeNode"/> class.
        /// </summary>
        /// <param name="parent">Parent control.</param>
        public PropertyTreeNode(Control parent)
            : base(parent)
        {
            m_Title.TextColorOverride = Skin.Colors.Properties.Title;
        }

        /// <summary>
        /// Renders the control using specified skin.
        /// </summary>
        /// <param name="skin">Skin to use.</param>
        protected override void Render(Skins.Skin skin)
        {
            skin.DrawPropertyTreeNode(this, m_InnerPanel.X, m_InnerPanel.Y);
        }
    }
}