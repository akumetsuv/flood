/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Editor/API.h"
#include "PropertyOperation.h"
#include "Editor.h"

#ifdef ENABLE_PLUGIN_PROPERTY

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

REFLECT_CHILD_CLASS(PropertyOperation, UndoOperation)
REFLECT_CLASS_END()

//-----------------------------------//

void PropertyOperation::undo()
{ 
	setFieldValue(oldValue);
	grid->setFieldValue(field, object, oldValue);
}

//-----------------------------------//

void PropertyOperation::redo()
{
	setFieldValue(newValue);
	grid->setFieldValue(field, object, newValue);
}

//-----------------------------------//

void PropertyOperation::setFieldValue(const wxAny& value)
{
	assert( type != nullptr );
	assert( field != nullptr );

	LogDebug("Changed property value: %s", field->type->name);

	bool isClass = ReflectionIsComposite(field->type);
	bool isResource = isClass && ClassInherits((Class*) field->type, ReflectionGetType(Resource));

	if( FieldIsPointer(field) && isResource )
	{
		String val = value.As<String>();

		ResourceManager* rm = GetResourceManager();
		ResourceHandle resource = rm->loadResource(val);

		if( !resource ) return;

		FieldSet<ResourceHandle>(field, object, resource);

		return;
	}

	switch(field->type->kind)
	{
	case TypeKind::Enumeration:
	{
		int32 val = value.As<int32>();
		FieldSet<int32>(field, object, val);
		break;
	}
	case TypeKind::Primitive:
	{
		Primitive* primitive = (Primitive*) field->type;

		switch(primitive->kind)
		{
		case PrimitiveTypeKind::Bool:
		{
			bool val = value.As<bool>();
			FieldSet<bool>(field, object, val);
			break;
		}
		//-----------------------------------//
		case PrimitiveTypeKind::Int32:
		{
			int32 val = value.As<int32>();
			FieldSet<int32>(field, object, val);
			break;
		}
		//-----------------------------------//
		case PrimitiveTypeKind::Float:
		{
			float val = value.As<float>();
			FieldSet<float>(field, object, val);
			break;
		}
		//-----------------------------------//
		case PrimitiveTypeKind::String:
		{
			String val = value.As<String>();
			FieldSet<String>(field, object, val);
			break;
		}
		//-----------------------------------//
		case PrimitiveTypeKind::Color:
		{
			Color val = value.As<Color>();
			FieldSet<Color>(field, object, val);
			break;
		}
		//-----------------------------------//
		case PrimitiveTypeKind::Vector3:
		{
			Vector3 val = value.As<Vector3>();
			FieldSet<Vector3>(field, object, val);
			break;
		}
		//-----------------------------------//
		case PrimitiveTypeKind::Quaternion:
		{
			Quaternion val = value.As<Quaternion>();
			FieldSet<Quaternion>(field, object, val);
			break;
		}
		//-----------------------------------//
		default:
			assert( false );
		}
		break;
	}
	default:
		assert( false );
	}
}

//-----------------------------------//

NAMESPACE_EDITOR_END

#endif