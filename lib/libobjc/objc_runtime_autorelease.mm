#include <objc/objc.h>
#include <objc/Object.h>

#include <stdio.h>
#include <b/util/Vector.h>

#include <kernel/thread.h>

#include "objc_runtime_autorelease.h"

static auto GetCurrentPool = []() -> b::util::InlinedVector<id>* {
    return reinterpret_cast<b::util::InlinedVector<id>*>(tls_get(TLS_ENTRY_OBJC_RUNTIME));
};

static auto SetCurrentPool = [](b::util::InlinedVector<id>* currentPool) {
    tls_set(TLS_ENTRY_OBJC_RUNTIME, reinterpret_cast<uintptr_t>(currentPool));
};

@implementation NSAutoreleasePool
- (id)init 
{
    printf("Hello NSAutoreleasePool");
    auto* autoReleasePool = new b::util::InlinedVector<id>;
    SetCurrentPool(autoReleasePool);
    return self;
}

- (void)drain 
{
    printf("Bye NSAutoreleasePool");
    delete GetCurrentPool();
    [self release];
}
@end

id objc_autorelease(id obj)
{
    printf("Enter objc_autorelease");
    GetCurrentPool()->push_back(obj);
    return obj;
}
