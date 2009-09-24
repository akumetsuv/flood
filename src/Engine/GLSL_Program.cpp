/************************************************************************
*
* vaporEngine (2008-2009)
*
*	<http://www.portugal-a-programar.org>
*
************************************************************************/

#include "vapor/PCH.h"

#ifdef VAPOR_SHADER_GLSL

#include "vapor/render/GLSL_Program.h"

#include "vapor/render/GL.h"

using namespace vapor::resources;

namespace vapor {
	namespace render {

//-----------------------------------//

GLSL_Program::GLSL_Program( GLSL_ShaderPtr vs, GLSL_ShaderPtr ps )
	: Program( vs, ps )
{
	id = glCreateProgram( );

#ifdef VAPOR_DEBUG
	if( glGetError() != GL_NO_ERROR )
	{
		warn( "glsl", "Could not create a new program object" );
		return;
	}
#endif

	shaders.push_back( vs );
	shaders.push_back( ps );
}

//-----------------------------------//

GLSL_Program::~GLSL_Program()
{
	// Detach shaders
	foreach( GLSL_ShaderPtr shader, shaders )
	{
		glDetachShader( id, shader->id() );

		#ifdef VAPOR_DEBUG
			if( glGetError() != GL_NO_ERROR )
			{
				warn( "glsl", "Could not detach shader object '%d'", shader->id() );
				return;
			}
		#endif
	}

	glDeleteProgram( id );

#ifdef VAPOR_DEBUG
	if( glGetError() != GL_NO_ERROR )
	{
		warn( "glsl", "Could not delete program object '%d'", id );
		return;
	}
#endif
}

//-----------------------------------//

void GLSL_Program::addAttribute( const std::string& name, VertexAttribute::Enum attr )
{
	glBindAttribLocation( id, attr, name.c_str() );

#ifdef VAPOR_DEBUG
	if( glGetError() != GL_NO_ERROR )
	{
		warn( "glsl", "Could not bind attribute variable in program object '%d'", id );
	}
#endif
}

//-----------------------------------//

void GLSL_Program::addUniform( const std::string& slot, std::vector< float > data )
{

}

//-----------------------------------//

bool GLSL_Program::link()
{
	// If the program is already linked, return.
	if( linked ) return true;

	// Make sure all shaders are compiled
	foreach( GLSL_ShaderPtr shader, shaders )
	{
		if( !shader->isCompiled() )
		{
			if( !shader->compile() )
			{
				linked = false;
				return false;
			}
		}

		// Shaders need to be attached to the program
		glAttachShader( id, shader->id() );
	}

	bindDefaultAttributes();

	glLinkProgram( id );

	// Check that the linking was good
#ifdef VAPOR_DEBUG
	if( glGetError() != GL_NO_ERROR )
	{
		warn( "glsl", "Could not link program object '%d'", id );
		linked = false;
		return false;
	}
#endif

	getGLSLLog();

	int status;
	glGetProgramiv( id, GL_LINK_STATUS, &status );

	if( status != GL_TRUE )
	{
		warn( "glsl", "Could not link program object '%d'", id );
		linked = false;
		return false;
	}

	linked = true;
	return true;
}

//-----------------------------------//

void GLSL_Program::bind()
{
	glUseProgram( id );

#ifdef VAPOR_DEBUG
	if( glGetError() != GL_NO_ERROR )
	{
		warn( "glsl", "Could not bind program object '%d'", id );
		return;
	}
#endif	
}

//-----------------------------------//

void GLSL_Program::unbind()
{
	glUseProgram( 0 );

#ifdef VAPOR_DEBUG
	if( glGetError() != GL_NO_ERROR )
	{
		warn( "glsl", "Could not bind program object '%d'", id );
		return;
	}
#endif	
}

//-----------------------------------//

void GLSL_Program::getGLSLLog()
{
	// get linking log size
	GLint size;
	glGetProgramiv( id, GL_INFO_LOG_LENGTH, &size );

	if( size == 0 )
	{
		log = "Program linked with success";
		return;
	}

	// TODO: move directly to string...

	GLchar* info = new char[size];
	GLsizei length;

	glGetProgramInfoLog( id, size, &length, info );

	log.assign( info );

	delete info;
}

//-----------------------------------//

void GLSL_Program::bindDefaultAttributes()
{
	addAttribute( "vp_Vertex", VertexAttribute::Vertex );
	addAttribute( "vp_Color", VertexAttribute::Color );
}

//-----------------------------------//

//uint GLSL_Program::id()
//{
//	return id;
//}

//-----------------------------------//

} } // end namespaces

#endif