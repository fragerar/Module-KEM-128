#ifndef TOOLS_H
#define TOOLS_H

#include "parameters.h"

int unpack_coef(const Packed_poly* x, unsigned i);
void pack_coef(Packed_poly* x, unsigned i, int val);

void pack(Poly* x, Packed_poly* y);
void unpack(Packed_poly* x, Poly* y);

void XOF(unsigned char *output, unsigned long long outlen, const unsigned char *input,  unsigned long long inlen);
void H(unsigned char* output, unsigned outlen, unsigned char* input, unsigned inlen);

int mm257(int a, int b);
int mod_q(int v);

#endif

