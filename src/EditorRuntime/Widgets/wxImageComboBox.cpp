/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "Editor/API.h"
#include "wxImageComboBox.h"

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

wxImageComboBox::wxImageComboBox( wxWindow* parent, wxWindowID id )
	: wxOwnerDrawnComboBox( parent, id, wxEmptyString, wxDefaultPosition, 
	wxSize(-1, -1), 0, nullptr, wxCC_STD_BUTTON/*|wxCB_READONLY*/ )
{
	SetCustomPaintWidth( 150 );
	GetTextCtrl()->Disable();
}

//-----------------------------------//

void wxImageComboBox::addImage( const ImageHandle& handle )
{
	Image* image = handle.Resolve();
	Append( image->getPath() );
	images.push_back(handle);
}

//-----------------------------------//

wxBitmap* ConvertImageToBitmap( Image* image, const Path& fullPath )
{
	if( !image || !image->isLoaded() )
		return nullptr;

	PixelFormat pf = image->getPixelFormat();
	
	if( pf != PixelFormat::R8G8B8A8 )
	{
		LogDebug("Invalid image format: %s", EnumGetValueName(ReflectionGetType(PixelFormat), (int32)pf));
		return nullptr;
	}

	//wxBitmap* bmp = new wxBitmap;
	//bmp->Create(&image->getBuffer(), wxBITMAP_TYPE_ANY, image->getWidth(), image->getHeight(), 4);

	Stream* stream = StreamCreateFromFile(AllocatorGetHeap(), fullPath, StreamOpenMode::Read);
	if( !stream ) return nullptr;
	
	std::vector<byte> data;
	StreamRead(stream, data);

	wxMemoryInputStream mem(&data[0], data.size());
	wxImage img(mem);
	img.Rescale(32, 32);

	StreamDestroy(stream);

#if 0
	const wxSize& size = GetSize();
	if( img.GetWidth() > size.GetWidth() || img.GetHeight() > size.GetHeight() )
	{
		img.Rescale( size.GetWidth(), size.GetHeight() );
	}
#endif

	wxBitmap* bmp = new wxBitmap(img);
	return bmp;
}

//-----------------------------------//

void wxImageComboBox::OnDrawBackground (wxDC &dc, const wxRect &rect, int item, int flags) const
{
	if ( item == wxNOT_FOUND ) return;

	const ImageHandle& image = images[item];
	
	wxBitmap* bmp = ConvertImageToBitmap( image.Resolve(), "" );
	if( !bmp ) return;

	dc.DrawBitmap( *bmp, rect.GetTopLeft() );
	
	if( flags & wxODCB_PAINTING_SELECTED )
		dc.DrawRectangle( rect );

	delete bmp;
}

//-----------------------------------//

void wxImageComboBox::OnDrawItem (wxDC &dc, const wxRect &rect, int item, int flags) const
{
	if ( item == wxNOT_FOUND ) return;

	const ImageHandle& image = images[item];

	wxBitmap* bmp = ConvertImageToBitmap( image.Resolve(), "" );
	if( !bmp ) return;

	dc.DrawBitmap( *bmp, rect.GetTopLeft() );

	delete bmp;
}

//-----------------------------------//

wxCoord	wxImageComboBox::OnMeasureItem (size_t item) const
{
	Image* image = images[item].Resolve();
	return image->getHeight();
}

//-----------------------------------//

wxCoord	wxImageComboBox::OnMeasureItemWidth (size_t item) const
{
	Image* image = images[item].Resolve();
	return image->getWidth();
}

//-----------------------------------//

NAMESPACE_EDITOR_END