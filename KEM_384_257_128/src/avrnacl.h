/*
 * Based on:
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


#endif
