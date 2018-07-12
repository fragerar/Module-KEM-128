#ifndef PARAMS_H
#define PARAMS_H

#define Q 257
#define N 128
#define inv_N 255
#define K 3
#define LAMBDA 16               // Symmetric security 
#define ERROR_POLY_ENTROPY 32   // Binomial sampling requires 2 bits per coef.
#define PACK_SIZE 144

typedef struct{
int c[N];
} Poly;

typedef struct{
unsigned char bytes[PACK_SIZE];
} Packed_poly;

typedef struct{
  unsigned char nonce[LAMBDA];
  Packed_poly U[K];
  Packed_poly V;
} CCA_ciphertext;

#endif

