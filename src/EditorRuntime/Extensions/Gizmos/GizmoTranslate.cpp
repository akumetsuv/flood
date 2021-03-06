/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Editor/API.h"
#include "GizmoTranslate.h"

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

// Gizmo cone base color.
static const float BASE_FACTOR = 0.5f;

//-----------------------------------//

GizmoTranslate::GizmoTranslate( const EntityPtr& entity, const CameraWeakPtr& camera )
	: Gizmo(entity, camera)
{ }

//-----------------------------------//

void GizmoTranslate::buildGeometry()
{
	lines = generateLines();
	
	RenderablePtr renderable = AllocateHeap(Renderable);
	renderable->setPrimitiveType(PrimitiveType::Lines);
	renderable->setGeometryBuffer(lines);
	renderable->setMaterial(material);

	addRenderable(renderable);

	cones = generateCones();
	
	renderable = AllocateHeap(Renderable);
	renderable->setPrimitiveType(PrimitiveType::Triangles);
	renderable->setGeometryBuffer(cones);
	renderable->setMaterial(material);
	renderable->setRenderLayer(RenderLayer::PostTransparency);
	renderable->setRenderPriority(100);

	addRenderable(renderable);
}

//-----------------------------------//

GizmoAxis::Enum GizmoTranslate::getAxis(Color& pickColor)
{
	if( pickColor.nearEqual(X*BASE_FACTOR) )
		return GizmoAxis::X;
	
	else if( pickColor.nearEqual(Y*BASE_FACTOR) )
		return GizmoAxis::Y;
	
	else if( pickColor.nearEqual(Z*BASE_FACTOR) )
		return GizmoAxis::Z;

	return Gizmo::getAxis(pickColor);
}

//-----------------------------------//

void GizmoTranslate::highlightAxis( GizmoAxis::Enum axis, bool highlight )
{
	uint32 sizeColors = lines->getNumVertices();
	assert( sizeColors == 6 ); // 2 vertices * 3 lines
	
	Color c = (highlight) ? Color::White : getAxisColor(axis);

	uint start = axis*2;

	for( size_t i = start; i < start+2; i++ )
	{
		Vector3* color = (Vector3*) lines->getAttribute( VertexAttribute::Color, i );
		*color = c;
	}

	lines->forceRebuild();
}

//-----------------------------------//

static void TransformVertices(std::vector<Vector3>& pos, std::vector<Vector3>& vs, Matrix4x3& transform)
{
	for( size_t i = 0; i < vs.size(); i++ )
	{
		const Vector3& v = vs[i];
		pos.push_back( transform*v );
	}
}

static const byte SLICES = 10;

GeometryBufferPtr GizmoTranslate::generateCones()
{
	GeometryBufferPtr gb = AllocateHeap(GeometryBuffer);

	// Unit cone vertex data
	std::vector< Vector3 > cone;
	generateSolidCone( 0.05f, 0.2f, SLICES, cone );

	// Vertex data
	std::vector< Vector3 > pos;
	std::vector< Vector3 > colors;

	// We need to transform the unit cone so it is oriented correctly 
	// in the gizmo. A transformation matrix will take care of that.
	Matrix4x3 transform;

	// X axis
	transform = Matrix4x3::createRotation( EulerAngles(0, 0, -90) );
	transform = transform * Matrix4x3::createTranslation( Vector3::UnitX / 2.0f );
	TransformVertices(pos, cone, transform);
	generateColors( colors, X );

	// Y axis
	transform = Matrix4x3::createTranslation( Vector3::UnitY / 2.0f );
	TransformVertices(pos, cone, transform);
	generateColors( colors, Y );

	// Z axis
	transform = Matrix4x3::createRotation( EulerAngles(90, 0, 0) );
	transform = transform * Matrix4x3::createTranslation( Vector3::UnitZ / 2.0f );
	TransformVertices(pos, cone, transform);
	generateColors( colors, Z );

	// Vertex buffer setup
	gb->set( VertexAttribute::Position, pos );
	gb->set( VertexAttribute::Color, colors );

	return gb;
}

//-----------------------------------//

void GizmoTranslate::generateColors( std::vector<Vector3>& colors, const Color& c )
{
	// Darkens the color a bit.
	Vector3 baseColor = Vector3(c) * BASE_FACTOR;
	
	for( uint i = 0; i < SLICES; i++ )
	{
		// Generate the base colors.
		colors.push_back( baseColor );
		colors.push_back( baseColor );
		colors.push_back( baseColor );
	}

	for( uint i = 0; i < SLICES; i++ )
	{
		// Generate the top colors.
		colors.push_back( c );
		colors.push_back( c );
		colors.push_back( c );
	}
}

//-----------------------------------//

void GizmoTranslate::generateSolidCone( float base, float height, uint slices,
							   std::vector<Vector3>& pos )
{
	float r = 2*PI / slices;
	
	for( uint i = 0; i < slices; i++ )
	{
		// Generate the base
		pos.push_back( Vector3::Zero );
		pos.push_back( Vector3( cos(i*r), 0, sin(i*r) )*base );
		pos.push_back( Vector3( cos((i+1)*r), 0, sin((i+1)*r) )*base );
	}

	for( uint i = 0; i < slices; i++ )
	{
		// Generate the top of the cone
		pos.push_back( Vector3( cos(i*r), 0, sin(i*r) )*base );
		pos.push_back( Vector3::UnitY*height );
		pos.push_back( Vector3( cos((i+1)*r), 0, sin((i+1)*r) )*base );
	}
}

//-----------------------------------//

NAMESPACE_EDITOR_END