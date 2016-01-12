#include "netencodingTools.h"

uint32_t htonf(float f){
    uint32_t p;
    uint32_t sign;
    if(f<0){ sign=1; f=-f;}
    else {sign=0;}

    p  = ((((uint32_t)f)&0x7fff)<<16)|(sign<<31);
    p |= (uint32_t)(((f-(int)f)*65536.0f))&0xffff;

    return p;
}

float     htohf(uint32_t p){
    float f = ((p>>16)&0x7fff);
    f+= (p&0xffff)/65536.0f;
    if(((p>>31)&0x1)==0x1){f=-f;}
    return f;
}

uint64_t pack754(long double f, unsigned bits, unsigned expbits){
	long double fnorm;
	int shift;
	long long sign, exp, significand;
	unsigned significandbits = bits - expbits -1; 

	if (f==0.0) return 0;

	// check sign and normalize
	if(f<0) { sign=1; fnorm=-f;}
	else { sign=0; fnorm=f;}

	// get normalized and exponent
	shift=0;
	while(fnorm >= 2.0){fnorm/=2.0; shift++;}
	while(fnorm <1.0){fnorm *= 2.0; shift--;}
	fnorm=fnorm-1.0;

	// binary form
	significand = fnorm * ((1LL<< significandbits) + 0.5f);

	// get biased exponent
	exp = shift + ((1<<(expbits-1))-1);

	// ruturn final
	return (sign<<(bits-1)) | (exp<<(bits-expbits-1)) | significand;

}

long double unpack754(uint64_t i, unsigned bits, unsigned expbits){

	long double result;
	long long shift;
	unsigned bias;
	unsigned significandbits = bits - expbits -1;

	if (i==0) return 0.0;


	result = (i&((1LL<<significandbits)-1));
	result /= (1LL<<significandbits);
	result += 1.0f;

	bias = (1<<(expbits-1))-1;
	shift = ((i>>significandbits)&((1LL<<expbits)-1))-bias;
	while(shift>0){result *=2.0; shift--;}
	while(shift<0){result /=2.0; shift++;}


	result *=(i>>(bits-1))&1?-1.0:1e0;
	return result;
}
