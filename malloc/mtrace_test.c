#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>
#include <unistd.h>

/*export MALLOC_TRACE=/tmp/t*/

int main(int argc, char *argv[])
{
	int j;
	mtrace();
	for (j = 0; j < 2; j++)
		malloc(100);            /* Never freed--a memory leak */
	calloc(16, 16);             /* Never freed--a memory leak */
	sleep(20);

	return 0;
}


