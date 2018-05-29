#include <cstdlib>
#include <sha256.h>

extern "C" unsigned char * c_sha(unsigned char * md, const unsigned char * msg, size_t msg_len) {
	CSHA256 h;
	h.Write(msg, msg_len);
	h.Finalize(md);
	return md;
}
