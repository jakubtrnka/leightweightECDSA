#!/bin/bash

printf "Bitcoin Signed Message:\nThere is nothing too shocking about this signature" | xargs -0 -I x ./ecdsa_verify "x" "02000000000005689111130e588a12ecda87b2dc5585c6c6ba66a412fa0cce65bc" "ffffffff077b7209dc866fbfa0d2bf67a0c696afffe57a822e2ba90059a2cc7abb998becb4e427650e282522bf9576524665301b807c0e3194cf1e6c795a0cf7"

printf "Bitcoin Signed Message:\nNor this, given a bit of algebra." | xargs -0 -I x ./ecdsa_verify "x" "03742088316dacf400cea17fdea1dba3bc1e1f58ac0f852fd85545b0ba7ebaee79" "10000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000001000000000000000000000000000"


printf "Bitcoin Signed Message:\nBut can you explain this one?" | xargs -0 -I x ./ecdsa_verify "x" "0200000000000000000000003b78ce563f89a0ed9414f5aa28ad0d96d6795f9c63" "deadbeef2f4a23b0f1954100b76bcb720f7b2ddc4a446dc06b8ffc4e143286e1e441f5f1583f300022ad3d134413a212581bcd36c20c7840d15b4d6b8e8f177f"
