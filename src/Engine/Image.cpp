/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#include "vapor/PCH.h"
#include "vapor/resources/Image.h"

namespace vapor { namespace resources {

//-----------------------------------//

namespace PixelFormat
{
	const std::string getString(Enum e) 
	{
		switch(e) 
		{
		case R8G8B8A8:
			return "R8G8B8A8";
		case R8G8B8:
			return "R8G8B8";
		default:
			return "(Unknown)";
		}
	}
}

//-----------------------------------//

void Image::log() const
{
	info("Image", "Image has pixel format '%s' and size %dx%d", 
		PixelFormat::getString(getPixelFormat()).c_str(), 
		getWidth(), getHeight());
}

//-----------------------------------//

} } // end namespaces