/************************************************************************
*
* vapor3D Engine © (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#include "vapor/PCH.h"
#include "vapor/scene/Skydome.h"
#include "vapor/render/Quad.h"

namespace vapor { namespace scene {

using namespace vapor::math;
using namespace vapor::render;

//-----------------------------------//

const std::string& Skydome::type = "Skydome";

//-----------------------------------//

Skydome::Skydome( const render::MaterialPtr& mat )
{
	generateDome();
	generateSun();
}

//-----------------------------------//

Skydome::~Skydome()
{

}

//-----------------------------------//

void Skydome::generateDome()
{
	dome = new Sphere( false, 2, 1000.0f );

	MaterialPtr matSky( new Material( "SkydomeSimple" ) );
	
	//matSky->setDepthWrite( false );
	matSky->setBackfaceCulling( false );
	matSky->setProgram( "diffuse" );

	dome->setMaterial( matSky );
	dome->setPolygonMode( PolygonMode::Solid );

	setSkyLinearGradient( Colors::SkyBlue, Colors::White );
	//setSkyLinearGradient( Color( 50, 90, 0 ), Colors::Black );
	//setSkyLinearGradient( Color( 65, 75, 75 ), Colors::Black );
	//setSkyLinearGradient( Color( 30, 40, 60 ), Color( 65, 75, 75 ) );

	addRenderable( dome );
}

//-----------------------------------//

math::Vector3 Skydome::getSunPosition()
{
	return Vector3::Zero;
}

//-----------------------------------//

void Skydome::generateSun()
{
	sun = new render::Quad( 100.0f, 100.0f );
	MaterialPtr matSun( new Material( "SunBlend" ) );
	matSun->setProgram( "tex" );
	matSun->setTexture( 0, "sun.png" );
	matSun->setBlending( BlendingOperationSource::SourceAlpha,
		BlendingOperationDestination::OneMinusSourceAlpha );
	matSun->setBackfaceCulling( false );
	sun->setMaterial( matSun );
	addRenderable( sun );

	render::RenderablePtr moon( new render::Quad( 25.0f, 25.0f ) );
	MaterialPtr matMoon( new Material( "MoonBlend" ) );
	matMoon->setProgram( "tex" );
	matMoon->setTexture( 0, "moon.png" );
	matMoon->setBlending( BlendingOperationSource::SourceAlpha,
		BlendingOperationDestination::OneMinusSourceAlpha );
	matMoon->setBackfaceCulling( false );
	moon->setMaterial( matMoon );
	//addRenderable( moon );
}

//-----------------------------------//

void Skydome::setSkyColor( const math::Color& color )
{
	VertexBufferPtr vb = dome->getVertexBuffer();
	uint numVertices = vb->getNumVertices();

	std::vector<Vector3> colors;
	colors.resize( numVertices, Vector3( color.r, color.g, color.b ) );

	vb->set( VertexAttribute::Color, colors );
}

//-----------------------------------//

float Skydome::scale( float number )
{
	const float rMin = 0.0f;
	const float rMax = 1.0f;

	number += abs(yMin);
	return (number / ((yMax) / (rMax - rMin))) + rMin;
}

//-----------------------------------//

void Skydome::setSkyLinearGradient( const math::Color& c1, const math::Color& c2 )
{
	colorBottom = Vector3( c1.r, c1.g, c1.b );
	colorTop = Vector3( c2.r, c2.g, c2.b );

	VertexBufferPtr vb = dome->getVertexBuffer();
	const std::vector<math::Vector3>& vertices = vb->getVertices();

	// Search for the max and min Y coordinate.
	yMin = std::numeric_limits<float>::max();
	yMax = std::numeric_limits<float>::min();

	foreach( const Vector3& vec, vertices )
	{
		if( vec.y > yMax ) 
			yMax = vec.y;
		else if( vec.y < yMin ) 
			yMin = vec.y;
	}

	yMax += abs(yMin);
	//yMin += abs(yMin);

	std::vector<Vector3> colors;
	foreach( const Vector3& vec, vertices )
	{
		Color c = getSkyVertexColor( vec );
		colors.push_back( Vector3( c.r, c.g, c.b ) );
	}	

	vb->set( VertexAttribute::Color, colors );
}

//-----------------------------------//

Color Skydome::getSkyVertexColor( const Vector3& v )
{
	float s = scale( v.y );
	float t = (s <= 0.5f) ? 0.0f : s - 0.5f;

	// Linear interpolate to get the color at the vertex.
	Vector3 newColor = colorBottom + (colorTop - colorBottom) * t;

	return Color( newColor.x, newColor.y, newColor.z );
}

//-----------------------------------//

const std::string& Skydome::getType() const
{
	return type;
}

//-----------------------------------//

} } // end namespaces
