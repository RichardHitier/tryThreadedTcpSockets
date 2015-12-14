#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main( int argc, char **argv){

    unsigned i;
	int len;
    char *buffer;

    if( argc < 2) {
        fprintf(stderr, "missing arg\n");
        return EXIT_FAILURE;
    }

    len=strlen(argv[1]);

    buffer=malloc(len);

	printf("strlen before strcpy: %zu\n", strlen(buffer));

    strcpy( buffer, argv[1]);

    printf("buffer:%s strlen:%zu sizeof:%zu\n", buffer, strlen(buffer), sizeof(buffer));

    for (i=0; i<len+1; ++i)
        printf("%d: %c\n", i, buffer[i]);

    printf( "%s\n", buffer);

    return EXIT_SUCCESS;
}
