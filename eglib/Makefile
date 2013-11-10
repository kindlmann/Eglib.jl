
CC = gcc
CFLAGS  = -g -W -Wall -fPIC

SRCS = egvec.c egop.c
OBJS = $(SRCS:.c=.o)
LIBNAME = eglib
DEMO = egdemo
SHLIBEXT = dylib
LIBTOOL = libtool
LIB = lib$(LIBNAME).$(SHLIBEXT)

all:    $(LIB) $(DEMO)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJS)
	$(LIBTOOL) -o $(LIB) $(OBJS)

$(DEMO): $(LIB) $(DEMO).c
	$(CC) $(DEMO).c -o $(DEMO) -L. -l$(LIBNAME) -lm

clean:
	rm -f *.o $(LIB) $(DEMO)
