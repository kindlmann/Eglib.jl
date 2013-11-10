
#include "eglib.h"

void
usage(const char *me) {
  /*                      0   1      2    (3) */
  fprintf(stderr, "usage: %s <N> <outfile>\n", me);
  return;
}

int main(int argc, const char **argv) {
  const char *me, *fname;
  FILE *file;
  unsigned int nn;
  egVec *A, *B, *C, *D;

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

  A = egVecNew(nn);
  B = egVecNew(nn);
  C = egVecNew(nn);
  D = egVecNew(nn);

  if (egVecSet(A, 1)
      || egVecSet(B, 2)
      || egVecCopy(C, B)
      || egVecOperate(D, egOpAdd, A, C)
      || egVecPrint(file, D)) {
    fprintf(stderr, "%s: problem\n", me);
    fclose(file);
    return 1;
  }

  egVecNix(A);
  egVecNix(B);
  egVecNix(C);
  egVecNix(D);

  fclose(file);
  return 0;
}
