#ifndef ECDSA_SECP256K1_H
#define ECDSA_SECP256K1_H

#include <stdlib.h>

unsigned char * doublesha(unsigned char * md, const char * msg);
unsigned char * randomfill(unsigned char * blob, size_t len);
unsigned char * readhex(unsigned char * dat, const char * hex);
int verify(const unsigned char * raw_sig, const char * msg, const unsigned char * raw_pub);
unsigned char * make_public(unsigned char * pub, const unsigned char * priv);
unsigned char * sign( unsigned char * compact_signature, const char * msg, const unsigned char * raw_priv);
#endif
