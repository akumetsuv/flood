/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include "vapor/input/Device.h"
#include "vapor/input/Keyboard.h"
#include "vapor/input/Mouse.h"
#include "vapor/input/Joystick.h"

namespace vapor {

//-----------------------------------//

/**
 * Manages a set of input devices.
 */

class VAPOR_API InputManager : private boost::noncopyable
{
public:

	virtual ~InputManager();

	// Adds a new device that will be managed by this class.
	void addDevice( Device* );
	
	// Gets a vector with all the known input devices.
	const std::vector< Device* >& getDevices() const;

	// Gets a keyboard device if it exists, nullptr otherwise.
	Keyboard* getKeyboard() const;
	
	// Gets a mouse device if it exists, nullptr otherwise.
	Mouse* getMouse() const;

	// Feeds an external input event to the input manager.
	// The input will be processed to all the devices and
	// each device will only process the ones they want.
	void processEvent( const Event& event );

private:

	// Holds all the input devices.
	std::vector< Device* > devices;
};

//-----------------------------------//

} // end namespace