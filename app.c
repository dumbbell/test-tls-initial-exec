#include <err.h>
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
		warnx("dlopen: %s", dlerror());
		return (1);
	}

	foo = dlsym(handle, "foo");
	if (foo == NULL) {
		warnx("dlsym: %s", dlerror());
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
