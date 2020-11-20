
#include "eglib.h"
#include "eglibPrivate.h"

int
_egVecAlloc(egVec *evec, size_t slen, unsigned int nn) {
  static const char me[]="_egVecAlloc";

  if (evec->desc) { free(evec->desc); }
  evec->desc = EG_CALLOC(slen+1, char);
  if (!evec->desc) {
    fprintf(stderr, "%s: couldn't allocate %u chars\n",
            me, (unsigned int)slen);
    return 1;
  }
  if (!( evec->vv && evec->nn == nn )) {
    if (evec->vv) { free(evec->vv); }
    evec->vv = EG_CALLOC(nn, float);
    if (!evec->vv) {
      fprintf(stderr, "%s: couldn't allocate %u floats\n", me, nn);
      return 1;  /* possible leak */
    }
    evec->nn = nn;
  }
  return 0;
}

egVec *
egVecNew(unsigned int nn) {
  static const char me[]="egVecNew";
  egVec *ret;

  if (!nn) {
    fprintf(stderr, "%s: need nn > 0\n", me);
    return NULL;
  }
  ret = EG_CALLOC(1, egVec);
  if (!ret) {
    fprintf(stderr, "%s: couldn't allocate egVec\n", me);
    return NULL;
  }
  if (_egVecAlloc(ret, 0, nn)) {
    fprintf(stderr, "%s: problem allocating\n", me);
    return NULL; /* possible leak */
  }
  strcpy(ret->desc, "");
  return ret;
}

void
egVecNix(egVec *evec) {
  static const char me[]="egVecNix";

  if (!evec) {
    fprintf(stderr, "%s: got NULL pointer\n", me);
    return;
  }
  if (evec->desc) { free(evec->desc); }
  if (evec->vv) { free(evec->vv); }
  free(evec);
  return;
}

int
egVecSet(egVec *evec, float dd) {
  static const char me[]="egVecSet";
  unsigned int ii, nn;
  char buff[512];

  sprintf(buff, "%g", dd);
  if (!evec) {
    fprintf(stderr, "%s: got NULL pointer\n", me);
    return 1;
  }
  /* too bad _egVecAlloc not usable for this */
  if (evec->desc) { free(evec->desc); }
  evec->desc = strdup(buff);
  nn = evec->nn;
  for (ii=0; ii<nn; ii++) {
    evec->vv[ii] = sin(dd*EG_AFFINE(0, ii, nn, 0, 2*EG_PI));
  }
  return 0;
}

int
egVecCopy(egVec *dst, const egVec *src) {
  static const char me[]="egVecCopy";
  unsigned int ii, nn;

  if (!(dst && src)) {
    fprintf(stderr, "%s: got NULL pointer\n", me);
    return 1;
  }
  if (_egVecAlloc(dst, strlen(src->desc), src->nn)) {
    fprintf(stderr, "%s: trouble allocating output\n", me);
    return 1;
  }
  strcpy(dst->desc, src->desc);
  nn = src->nn;
  for (ii=0; ii<nn; ii++) {
    dst->vv[ii] = src->vv[ii];
  }
  return 0;
}

int
egVecPrint(FILE *file, const egVec *evec) {
  static const char me[]="egVecPrint";
  unsigned int ii;

  if (!( file && evec )) {
    fprintf(stderr, "%s: got NULL pointer\n", me);
    return 1;
  }
  fprintf(file, "# %s\n", evec->desc);
  for (ii=0; ii<evec->nn; ii++) {
    fprintf(file, "%3u %g\n", ii, evec->vv[ii]);
  }
  return 0;
}
