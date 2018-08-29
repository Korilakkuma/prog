LIBDIR = ../lib
LIB    = $(LIBDIR)/lib.a
CFLAGS = -I$(LIBDIR)

all:	s c

s:	server.o session.o
	gcc -Wall -o $@ $^ $(LIB) -lcurses

c:	client.o session.o
	gcc -Wall -o $@ $^ $(LIB) -lcurses

server.o client.o:	tag.h session.h

clean:
	$(RM) s c *.o *~
