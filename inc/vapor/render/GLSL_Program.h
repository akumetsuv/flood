/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include "Render/Program.h"
#include "Render/VertexBuffer.h"
#include "Render/GLSL_Shader.h"
#include "Render/GL.h"

FWD_DECL_INTRUSIVE(GLSL_Text)

namespace vapor {

//-----------------------------------//
		
/**
 * GLSL Program.
 */

class VAPOR_API GLSL_Program : public Program
{
public:

	GLSL_Program( const GLSL_TextPtr& );
	virtual ~GLSL_Program();

	// Creates the program.
	virtual bool create();

	// Links the program.
	virtual bool link();

	// Binds the program.
	virtual void bind();

	// Unbinds the program.
	virtual void unbind();

	// Creates the shaders and adds them to the program.
	virtual void createShaders();

	// Updates the shader's text with the program text.
	virtual void updateShadersText();

	// Gets/sets the resource text that backs this shader.
	ACESSOR(Text, const GLSL_TextPtr&, text)

	// Adds a parameter to the shader.
	virtual void setAttribute( const String& slot, VertexAttribute::Enum attr );

	// Adds a uniform to the shader.
	virtual void setUniform( const String& slot, int data );

	// Adds a named float uniform to the program.
	virtual void setUniform( const String& slot, float value );

	// Adds a named float array uniform to the program.
	//virtual void setUniform( const String& slot, const std::vector<float> vec ) = 0;

	// Adds a named Vector3 array uniform to the program.
	virtual void setUniform( const String& slot, const std::vector<Vector3>& vec );

	// Adds a named color array uniform to the program.
	virtual void setUniform( const String& slot, const std::vector<Color>& vec );

	// Adds a named vector uniform to the program.
	virtual void setUniform( const String& slot, const Vector3& vec );

	// Adds a named angles vector uniform to the program.
	virtual void setUniform( const String& slot, const EulerAngles& vec );

	// Adds a named matrix uniform to the program.
	virtual void setUniform( const String& slot, const Matrix4x3& );

	// Adds a named 4x4 matrix uniform to the program.
	virtual void setUniform( const String& slot, const Matrix4x4& );

	// Adds a named 4x4 matrix vector uniform to the program.
	virtual void setUniform( const String& slot, const std::vector<Matrix4x4>& vec );

protected:

	// Adds a shader to the program.
	void addShader( const GLSL_ShaderPtr& );

	// Binds the default engine attributes to the program.
	void bindDefaultAttributes();

	// Validates that the program is well-formed.
	bool validate();

	// Compiles (if needed) and attaches all shaders to the program.
	bool attachShaders();

	// Gets the linking log of the program.
	void getLogText();

	GLuint id;
	bool linkError;
	GLSL_TextPtr text;

	typedef std::vector< GLSL_ShaderPtr > ShaderVector;
	ShaderVector shaders;

	typedef std::map< GLSL_ShaderPtr, bool > ShaderAttachMap;
	ShaderAttachMap attached;
};

TYPEDEF_INTRUSIVE_POINTER_FROM_TYPE( GLSL_Program );

//-----------------------------------//

} // end namespace