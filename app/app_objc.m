#include "app_objc.h"
#include <object.h>

#include <stdio.h>

@interface Test : Object {
@public
    int value;
}

- (int)value;
- (void)setValue:(int)v;

@end

@implementation Test
- (int)value
{
    return value;
}

- (void)setValue:(int)v
{
    value = v;
}
@end

void test_objc_call()
{
    printf("HEN::-> test_objc_call entered...\r\n");

    Test* t = [[Test alloc] init];

    [t setValue: 30];

    int v = [t value];

    printf("HEN::-> It's now [t value] is %d\r\n", v);

    [t release];
}
