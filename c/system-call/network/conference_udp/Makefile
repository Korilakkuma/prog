LIBDIR = ../lib
LIB    = $(LIBDIR)/lib.a
OBJS1  = server.o sessionman.o
OBJS2  = client.o session.o
CC     = gcc
CFLAGS = -I$(LIBDIR)

all:	s c

s:	$(OBJS1)
	$(CC) -Wall -o $@ $^
c:	$(OBJS2)
	$(CC) -Wall -o $@ $^ $(LIB) -lcurses

server.o:	mtalk2.h sessionman.h

client.o:	mtalk2.h session.h

sessionman.o session.o:	mtalk2.h

clean:
	$(RM) s c *.o *~
