#include "lib/bio.h"
#include <lib/fs.h>
#include <lib/fsplus.h>
#include <sys/types.h>

class EXT2FS : public FileSystemClass
{
    DefineFileSystemMetaClass();
public:
    status_t Mount(bdev_t* dev, fscookie** cookie) override;
    status_t Unmount(fscookie* cookie) override;
    status_t Open(fscookie* cookie, const char* path, filecookie** fcookie) override;
    ssize_t Read(filecookie* fcookie, void* buf, off_t offset, size_t len) override;
    status_t Close(filecookie* fcookie) override;
};

status_t EXT2FS::Mount(bdev_t* dev, fscookie** cookie)
{
    return 0;
}

status_t EXT2FS::Unmount(fscookie* cookie)
{
    return 0;
}

status_t EXT2FS::Open(fscookie* cookie, const char* path, filecookie** fcookie)
{
    return 0;
}

ssize_t EXT2FS::Read(filecookie* fcookie, void* buf, off_t offset, size_t len)
{
    return 0;
}

status_t EXT2FS::Close(filecookie* fcookie)
{
    return 0;
}

DeclareFileSystem("EXT2PP", EXT2FS);