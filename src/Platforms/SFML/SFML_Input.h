/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#define ENABLE_INPUT_SFML

#ifdef ENABLE_INPUT_SFML

#include "Engine/Input/InputManager.h"
#include "Engine/Input/Keyboard.h"

#include <SFML/Window.hpp>

NAMESPACE_GAMERUNTIME_BEGIN

//-----------------------------------//

class API_GAMERUNTIME SFML_Input : public InputManager
{
public:

	SFML_Input();

	// Processes a SMFL input events.
	void processSFMLEvent( const sf::Event& event );
	void processMouseEvent(const sf::Event& event);
	void processKeyboardEvent(const sf::Event& event);
	void processJoystickEvent(const sf::Event& event);
};

//-----------------------------------//

NAMESPACE_GAMERUNTIME_END

#endif