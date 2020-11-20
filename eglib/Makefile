
CC = cc
CFLAGS  = -g -W -Wall -Wextra

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
    #LD = libtool -dynamic
    LD = clang -shared -fpic
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
	$(LD) $(OBJS) -o $(LIB)

$(DEMO): $(LIB) $(DEMO).c
	$(CC) $(CFLAGS) $(DEMO).c -o $(DEMO) -L. -l$(LIBNAME) -lm

## if using only dlopen/dlsym to get symbols from libeg
$(DLDEMO): $(HDRS) $(DLDEMO).c
	$(CC) $(CFLAGS) -DSHLIB_EXT=\"$(SHLIB_EXT)\" $(DLDEMO).c -o $(DLDEMO) -ldl -lm

## if using direct references (not via dlsym) to libeg symbols
#$(DLDEMO): $(HDRS) $(DLDEMO).c
#	$(CC) $(CFLAGS) -DSHLIB_EXT=\"$(SHLIB_EXT)\" $(DLDEMO).c -o $(DLDEMO) -L. -l$(LIBNAME) -ldl -lm

clean:
	rm -rf *.o $(LIB) $(DEMO) $(DLDEMO) $(DEMO).dSYM
