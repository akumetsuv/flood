/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

class EditorFrame;

class ResourcesPage : public wxTreeCtrl 
{
public:

	ResourcesPage( wxWindow* parent, wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize );

	~ResourcesPage();

	// Gets the resource associated with the tree item.
	ResourceHandle getResourceFromTreeId( wxTreeItemId id );

	// Synchronizes the tree with the resources.
	void updateTree();

	// Adds a new resource to the tree.
	wxTreeItemId addResource(const ResourceHandle& res);

protected:

	void initControl();
	void initIcons();

	void onItemChanged( wxTreeEvent& event );
	void onTreeItemMenu(wxTreeEvent& event);
	void onCommandMenuSelected( wxCommandEvent& event );

	// Resource-monitoring callbacks.
	void onResourcePrepared( const ResourceEvent& event );
	void onResourceRemoved( const ResourceEvent& event );
	void onResourceReloaded( const ResourceEvent& event );

	wxImageList* imageList;
	wxTreeItemId rootId;
	wxTreeItemId menuItemId;

	typedef std::map< Resource*, wxTreeItemId > ResourceIdsMap;
	ResourceIdsMap resourceIds;

	typedef std::map< ResourceGroup, wxTreeItemId > ResourceGroupIdsMap;
	ResourceGroupIdsMap resGroupIds;
	
	typedef std::map< ResourceGroup, int > ResourceGroupIconsMap;
	ResourceGroupIconsMap resGroupIcons;
};

//-----------------------------------//

NAMESPACE_EDITOR_END