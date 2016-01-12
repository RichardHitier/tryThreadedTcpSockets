#include "netencodingTools.h"
#include <stdio.h>
#include <inttypes.h>

int main(void){
    float f = 3.1415926, f2;
	double d=3.14159265358979323, d2;
    uint32_t netf, fi;
	uint64_t di;

    netf = htonf(f);
    f2=htohf(netf);

	printf("---- HTONF -----\n");

    printf("Original: %f\n", f);
    printf("Network: 0x%08X\n", netf);
    printf("Unpacked: %f\n", f2);

	printf("---- unpack754 -----\n");

	fi = pack754_32(f);
	f2 = unpack754_32(fi);

	di = pack754_64(d);
	d2 = unpack754_64(di);

	printf("float before: %.7f\n", f);
	printf("fload 754 encoded: 0x%08"PRIx32"\n", fi);
	printf("float after: %.7f\n\n", f2);


	printf("double before: %.20lf\n", d);
	printf("double 754 encoded: 0x%16"PRIx64"\n", di);
	printf("double after: %.20lf\n\n", d2);
}
