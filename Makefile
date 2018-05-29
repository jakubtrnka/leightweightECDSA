CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -I. -O3 -c
CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++11 -I. -O3 -c
LD=gcc
LDFLAGS=-Wall -pedantic -std=c99

all: ecdsa_sign ecdsa_verify

ecdsa_verify: ecdsa_verify.o ecdsa_secp256k1.o c_sha256.o sha256.o
	$(LD) $(LDFLAGS) -o $@ -lsecp256k1 $^

ecdsa_sign: ecdsa_sign.o ecdsa_secp256k1.o c_sha256.o sha256.o
	$(LD) $(LDFLAGS) -o $@ -lsecp256k1 $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

ecdsa_sign.o: ecdsa_sign.c
ecdsa_secp256k1.o: ecdsa_secp256k1.c ecdsa_secp256k1.h
sha256.o: sha256.cpp
c_sha256.o: c_sha256.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^


clean:
	-rm ecdsa_sign ecdsa_verify *.o

check: all
	bash test_blockstream.sh
