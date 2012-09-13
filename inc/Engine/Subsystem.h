/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

NAMESPACE_CORE_BEGIN

//-----------------------------------//

/**
 * Subsystems are managed by the engine. They are updated once in a while
 * (the subsystem can control the update rate) and are used mostly to 
 * implement the main services provided by the engine.
 */

class API_CORE NO_VTABLE Subsystem
{
	DECLARE_UNCOPYABLE(Subsystem)

public:

	virtual ~Subsystem() { }
	virtual void update() { }

protected:

	Subsystem() { }
};

//-----------------------------------//

NAMESPACE_CORE_END