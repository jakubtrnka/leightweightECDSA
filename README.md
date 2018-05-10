# leightweightECDSA
Basic command line utility that produces/verifies ECDSA/double-sha256 on curve secp256k1.
Reads text-message and hex-encoded private, public key or compact signature.

Depends on libsecp256k1 and OpenSSL.

## basic usage
```
$ ./ecdsa_sign "hey hey" c046765f09168239c898b2787ae9d17b401c4d987b8e5f2d60b73f8db0c50422
$ ./ecdsa_verify "hey hey" 02e80f2f21b8f4c49bd1c4f3822975bd270d4b72e18742780df0e467dce0b1d2a1 22f5173b3888c761b8c50b85de72cddb35c39e309bd8c34ec5611af85c30dbee643c757dbefa0e6ef2b42ff49c9fd931eeeb7c0c73d9d4c853db017f551f38a7
```
