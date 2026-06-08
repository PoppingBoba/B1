#ifndef __OBJC_OBJECT_H
#define __OBJC_OBJECT_H

#include "objc/objc.h"

@interface Object {
@public
    Class isa;
    uint32_t rc;
}
+ (id)alloc;
- (id)init;
- (id)retain;
- (void)release;
- (void)dealloc;
- (id)autorelease;
@end

#endif