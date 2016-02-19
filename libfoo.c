#include <stdio.h>

#include "libfoo.h"

int now = 2016;

__thread void *tls_var __attribute__ ((tls_model("initial-exec")))
   = &now;

void
foo()
{
	int *now_p = tls_var;

	printf("foo: %d\n", *now_p);
}
