#include <err.h>
#include <stdio.h>

#ifdef DLOPEN
#include <dlfcn.h>
#endif

#ifdef LINK
#include "libfoo.h"
#endif

#ifdef DLOPEN
static void
show_dlerror(const char *fn)
{
	const char *errstr;

	errstr = dlerror();
	if (errstr != NULL)
		warnx("%s: %s", fn, errstr);
	else
		warnx("%s: dlerror() returned NULL, huh?", fn);
}

#endif
int
main(int argc, char *argv[])
{

#ifdef DLOPEN
	void *handle;
	void *(*foo)(void);

	handle = dlopen("./libfoo.so", RTLD_LAZY);
	if (handle == NULL) {
		show_dlerror("dlopen");
		return (1);
	}

	foo = dlsym(handle, "foo");
	if (foo == NULL) {
		show_dlerror("dlsym");
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
