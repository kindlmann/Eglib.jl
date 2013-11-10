
CC = gcc
CFLAGS  = -g -W -Wall -fPIC

# file extensions
ifeq ($(OS), WINNT)
  SHLIB_EXT = dll
  SHELL_EXT = bat
else ifeq ($(OS), Darwin)
  SHLIB_EXT = dylib
  SHELL_EXT = sh
else
  SHLIB_EXT = so
  SHELL_EXT = sh
endif

SRCS = egvec.c egop.c
OBJS = $(SRCS:.c=.o)
LIBNAME = eglib
DEMO = egdemo
LIBTOOL = libtool
LIB = lib$(LIBNAME).$(SHLIB_EXT)

all:    $(LIB) $(DEMO)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJS)
	$(LIBTOOL) -o $(LIB) $(OBJS)

$(DEMO): $(LIB) $(DEMO).c
	$(CC) $(DEMO).c -o $(DEMO) -L. -l$(LIBNAME) -lm

clean:
	rm -f *.o $(LIB) $(DEMO)
