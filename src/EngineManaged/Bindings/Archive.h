/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "CppSharp.h"
#include <Core/Archive.h>

namespace Flood
{
    ref class Archive;
    value struct FileWatchEvent;
    ref class ArchiveVirtual;
    ref class ArchiveDirectory;
    ref class ArchiveZip;
}

namespace Flood
{
    /// <summary>
    /// Archives are a structured collection of files. The most common archive
    /// implementations are ZIP archive files and OS filesystem directories.
    /// </summary>
    public ref class Archive : ICppInstance
    {
    public:

        property ::Archive* NativePtr;
        property System::IntPtr Instance
        {
            virtual System::IntPtr get();
            virtual void set(System::IntPtr instance);
        }

        Archive(::Archive* native);
        Archive(System::IntPtr native);
        Archive();

        /// <summary>
        /// Creates the archive.
        /// </summary>
        Archive(System::String^ path);

        property System::String^ Path
        {
            System::String^ get();
        }
        property System::IntPtr Userdata
        {
            System::IntPtr get();
            void set(System::IntPtr);
        }
        property unsigned int WatchId
        {
            unsigned int get();
            void set(unsigned int);
        }
        property bool IsValid
        {
            bool get();
            void set(bool);
        }
        /// <summary>
        /// Opens the archive.
        /// </summary>
        virtual bool Open(System::String^ path);

        /// <summary>
        /// Closes the archive.
        /// </summary>
        virtual bool Close();

        /// <summary>
        /// Checks if a file exists.
        /// </summary>
        virtual bool ExistsFile(System::String^ path);

        /// <summary>
        /// Checks if a directory exists.
        /// </summary>
        virtual bool ExistsDir(System::String^ path);

        /// <summary>
        /// Sets up and updates the watching functionality for the archive.
        /// </summary>
        virtual bool Monitor();

        /// <summary>
        /// Combines the path of a file to get the full path to an archive file.
        /// </summary>
        System::String^ CombinePath(System::String^ filePath);

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };

    public ref class ArchiveVirtual : Flood::Archive
    {
    public:

        ArchiveVirtual(::ArchiveVirtual* native);
        ArchiveVirtual(System::IntPtr native);
        ArchiveVirtual();

        /// <summary>
        /// Opens the archive.
        /// </summary>
        virtual bool Open(System::String^ path) override;

        /// <summary>
        /// Closes the archive.
        /// </summary>
        virtual bool Close() override;

        /// <summary>
        /// Checks if a file exists.
        /// </summary>
        virtual bool ExistsFile(System::String^ path) override;

        /// <summary>
        /// Checks if a directory exists.
        /// </summary>
        virtual bool ExistsDir(System::String^ path) override;

        /// <summary>
        /// Sets up and updates the watching functionality for the archive.
        /// </summary>
        virtual bool Monitor() override;

        /// <summary>
        /// Mounts an archive in the virtual archive.
        /// </summary>
        bool Mount(Flood::Archive^ mount, System::String^ mountPath);

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };

    public ref class ArchiveDirectory : Flood::Archive
    {
    public:

        ArchiveDirectory(::ArchiveDirectory* native);
        ArchiveDirectory(System::IntPtr native);
        /// <summary>
        /// Creates the archive from a directory.
        /// </summary>
        ArchiveDirectory(System::String^ _0);

        /// <summary>
        /// Opens the archive.
        /// </summary>
        virtual bool Open(System::String^ path) override;

        /// <summary>
        /// Closes the archive.
        /// </summary>
        virtual bool Close() override;

        /// <summary>
        /// Checks if a file exists.
        /// </summary>
        virtual bool ExistsFile(System::String^ path) override;

        /// <summary>
        /// Checks if a directory exists.
        /// </summary>
        virtual bool ExistsDir(System::String^ path) override;

        /// <summary>
        /// Sets up and updates the watching functionality for the archive.
        /// </summary>
        virtual bool Monitor() override;

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };

    public ref class ArchiveZip : Flood::Archive
    {
    public:

        ArchiveZip(::ArchiveZip* native);
        ArchiveZip(System::IntPtr native);
        /// <summary>
        /// Creates the archive from a ZIP.
        /// </summary>
        ArchiveZip(System::String^ path);

        property System::IntPtr Handle
        {
            System::IntPtr get();
            void set(System::IntPtr);
        }
        /// <summary>
        /// Opens the archive.
        /// </summary>
        virtual bool Open(System::String^ path) override;

        /// <summary>
        /// Closes the archive.
        /// </summary>
        virtual bool Close() override;

        /// <summary>
        /// Checks if a file exists.
        /// </summary>
        virtual bool ExistsFile(System::String^ path) override;

        /// <summary>
        /// Checks if a directory exists.
        /// </summary>
        virtual bool ExistsDir(System::String^ path) override;

        /// <summary>
        /// Sets up and updates the watching functionality for the archive.
        /// </summary>
        virtual bool Monitor() override;

        virtual bool Equals(System::Object^ object) override;

        virtual int GetHashCode() override;

    };
}
