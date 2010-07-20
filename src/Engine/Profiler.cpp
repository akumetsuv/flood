/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#include "vapor/PCH.h"
#include "vapor/Profiler.h"

namespace vapor {

//-----------------------------------//

Profiler::Profiler(const std::string& name)
	: name(name)
{ }

//-----------------------------------//

Profiler::~Profiler()
{
	double time = timer.getElapsedTime();

	float ms = time * 1000;

	debug( "%s: took %lu ms (%.5lf)",
		name.c_str(), (ulong) ms, ms );
}

//-----------------------------------//

} // end namespace 