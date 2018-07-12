/*
 * File:    avrnacl.h
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Tue Aug 12 08:23:16 2014 +0200
 * Public Domain
 */

#ifndef AVRNACL_H
#define AVRNACL_H

typedef char crypto_int8;
typedef unsigned char crypto_uint8;
typedef int crypto_int16;
typedef unsigned int crypto_uint16;
typedef long crypto_int32;
typedef unsigned long crypto_uint32;
typedef long long crypto_int64;
typedef unsigned long long crypto_uint64;



#define crypto_stream_salsa20_KEYBYTES 32
#define crypto_stream_salsa20_NONCEBYTES 8
int crypto_stream_salsa20(unsigned char *,crypto_uint16,const unsigned char *,const unsigned char *);
int crypto_stream_salsa20_xor(unsigned char *,const unsigned char *,crypto_uint16,const unsigned char *,const unsigned char *);

#define crypto_hashblocks_PRIMITIVE "sha512"
#define crypto_hashblocks crypto_hashblocks_sha512
#define crypto_hashblocks_STATEBYTES crypto_hashblocks_sha512_STATEBYTES
#define crypto_hashblocks_BLOCKBYTES crypto_hashblocks_sha512_BLOCKBYTES
#define crypto_hashblocks_sha512_STATEBYTES 64
#define crypto_hashblocks_sha512_BLOCKBYTES 128
extern int crypto_hashblocks_sha512(unsigned char *,const unsigned char *,crypto_uint16);

#define crypto_hash_PRIMITIVE "sha512"
#define crypto_hash crypto_hash_sha512
#define crypto_hash_BYTES crypto_hash_sha512_BYTES
#define crypto_hash_sha512_BYTES 64
extern int crypto_hash_sha512(unsigned char *,const unsigned char *,crypto_uint16);


#endif
