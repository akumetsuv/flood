/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include "script/Script.h"

NAMESPACE_ENGINE_BEGIN

//-----------------------------------//

class Engine;

/**
 * Scripting context that can be used to execute scripts. 
 * Currently this represents a Lua interpreter state. 
 */

class API_ENGINE State
{
	DECLARE_UNCOPYABLE(State)

public:

	// Constructs a new scripting VM.
	State();
	
	// Destructs this scripting VM.
	~State();

	// Loads a script resource.
	bool load( Script* script );

	// Executes a piece of source code.
	bool execute( const String& source );

	// Executes a script resource.
	bool execute( Script* script );

	// Invokes a function in the state.
	bool invoke( const String& name, uint8 numArguments );

	// Handles the Lua error states.
	void handleError();

	// Gets the last error.
	GETTER(LastError, const String&, lastError)

protected:

	// Last error.
	String lastError;
};

//-----------------------------------//

NAMESPACE_ENGINE_END