#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/*
 * man ld
 
    --wrap=symbol
    Use a wrapper function for symbol.  Any undefined reference to symbol will be resolved to "__wrap_symbol".  Any undefined reference to "__real_symbol" will be resolved to
    symbol.
    This can be used to provide a wrapper for a system function.  The wrapper function should be called "__wrap_symbol".  If it wishes to call the system function, it should
    call "__real_symbol".
    Here is a trivial example:
         void *  __wrap_malloc (size_t c)
         {
              printf ("malloc called with %zu\n", c);
              return __real_malloc (c);
         }
    If you link other code with this file using --wrap malloc, then all calls to "malloc" will call the function "__wrap_malloc" instead.  The call to "__real_malloc" in
    "__wrap_malloc" will call the real "malloc" function.h
    You may wish to provide a "__real_malloc" function as well, so that links without the --wrap option will succeed.  If you do this, you should not put the definition of
    "__real_malloc" in the same file as "__wrap_malloc"; if you do, the assembler may resolve the call before the linker has a chance to wrap it to "malloc".

	gcc -g -Wl,--wrap,malloc -o wrap_malloc wrap_malloc.c
 */
void *my_malloc(size_t size, const void *caller)
{
	printf("My fake malloc\n");
	return NULL;
}

void * __real_malloc(size_t size);

void * __wrap_malloc(size_t size)
{
	printf("Malloc %d bytes\n", size);
	return __real_malloc(size);
}

int main(int argc, char* argv[])
{
	/*__malloc_hook = my_malloc;*/

	char *test = (char*)malloc(32*8);
	printf("Address %p\n", test);
	malloc_stats();
	char *test1 = (char*)malloc(32*4);
	malloc_stats();
	char *test2 = (char*)malloc(234);
	malloc_stats();
	free(test);
	malloc_stats();

	return 0;
}
