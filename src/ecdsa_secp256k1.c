#include <ecdsa_secp256k1.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <secp256k1.h>
#include <secp256k1_recovery.h>
#include <c_sha256.h>
//#include <openssl/sha.h>

#define SHA256_DIGEST_LENGTH 32

unsigned char * randomfill(unsigned char * blob, size_t len) {
	FILE *fr = fopen("/dev/urandom", "rb");
	fread((void *) blob, sizeof(unsigned char), len, fr);
	if (ferror(fr)) {
		printf("there has been some error loading randomness\n");
		exit(1);
	}
	fclose(fr);
	return blob;
}

unsigned char * doublesha(unsigned char * md, const char * msg) {
	//unsigned char tmp[SHA256_DIGEST_LENGTH];
	//return SHA256(SHA256((const unsigned char *) msg, strlen(msg), tmp), SHA256_DIGEST_LENGTH, md);
	return c_sha(md, c_sha(md, (const unsigned char *) msg, strlen(msg)), SHA256_DIGEST_LENGTH);
}

unsigned char * readhex(unsigned char * dat, const char * hex) {
	int n = strlen(hex);
	int i;
	unsigned tmp;
	if (n % 2) {
		printf("There must not be odd number of hex-characters\n");
		exit(1);
	}
	for (i = 0; i < n/2; ++i) {
		if (1 != sscanf(hex + 2*i, "%02x", &tmp)) {
			printf("bad hex string\n");
			exit(1);
		}
		dat[i] = (unsigned char) tmp;
	}
	return dat;
}

unsigned char * sign(unsigned char * compact_signature, const char * msg, const unsigned char * raw_priv) {
	unsigned char md[SHA256_DIGEST_LENGTH], seed[1024];
	secp256k1_context * ctx_sign;
	secp256k1_ecdsa_signature sig_t;
	
	ctx_sign = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);
	if (! secp256k1_context_randomize(ctx_sign, randomfill(seed, 32))) printf("problem with randomization");
	secp256k1_ecdsa_sign(ctx_sign, &sig_t, doublesha(md, msg), raw_priv, NULL, randomfill(seed, 1024));
	secp256k1_ecdsa_signature_serialize_compact(ctx_sign, compact_signature, &sig_t);
	secp256k1_context_destroy(ctx_sign);
	return compact_signature;
}

unsigned char * recovery_pubkey(unsigned char * pubkey, unsigned char * compact_signature, const char * msg) {
	secp256k1_context * ctx;
	secp256k1_ecdsa_signature sig_t;
	unsigned char md[SHA256_DIGEST_LENGTH];
	secp256k1_pubkey pub_t;
	long l = 33;
	ctx = secp256k1_context_create(SECP256K1_CONTEXT_VERIFY);
	if (!secp256k1_ecdsa_recoverable_signature_parse_compact(ctx, &sig_t, compact_signature, 0)) {
		printf("Given data failed to be parsed as signature\n");
		exit(1);
	}
	if (!secp256k1_ecdsa_recover(ctx, &pub_t, &sig_t, doublesha(md, msg))) {
		printf("Failed to restore public key\n");
		exit(1);
	}

	secp256k1_ec_pubkey_serialize(ctx, pubkey, &l, &pub_t, SECP256K1_EC_COMPRESSED);
	return pubkey;
}

int verify(const unsigned char * raw_sig, const char * msg, const unsigned char * raw_pub) {
	unsigned char md[SHA256_DIGEST_LENGTH];
	secp256k1_context * ctx_sign;
	secp256k1_ecdsa_signature sig_t;
	secp256k1_pubkey pub_t;
	ctx_sign = secp256k1_context_create(SECP256K1_CONTEXT_VERIFY);
	if ( (int)raw_pub[0] != 2 && (int)raw_pub[0] != 3 && (int)raw_pub[0] != 4) {
		printf("invalid public key\n");
		return 0;
	}
	if (! secp256k1_ec_pubkey_parse(ctx_sign, &pub_t, raw_pub, (int)(raw_pub[0]) == 4 ? 65 : 33)) {
		printf("pubkey not parsed\n");
		return 0;
	}
	if (!secp256k1_ecdsa_signature_parse_compact(ctx_sign, &sig_t, raw_sig)) {
		printf("signature not parsed\n");
		return 0;
	}
	return secp256k1_ecdsa_verify(ctx_sign, &sig_t, doublesha(md, msg), &pub_t);
}

unsigned char * make_public(unsigned char * pub, const unsigned char * priv) {
	secp256k1_context * ctx;
	secp256k1_pubkey pub_t;
	ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);
	if (! secp256k1_ec_pubkey_create(ctx, &pub_t, priv)) {
		printf("problem with pubkey creation");
		return NULL;
	}

	size_t l = 33;
	secp256k1_ec_pubkey_serialize(ctx, pub, &l, &pub_t, SECP256K1_EC_COMPRESSED);
	if ( l != 33) {
		printf("written %ld bytes\n", l);
		return NULL;
	}
	return pub;
}
