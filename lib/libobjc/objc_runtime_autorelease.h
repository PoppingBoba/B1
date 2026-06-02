#ifndef __OBJC_RUNTIME_AUTORELEASE_H
#define __OBJC_RUNTIME_AUTORELEASE_H

// Forward Declaring
struct objc_object;

struct AutoReleasePool
{
    // 'objc_object*' is same as 'id' type
    // So it means 'id*'
    objc_object** objects;
};

#endif