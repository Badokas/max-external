#include "c74_msp.h"

using namespace c74::max;

#define OBJECT_NAME "abc.simple" // name of the object

static t_class *demo_class; // required global pointer to this class

typedef struct _demo
{
    t_object x_obj;
} t_demo;

void *demo_new(t_symbol *s, short ac, t_atom *av);
void  demo_free(t_demo *x);

int C74_EXPORT main(void)
{
    t_class *c;

    c = class_new(OBJECT_NAME, (method)demo_new, (method)demo_free, (short)sizeof(t_demo), 0L, A_DEFFLOAT, 0);

    class_register(CLASS_BOX, c);
    demo_class = c;

    return 0;
}

void *demo_new(t_symbol *s, short ac, t_atom *av)
{
    t_demo *x = (t_demo *)object_alloc((t_class *)demo_class);
    object_post((t_object *)x, "Hello from demo.hello");

    return (x);
}

void demo_free(t_demo *x) {}
