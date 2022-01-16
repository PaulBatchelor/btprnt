CFLAGS+=-std=c89 -Wall -pedantic -O3

default: example libbtprnt.a

example: example.c btprnt.h
	$(CC) $(CFLAGS) $< -o $@

btprnt.h: btprnt.org
	worgle -Werror -g btprnt.org

libbtprnt.a: btprnt.o
	$(AR) rcs $@ $<

install: btprnt.h libbtprnt.a
	cp btprnt.h /usr/local/include
	cp libbtprnt.a /usr/local/lib

clean:
	$(RM) btprnt.h out.pbm example libbtprnt.a btprnt.o
