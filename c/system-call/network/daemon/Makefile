LIBDIR  = ../lib
LIB     = $(LIBDIR)/lib.a
CC      = gcc -Wall
CFLAGS  = -I$(LIBDIR)
OBJS    = bb0d.o bb1d.o bb9d.o bbreader.ob bb9reader.o service.o session.o
DAEMONS = bb0d bb1d bb9d
CLIENTS = bbreader bb9reader

all:	$(DAEMONS) $(CLIENTS)

bb0d:	bb0d.o service.o
	$(CC) -o $@ $^

bb1d:	bb1d.o service.o
	$(CC) -o $@ $^

bb9d:	bb9d.o service.o
	$(CC) -o $@ $^

bbreader:	bbreader.o session.o
	$(CC) -o $@ $^ $(LIB)

bb9reader:	bb9reader.o session.o
	$(CC) -o $@ $^ $(LIB)

$(OBJS):	bb.h

clean:
	$(RM) $(DAEMONS) $(CLIENTS) $(OBJS) *~

v0:	bb0d bbreader

v1:	bb1d bbreader

v9: bb9d bb9reader
