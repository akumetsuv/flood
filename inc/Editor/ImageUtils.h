/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

//-----------------------------------//

#define wxMEMORY_IMAGE( name ) _wxConvertMemoryToImage( name, sizeof( name ) )
#define wxMEMORY_IMAGEEX( name, type ) _wxConvertMemoryToImage( name, sizeof( name ) )
#define wxMEMORY_BITMAP( name ) _wxConvertMemoryToBitmap( name, sizeof( name ) )
#define wxMEMORY_BITMAPEX( name, type ) _wxConvertMemoryToBitmap( name, sizeof( name ) )

//-----------------------------------//

inline wxImage _wxConvertMemoryToImage(const unsigned char* data, int length )
{
	wxMemoryInputStream stream( data, length );
	return wxImage( stream );
}

inline wxBitmap _wxConvertMemoryToBitmap(const unsigned char* data, int length )
{
	wxMemoryInputStream stream( data, length );
	return wxBitmap( wxImage( stream ), -1 );
}

//-----------------------------------//