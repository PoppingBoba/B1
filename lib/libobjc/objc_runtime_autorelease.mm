#include <objc/objc.h>
#include <objc/Object.h>

#include <stdio.h>
#include <b/util/List.h>

#include <kernel/thread.h>

#include "objc_runtime_autorelease.h"

using AutoReleasePoolList = b::util::LinkedList<b::util::LinkedList<id>>;

static auto GetCurrentPool = []() -> AutoReleasePoolList* {
    return reinterpret_cast<AutoReleasePoolList*>(tls_get(TLS_ENTRY_OBJC_RUNTIME));
};

static auto SetCurrentPool = [](AutoReleasePoolList* currentPool) {
    tls_set(TLS_ENTRY_OBJC_RUNTIME, reinterpret_cast<uintptr_t>(currentPool));
};

@implementation NSAutoreleasePool
- (id)init 
{
    printf("Hello NSAutoreleasePool\r\n");

    if (!GetCurrentPool())
    {
        auto currPool = new AutoReleasePoolList;
        SetCurrentPool(currPool);
    }

    auto linkedList = b::util::LinkedList<id>();
    GetCurrentPool()->PushFront(b::util::Move(linkedList));

    return self;
}

- (void)drain 
{
    printf("Bye NSAutoreleasePool\r\n");
    if (GetCurrentPool() && GetCurrentPool()->Front())
    {
        auto& objList = GetCurrentPool()->Front()->Value;

        for (auto i : objList)
        {
            printf("Autorelease Activated : Obj [%p]\r\n", i);
            [i release];
        }

        GetCurrentPool()->PopFront();

        if (!GetCurrentPool()->Front())
            delete GetCurrentPool();
    }
    [self release];
}
@end

id objc_autorelease(id obj)
{
    printf("Enter objc_autorelease\r\n");
    
    if (GetCurrentPool() && GetCurrentPool()->Front())
    {
        auto& objList = GetCurrentPool()->Front()->Value;

        objList.PushFront(obj);

        printf("objc_autorelease object Ptr: %p\r\n", obj);
    }

    return obj;
}
