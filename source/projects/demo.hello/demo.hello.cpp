#include "c74_msp.h"

using namespace c74::max;

//#define DEBUG			//enable debugging messages

#define OBJECT_NAME "demo.hello" // name of the object

/* for the assist method */
#define ASSIST_INLET 1
#define ASSIST_OUTLET 2

static t_class *demo_class; // required global pointer to this class

/* structure definition for this object */
typedef struct _demo
{
	t_object x_obj;
} t_demo;

/* method definitions for this object */
void *demo_new(t_symbol *s, short argc, t_atom *argv);
void demo_free(t_demo *x);

/* method definitions for debugging this object */
#ifdef DEBUG
#endif /* DEBUG */

/********************************************************************************
void main(void)

inputs:			nothing
description:	called the first time the object is used in MAX environment;
		defines inlets, outlets and accepted messages
returns:		int
********************************************************************************/
int C74_EXPORT main(void)
{
	t_class *c;

	c = class_new(OBJECT_NAME, (method)demo_new, (method)demo_free, (short)sizeof(t_demo), 0L, A_DEFFLOAT, 0);
	class_dspinit(c); // add standard functions to class

#ifdef DEBUG
#endif /* DEBUG */

	class_register(CLASS_BOX, c); // register the class w max
	demo_class = c;

#ifdef DEBUG
#endif /* DEBUG */

	return 0;
}

void *demo_new(t_symbol *s, short argc, t_atom *argv)
{
	t_demo *x = (t_demo *)object_alloc((t_class *)demo_class);

	// outlet_new((t_pxobject *)x, "signal"); // left outlet
	// outlet_new((t_pxobject *)x, "signal"); // right outlet
	object_post((t_object *)x, "Hello from demo.hello");

#ifdef DEBUG
	object_post((t_object *)x, "new function was called");
#endif /* DEBUG */

	/* return a pointer to the new object */
	return (x);
}

void demo_free(t_demo *x)
{
}
