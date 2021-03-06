/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "Engine/Input/Device.h"

NAMESPACE_ENGINE_BEGIN

//-----------------------------------//

struct JoystickID
{
	JoystickID(int, int);
	
	int id;
	int button;
};

/**
 * Different types of joystick axis.
 */

namespace JoystickAxis
{
	enum Enum
	{
		AxisX,
		AxisY,
		AxisZ,
		AxisR,
		AxisU,
		AxisV,
		AxisPOV,
	};
}

/**
 * Different types of joystick events.
 */

namespace JoystickEventType
{
	enum Enum
	{
		JoystickPress,
		JoystickRelease,
		JoystickMove
	};
}

//-----------------------------------//

/**
 * Generic event for joystick actions.
 */

struct JoystickEvent : public InputEvent
{
	friend class Joystick;

	JoystickEvent( JoystickEventType::Enum eventType );

private:

	JoystickEventType::Enum eventType;
};

//-----------------------------------//

/**
 * Event that happens when a joystick is moved.
 */

struct JoyMoveEvent: public JoystickEvent
{
	JoyMoveEvent(uint id, JoystickAxis::Enum axis, float pos);
	
	uint JoystickId;
	JoystickAxis::Enum Axis;
	float Position;
};

//-----------------------------------//

/**
 * Event that happens when a joystick button is pressed or released.
 */

struct JoyButtonEvent: public JoystickEvent
{	
	JoyButtonEvent(uint JoystickId, uint Button, 
		JoystickEventType::Enum eventType);

	uint JoystickId;
	uint Button;
};

//-----------------------------------//

class API_ENGINE Joystick : public InputDevice
{
	// Processes an event (only if it's a joystick event).
	virtual void processEvent( const InputEvent& event );

	// Return this device as a joystick.
	virtual const InputDeviceType::Enum getType();

	// Events

	// Occurs when the joystick is moved.
	Event1< const JoyMoveEvent& > onJoystickMove;
	
	// Occurs when a joystick button is pressed.
	Event1< const JoyButtonEvent& > onJoystickButtonPress;
	
	// Occurs when a joystick button is released.
	Event1< const JoyButtonEvent& > onJoystickButtonRelease;

private:

	// Private event handlers.
	void joyButtonPressed(const JoyButtonEvent& jevt);
	void joyButtonReleased(const JoyButtonEvent& jevt);
	void joyMoved(const JoyMoveEvent& jevt);
};

//-----------------------------------//

NAMESPACE_ENGINE_END