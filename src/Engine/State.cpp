/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Engine/API.h"
#include "Script/State.h"

NAMESPACE_ENGINE_BEGIN

//-----------------------------------//

State::State()
{
}

//-----------------------------------//

State::~State()
{
}

//-----------------------------------//

bool State::load(Script* script)
{
	if( !script ) return false;

	return true;
}

//-----------------------------------//

bool State::execute( Script* script )
{
	return execute( script->getSource() );
}

//-----------------------------------//

bool State::execute( const String& source )
{
	return true;
}

//-----------------------------------//

bool State::invoke( const String& name, uint8 numArguments )
{
	return true;
}

//-----------------------------------//

void State::handleError()
{
}

//-----------------------------------//

NAMESPACE_ENGINE_END