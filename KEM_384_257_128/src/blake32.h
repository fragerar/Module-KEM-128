#ifndef BLAKE32_H
#define BLAKE32_H

#include <stdint.h>
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint8_t u8;
typedef struct  {
  u32 h[8], s[4], t[2];
  int buflen, nullt;
  u8  buf[64];
} state;

#define ROT(x,n) (((x)<<(32-n))|( (x)>>(n)))
#define G(a,b,c,d,e)					\
  v[a] += (m[sigma[i][e]] ^ cst[sigma[i][e+1]]) + v[b];	\
  v[d] = ROT( v[d] ^ v[a],16);				\
  v[c] += v[d];						\
  v[b] = ROT( v[b] ^ v[c],12);				\
  v[a] += (m[sigma[i][e+1]] ^ cst[sigma[i][e]])+v[b];	\
  v[d] = ROT( v[d] ^ v[a], 8);				\
  v[c] += v[d];						\
  v[b] = ROT( v[b] ^ v[c], 7);

void blake32_hash( uint8_t *out, const uint8_t *in, uint64_t inlen );
void blake32_compress( state *S, const u8 *block );
void blake32_init( state *S );
void blake32_update( state *S, const u8 *data, u64 datalen );
void blake32_final( state *S, u8 *digest );

#endif
