#ifndef __ENCDEC_H__
#define __ENCDEC_H__


#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <asm/byteorder.h> 
#include <openssl/aes.h>
#include <string.h>
#include <time.h>

#define ENCLENBASE 16


unsigned char getRandom(void);
void Encrypt_ecb(unsigned char *in, unsigned char *out, unsigned char *key, int len );
void Decrypt_ecb(unsigned char *in, unsigned char *out, unsigned char *key, int len );
void Encrypt_cbc(unsigned char *in, unsigned char *out, unsigned char *key, unsigned char *iv, int len );
void Decrypt_cbc(unsigned char *in, unsigned char *out, unsigned char *key, unsigned char *iv, int len );


#endif
