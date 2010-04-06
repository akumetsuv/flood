/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

namespace vapor { namespace resources {

class ResourceLoader;

//-----------------------------------//

/**
 * When you request a resource, you will be given a resource handle that
 * you can later use to query the resource manager for the real pointer.
 * Never store the dumb pointers, because if the resource is updated it
 * might have a different pointer.
 */

typedef int	ResourceHandle;

//-----------------------------------//

/**
 * Resources can be loaded in a background task. In that case the caller
 * will still receive a resource but it won't be fully loaded. It will
 * only be fully loaded when the resource status changes to loaded.
 */

namespace ResourceStatus
{
	enum Enum
	{
		Unloaded = 0,
		Loading,
		Loaded
	};
}

//-----------------------------------//

/**
 * Resource groups identify the kind of data a resource holds.
 * The ResourceManager class uses this information to keep the
 * related resources together, and for managing the data.
 */

namespace ResourceGroup
{
	enum Enum
	{
		General = 0,
		Images,
		Meshes,
		Fonts,
		Shaders,
		Audio,
		Scripts
	};

	// Yeah, a bit ugly, but it works.
	const std::string getString(Enum e);
}

//-----------------------------------//

/**
 * Represents a generic resource that tipically is used to hold a piece
 * of data that is used by the various systems of the engine, for example
 * mesh, sounds, fonts, images, shaders, and other types of resource data.
 * Each resource is identified by an URI (Uniform Resource Identifier),
 * that way we can add virtual resources (it could be used for various
 * things, like procedural content generation and to identify streaming
 * resource from a network connection).
 */

class VAPOR_API Resource : public ReferenceCounted, private boost::noncopyable
{
	static const ResourceHandle NotFound = -1;

public:

	virtual ~Resource() {}

	// Reloads this resource.
	bool reload();

	// Releases the contents of this resource (to save memory).
	// void release();

	// Gets/sets the path that identifies this resource.
	IMPLEMENT_ACESSOR(URI, const std::string&, uri)
	
	// Gets the resource group associated with this resource.
	virtual ResourceGroup::Enum getResourceGroup() const = 0;

	// Gets the resource loader associated with this resource.
	//virtual ResourceLoader* getResourceLoader() = 0;

	// Gets/sets the resource loading status.
	IMPLEMENT_GETTER(Status, ResourceStatus::Enum, status)

protected:

	Resource( const std::string& uri = "" );

	// Uniform Resource Identifier.
	std::string uri;

	// Status of the resource.
	ResourceStatus::Enum status;
};

//-----------------------------------//

#if defined(VAPOR_MEMORY_INTRUSIVE_PTR)
	#define TYPEDEF_RESOURCE_POINTER_FROM_TYPE(T)	\
		TYPEDEF_INTRUSIVE_POINTER_FROM_TYPE(T)
	#define RESOURCE_TYPEDECL_FROM_TYPE(T)			\
		boost::intrusive_ptr<T>
	#define RESOURCE_SMART_PTR_CAST					\
		boost::static_pointer_cast
#elif defined(VAPOR_MEMORY_SHARED_PTR)
	#define TYPEDEF_RESOURCE_POINTER_FROM_TYPE(T)	\
		TYPEDEF_SHARED_POINTER_FROM_TYPE(T)
	#define RESOURCE_TYPEDECL_FROM_TYPE(T)			\
		std::shared_ptr<T>
	#define RESOURCE_SMART_PTR_CAST					\
		std::static_pointer_cast
#else
	#error No smart pointer implementation found
#endif
		
TYPEDEF_RESOURCE_POINTER_FROM_TYPE( Resource );

//-----------------------------------//

} } // end namespaces


