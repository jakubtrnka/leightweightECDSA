#include <ecdsa_secp256k1.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char * check64(const char *s) {
	if (strlen(s) != 64) {
		printf("private key must be 32B long, but has %ldB\n", (strlen(s))/2);
		exit(1);
	}
	return s;
}

int main(int argc, const char * argv[]) {
	unsigned char comp_sig[64], raw_priv[32], raw_pub[33];
	if (argc != 3) {
		printf("Usage: %s %s %s\n", argv[0], "<message>", "<hex-private-key>");
		exit(1);
	}
	sign(comp_sig, argv[1], readhex(raw_priv, check64(argv[2])));
	printf("============================\nECDSA-secp256k1, sha256(sha256(.))\n");
	printf("----------------------------\nmessage:\n%s\n", argv[1]);
	printf("----------------------------\nsignature:\n");
	for (int i = 0; i < 64; ++i) printf("%02x", comp_sig[i]);
	putchar('\n');
	printf("----------------------------\npublic key:\n");
	if (NULL == make_public(raw_pub, raw_priv)) {
		printf("error private->public\n");
		return 1;
	}
	for (int i=0; i<33; ++i) printf("%02x", raw_pub[i]);
	printf("\n============================\n");
	return 0;
}
