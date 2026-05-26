#include <objc.h>

#include <string.h>

struct objc_method {
    const char* name;
    const char* types;
    IMP imp;
};

struct objc_method_list {
    struct objc_method_list* next;
    int32_t count;
    struct objc_method methods[];
};

struct objc_ivar {
    const char* name;
    const char* type;
    int32_t offset;
};

struct objc_ivar_list {
    int32_t count;
    struct objc_ivar ivars[];
};

struct objc_class {
    Class isa;
    Class super_class;
    const char* name;
    uint64_t version;
    uint64_t info;
    uint64_t instance_size;

    struct objc_ivar_list* ivars;
    struct objc_method_list* methods;

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
    struct objc_symtab* symtab;
};

#define OBJC_MAX_CLASSES 64

static Class g_classes[OBJC_MAX_CLASSES];
static uint32_t g_class_count = 0;


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
        return (IMP)0;
    }

    const char *name = sel->name;

    for (Class c = cls; c; c = c->super_class) 
    {
        for (struct objc_method_list* ml = c->methods; ml; ml = ml->next) 
        {
            for (int32_t i = 0; i < ml->count; i++) 
            {
                if (!strcmp(ml->methods[i].name, name))
                {
                    return ml->methods[i].imp;
                }
            }
        }
    }

    return (IMP)0;
}

static BOOL is_registered_class(Class c)
{
    for (uint32_t i = 0; i < g_class_count; i++)
    {
        if (g_classes[i] == c)
        {
            return YES;
        }
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

    if (g_class_count >= OBJC_MAX_CLASSES)
    {
        return;
    }

    g_classes[g_class_count++] = cls;
}

static Class find_class_by_name(const char* name)
{
    for (uint32_t i = 0; i < g_class_count; i++)
    {
        if (!strcmp(g_classes[i]->name, name))
        {
            return g_classes[i];
        }
    }
    return (Class)0;
}

static void resolve_class(Class cls)
{
    if (!cls)
    {
        return;
    }

    if (cls->super_class && !is_registered_class(cls->super_class))
    {
        const char* super_name = (const char*)cls->super_class;
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
            meta->super_class = cls->super_class ? cls->super_class->isa : 0;
        }
        else if (!is_registered_class(meta->super_class))
        {
            const char* super_name = meta->super_class;
            Class s = find_class_by_name(super_name);
            meta->super_class = s ? s->isa : 0;
        }
    }
}

void resolve_all_classes(void)
{
    for (uint32_t i = 0; i < g_class_count; i++)
    {
        resolve_class(g_classes[i]);
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
        return (IMP)objc_nil_method;
    }

    Class cls = receiver->isa;
    IMP imp = find_method(cls, selector);

    return imp ? imp : (IMP)objc_missing_method;
}

IMP objc_msg_lookup_super(struct objc_super* super, SEL selector)
{
    if (!super || !super->self)
    {
        return (IMP)objc_nil_method;
    }

    IMP imp = find_method(super->super_class, selector);

    return imp ? imp : (IMP)objc_missing_method;
}

void __objc_exec_class(void* module, ...)
{
    struct objc_module* m = (struct objc_module*)module;

    if (!m || !m->symtab)
    {
        return;
    }

    struct objc_symtab* s = m->symtab;

    for (uint16_t i = 0; i < s->class_count; i++)
    {
        // printf("Enter Register Class %d\r\n", i);
        register_class((Class)s->defs[i]);
    }
}

id objc_alloc_object(Class cls)
{
    if (!cls || cls->instance_size <= 0)
    {
        return nil;
    }

    id obj = (id)malloc(cls->instance_size);

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
