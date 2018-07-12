#include "./src/avrnacl.h"
#include "./src/blake32.h"
#include "utils.h"

int unpack_coef(const Packed_poly* x, unsigned i){
    /*
     * Returns unpacked value of the i-th coefficient of x
     */
    int res;
    res   = (x->bytes[128+i/8] >> (i%8));
    res   = -(res&1);
    res <<= 8;        
    res  |= x->bytes[i];
    return res;
}

void pack_coef(Packed_poly* x, unsigned i, int val){
    /*
     * Packs val into x as i-th coefficient
     */
    int v,w;
    x->bytes[i] = val&0xFF;
    v = ((val&0x100)>>(8-(i%8)));
    w = (1 << (i%8));
    x->bytes[128+i/8] = ((x->bytes[128+i/8])&(~w))|v; // set sign bit
}

void pack(Poly* x, Packed_poly* y){
    /* 
     * Packs x into y 
     */
    int i;
    
    for(i=0; i < N; ++i){
        pack_coef(y, i, x->c[i]); 
    }
}

void unpack(Packed_poly* x, Poly* y){
    /*
     * Unpacks x into y
     */
    int i;
    
    for(i=0; i < N; ++i){
        y->c[i] = unpack_coef(x,i);
    }
}


void XOF(unsigned char *output, unsigned long long outlen, const unsigned char *input,  unsigned long long inlen){
    /* 
     *  Extendable output function, from inlen bytes to outlen bytes.
     *  Used to expand a seed into a random tape. Core is salsa20
     */
    unsigned char k[32], n[16]; 
    int i;    
    
    for(i=0; i < LAMBDA; ++i)  k[i] = input[i]; 
    for(i=LAMBDA; i < 32; ++i) k[i] = 0;
    for(i=0; i < 16; ++i)      n[i] = 0;

    crypto_uint16 clen = outlen;
    crypto_stream_salsa20(output,clen,n,k);

}

void H(unsigned char* output, unsigned outlen, unsigned char* input, unsigned inlen){
    /*  
     *  Puts outlen truncated evaluation of Blake32(input) in output
     *  outlen should be <= 32   
     */
    
    unsigned char res[32];
    int i;
    
    blake32_hash(res, input, inlen);
    for(i=0; i < outlen; ++i) output[i] = res[i];
}


int mm257(int a, int b){
  /*
   * Modular multiplication modulo 257
   * Product a*b should fit in 16 bits
   * Result in [-128, 128]
   */
  asm volatile(
  "movw r18, %1\n"
  "movw r20, %2\n"
  "mul r20, r18 \n"
  "movw  r22, r0 \n"
  "mul r20, r19 \n"
  "add r23, r0 \n"
  "mul r21, r18 \n"
  "add r23, r0 \n"
  "eor r1, r1 ; r23:r22 = a*b \n"  
  "mov r24, r23 \n" 
  "ldi r25, 0x00 \n"
  "rol r24 \n"
  "sbc r25, r25\n"
  "ror r24 \n"
  "ldi r23,0x00 \n"  
  "sub r22, r24 \n "
  "sbc r23,r25 ; v = (v&0xFF)-(v>>8) in 23:22\n "
  "ldi r18, 0x80 \n"
  "ldi r19, 0x00 \n"
  "movw r20, r18 \n"
  "sub r20, r22 \n"
  "sbc r21, r23 ; r=(0x80-v) in 21:20 \n "
  "rol r21 \n "
  "sbc r19, r19 \n"
  "andi r19, 0x01 ; 0x101&(r>>15) \n"
  "sub r22, r19 \n"
  "sbc r23, r19 \n"
  "movw %0, r22 \n"
  : "=r" (a) : "r"(a),"r"(b) );
  return a;
}

int mod_q(int v){
  /*
   * Reduction mod 257 of 16-bit integer
   */
  asm volatile (
  "movw r22, %1 \n"  
  "mov r24, r23 \n" 
  "ldi r25, 0x00 \n"
  "rol r24 \n"
  "sbc r25, r25\n"
  "ror r24 \n"
  "ldi r23,0x00 \n"  
  "sub r22, r24 \n "
  "sbc r23,r25 ; v = (v&0xFF)-(v>>8) in 23:22\n "
  "ldi r18, 0x80 \n"
  "ldi r19, 0x00 \n"
  "movw r20, r18 \n"
  "sub r20, r22 \n"
  "sbc r21, r23 ; r=(0x80-v) in 21:20 \n "
  "rol r21 \n "
  "sbc r19, r19 \n"
  "andi r19, 0x01 ; 0x101&(r>>15) \n"
  "sub r22, r19 \n"
  "sbc r23, r19 \n"
  "movw %0, r22 \n"
  : "=r" (v) : "r" (v) );
  return v;
}



