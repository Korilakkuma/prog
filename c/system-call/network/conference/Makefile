LIBDIR = ../lib
LIB    = $(LIBDIR)/lib.a
OBJS1  = server.o sessionman.o
OBJS2  = client.o session.o
CFLAGS = -I$(LIBDIR)

all:	s c

s:	$(OBJS1)
	gcc -Wall -o $@ $^ $(LIB) -lcurses
c:	$(OBJS2)
	gcc -Wall -o $@ $^ $(LIB) -lcurses

server.o:	sessionman.h

client.o:	session.h

clean:
	$(RM) s c *.o *~
