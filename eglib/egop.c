
#include "eglib.h"
#include "eglibPrivate.h"

static float opAdd(float a, float b)      { return a + b; }
static float opMultiply(float a, float b) { return a * b; }

static egOp _egOpAdd      = { "+", opAdd };
static egOp _egOpMultiply = { "*", opMultiply };

egOp *const egOpAdd = &_egOpAdd;
egOp *const egOpMultiply = &_egOpMultiply;

int
egVecOperate(egVec *dst, const egOp *op,
             const egVec *srcA, const egVec *srcB) {
  static const char me[]="egVecOperate";
  size_t slen;
  unsigned int ii, nn;

  if (!( dst && op && srcA && srcB )) {
    fprintf(stderr, "%s: got NULL pointer\n", me);
    return 1;
  }
  if (srcA->nn != srcB->nn) {
    fprintf(stderr, "%s: lengths of A (%u) and B (%u) don't match\n",
            me, srcA->nn, srcB->nn);
    return 1;
  }
  slen = (strlen(srcA->desc) + strlen(op->str)
          + strlen(srcA->desc) + strlen("()()"));
  if (_egVecAlloc(dst, slen + 1, srcA->nn)) {
    fprintf(stderr, "%s: unable to allocate output\n", me);
    return 1;
  }

  sprintf(dst->desc, "(%s)%s(%s)", srcA->desc, op->str, srcB->desc);
  nn = srcA->nn;
  for (ii=0; ii<nn; ii++) {
    dst->vv[ii] = op->f(srcA->vv[ii], srcB->vv[ii]);
  }
  return 0;
}
