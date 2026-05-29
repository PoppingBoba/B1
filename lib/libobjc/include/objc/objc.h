#ifndef __OBJC_MIN_H
#define __OBJC_MIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef signed char BOOL;

#define YES ((BOOL)1)
#define NO  ((BOOL)0)
#define nil ((id)0)

typedef struct objc_class* Class;
typedef struct objc_object* id;

typedef struct objc_selector {
    const char *name;
    const char *types;
}*SEL;

typedef id (*IMP)(id, SEL, ...);

struct objc_object {
    Class isa;
    uint32_t rc;
};

struct objc_super {
    id self;
    Class super_class;
};

Class objc_lookup_class(const char* name, ...);
Class objec_get_class(const char* name, ...);

IMP objc_msg_lookup(id receiver, SEL selector);
IMP objc_msg_lookup_super(struct objc_super* super, SEL selector);

void __objc_exec_class(void* module, ...);

id objc_alloc_object(Class cls);
void objc_dealloc_object(id obj);

#ifdef __cplusplus
};
#endif

#endif