/************************************************************************
*
* vaporEngine (2008-2009)
*
*	<http://www.portugal-a-programar.org>
*
************************************************************************/

#pragma once

#include "vapor/Platform.h"

#include "vapor/input/Device.h"

#include "vapor/input/Keyboard.h"
#include "vapor/input/Mouse.h"
#include "vapor/input/Joystick.h"

namespace vapor {
	namespace input {

//-----------------------------------//

/**
 * Manages a set of input devices.
 */

class InputManager
{
public:

	InputManager();
	virtual ~InputManager();

	// Adds a new device that will be managed by this class.
	void addDevice( input::Device* );
	
	// Gets a vector with all the known input devices.
	const std::vector< input::Device* >& getDevices();

	// Gets a keyboard device if it exists, nullptr otherwise.
	Keyboard* getKeyboard();
	
	// Gets a mouse device if it exists, nullptr otherwise.
	Mouse* getMouse();

	// Feeds an external input event to the input manager.
	// The input will be processed to all the devices and
	// each device will only process the ones they want.
	void processEvent( const input::Event& event );

private:

	//std::vector< const Event& > events;

	std::vector< input::Device* > devices;
};

//-----------------------------------//

} } // end namespaces