/*
 * many thanks to beej's guide to network programming
 * (where all the following code is from)
 * http://beej.us/guide/bgnet/
 * beej@beej.us
 *
 */
#include <stdint.h>

#define pack754_32(f)   (pack754((f), 32, 8))
#define pack754_64(f)   (pack754((f), 64, 11))
#define unpack754_32(i) (unpack754((i), 32, 8))
#define unpack754_64(i) (unpack754((i), 64, 11))

uint64_t pack754(long double, unsigned, unsigned);
long double unpack754(uint64_t, unsigned, unsigned);

uint32_t htonf(float f);
float     htohf(uint32_t p);
