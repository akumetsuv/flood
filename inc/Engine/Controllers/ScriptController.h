/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "Engine/Controllers/Controller.h"
#include "Script/Script.h"

NAMESPACE_ENGINE_BEGIN

//-----------------------------------//

class ScriptState;
struct KeyEvent;
struct MouseButtonEvent;

/**
 * Script that can be executed by a script state.
 */

API_ENGINE REFLECT_DECLARE_CLASS(ScriptController)

class API_ENGINE ScriptController : public Controller
{
	REFLECT_DECLARE_OBJECT(ScriptController)

public:

	ScriptController();
	~ScriptController();

	// Updates the script.
	virtual void _update( float delta );

protected:

	// Creates a new state.
	void createState();

	// Gets the script by its name.
	ScriptHandle getScript();

	// Input callback functions.
	virtual void onKeyPress( const KeyEvent& );
	virtual void onKeyRelease( const KeyEvent& );
	virtual void onMouseButtonPressed( const MouseButtonEvent& );
	virtual void onMouseButtonReleased( const MouseButtonEvent& );

	// Source code of the script.
	ScriptHandle script;

	// Scripting state.
	ScriptState* state;
};

TYPEDEF_INTRUSIVE_POINTER_FROM_TYPE( Script );

//-----------------------------------//

NAMESPACE_ENGINE_END