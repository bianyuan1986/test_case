#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>

struct exceptionHandler
{
	struct exceptionHandler *prev;
	jmp_buf env;
	int error_code;
};

struct exceptionHandler *current = NULL;

struct exceptionHandler *getExceptionHandler()
{
	struct exceptionHandler *handler = NULL;

	handler = (struct exceptionHandler*)malloc(sizeof(struct exceptionHandler));
	memset(handler, 0x00, sizeof(*handler));

	return handler;
}

void a4()
{
	longjmp(current->env, 1);
}

void a3()
{
	struct exceptionHandler *handler = NULL;
	handler = getExceptionHandler();
	handler->prev = current;
	current = handler;
	if( setjmp(current->env) == 0 )
	{
		printf("a3() set exception handler!\n");
		a4();
	}
	else
	{
		printf("a3() capture exception!\n");
		current = current->prev;
		longjmp(current->env, 2);
	}
}

void a2()
{
	struct exceptionHandler *handler = NULL;
	handler = getExceptionHandler();
	handler->prev = current;
	current = handler;
	if( setjmp(current->env) == 0 )
	{
		printf("a2() set exception handler!\n");
		a3();
	}
	else
	{
		printf("a2() capture exception!\n");
		current = current->prev;
		longjmp(current->env, 3);
	}
}

void a1()
{
	struct exceptionHandler *handler = NULL;
	handler = getExceptionHandler();
	handler->prev = current;
	current = handler;
	if( setjmp(current->env) == 0 )
	{
		printf("a1() set exception handler!\n");
		a2();
	}
	else
	{
		printf("a1() capture exception!\n");
	}
}

int main(int argc, char *argv[])
{
	a1();
}

