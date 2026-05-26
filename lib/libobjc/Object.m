#include <objc.h>

__attribute__((objc_root_class))
@interface Object
{
@public
    Class isa;
    uint32_t rc;
}

+ (id)alloc;
- (id)init;
- (id)retain;
- (void)release;
- (void)dealloc;
@end

@implementation Object

+ (id)alloc
{
    return objc_alloc_object((Class)self);
}

- (id)init
{
    return self;
}

- (id)retain
{
    ((struct objc_object*)self)->rc++;
    return self;
}

- (void)release
{
    struct objc_object* o = (struct objc_object*)self;
    
    if (o->rc && --o->rc == 0)
    {
        [self dealloc];
        objc_dealloc_object(self);
    }
}

- (void)dealloc
{
}

@end
