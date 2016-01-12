#include "netencodingTools.h"
#include <stdio.h>

int main(void){
    float f = 3.1415926, f2;
    uint32_t netf;

    netf = htonf(f);
    f2=htohf(netf);

    printf("Original: %f\n", f);
    printf("Network: 0x%08X\n", netf);
    printf("Unpacked: %f\n", f2);
}
