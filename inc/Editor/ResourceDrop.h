/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

class ResourceDropTarget : public wxDropTarget
{
public:

	ResourceDropTarget(EditorFrame* frame);
	wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def);

protected:

	wxTextDataObject* data;
	EditorFrame* frame;
};

//-----------------------------------//

ResourceDropTarget::ResourceDropTarget(EditorFrame* frame)
	: frame(frame)
{
	data = new wxTextDataObject();
	SetDataObject(data);
}

//-----------------------------------//

wxDragResult ResourceDropTarget::OnData(wxCoord x, wxCoord y, wxDragResult def)
{
	Vector2 coords(x, y);
	frame->setDropCoords(coords);

	return def;
}

//-----------------------------------//

NAMESPACE_EDITOR_END