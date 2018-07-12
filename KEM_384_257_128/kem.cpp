#include "kem.h"
#include "utils.h"
#include "NTT.h"
#include <stdlib.h>
#include <avr/pgmspace.h>

const PROGMEM Poly A[K*K] = {{101, 102, 51, 6, -107, 104, -52, 113, -73, -60, -34, 83, 58, 100, 59, 120, -71, -110, 124, 44, -77, -37, -109, -94, 116, 17, -45, 18, 71, -98, -103, -99, 91, 57, -2, 98, -42, 44, -102, 86, -50, -37, -98, -71, -92, -110, -5, 28, -105, -61, -53, -125, 58, -114, -99, 73, -42, -52, 5, 31, 78, 87, 15, 102, -55, -73, -13, 57, 10, 72, 19, -63, 61, 44, 88, 44, -94, 0, 2, 80, -69, -126, 69, 104, 75, 105, -93, 112, 7, -17, -38, -43, -96, 66, 83, 107, -69, 75, 95, 16, 5, -44, -38, -91, -119, -34, -60, -98, -83, -115, 125, -22, 68, -94, 46, 20, -23, -107, -90, -107, -95, 71, -30, 108, -74, 124, 123, 90}, {-124, 86, -27, 74, -2, -31, -16, -128, 65, 98, -20, -19, 124, 19, 63, -107, 115, 64, 114, -96, -48, -64, 0, 69, -82, 88, -48, 86, -103, 29, 48, 96, 126, -75, 114, -47, -54, 70, -25, -26, -41, 91, 121, 122, 74, -97, -63, -90, 55, -8, -89, -127, -112, -49, -17, -100, 88, -27, -119, 55, -21, -85, -73, -21, 36, -48, 0, -7, 35, 47, -103, 84, 32, -90, 91, 103, 59, -86, -89, -33, 126, -21, -92, -90, -117, 36, -48, 49, 127, -19, -88, 54, -83, -42, 7, 81, 51, -60, 86, 89, 24, 34, -67, -112, -87, -104, 58, -28, 128, 24, -103, -55, -110, -99, -120, -39, 40, 92, -83, 119, -38, 127, -74, -123, -72, -101, 110, 74}, {-104, 34, -116, -59, -37, 114, -100, 78, -118, -75, -45, -28, 115, 45, -66, -35, -9, 121, -43, -1, 36, -47, 96, 4, 83, -101, -64, 67, 101, 78, 54, 25, 73, -80, -10, 29, -99, -124, -120, 60, -99, 122, -7, -26, 67, -103, 91, -128, 77, -29, 14, 71, 49, -34, 47, 128, 73, -94, -83, 34, -23, 87, -97, 62, 17, -106, -87, 1, -78, 55, 69, 41, -117, 52, -27, -49, -40, 95, 33, -95, -16, 56, -122, -127, -124, 83, -47, 108, -29, -84, 37, 92, 18, 97, -57, 115, 116, 87, 92, 27, -51, 107, 31, -92, 40, 14, -121, -25, 62, 119, 43, -6, -54, 86, 81, -95, 36, 61, -127, -111, -59, -107, -30, 16, 121, 43, 12, 10}, {-18, 95, 17, -117, -11, 119, 116, -76, -43, -106, 126, -45, -29, -64, -8, 29, 99, -96, -86, -104, -33, 25, -82, 47, 89, 57, -43, 75, -107, 100, -68, -100, 119, -35, -64, -74, -43, 38, 110, -17, -36, 59, -74, -8, 16, -123, 117, 38, 106, -62, 19, 32, -109, 19, 16, 107, 102, -82, 98, -72, 71, -10, 108, -96, -99, 59, 14, 125, 76, -107, -128, -47, -43, 52, 34, -115, -128, -19, 51, -82, 52, 7, 77, 114, -51, 102, 92, -117, -91, 98, 27, -92, -108, -89, -84, -25, -85, -124, -81, 3, 107, 89, 23, 0, 49, 19, 87, 21, -41, -112, -121, 85, 127, -70, 33, -34, -128, -20, 13, 55, -69, -6, 47, 96, -51, -93, -105, 65}, {41, 32, -123, 21, 9, 77, 17, -4, -66, 25, -43, -47, 18, -124, 97, 80, 103, 118, 114, 5, 48, 77, -114, -29, 15, 114, -16, 52, 126, -61, 30, -24, 98, 104, 33, -36, -38, 37, 105, -81, 44, 128, 92, -51, 62, -73, -71, -96, 117, 48, 83, 54, -109, 96, -14, 93, -98, -91, 73, -119, -89, 7, -74, 118, -83, -119, 12, -74, 12, -103, 23, 58, 52, 83, 64, -85, 52, -40, 5, 105, -76, -84, 90, 18, -90, 8, 11, -91, -61, 127, -10, -34, -30, 73, -103, -65, 24, 92, 25, -62, -118, -114, -106, 64, -33, -24, -36, -14, -95, -70, -22, 14, 76, 124, -15, -75, -25, 108, -81, 59, -117, -113, 103, -69, 7, 78, 41, -26}, {43, 128, -101, -75, -111, -50, 104, -99, 92, 7, -96, 14, 11, 63, -16, -92, -103, 85, -23, -16, 38, 63, 98, -31, 101, 75, 110, 3, -116, 34, 9, -75, 2, 98, -2, -32, 92, -125, -116, -113, -15, 112, -78, 96, 62, 45, 58, -74, -71, 58, 77, -76, -83, 86, 77, -126, -20, -29, 83, 26, -47, -109, 63, -105, -98, -15, -105, 30, 75, 115, -3, -53, 16, 92, 49, 10, -11, -40, 57, -60, -95, 80, 97, 96, 74, -12, 35, -101, 27, 2, -101, 84, -55, 66, -21, 124, -95, -30, -76, 12, -114, -112, -26, -113, -94, -98, -79, 36, 53, 24, 29, -5, 122, -21, -19, 91, -11, -93, -83, -33, 48, -46, 15, -9, -121, -63, 66, 56}, {-92, -86, -53, -4, 89, 23, -30, -32, -103, 124, 32, 100, 37, 53, -124, 26, -60, 36, -51, 118, -37, 82, -98, 117, -74, -46, -80, -15, 24, -14, 68, -100, 101, 27, 109, -83, 77, -101, -25, 31, -20, 22, -99, 37, -49, -62, 8, 86, 56, 68, 38, 40, -42, 108, -102, -16, 38, -16, 36, 13, -112, 108, 90, 110, 59, -84, -67, 99, -50, 108, -83, -33, 78, 70, -98, -108, 38, 67, -66, -6, -12, -118, -57, 87, -117, -33, 92, 70, 86, -113, -2, -45, -44, -68, -47, 42, -109, -68, 71, -84, -124, 30, 78, 32, 83, -5, -126, 37, 117, -61, 23, 16, -24, 78, 61, 125, -46, 82, 58, -84, 4, -86, -43, -85, 3, 107, -56, 104}, {18, -118, -9, -35, 109, 72, -44, -127, -87, 104, 49, 62, -42, -25, -33, -36, -52, -26, -96, 32, 62, -30, 78, -45, -74, -23, 126, -117, -41, 100, 68, 63, -108, -56, 126, -78, 119, -57, -24, -8, -117, -126, 94, 116, -48, 95, 69, -22, -94, 50, 53, -9, -111, -104, -48, -69, 43, -94, -81, -29, 98, 7, 100, -101, 38, -100, -31, 9, 42, -84, 47, 27, -127, -90, -124, 2, -18, -64, -2, 27, 63, 5, 94, 49, 9, 126, -83, -61, -3, -66, -36, 115, 123, 120, -48, -73, 109, -16, -36, 67, -68, -51, 97, 65, 61, -34, -41, -32, 37, -35, -24, -124, 124, 92, 68, 96, -48, -66, 83, 97, -68, -20, -86, -117, 106, 86, -54, 54}, {-76, 38, -91, 47, 114, -45, 91, -67, -39, 58, -95, -33, -79, 123, -13, -18, 86, 24, 43, 97, 52, 48, -48, -126, -42, 45, -70, -13, 62, -111, 38, 65, 39, -56, 97, 93, -90, 128, -90, 86, 122, -15, -10, -122, 106, 53, -15, -20, -120, 120, -86, 12, 5, 96, 33, 16, -29, 34, 31, 113, 105, -6, -58, 3, -78, 39, -89, -54, -61, -20, 45, -91, 94, -65, 79, 83, -115, 92, -33, -93, 73, -16, -93, 70, 24, 25, 88, 69, -19, -87, 34, -5, 115, -123, -28, 5, -116, 127, -67, 15, -42, -97, -118, -36, -71, 63, -58, 109, -20, 36, 96, 63, -108, -125, 32, 24, -61, 57, -103, 106, -31, 1, -80, -120, -105, 50, -26, -100}};
const PROGMEM Poly S[K] = {{119, -121, 99, -38, -20, -49, 33, -118, -81, 74, -80, -27, -30, 119, 28, 117, -71, -79, -3, -110, -53, -105, -79, -110, -72, 109, 6, 19, -36, -9, -112, 36, 26, -82, 48, 59, 45, 86, 21, -37, -29, -103, 66, 18, -91, 56, 22, 128, -99, -50, -118, 42, -4, -22, -109, -115, -57, 67, 124, 57, -121, -73, 68, 46, -54, -8, 11, -23, 59, 13, -114, -39, -11, -121, -61, -55, 94, -28, 121, 51, 30, 25, 48, -11, 125, -120, -73, -54, 31, 28, 98, -108, 18, 118, 32, -12, -80, 128, -83, 37, 122, 50, -69, 25, 87, 12, -89, -63, 71, -79, -94, -68, -116, -104, -115, -94, 33, 63, 86, -62, -61, -26, -69, 85, -104, -45, 13, 89}, {-127, 83, 41, -118, -12, 127, 54, -81, 86, 94, 92, -69, 104, 77, 50, -46, -44, 107, 106, -10, 42, 2, -72, 27, 67, -20, 13, 39, -30, 126, 117, 82, -32, 90, -105, 25, -47, -35, -94, -111, -117, -24, 0, -60, -65, -48, -61, 68, -35, 50, 75, 125, -120, 123, -77, -72, -62, 118, 46, -41, -71, -31, 56, -118, 104, 21, -123, -78, -31, -28, 38, -117, -106, 20, 86, 97, -22, -83, -121, -103, 53, 57, -82, -101, -67, 64, 32, 41, -31, -100, 40, -42, 67, 16, -67, -84, -41, -98, 92, 73, -106, -37, -125, 42, 96, 100, 13, -91, -125, -44, -103, 28, 46, -117, -107, -100, -76, 47, 26, 3, -92, 10, 51, -17, 109, 127, 127, -89}, {-53, 33, 58, 81, 72, -25, -12, 12, -120, -63, -15, 74, -2, -75, -41, 72, 26, -39, 124, 56, -59, 56, 57, 88, 76, -45, 25, -46, -37, 87, -50, -66, 84, 12, 23, 25, 105, -61, -97, -127, -7, -48, 102, 92, 39, -43, -122, 27, -58, -4, -104, -57, 31, -86, 87, 83, -107, -75, 83, 128, -65, 78, 55, 15, -50, 123, 55, 20, 61, 81, -41, -21, 124, 57, 55, 60, -48, -58, -126, 29, -34, 84, -32, -74, 37, -120, -33, 1, -64, -95, -49, -97, 47, 100, 82, 54, 25, -54, 104, 90, -31, -12, -84, 19, 53, -92, -99, 50, 85, 55, 94, -10, -92, 0, 89, -15, 60, -24, -48, 9, 65, 20, -113, -125, -28, 54, 92, -8}};
const PROGMEM Poly T[K] = {{71, 15, -7, -77, 25, 44, 123, -8, -43, 99, 33, -94, -52, 82, -40, 40, -85, 124, 25, 67, 21, 1, 87, 72, 77, -95, 60, -110, 42, -119, 88, 72, 96, -66, -116, -99, 25, -57, -103, 41, 61, -104, -106, 23, 2, -121, 70, -27, 20, -108, 59, 17, 100, 103, 42, 114, -5, -62, 81, -9, 18, 38, 93, -75, -60, -45, 47, 8, 69, 112, -122, 55, 7, 28, 23, -24, 35, -94, -29, -76, 104, -38, 101, 96, 5, 33, 49, -117, 106, -66, 58, 125, 38, -125, 12, -127, 70, -73, 85, -62, 53, -70, 20, -44, -62, -89, -84, -98, 39, -58, -98, -16, -19, 100, 62, -29, 117, -16, -43, -22, -72, -81, -123, -94, -67, -22, 106, -95}, {38, 97, -122, -10, -85, -5, 73, 28, 63, -111, -57, -128, -25, 18, 123, 125, 78, -43, -17, 66, -65, -36, -4, -114, -87, -90, -127, 33, -81, -18, 110, -128, 60, -43, -84, 109, -31, 31, 47, -94, -82, 77, -79, -22, 3, 0, 61, -100, 80, -45, 36, 72, 27, -104, 60, -119, -54, 79, 47, 40, -85, -119, 55, 84, -109, 2, -74, 102, 1, -65, -83, 122, 18, -78, -102, 120, -93, -46, -110, 55, 10, 82, 76, 123, -7, -56, -112, 101, 19, -17, -16, 31, -29, -17, 32, -51, 77, 63, 8, 44, -16, -72, -116, -94, -57, 43, 95, -56, -95, -48, -3, 77, -81, 82, -52, 126, 26, 20, 24, 98, -88, 69, 51, 9, -96, 0, 109, -87}, {73, 3, -62, 3, -87, 70, 117, 107, 52, -17, 87, -74, -35, 109, -110, -53, -109, 54, -71, -83, -108, 24, -10, -68, -75, 51, 2, 41, -57, 71, 80, -83, -44, -25, 103, -51, 21, -128, 58, -27, 76, -104, 119, 62, 109, 39, 77, -21, -113, 100, 26, 93, -58, -75, 90, 51, -61, 15, 42, 19, 121, 125, -87, 61, -16, 100, 84, 28, -74, 43, 106, 67, 74, 72, 93, -61, 77, 33, -66, -77, 12, 47, 79, -47, -128, -15, 120, 47, -19, -99, -13, 78, -122, -57, -29, -75, 82, 103, 109, 28, 30, 128, -85, -78, -33, 84, -71, -127, 89, -120, -74, -89, -97, -33, 104, -91, 69, -96, -97, 57, -98, 114, -32, -100, -72, 90, -87, 67}};
const PROGMEM unsigned char z[LAMBDA]={0xDE, 0xAD, 0xBE, 0xEF};


void add_key(Poly* p, unsigned char* k){
    /*
     * Adds encoding of k to the polynomial p
     */
    int i;
    
    for(i=0; i < LAMBDA*8; ++i) p->c[i] = mod_q(p->c[i] + ((k[i/8]>>(i%8))&1)*(Q/2));
}

void decode_key(const Poly* p, unsigned char* k){
    /*
     * Threshold decodes p and put the result in k
     */
    int i, v; 
    
    for(i=0; i < LAMBDA;   ++i) k[i] = 0;
    for(i=0; i < LAMBDA*8; ++i){
        v = p->c[i];
        k[i/8] += (((v > Q/4) || (v < -Q/4)) << (i%8));
    }
}

void fill_error_poly(Poly* p, unsigned char* r){
    /*
     * Sets p to an error polynomial.
     * Uses ERROR_POLY_ENTROPY bytes of r
     */
    int i;
    
    for(i=0; i < N/4;++i){
        p->c[i*4+0] = ((r[i] >> 0)&1) - ((r[i] >> 1)&1);
        p->c[i*4+1] = ((r[i] >> 2)&1) - ((r[i] >> 3)&1);
        p->c[i*4+2] = ((r[i] >> 4)&1) - ((r[i] >> 5)&1);
        p->c[i*4+3] = ((r[i] >> 6)&1) - ((r[i] >> 7)&1);   
    }
    
}

void sub_poly_packed(const Packed_poly* a, const Poly* b, Poly* res){
    /*
     * Computes a - b and puts the result in res
     * A is in packed form
     */
    int i;
    
    for(i=0; i < N; ++i) res->c[i] = mod_q( unpack_coef(a,i) - b->c[i]); 

}

void pgm_dot_product_packed(const Poly* A, const Packed_poly* B, Poly* temp, int k){
    /*
     * Computes dot product between to vectors of length k and puts the result in temp
     * All polynomials should be in frequency domain
     * A is stored unpacked in flash memory
     * B is in packed form
     */
    int i,j;
    
    for(j=0; j < N; ++j) temp->c[j] = mm257(pgm_read_word_near(A[0].c + j),unpack_coef(B,j));
    for(i=1; i < k; ++i) for(j=0; j < N; ++j) temp->c[j] = mod_q(temp->c[j] + pgm_read_word_near(A[i].c + j) * unpack_coef(&B[i],j)); 

}


void pgm_pointwise_add_mul_packed(const Poly* a, const Poly* b, Packed_poly* res){
    /*
     * Computes res = res + a * b with res in packed form
     * All polynomials should be in frequency domain 
     */
    int i, v;
    
    for(i=0; i < N; ++i) {
      v = unpack_coef(res,i);
      v = mod_q(v + pgm_read_word_near(a->c + i) * b->c[i]); 
      pack_coef(res, i, v);
    }
}
/*
void CCA_encaps(Packed_poly* ct, unsigned char* k){
    int i;
    unsigned char pk_m[2*LAMBDA];
    unsigned char k_hat_r[2*LAMBDA];
    
    for(i= 0; i < LAMBDA; ++i) pk_m[i] = pgm_read_word(T[0].c + i)&0xFF;
    for(i=LAMBDA; i < 2*LAMBDA; ++i) pk_m[i] = random()&0xFF;   

    H(k_hat_r, 2*LAMBDA, pk_m, 2*LAMBDA); //K,r = G(pk,m)
    encaps(ct,ct+K, pk_m+LAMBDA, k_hat_r+LAMBDA);
    
    for(i=LAMBDA; i < 2*LAMBDA; ++i) k_hat_r[i] = ct->bytes[i];
    
    H(k, LAMBDA, k_hat_r,2*LAMBDA);
}

void CCA_decaps(Packed_poly* ct, unsigned char* k){
    unsigned char pk_m[2*LAMBDA];
    unsigned char k_hat_r[2*LAMBDA];
    unsigned char h1[LAMBDA];
    unsigned char h2[LAMBDA];
    int i, correct=1;
    
    for(i=0; i < LAMBDA; ++i) pk_m[i] = pgm_read_word(T[0].c + i)&0xFF;
    
    decaps(ct,ct+K, pk_m+LAMBDA);
    H(k_hat_r, 2*LAMBDA, pk_m, 2*LAMBDA); //K,r = G(pk,m)
    H(h1, LAMBDA, ct->bytes,(K+1)*PACK_SIZE);  

    encaps(ct, ct+K, pk_m+LAMBDA, k_hat_r+LAMBDA);
    H(h2, LAMBDA, ct->bytes, (K+1)*PACK_SIZE); 

    for(i=0; i < LAMBDA; ++i) correct = correct & (h1[i] == h2[i]);
     
    correct = -correct; // 0x000000 or 0xFFFFFFFF
    
    for(i=0; i < LAMBDA; ++i)         k_hat_r[i] = (k_hat_r[i]&correct) | (pgm_read_word(z+i)&(~correct));
    for(i=LAMBDA; i < 2*LAMBDA; ++i)  k_hat_r[i] = ct->bytes[i];
    
    H(k, LAMBDA, k_hat_r,2*LAMBDA);
    
}*/


void CCA_encaps(CCA_ciphertext* ct, unsigned char* k){
    int i;
    unsigned char pk_m[2*LAMBDA];
    unsigned char k_hat_r[2*LAMBDA];
    
    for(i= 0; i < LAMBDA; ++i) pk_m[i] = pgm_read_word(T[0].c + i)&0xFF;
    for(i=LAMBDA; i < 2*LAMBDA; ++i) pk_m[i] = random()&0xFF;   

    H(k_hat_r, 2*LAMBDA, pk_m, 2*LAMBDA); //K,r = G(pk,m)
    encaps(ct->U,&(ct->V), pk_m+LAMBDA, k_hat_r+LAMBDA);
    
    for(i=0; i < LAMBDA; ++i) ct->nonce[i] = k_hat_r[i];
    
    H(k, LAMBDA, ct->nonce, LAMBDA+(K+1)*PACK_SIZE);
}

void CCA_decaps(CCA_ciphertext* ct, unsigned char* k){
    unsigned char pk_m[2*LAMBDA];
    unsigned char k_hat_r[2*LAMBDA];
    unsigned char h1[LAMBDA];
    unsigned char h2[LAMBDA];
    int i, correct=1;
    
    for(i=0; i < LAMBDA; ++i) pk_m[i] = pgm_read_word(T[0].c + i)&0xFF;
    
    decaps(ct->U,&(ct->V), pk_m+LAMBDA);
    H(k_hat_r, 2*LAMBDA, pk_m, 2*LAMBDA); //K,r = G(pk,m)
    H(h1, LAMBDA, (ct->U)->bytes, (K+1)*PACK_SIZE);  

    encaps(ct->U,&(ct->V), pk_m+LAMBDA, k_hat_r+LAMBDA);
    H(h2, LAMBDA, (ct->U)->bytes, (K+1)*PACK_SIZE); 

    for(i=0; i < LAMBDA; ++i) correct = correct & (h1[i] == h2[i]);
     
    correct = -correct; // 0x000000 or 0xFFFFFFFF
    
    for(i=0; i < LAMBDA; ++i) ct->nonce[i] = (k_hat_r[i]&correct) | (pgm_read_word(z+i)&(~correct));

    
    H(k, LAMBDA, ct->nonce, LAMBDA+(K+1)*PACK_SIZE);
    
}

void encaps(Packed_poly* U, Packed_poly* V, unsigned char* k, unsigned char* randomness){ 
    int i, j, random_size = (1+2*K)*ERROR_POLY_ENTROPY;  
    unsigned char random_tape[random_size]; 
    Poly x; 
    
    XOF(random_tape, random_size, randomness, LAMBDA); // extend seed into large entropy pool

    fill_error_poly(&x, random_tape); 
    add_key(&x,k);
    NTT(&x);
    pack(&x,V);    

    for(i=0; i < K; ++i){ // sample packed vector in K-rank module, coef. of ring elements from binomial 1 dist.
        fill_error_poly(&x, random_tape+ERROR_POLY_ENTROPY*(i+1));
        NTT(&x); // frequency domain
        pack(&x, &U[i]);
    }
    
    for(i=0; i < K; ++i){ // Matrix-vector multiplication with iterative sampling
        fill_error_poly(&x,random_tape+ERROR_POLY_ENTROPY*(K+1+i));
        NTT(&x);
        
        for(j=0; j < K; ++j) pgm_pointwise_add_mul_packed(&A[i*K + j], &x, &U[j]);   
                 
        pgm_pointwise_add_mul_packed(&T[i],&x,V);
    }
}


void decaps(Packed_poly* U, Packed_poly* V, unsigned char* k){
    Poly temp;
    
    pgm_dot_product_packed(S, U, &temp, K);
    sub_poly_packed(V, &temp, &temp);
    INTT(&temp);
    decode_key(&temp, k);
}
