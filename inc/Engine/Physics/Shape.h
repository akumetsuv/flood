/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#ifdef ENABLE_PHYSICS_BULLET

#include "Engine/Scene/Component.h"

class btCollisionShape;

NAMESPACE_ENGINE_BEGIN

//-----------------------------------//

class Body;
TYPEDEF_INTRUSIVE_POINTER_FROM_TYPE(Body)

API_ENGINE REFLECT_DECLARE_CLASS(Shape)

class API_ENGINE Shape : public Component
{
	REFLECT_DECLARE_OBJECT(Shape)

public:

	virtual ~Shape();

	// Gets the internal Bullet shape.
	virtual btCollisionShape* const getBulletShape() const = 0;

	// Sets the associated body.
	SETTER(Body, const BodyPtr&, body)

protected:

	// Removes the body from the world.
	virtual void removeBody();

	// Weak pointer to body.
	BodyPtr body;
};

TYPEDEF_INTRUSIVE_POINTER_FROM_TYPE( Shape );

//-----------------------------------//

NAMESPACE_ENGINE_END

#endif