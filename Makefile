.PHONY: all clean

all: app-link app-dlopen libfoo.so

clean:
	rm -f app-link app-dlopen libfoo.so *.core

test: all
	LD_LIBRARY_PATH=. ./app-link
	./app-dlopen

app-link: app.c libfoo.so
	$(CC) -g -Wall -O0 -DLINK -I. -L. -lfoo -o $@ app.c

app-dlopen: app.c libfoo.h libfoo.so
	$(CC) -g -Wall -O0 -DDLOPEN -o $@ app.c

libfoo.so: libfoo.c libfoo.h
	$(CC) -g -Wall -O0 -shared -fPIC -o $@ libfoo.c
