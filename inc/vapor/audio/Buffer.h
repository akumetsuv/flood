/************************************************************************
*
* vaporEngine (2008-2009)
*
*	<http://www.portugal-a-programar.org>
*
************************************************************************/

#pragma once

#include "vapor/CompileOptions.h"

#ifdef VAPOR_AUDIO_OPENAL

#include "vapor/Platform.h"

#include "vapor/resources/Sound.h"
#include "vapor/audio/Device.h"
#include "vapor/audio/Source.h"

namespace vapor {
	namespace audio {

//-----------------------------------//

/**
 * Wraps an OpenAL buffer in a class. A buffer in OpenAL is the object 
 * that contains the audio data. This will hold the id to the data and
 * delete it when no other source needs it.
 *
 * TODO: Streaming audio and maybe have some chaching strategy so it
 * doesn't delete the audio data if it's potentially needed in the future.
 */

class VAPOR_API Buffer : private boost::noncopyable
{
	friend class Source;

public:
	
	Buffer( audio::Device* device, std::shared_ptr<resources::Sound> sound );
	~Buffer();
  
protected:

	// Gets the OpenAL id of this buffer
	ALuint id();

	// Queues the buffer data in the source.
	void upload();

	// Holds a pointer to the audio device.
	audio::Device* device;
	
	// Holds a pointer to the audio data buffer.
	resources::SoundPtr resource;

	// Holds the source id from OpenAL.
	ALuint bufferId;
};

//-----------------------------------//

} } // end namespaces

#endif