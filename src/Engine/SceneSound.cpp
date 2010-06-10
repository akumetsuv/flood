/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#include "vapor/PCH.h"

#ifdef VAPOR_AUDIO_OPENAL

#include "vapor/scene/Sound.h"

namespace vapor {

//-----------------------------------//

Sound::Sound( ListenerPtr ls, SoundPtr sound )
	: Source( Listener::getContext(ls), sound )
{ }


//-----------------------------------//

void Sound::update( double delta )
{

}

//-----------------------------------//

const std::string Sound::save(int indent)
{
	return "";
}

//-----------------------------------//

} // end namespace

#endif