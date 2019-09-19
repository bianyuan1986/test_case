#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 10000

/*asm(".symver memcpy, memcpy@GLIBC_2.2.5");*/

int main(int argc, char *argv[])
{
	char a[LEN] = {0};
	char *b = (char*)malloc(LEN);

	memcpy(a, b, LEN);

	return 0;
}

