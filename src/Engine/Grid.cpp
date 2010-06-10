/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#include "vapor/PCH.h"
#include "vapor/scene/Grid.h"

namespace vapor {

//-----------------------------------//

const std::string& Grid::type = "Grid";

//-----------------------------------//

Grid::Grid( /*const MaterialPtr&*/ )
	: sizeX( 500 ), sizeZ( 500 ), divX( 20 ), divZ( 20 ), 
	strongMainLines( true )
{
	RenderablePtr rend( new Renderable( Primitive::Lines, getGridBuffer() ) );
	
	MaterialPtr mat( new Material( "Grid" ) );
	rend->setMaterial( mat );

	addRenderable( rend );
}

//-----------------------------------//

VertexBufferPtr Grid::getGridBuffer()
{
	// Create a new VBO and upload triangle data
	VertexBufferPtr vb( new VertexBuffer() );

	// Vertex position data
	std::vector< Vector3 > vertex;

	// Vertex color data
	std::vector< Vector3 > colors;
	
	// Let's make the lines perpendicular to the X-axis.
	float x_pos = -sizeX / 2;
	float z_pos = -sizeZ / 2;	
	
	for( int i = 0; i < divX+1; i++ )
	{
		vertex.push_back( Vector3( x_pos, 0.0f, z_pos ) );
		vertex.push_back( Vector3( -x_pos, 0.0f, z_pos ) );

		if( strongMainLines && (i % 5 == 0) 
			&& (i != 0) && (i != divX) )
		{
			colors.push_back( Vector3( 0.9f, 0.9f, 0.9f ) );
			colors.push_back( Vector3( 0.9f, 0.9f, 0.9f ) );
		}
		else
		{
			colors.push_back( Vector3( 0.4f, 0.4f, 0.4f ) );
			colors.push_back( Vector3( 0.4f, 0.4f, 0.4f ) );
		}

		z_pos += sizeZ / (float)divZ;
	}

	// Now the lines perpendicular to the Z-axis.
	x_pos = -sizeX / 2;
	z_pos = -sizeZ / 2;	
	
	for( int i = 0; i < divZ+1; i++ )
	{
		vertex.push_back( Vector3( x_pos, 0.0f, z_pos ) );
		vertex.push_back( Vector3( x_pos, 0.0f, -z_pos ) );

		if( strongMainLines && (i % 5 == 0)
			&& (i != 0) && (i != divX) )
		{
			colors.push_back( Vector3( 0.9f, 0.9f, 0.9f ) );
			colors.push_back( Vector3( 0.9f, 0.9f, 0.9f ) );
		}
		else
		{
			colors.push_back( Vector3( 0.4f, 0.4f, 0.4f ) );
			colors.push_back( Vector3( 0.4f, 0.4f, 0.4f ) );
		}

		x_pos += sizeX / divX;
	}

	// Vertex buffer setup
	vb->set( VertexAttribute::Position, vertex );
	vb->set( VertexAttribute::Color, colors );

	return vb;
}

//-----------------------------------//

} // end namespace