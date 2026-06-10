#ifndef __LIB_FSPLUS_H
#define __LIB_FSPLUS_H

#include <lk/compiler.h>
#include <sys/types.h>

struct bdev;
struct fscookie;
struct filecookie;
struct dircookie;
struct file_stat;

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

    virtual status_t mkdir(fscookie *, const char *)
    {
        return 0;
    }

    virtual status_t OpenDir(fscookie *, const char *, dircookie **)
    {
        return 0;
    }

    virtual status_t readdir(dircookie *, struct dirent *)
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

#endif