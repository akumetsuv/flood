/************************************************************************
*
* vaporEngine (2008-2009)
*
*	<http://www.portugal-a-programar.org>
*
************************************************************************/

#pragma once

#include <vapor/Platform.h>
#include <vapor/Engine.h>

namespace vapor {

 /**
 * Simple framework to facilitate the use of the engine functionality in
 * applications. It asks for a rendering device to use, and has some 
 * virtual methods used to setup all the needed resources. Applications 
 * can just derive from this class and setup the needed stuff, call the 
 * run() method and everything should automagically work.
 */

class Framework : protected Engine
{
public:

	Framework(const std::string app);
	virtual ~Framework();

	// Kickstart the framework in action.
	void run();

protected:

	// Called once when the app starts.
	virtual void onInit() = 0;

	// Sets up all the needed resources.
	virtual void onSetupResources() = 0;

	// Sets up all the scene nodes.
	virtual void onSetupScene() = 0;

	// Updates the scene (called once per frame).
	virtual void onUpdate() = 0;

	// Renders the scene (called once per frame).
	virtual void onRender() = 0;

private:

	// Initializes the engine.
	virtual void init();

	// Main rendering loop ( calls onRender() ).
	virtual void render();
};

} // end namespace		
