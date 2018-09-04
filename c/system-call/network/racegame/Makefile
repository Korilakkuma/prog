LIBDIR = ../lib
LIB    = $(LIBDIR)/lib.a
OBJS1  = server.o sessionman.o
OBJS2  = client.o session.o
CFLAGS = -I$(LIBDIR)

all:	s c

s:	$(OBJS1)
	gcc -Wall -o $@ $^ $(LIB)
c:	$(OBJS2)
	gcc -Wall -o $@ $^ $(LIB) -lcurses
data_ed: data_ed.o
	gcc -Wall -o $@ $^ -lcurses
checker: checker.o
	gcc -Wall -o $@ $^
server.o:	race.h sessionman.h

client.o:	race.h session.h

data_ed.o checker.o session.o sessionman.o:	race.h

clean:
	$(RM) $(OBJS1) $(OBJS2) s c data_ed checker *~
