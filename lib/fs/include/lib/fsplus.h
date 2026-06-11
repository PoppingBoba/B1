#ifndef __LIB_FSPLUS_H
#define __LIB_FSPLUS_H

#include <lk/compiler.h>
#include <sys/types.h>

struct bdev;
struct fscookie;
struct filecookie;
struct dircookie;
struct file_stat;
struct fs_stat;

class FileSystemClass
{
public:
    virtual status_t Format(bdev*, const void*)
    {
        return 0;
    }

    virtual status_t FSStat(fscookie*, fs_stat*)
    {
        return 0;
    }

    virtual status_t Mount(bdev*, fscookie**)
    {
        return 0;
    }

    virtual status_t Unmount(fscookie*)
    {
        return 0;
    }

    virtual status_t Open(fscookie*, const char*, filecookie**)
    {
        return 0;
    }

    virtual status_t Create(fscookie*, filecookie**, uint64_t)
    {
        return 0;
    }

    virtual status_t Remove(fscookie*, const char*)
    {
        return 0;
    }

    virtual status_t Truncate(filecookie*, uint64_t)
    {
        return 0;
    }

    virtual status_t Stat(filecookie*, file_stat*)
    {
        return 0;
    }

    virtual ssize_t Read(filecookie *, void *, off_t, size_t)
    {
        return 0;
    }

    virtual ssize_t Write(filecookie *, const void *, off_t, size_t)
    {
        return 0;
    }

    virtual status_t Close(filecookie *)
    {
        return 0;
    }

    virtual status_t MkDir(fscookie *, const char *)
    {
        return 0;
    }

    virtual status_t OpenDir(fscookie *, const char *, dircookie **)
    {
        return 0;
    }

    virtual status_t ReadDir(dircookie *, struct dirent *)
    {
        return 0;
    }

    virtual status_t CloseDir(dircookie *)
    {
        return 0;
    }

    virtual status_t Ioctl(filecookie *, int, void *)
    {
        return 0;
    }
};

class FileSystemMetaClass
{
    const char* name;
public:
    explicit FileSystemMetaClass(const char* name) : name(name) {}

    virtual FileSystemClass* Alloc()
    {
        return nullptr;
    }

    const char* Name() const
    {
        return name;
    }
};

#define DefineFileSystemMetaClass()                                     \
public:                                                                 \
    class MetaClass : public FileSystemMetaClass                        \
    {                                                                   \
    public:                                                             \
        MetaClass();                                                    \
        virtual FileSystemClass* Alloc();                               \
    };                                                                  \
    static MetaClass gMetaClass                                                 

#define DeclareFileSystem(FSNAME, FSCLASS)                                \
    FSCLASS::MetaClass::MetaClass() : FileSystemMetaClass(FSNAME) {}      \
    FileSystemClass* FSCLASS::MetaClass::Alloc() { return new FSCLASS; }  \
    FSCLASS::MetaClass FSCLASS::gMetaClass __SECTION("fsplus_meta");      


#endif