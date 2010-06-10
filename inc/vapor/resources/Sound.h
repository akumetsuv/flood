/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include "vapor/resources/Resource.h"
#include "vapor/resources/ResourceManager.h"

namespace vapor {

//-----------------------------------//

/**
 * Represents a sound in the engine. 
 * A sound holds uncompressed audio data that can be played back.
 */

class VAPOR_API Sound : public Resource
{
public:

	Sound();

	/// Gets/sets the frequency of the sound.
	IMPLEMENT_ACESSOR(Frequency, const int, frequency)

	/// Gets/sets the audio channels.
	IMPLEMENT_ACESSOR(Channels, byte, channels)

	/// Gets/sets the buffer containing the data.
	IMPLEMENT_ACESSOR(Buffer, const std::vector<byte>&, dataBuffer)

	/// Return the proper resource group for this resource.
	IMPLEMENT_GETTER(ResourceGroup, ResourceGroup::Enum, ResourceGroup::Audio)

private:

	/// Sound frequency
	int frequency;

	/// Sound channels
	byte channels;

	/// Holds the sound data
	std::vector<byte> dataBuffer;
};

//-----------------------------------//

TYPEDEF_RESOURCE_POINTER_FROM_TYPE( Sound );

//-----------------------------------//

} // end namespace