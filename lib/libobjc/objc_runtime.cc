#include <objc/objc.h>

#include <stdio.h>
#include <string.h>
#include <b/util/Array.h>
#include <b/util/Stack.h>

#include "objc_runtime_internal.h"

#define OBJC_MAX_CLASSES 64

static b::util::Stack<Class, OBJC_MAX_CLASSES> globalClasses;

extern "C" 
{
void resolve_all_classes(void);
}


static id objc_nil_method(id self, SEL _cmd, ...)
{
    return nil;
}

static id objc_missing_method(id self, SEL _cmd, ...)
{
    return nil;
}

static IMP find_method(Class cls, SEL sel)
{
    if (!sel)
    {
        return reinterpret_cast<IMP>(0);
    }

    const char *name = sel->name;

    for (Class c = cls; c; c = c->super_class) 
    {
        for (objc_method_list* ml = c->methods; ml; ml = ml->Next()) 
        {
            for (auto& method : *ml) 
            {
                if (!strcmp(method.name, name))
                {
                    return method.imp;
                }
            }
        }
    }

    return reinterpret_cast<IMP>(0);
}

static BOOL is_registered_class(Class c)
{
    for (auto _class : globalClasses)
    {
        if (_class == c)
            return YES;
    }

    return NO;
}

static void register_class(Class cls)
{
    if (!cls)
    {
        return;
    }

    if (is_registered_class(cls))
    {
        return;
    }

    globalClasses.push(cls);
}

static Class find_class_by_name(const char* name)
{
    for (auto _class : globalClasses)
    {
        if (!strcmp(_class->name, name))
        {
            return _class;
        }
    }
    return reinterpret_cast<Class>(0);
}

static void resolve_class(Class cls)
{
    if (!cls)
    {
        return;
    }

    if (cls->super_class && !is_registered_class(cls->super_class))
    {
        const char* super_name = reinterpret_cast<const char*>(cls->super_class);
        cls->super_class = find_class_by_name(super_name);
    }

    Class meta = cls->isa;

    if (meta)
    {
        if (!meta->isa)
        {
            Class root = cls;

            while (root->super_class)
            {
                root = root->super_class;
            }

            meta->isa = root->isa ? root->isa : meta;
        }

        if (!meta->super_class)
        {
            meta->super_class = cls->super_class ? cls->super_class->isa : reinterpret_cast<Class>(0);
        }
        else if (!is_registered_class(meta->super_class))
        {
            const char* super_name = reinterpret_cast<char*>(meta->super_class);
            Class s = find_class_by_name(super_name);
            meta->super_class = s ? s->isa : reinterpret_cast<Class>(0);
        }
    }
}

void resolve_all_classes(void)
{
    for (auto _class : globalClasses)
    {
        resolve_class(_class);
    }
}

Class objc_lookup_class(const char* name, ...)
{
    return find_class_by_name(name);
}

Class objec_get_class(const char* name, ...)
{
    return find_class_by_name(name);
}

IMP objc_msg_lookup(id receiver, SEL selector)
{
    if (!receiver)
    {
        return reinterpret_cast<IMP>(objc_nil_method);
    }

    Class cls = receiver->isa;
    IMP imp = find_method(cls, selector);

    return imp ? imp : reinterpret_cast<IMP>(objc_missing_method);
}

IMP objc_msg_lookup_super(struct objc_super* super, SEL selector)
{
    if (!super || !super->self)
    {
        return reinterpret_cast<IMP>(objc_nil_method);
    }

    IMP imp = find_method(super->super_class, selector);

    return imp ? imp : reinterpret_cast<IMP>(objc_missing_method);
}

void __objc_exec_class(void* module, ...)
{
    struct objc_module* m = reinterpret_cast<objc_module*>(module);

    if (!m || !m->symtab)
    {
        return;
    }

    struct objc_symtab* s = m->symtab;

    for (uint16_t i = 0; i < s->class_count; i++)
    {
        // printf("Enter Register Class %d\r\n", i);
        register_class(reinterpret_cast<Class>(s->defs[i]));
    }
}

id objc_alloc_object(Class cls)
{
    if (!cls || cls->instance_size <= 0)
    {
        return nil;
    }

    auto obj = reinterpret_cast<id>(malloc(cls->instance_size));

    if (!obj) {
        return nil;
    }

    memset(obj, 0, cls->instance_size);
    
    obj->isa = cls;
    obj->rc = 1;
    
    return obj;
}

void objc_dealloc_object(id obj)
{
    free(obj);
}
