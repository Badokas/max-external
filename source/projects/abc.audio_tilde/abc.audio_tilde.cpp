#include "c74_msp.h"

using namespace c74::max;

#define OBJECT_NAME "abc.audio~" // name of the object

static t_class *this_class; // required global pointer to this class

typedef struct _abc
{
    t_pxobject x_obj;
} t_abc;

void *abc_new(t_symbol *s, short ac, t_atom *av);
void  abc_free(t_abc *x);
void  abc_in1(t_abc *x, long n);
void  abc_perform64(t_abc *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void  abc_dsp64(t_abc *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void  abc_assist(t_abc *x, void *b, long m, long a, char *s);

void ext_main(void *r)
{
    this_class = class_new(OBJECT_NAME, (method)abc_new, (method)abc_free, (short)sizeof(t_abc), 0L, A_DEFFLOAT, 0);
    class_addmethod(this_class, (method)abc_in1, "in1", A_SYM, 0);
    class_addmethod(this_class, (method)abc_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(this_class, (method)abc_assist, "assist", A_CANT, 0);

    class_dspinit(this_class);
    class_register(CLASS_BOX, this_class);

    return 0;
}

void abc_in1(t_abc *x, long n) {}

void abc_dsp64(t_abc *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    dsp_add64(dsp64, (t_object *)x, (t_perfroutine64)abc_perform64, 0, NULL);
}

void abc_perform64(t_abc *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    double *in  = ins[0];
    double *out = outs[0];

    int n = (int)sampleframes;

    while(n--)
        *out++ = *in++;
}

void abc_assist(t_abc *x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_OUTLET)
        sprintf(s, "(signal) Audio input");
    else
        sprintf(s, "(signal) Audio output");
}

void abc_free(t_abc *x) {}

void *abc_new(t_symbol *s, short ac, t_atom *av)
{
    t_abc *x = (t_abc *)object_alloc((t_class *)this_class);

    if(!x)
        return (x);

    dsp_setup((t_pxobject *)x, 1);
    outlet_new((t_object *)x, "signal");

    object_post((t_object *)x, "Hello from abc.audio~");

    return (x);
}
