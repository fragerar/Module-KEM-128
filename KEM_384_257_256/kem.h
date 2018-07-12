#ifndef KEM_H
#define KEM_H

#include "parameters.h"

void add_key(Poly* p, unsigned char* k);
void decode_key(const Poly* p, unsigned char* k);

void fill_error_poly(Poly* p, unsigned char* r);

void pgm_dot_product(const Poly* A, const Poly* B, Poly* res, int k);

void sub_poly_packed(const Packed_poly* a, const Poly* b, Poly* res);
void pgm_pointwise_add_mul_packed(const Poly* a, const Poly* b, Packed_poly* res);

void encaps(Packed_poly* U, Packed_poly* V, unsigned char* k, unsigned char* randomness);
void decaps(Packed_poly* U, Packed_poly* V, unsigned char* k);

void CCA_encaps(CCA_ciphertext* ct, unsigned char* k);
void CCA_decaps(CCA_ciphertext* ct, unsigned char* k);

#endif

