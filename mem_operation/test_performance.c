#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_malloc_mmap()
{
	int i = 0;
	int size = 128*1024;
	struct timeval t1;
	struct timeval t2;
	char *addr = NULL;

	printf("Malloc Brk Test:\n");
	for( ; i <= 7; i++)
	{
		gettimeofday(&t1, NULL);
		malloc(size);
		gettimeofday(&t2, NULL);
		printf("Size:%10dk  Time counsumed:%5dus\n", size/1024, (t2.tv_sec-t1.tv_sec)*1000000+(t2.tv_usec-t1.tv_usec));
		size *= 2;
	}
	printf("\n");
}

void test_malloc_brk()
{
	int i = 0;
	int size = 8*1024;
	struct timeval t1;
	struct timeval t2;
	char *addr = NULL;

	printf("Malloc Mmap Test:\n");
	for( ; i <= 3; i++)
	{
		gettimeofday(&t1, NULL);
		addr = malloc(size);
		gettimeofday(&t2, NULL);
		printf("Size:%10dk  Time counsumed:%5dus\n", size/1024, (t2.tv_sec-t1.tv_sec)*1000000+(t2.tv_usec-t1.tv_usec));
		size *= 2;
	}
	printf("\n");
}

void test_memcpy()
{
	int i = 0;
	int size = 8*1024;
	struct timeval t1;
	struct timeval t2;
	char *src = NULL;
	char *target = NULL;

	printf("Memcpy Test:\n");
	for( ; i <= 10; i++)
	{
		src = malloc(size);
		target = malloc(size);
		gettimeofday(&t1, NULL);
		memcpy(target, src, size);
		gettimeofday(&t2, NULL);
		printf("Size:%10dk  Time counsumed:%5dus\n", size/1024, (t2.tv_sec-t1.tv_sec)*1000000+(t2.tv_usec-t1.tv_usec));
		size *= 2;
	}
	printf("\n");
}

void test_memset()
{
	int i = 0;
	int size = 8*1024;
	struct timeval t1;
	struct timeval t2;
	char *src = NULL;

	printf("Memset Test:\n");
	for( ; i <= 10; i++)
	{
		src = malloc(size);
		gettimeofday(&t1, NULL);
		memset(src, 0x00, size);
		gettimeofday(&t2, NULL);
		printf("Size:%10dk  Time counsumed:%5dus\n", size/1024, (t2.tv_sec-t1.tv_sec)*1000000+(t2.tv_usec-t1.tv_usec));
		size *= 2;
	}
	printf("\n");
}

void test_strncpy()
{
	int i = 0;
	int size = 8*1024;
	struct timeval t1;
	struct timeval t2;
	char *src = NULL;
	char *target = NULL;

	printf("Strncpy Test:\n");
	for( ; i <= 10; i++)
	{
		src = malloc(size);
		target = malloc(size);
		gettimeofday(&t1, NULL);
		strncpy(target, src, size);
		gettimeofday(&t2, NULL);
		printf("Size:%10dk  Time counsumed:%5dus\n", size/1024, (t2.tv_sec-t1.tv_sec)*1000000+(t2.tv_usec-t1.tv_usec));
		size *= 2;
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	test_malloc_mmap();
	test_malloc_brk();
	test_memcpy();
	test_memset();
	test_strncpy();

	return 0;
}

