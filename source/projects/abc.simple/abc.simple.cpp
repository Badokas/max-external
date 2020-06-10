#include "c74_msp.h"

using namespace c74::max;

#define OBJECT_NAME "abc.simple" // name of the object

static t_class *this_class = nullptr; // required global pointer to this class

typedef struct _abc
{
    t_object x_obj;
} t_abc;

void *abc_new(t_symbol *s, short ac, t_atom *av);
void  abc_free(t_abc *x);

void ext_main(void *r)
{
    this_class = class_new(OBJECT_NAME, (method)abc_new, (method)abc_free, (short)sizeof(t_abc), 0L, A_DEFFLOAT, 0);

    class_register(CLASS_BOX, this_class);
}

void *abc_new(t_symbol *s, short ac, t_atom *av)
{
    t_abc *x = (t_abc *)object_alloc((t_class *)this_class);
    object_post((t_object *)x, "Hello from abc.hello");

    return (x);
}

void abc_free(t_abc *x) {}
