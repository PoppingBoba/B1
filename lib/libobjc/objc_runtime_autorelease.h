#ifndef __OBJC_RUNTIME_AUTORELEASE_H
#define __OBJC_RUNTIME_AUTORELEASE_H

#include "b/util/List.h"
#include <objc/Object.h>

// Forward Declaring
struct objc_object;

@interface NSAutoreleasePool : Object
{
@private
}
- (id)init;
- (void)drain;
@end

#endif