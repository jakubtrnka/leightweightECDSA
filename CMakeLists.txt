cmake_minimum_required (VERSION 3.0)

project (LeightweightECDSA)
set (CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 11)

add_executable(Sign_ecdsa)
add_executable(Verify_ecdsa)

add_library(c_sha256 c_sha256.c)
add_library(ecdsa_secp256k1 ecdsa_secp256k1.c ecdsa_secp256k1.h) 
add_library(ecdsa_sign ecdsa_sign.c ecdsa_sign.h) 
add_library(ecdsa_verify ecdsa_verify.c ecdsa_verify.h) 
add_library(sha256 sha256.cpp sha256.h)
target_link_libraries(Verify_ecdsa c_sha256 sha256 ecdsa_secp256k1 ecdsa_verify)
target_link_libraries(Sign_ecdsa c_sha256 sha256 ecdsa_secp256k1 ecdsa_sign)
