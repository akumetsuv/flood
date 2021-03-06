/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "EditorPlugin.h"

#ifdef ENABLE_PLUGIN_PROPERTY

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

class PropertyPage;

REFLECT_DECLARE_CLASS(PropertyPlugin)

class PropertyPlugin : public EditorPlugin
{
	REFLECT_DECLARE_OBJECT(PropertyPlugin)

public:

	PropertyPlugin();

	// Gets metadata about this plugin.
	PluginMetadata getMetadata() OVERRIDE;

	// Plugin callbacks.
	void onPluginEnable() OVERRIDE;
	void onPluginDisable() OVERRIDE;
	
	// Resource callbacks.
	void onResourceSelect( const ResourcePtr& ) OVERRIDE;
	void onResourceUnselect( const ResourcePtr& ) OVERRIDE;

	// Updates the properties.
	void updateProperties(const EntityPtr& entity);

	PropertyPage* propertyPage;
};

//-----------------------------------//

NAMESPACE_EDITOR_END

#endif