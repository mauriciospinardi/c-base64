#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************************/
/* Externalized functions */
/**************************/

char *
b64_encode(const unsigned char *in, unsigned long len);

int
b64_decode(const char *in, unsigned char *out, unsigned long outlen);
