#ifndef __OBJC_RUNTIME_INTERNAL_H
#define __OBJC_RUNTIME_INTERNAL_H

#include <objc/objc.h>
#include <b/util/Iterator.h>

struct objc_method {
    const char* name;
    const char* types;
    IMP imp;
};

class objc_method_list {
    objc_method_list* next;
    int32_t count;
    objc_method methods[];
    
public:
    b::util::Iterator<objc_method>
    begin()
    {
        return b::util::Iterator<objc_method>(reinterpret_cast<objc_method*>(methods));
    }

    b::util::Iterator<objc_method>
    end()
    {
        return b::util::Iterator<objc_method>(reinterpret_cast<objc_method*>(methods) + count);
    }

    bool IsNext()
    {
        return (next != nullptr);
    }

    objc_method_list* Next()
    {
        return next;
    }
};

struct objc_ivar {
    const char* name;
    const char* type;
    int32_t offset;
};

struct objc_ivar_list {
    int32_t count;
    objc_ivar ivars[];
};

struct objc_class {
    Class isa;
    Class super_class;
    const char* name;
    uint64_t version;
    uint64_t info;
    uint64_t instance_size;

    objc_ivar_list* ivars;
    objc_method_list* methods;

    void* dtable;
    Class subclass_list;
    Class sibiling_class;

    void* protocols;
    void* gc_object_type;

    uint64_t abi_version;
    void* ivar_offsets;
    void* properties;

    uint64_t strong_ivar_bitmap;
    uint64_t weak_ivar_bitmap;
};

struct objc_symtab {
    uint32_t selectors_count;
    SEL selectors;
    uint16_t class_count;
    uint16_t category_count;
    void* defs[];
};

struct objc_module {
    uint64_t version;
    uint64_t size;
    const char* name;
    objc_symtab* symtab;
};

#endif