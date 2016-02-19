# "initial-exec" TLS variables and dlopen(3)

## Description

This test program reproduces how Mesa's and NVIDIA's `libGL.so` use
static TLS variables, using the "`initial-exec`" model.

When `libGL.so` is dlopen()'d directly or indirectly, the application
crashes on FreeBSD. This happens with Firefox and Mesa when the latter
is built with `--enable-glx-tls`. Firefox dlopen()'s `libxul.so` which
is linked to `libGL.so`. `LD_PRELOAD`'ing `libGL.so` works around the
crash. This test program is here to help understand the issue and fix
it.

## How to build and test

```
$ make test
```

Two programs and a library are compiled:
* `app-link`, which is linked to `libfoo.so`;
* `app-dlopen`, who dlopen()'s `libfoo.so`;
* `libfoo.so`, a simple library with a TLS variable.

`app-linked` works fine and prints:
```
$ ./app-link
foo: 2016
```

`app-dlopen` segfaults.
