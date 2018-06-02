#include <ecdsa_secp256k1.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char * checkN(const char *s, int n) {
	if (strlen(s) != n) {
		printf("signature must be %d char long, but has %ld\n", n, strlen(s));
		exit(1);
	}
	return s;
}

int main(int argc, const char * argv[]) {
	unsigned char comp_sig[100], raw_pub[100];
	int i;
	if (argc != 3) {
		printf("Usage: %s %s\n", argv[0], "<compact-signature> <message>");
		exit(1);
	}
	//printf("verification %s!\n", recovery_pubkey(readhex(comp_sig, checkN(argv[3], 128)), argv[1], readhex(raw_pub, checkN(argv[2], 130))) ? "successfull": "failed");
	recovery_pubkey(raw_pub, readhex(comp_sig, checkN(argv[1], 128)), argv[2]);
	for (i=0; i<33; ++i) printf("%02x", raw_pub[i]);
	putchar('\n');
	//printf("============================\n");
	return 0;
}
