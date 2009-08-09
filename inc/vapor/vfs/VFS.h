/************************************************************************
*
* vaporEngine (2008-2009)
*
*	<http://www.portugal-a-programar.org>
*
************************************************************************/

#pragma once

#include "vapor/CompileOptions.h"

#ifdef VAPOR_VFS_PHYSFS

#include "vapor/Platform.h"
#include "vapor/vfs/File.h"

namespace vapor {
	namespace vfs {

/**
 * Represents a virtual file system that will be used by all the other
 * engine classes for file I/O operations. When this is constructed,
 * it needs to be populated with 'mount points'. Each mount point can
 * be a different kind of device. For example, you can mount a CD-ROM
 * drive, or a filesystem folder hierarchy, or even a compressed ZIP.
 * Mount points can also overlap. In that case, the first mount found
 * with the requested file will be the one used. You can control the
 * order of search by prepending or appending the archive or directory
 * to the search path while mounting it in the virtual filesystem.
 */

class VFS
{
public:

	VFS(const std::string& app);
	~VFS();

	// Mount an archive into the virtual file system point.
	bool mount(const std::string& path, const std::string& mount = "",
		bool append = true);

private:

	// Logs the version and supported archive types.
	void log();

	// Sets up some sensible default mount points.
	void setDefaultConfig(const std::string& app);

	// holds the mounted archives/directories in the filesystem
	std::vector< const std::string > mountPoints;
};

} } // end namespaces

#endif