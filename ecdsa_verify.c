#include <ecdsa_secp256k1.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BRIEF

const char * checkN(const char *s, int n) {
	if (strlen(s) > n) {
		printf("private key must be %d char long, but has %ld\n", n, strlen(s));
		exit(1);
	}
	return s;
}

int main(int argc, const char * argv[]) {
	unsigned char comp_sig[100], raw_pub[100];
	if (argc != 4) {
		printf("Usage: %s %s %s\n", argv[0], "<message>", "<hex-public-key> <hex-signature>");
		exit(1);
	}
#ifndef BRIEF
	printf("============================\nECDSA-secp256k1, sha256(sha256(.))\n");
	printf("----------------------------\nmessage:\n%s\n", argv[1]);
	printf("----------------------------\npublic key:\n%s\n", argv[2]);
	printf("----------------------------\nsignature:\n%s\n", argv[3]);
#endif
	printf("verification %s!\n", verify(readhex(comp_sig, checkN(argv[3], 128)), argv[1], readhex(raw_pub, checkN(argv[2], 130))) ? "successfull": "failed");
//putchar('\n');
#ifndef BRIEF
	printf("============================\n");
#endif
	return 0;
}
