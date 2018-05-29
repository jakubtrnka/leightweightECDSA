#ifndef C_SHA_H
#define C_SHA_H

#include <stdlib.h>

unsigned char * c_sha(unsigned char * md, const unsigned char * msg, size_t msg_len);

#endif
