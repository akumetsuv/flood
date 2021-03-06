/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Core/API.h"
#include "Core/Reflection.h"
#include "Core/Object.h"
#include "Core/Log.h"
#include "Core/Math/Hash.h"
#include "Core/Math/Vector.h"
#include "Core/Math/Color.h"

NAMESPACE_CORE_BEGIN

//-----------------------------------//

REFLECT_ABSTRACT_CLASS(Object)
REFLECT_CLASS_END()

//-----------------------------------//

bool ReflectionIsPrimitive(const Type* type)
{
	return type && type->kind == TypeKind::Primitive;
}

//-----------------------------------//

bool ReflectionIsComposite(const Type* type)
{
	return type && type->kind == TypeKind::Composite;
}

//-----------------------------------//

bool ReflectionIsEnum(const Type* type)
{
	return type && type->kind == TypeKind::Enumeration;
}

//-----------------------------------//

ReflectionDatabase& ReflectionGetDatabase()
{
	static ReflectionDatabase s_ReflectionDatabase;
	return s_ReflectionDatabase;
}

//-----------------------------------//

static void RegisterClass(Class* klass)
{
	klass->id = ClassCalculateId(klass);

	//LogDebug("Registering class: '%s' with id '%u'", klass->name, klass->id);

	// Register as child class in the parent class.
	Class* parent = klass->parent;
	if( parent ) parent->childs.push_back(klass);

	// Register the class id in the map.
	ClassIdMap& ids = ClassGetIdMap();

	if( ids.find(klass->id) != ids.end() )
	{
		LogError("Class with the same id already exists: '%s'", klass->name);
		return;
	}

	ids[klass->id] = klass;
}

//-----------------------------------//

bool ReflectionDatabaseRegisterType(ReflectionDatabase* db, Type* type)
{
	if( !db || !type ) return false;

	const char* name = type->name;

	if( db->types.find(name) != db->types.end() )
	{
		LogAssert("Type '%s' already exists in the database", name);
		return false;
	}

	db->types[name] = type;

	if( !ReflectionIsComposite(type) )
		return true;

	Class* klass = (Class*) type;
	RegisterClass(klass);

	return true;
}

//-----------------------------------//

bool ReflectionRegisterType(Type* type)
{
	ReflectionDatabase& db = ReflectionGetDatabase();
	return ReflectionDatabaseRegisterType(&db, type);
}

//-----------------------------------//

Type* ReflectionFindType(const char* name)
{
	ReflectionDatabase& db = ReflectionGetDatabase();
	
	TypeMap::iterator it = db.types.find(name);
	if( it == db.types.end() ) return nullptr;

	return it->second;
}

//-----------------------------------//

bool ReflectionIsEqual(const Type* t1, const Type* t2)
{
	return t1 == t2;
}

//-----------------------------------//

void EnumAddValue(Enum* enumeration, const char* name, int32 value)
{
	if( !enumeration ) return;

	EnumValuesMap& values = enumeration->values;
	values[name] = value;
}

//-----------------------------------//

int32 EnumGetValue(Enum* enumeration, const char* name)
{
	if( !enumeration ) return -1;
	EnumValuesMap& values = enumeration->values;
	
	EnumValuesMap::iterator it = values.find(name);
	if( it == values.end() ) return -1;
	
	return it->second;
}

//-----------------------------------//

const char* EnumGetValueName(Enum* enumeration, int32 value)
{
	if( !enumeration ) return nullptr;
	EnumValuesMap& values = enumeration->values;
	
	EnumValuesMap::iterator it = values.begin();
	
	for(; it != values.end(); ++it)
	{
		const char* name = it->first;
		if( value == it->second ) return name;
	}

	return nullptr;
}

//-----------------------------------//

void ClassAddField(Class* klass, Field* field)
{
	klass->fields.push_back(field);

	if( ClassGetFieldById(klass, field->id) )
	{
		LogAssert("Duplicate id found for field '%s' in '%s'",
			field->name, klass->name);
		return;
	}

	if( field->id == FieldInvalid )
	{
		LogAssert("Field id in '%s' is reserved", field->id);
		return;
	}

	ClassFieldIdMap& fieldIds = klass->fieldIds;
	fieldIds[field->id] = field;
}

//-----------------------------------//

ClassIdMap& ClassGetIdMap()
{
	static ClassIdMap s_ClassIds;
	return s_ClassIds;
}

//-----------------------------------//

Class* ClassGetById(ClassId id)
{
	ClassIdMap& classIds = ClassGetIdMap();
	ClassIdMap::iterator it = classIds.find(id);

	if( it == classIds.end() )
		return nullptr;

	return it->second;
}

//-----------------------------------//

Class* ClassGetType(const Object* object)
{
	if( !object ) return nullptr;
	return object->getType();
}

//-----------------------------------//

Field* ClassGetField(const Class* klass, const char* name)
{
	const std::vector<Field*>& fields = klass->fields;
	
	for(size_t i = 0; i < fields.size(); i++)
	{
		Field* field = fields[i];
		if(strcmp(field->name, name) == 0) return field;

		for(size_t u = 0; u < field->aliases.size(); u++)
		{
			const char* alias = field->aliases[u];
			if(strcmp(alias, name) == 0) return field;
		}
	}

	Class* parent = klass->parent;
	if(!parent) return nullptr;
	
	return ClassGetField(parent, name);
}

//-----------------------------------//

Field* ClassGetFieldById(Class* klass, FieldId id)
{
	ClassFieldIdMap& fieldIds = klass->fieldIds;

	ClassFieldIdMap::iterator it = fieldIds.find(id);

	if( it != fieldIds.end() )
		return it->second;

	if( klass->parent )
		return ClassGetFieldById(klass->parent, id);
	else
		return nullptr;
}

//-----------------------------------//

void* ClassGetFieldAddress(const void* object, const Field* field)
{
	if( !object || !field ) return nullptr;
	
	return (uint8*) object + field->offset;
}

//-----------------------------------//

bool ClassInherits(const Class* klass, const Class* test)
{
	bool equals = ReflectionIsEqual(klass, test);

	if( klass->parent == nullptr )
		return equals;

	return equals || ClassInherits(klass->parent, test);
}

//-----------------------------------//

void* ClassCreateInstance(const Class* klass, Allocator* alloc)
{
	if( !klass ) return nullptr;

	if( ClassIsAbstract(klass) )
	{
		LogAssert("Could not create instance of abstract class '%s'", klass->name);
		return nullptr;
	}
	
	void* object = klass->create_fn(alloc);
	return object;
}

//-----------------------------------//

ClassId ClassCalculateId(const Class* klass)
{
	uint32 hash = HashMurmur2(0xBEEF, (uint8*) klass->name, strlen(klass->name));
	return (ClassId) hash;
}

//-----------------------------------//

bool ClassIsAbstract(const Class* klass)
{
	if( !klass ) return false;
	
	return klass->create_fn == nullptr;
}

//-----------------------------------//

Field::Field()
	: type(nullptr)
	, id(FieldInvalid)
	, name(nullptr)
	, size(0)
	, offset(0)
	, pointer_size(0)
	, qualifiers((FieldQualifier)0)
	, setter(nullptr)
	, resize(nullptr)
	, serialize(nullptr)
{

}

//-----------------------------------//

bool FieldHasQualifier(const Field* field, FieldQualifier qual)
{
	if( !field ) return false;
	return ((uint16)field->qualifiers & (uint16)qual) != 0;
}

//-----------------------------------//

void FieldSetQualifier(Field* field, FieldQualifier qual)
{
	if( !field ) return;
	*((uint16*)&field->qualifiers) |= (uint16)qual;
}

//-----------------------------------//

void FieldSetSetter(Field* field, FieldSetterFunction fn)
{
	if( !field ) return;
	field->setter = fn;
}

//-----------------------------------//

PrimitiveBuiltins::PrimitiveBuiltins()
	: p_bool(PrimitiveTypeKind::Bool, "bool", sizeof(bool))
	, p_int8(PrimitiveTypeKind::Int8, "int8", sizeof(int8))
	, p_uint8(PrimitiveTypeKind::Uint8, "uint8", sizeof(uint8))
	, p_uint16(PrimitiveTypeKind::Uint16, "uint16", sizeof(uint16))
	, p_int16(PrimitiveTypeKind::Int16, "int16", sizeof(int16))
	, p_int32(PrimitiveTypeKind::Int32, "int32", sizeof(int32))
	, p_uint32(PrimitiveTypeKind::Uint32, "uint32", sizeof(uint32))
	, p_int64(PrimitiveTypeKind::Int64, "int64", sizeof(int64))
	, p_uint64(PrimitiveTypeKind::Uint64, "uint64", sizeof(uint64))
	, p_float(PrimitiveTypeKind::Float, "float", sizeof(float))
	, p_string(PrimitiveTypeKind::String, "string", sizeof(String))
	, p_Vector3(PrimitiveTypeKind::Vector3, "Vector3", sizeof(Vector3))
	, p_Color(PrimitiveTypeKind::Color, "Color", sizeof(Color))
	, p_Quaternion(PrimitiveTypeKind::Quaternion, "Quaternion", sizeof(Quaternion))
{}

PrimitiveBuiltins& PrimitiveGetBuiltins()
{
	static PrimitiveBuiltins g_PrimitiveBuiltins;
	return g_PrimitiveBuiltins;
}

//-----------------------------------//

// Specializations for all known primitive types.
template<> Primitive* GetPrimitiveFromType<bool>() { return &PrimitiveGetBuiltins().p_bool; }
template<> Primitive* GetPrimitiveFromType<int8>() { return &PrimitiveGetBuiltins().p_int8; }
template<> Primitive* GetPrimitiveFromType<uint8>() { return &PrimitiveGetBuiltins().p_uint8; }
template<> Primitive* GetPrimitiveFromType<int16>() { return &PrimitiveGetBuiltins().p_int16; }
template<> Primitive* GetPrimitiveFromType<uint16>() { return &PrimitiveGetBuiltins().p_uint16; }
template<> Primitive* GetPrimitiveFromType<int32>() { return &PrimitiveGetBuiltins().p_int32; }
template<> Primitive* GetPrimitiveFromType<uint32>() { return &PrimitiveGetBuiltins().p_uint32; }
template<> Primitive* GetPrimitiveFromType<int64>() { return &PrimitiveGetBuiltins().p_int64; }
template<> Primitive* GetPrimitiveFromType<uint64>() { return &PrimitiveGetBuiltins().p_uint64; }
template<> Primitive* GetPrimitiveFromType<float>() { return &PrimitiveGetBuiltins().p_float; }
template<> Primitive* GetPrimitiveFromType<const char*>() { return &PrimitiveGetBuiltins().p_string; }
template<> Primitive* GetPrimitiveFromType<String>() { return &PrimitiveGetBuiltins().p_string; }
template<> Primitive* GetPrimitiveFromType<Vector3>() { return &PrimitiveGetBuiltins().p_Vector3; }
template<> Primitive* GetPrimitiveFromType<Color>() { return &PrimitiveGetBuiltins().p_Color; }
template<> Primitive* GetPrimitiveFromType<Quaternion>() { return &PrimitiveGetBuiltins().p_Quaternion; }

//-----------------------------------//

NAMESPACE_CORE_END