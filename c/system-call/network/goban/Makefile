LIBDIR = ../lib
LIB    = $(LIBDIR)/lib.a
# CFLAGS = -I$(LIBDIR)

all:	s c

s:	server.o goban.o
	gcc -Wall -o $@ $^ $(LIB)

c:	client.o goban.o
	gcc -Wall -o $@ $^ $(LIB)

server.o client.o:	goban.h

clean:
	$(RM) s c *.o *~
