
CC = gcc
CFLAGS  = -g -W -Wall

# http://stackoverflow.com/questions/714100/os-detecting-makefile
ifeq ($(OS), WINNT)
  SHLIB_EXT = dll
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
    SHLIB_EXT = so
    CFLAGS += -fPIC
    LD = ld -shared
  endif
  ifeq ($(UNAME_S),Darwin)
    SHLIB_EXT = dylib
    CFLAGS += -dynamic
    LD = libtool -dynamic
  endif
endif

SRCS = egvec.c egop.c
HDRS = eglib.h eglibPrivate.h
OBJS = $(SRCS:.c=.o)
LIBNAME = eg
DEMO = egdemo
DLDEMO = dlegdemo
LIB = lib$(LIBNAME).$(SHLIB_EXT)

all: $(LIB) $(DEMO) $(DLDEMO)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJS)
	$(LD) -o $(LIB) $(OBJS) -lm

$(DEMO): $(LIB) $(DEMO).c
	$(CC) $(CFLAGS) $(DEMO).c -o $(DEMO) -L. -l$(LIBNAME) -lm

$(DLDEMO): $(HDRS) $(DLDEMO).c
#  if using version that only uses dlopen/dlsym
	$(CC) $(CFLAGS) -DSHLIB_EXT=\"$(SHLIB_EXT)\" $(DLDEMO).c -o $(DLDEMO) -lm
#  if using direct references (not via dlsym) to libeg symbols
#	$(CC) $(CFLAGS) -DSHLIB_EXT=\"$(SHLIB_EXT)\" $(DLDEMO).c -o $(DLDEMO) -L. -l$(LIBNAME) -lm

clean:
	rm -rf *.o $(LIB) $(DEMO) $(DEMO).dSYM
