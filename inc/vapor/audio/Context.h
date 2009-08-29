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

#include "vapor/audio/Device.h"
#include "vapor/math/Vector3.h"

namespace vapor {
	namespace audio {

//-----------------------------------//

/**
 * Wraps an OpenAL context in a class. A context in OpenAL is like a context 
 * in OpenGL, in that it's properties are independent of of other contexts. 
 * Each listener in the scene graph will match a context in the audio device, 
 * so that we can play sounds from  different positions without changing 
 * everything in a context.
 *
 * TODO: check that switching contexts is faster than switching everything all
 * the settings of a context.
 */

class Context
{
	friend class Source;

public:
  
	// Set the global volume of this context.
	void setVolume( float volume );

	// Make this the current context in the audio device.
	void makeCurrent();

	// Sets the listener position
	void setListener(const math::Vector3& position);

protected:

	Context(audio::Device* device);
	virtual ~Context();

	// Creates a new OpenAL context
	ALCcontext* createContext();

	// Checks if the last operation was successful
	bool checkError();	

	// Returns a string representation of an OpenAL context error
	const std::string getError();

	// Audio device
	audio::Device* device;

	// Holds an OpenAL context
	ALCcontext* context;

	// Holds the last OpenAL error code
	int error;
};

//-----------------------------------//

} } // end namespaces

#endif