cmake_minimum_required (VERSION 3.0)

project (LeightweightECDSA)
set (CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 11)

add_executable(Sign_ecdsa ecdsa_sign.c)
add_executable(Verify_ecdsa ecdsa_verify.c)
add_executable(Recovery_pubkey ecdsa_recovery.c)

include_directories( . )

add_library(c_sha256 c_sha256.cpp)
add_library(ecdsa_secp256k1 ecdsa_secp256k1.c ecdsa_secp256k1.h c_sha256.cpp sha256.cpp sha256.h) 
add_library(sha256 sha256.cpp sha256.h)
target_link_libraries(Verify_ecdsa c_sha256 sha256 ecdsa_secp256k1 secp256k1)
target_link_libraries(Sign_ecdsa c_sha256 sha256 ecdsa_secp256k1 secp256k1)
target_link_libraries(Recovery_pubkey ecdsa_secp256k1 secp256k1)
#set_target_properties(Verify_ecdsa PROPERTIES COMPILE_FLAGS "-I.")
#set_target_properties(Sign_ecdsa PROPERTIES COMPILE_FLAGS "-I.")
