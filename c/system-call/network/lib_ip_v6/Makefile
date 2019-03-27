OBJS = setup_client.o setup_server.o setup_mserver.o chop_newline.o
AR   = ar -qc

lib.a:	$(OBJS)
	$(RM) $@
	$(AR) $@ $(OBJS)

$(OBJS):	lib.h

clean:
	$(RM) *.o lib.a
