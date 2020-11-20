#include <stdio.h>
#include <dlfcn.h>
#include "eglib.h"

#ifndef SHLIB_EXT
  #error "Need SHLIB_EXT defined"
#endif
#define LIBNAME ("./libeg." SHLIB_EXT)

void
usage(const char *me) {
  /*                      0   1      2    (3) */
  fprintf(stderr, "usage: %s <N> <outfile>\n", me);
  return;
}

int main(int argc, const char **argv) {
  const char *me;
  FILE *file;
  unsigned int nn;
  egVec *A, *B, *C, *D;

  void *lib;
  egVec *(*VecNew)(unsigned int nn);
  void (*VecNix)(egVec *egv);
  int (*VecSet)(egVec *egv, float kk);
  int (*VecCopy)(egVec *dst, const egVec *src);
  int (*VecPrint)(FILE *file, const egVec *egv);
  egOp *OpAdd;
  egOp *OpMultiply;
  int (*VecOperate)(egVec *dst, const egOp *op,
                    const egVec *srcA, const egVec *srcB);

  me = argv[0];
  if (3 != argc) {
    usage(me);
    return 1;
  }
  if (1 != sscanf(argv[1], "%u", &nn)) {
    fprintf(stderr, "%s: couldn't parse %s as uint\n", me, argv[1]);
    usage(me);
    return 1;
  }
  if (!(file = fopen(argv[2], "w"))) {
    fprintf(stderr, "%s: couldn't open %s for writing\n", me, argv[2]);
    usage(me);
    return 1;
  }

  if (!(lib = dlopen(LIBNAME, RTLD_LAZY))) {
    fprintf(stderr, "dlerror: %s\n", dlerror());
    exit(1);
  }
  VecNew = dlsym(lib, "egVecNew");
  VecNix = dlsym(lib, "egVecNix");
  VecSet = dlsym(lib, "egVecSet");
  VecCopy = dlsym(lib, "egVecCopy");
  VecPrint = dlsym(lib, "egVecPrint");
  OpAdd = *((void**)dlsym(lib, "egOpAdd"));
  OpMultiply = *((void**)dlsym(lib, "egOpMultiply"));
  VecOperate = dlsym(lib, "egVecOperate");

  printf("VecNew = %p\n", VecNew);
  printf("OpAdd(%p)->str = \"%s\"\n", OpAdd, OpAdd->str);
  printf("OpMultiply(%p)->str = \"%s\"\n", OpMultiply, OpMultiply->str);
  /* learned that if you've linked an executable with a shared library
     (i.e. for this, adding "-L.  -lel" to link line) and then also
     get symbols via dlopen/dlsym, they will be the same as from the
     linked library */
  /*
  printf("egVecNew = %p\n", egVecNew);
  printf("egOpAdd(%p)->str = \"%s\"\n", egOpAdd, egOpAdd->str);
  printf("egOpMultiply(%p)->str = \"%s\"\n", egOpMultiply, egOpMultiply->str);
  */


  A = VecNew(nn);
  B = VecNew(nn);
  C = VecNew(nn);
  D = VecNew(nn);

  if (VecSet(A, 0.5)
      || VecSet(B, 1.0)
      || VecOperate(C, OpAdd, A, B)
      || VecCopy(B, C)
      || VecSet(C, 2)
      || VecOperate(D, OpMultiply, B, C)
      || VecPrint(file, D)) {
    fprintf(stderr, "%s: problem\n", me);
    fclose(file);
    return 1;
  }

  VecNix(A);
  VecNix(B);
  VecNix(C);
  VecNix(D);

  fclose(file);
  return 0;
}
