CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -I. -O3

all: ecdsa_sign ecdsa_verify

ecdsa_verify: ecdsa_verify.o ecdsa_secp256k1.o
	$(CC) $(CFLAGS) -o $@ -lsecp256k1 -lcrypto $^

ecdsa_sign: ecdsa_sign.o ecdsa_secp256k1.o
	$(CC) $(CFLAGS) -o $@ -lsecp256k1 -lcrypto $^

ecdsa_sign.o: ecdsa_sign.c
ecdsa_secp256k1.o: ecdsa_secp256k1.c ecdsa_secp256k1.h

clean:
	-rm ecdsa_sign ecdsa_verify *.o

check: all
	bash test_blockstream.sh
