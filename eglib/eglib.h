
#ifndef EGLIB_HAS_BEEN_INCLUDED
#define EGLIB_HAS_BEEN_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

/* see what happens with #define's */
#define EG_PI 3.14159265358979323846
#define EG_AFFINE(i,x,I,o,O) ( \
 ((double)(O)-(o))*((double)(x)-(i)) / ((double)(I)-(i)) + (o))
#define EG_CALLOC(N, T) (T*)(calloc((N), sizeof(T)))

/* see what happens with an enum */
enum {
  egEnumNegOne = -1,
  egEnumZero,
  egEnumOne,
  egEnumTwo,
  egEnumThree
};

/*
** things to try adding to structs:
** fixed-length vector
** variables of type size_t and ptrdiff_t
*/

typedef struct {
  char *str;
  float (*f)(float, float);
} egOp;

typedef struct {
  char *desc;
  unsigned int nn;
  float *vv;
} egVec;

/* egvec.c */
extern egVec *egVecNew(unsigned int nn);
extern void egVecNix(egVec *egv);
extern int egVecSet(egVec *egv, float kk);
extern int egVecCopy(egVec *dst, const egVec *src);
extern int egVecPrint(FILE *file, const egVec *egv);

/* egop.c */
extern egOp *const egOpAdd;
extern egOp *const egOpMultiply;
extern int egVecOperate(egVec *dst, const egOp *op,
                        const egVec *srcA, const egVec *srcB);

extern void* const get_add();
extern void* const get_multiply();

#ifdef __cplusplus
}
#endif

#endif /* EGLIB_HAS_BEEN_INCLUDED */
