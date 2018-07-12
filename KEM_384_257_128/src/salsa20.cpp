/*
 * File:    avrnacl_fast/crypto_core/salsa20.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Mon Aug 11 18:51:27 2014 +0200
 * Public Domain
 */

#include "avrnacl.h"
#include "bigint.h"

#define ROUNDS 20

static const unsigned char sigma[16] = "expand 32-byte k";
extern "C" void avrnacl_calc_rounds(unsigned char *xj, unsigned char *out, int rounds);
extern "C" void avrnacl_init_core(unsigned char *xj, const unsigned char *c, const unsigned char *k, const unsigned char *in);

int crypto_core_salsa20(
        unsigned char *out,
  const unsigned char *in,
  const unsigned char *k,
  const unsigned char *c
)
{
  unsigned char xj[128];
  avrnacl_init_core(xj, c, k, in);
  avrnacl_calc_rounds(xj, out, ROUNDS);
  return 0;
}


int crypto_stream_salsa20_xor(
    unsigned char *c, 
    const unsigned char *m,crypto_uint16 mlen, 
    const unsigned char *n,const unsigned char *k
    )
{
  unsigned char z[16],x[64],u[8],i;

  for(i=0;i<8;i++) 
  {
    z[i] = n[i];
    z[i+8] = 0;
    u[i] = 0;
  }
  u[0] = 1;

  while (mlen >= 64) 
  {
    if(m)
    {
      crypto_core_salsa20(x,z,k,sigma);
      for(i=0;i<64;i++)
        c[i] = m[i] ^ x[i];
    }
    else
      crypto_core_salsa20(c,z,k,sigma);

    bigint_add(z+8,z+8,u,8);
    mlen -= 64;
    c += 64;
    if (m) m += 64;
  }
  if (mlen) 
  {
    crypto_core_salsa20(x,z,k,sigma);
    if(m)
      for(i=0;i<mlen;i++)
        c[i] = x[i] ^ m[i];
    else
      for(i=0;i<mlen;i++)
        c[i] = x[i];
  }
  return 0;
}

int crypto_stream_salsa20(
    unsigned char *c,crypto_uint16 clen,
    const unsigned char *n,
    const unsigned char *k
    )
{
  return crypto_stream_salsa20_xor(c,0,clen,n,k);
}

