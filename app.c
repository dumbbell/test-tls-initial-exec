#include <stdio.h>

#ifdef DLOPEN
#include <dlfcn.h>
#endif

#ifdef LINK
#include "libfoo.h"
#endif

int
main(int argc, char *argv[])
{

#ifdef DLOPEN
	void *handle;
	void *(*foo)(void);

	handle = dlopen("./libfoo.so", RTLD_LAZY);
	if (handle == NULL) {
		perror("dlopen");
		return (1);
	}

	foo = dlsym(handle, "foo");
	if (foo == NULL) {
		perror("dlsym");
		dlclose(handle);
		return(1);
	}
#endif

	foo();

#ifdef DLOPEN
	dlclose(handle);
#endif

	return (0);
}
