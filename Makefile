CFLAGS+=-std=c89 -Wall -pedantic -O3

example: example.c btprnt.h
	$(CC) $(CFLAGS) $< -o $@

btprnt.h: btprnt.org
	worgle -Werror -g btprnt.org

clean:
	$(RM) btprnt.h out.pbm example
