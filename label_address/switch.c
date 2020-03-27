#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int t1()
{
	printf("Label %s\n", __FUNCTION__);
	return 0;
}

int t2()
{
	printf("Label %s\n", __FUNCTION__);
	return 0;
}

int t3()
{
	printf("Label %s\n", __FUNCTION__);
	return 0;
}

int t4()
{
	printf("Label %s\n", __FUNCTION__);
	return 0;
}

int main(int argc, char *argv[])
{
	/*To get the address of label, we should use "&&" and store the address in a void pointer variable*/
	static const void *labels[] = {
		(void*)&&FLAG1,
		(void*)&&FLAG2,
		(void*)&&FLAG3,
		(void*)&&FLAG4
	};

FLAG1:
	t1();
FLAG2:
	t2();
FLAG3:
	t3();
FLAG4:
	t4();

	return 0;
}

/*
(gdb) print labels
$1 = {0x4005bb <main+15>, 0x4005c5 <main+25>, 0x4005cf <main+35>, 0x4005d9 <main+45>}
(gdb) disassemble main
Dump of assembler code for function main:
    0x00000000004005ac <+0>:     push   %rbp
    0x00000000004005ad <+1>:     mov    %rsp,%rbp
    0x00000000004005b0 <+4>:     sub    $0x10,%rsp
	0x00000000004005b4 <+8>:     mov    %edi,-0x4(%rbp)
	0x00000000004005b7 <+11>:    mov    %rsi,-0x10(%rbp)
 => 0x00000000004005bb <+15>:    mov    $0x0,%eax
	0x00000000004005c0 <+20>:    callq  0x400530 <t1>
	0x00000000004005c5 <+25>:    mov    $0x0,%eax
	0x00000000004005ca <+30>:    callq  0x40054f <t2>
	0x00000000004005cf <+35>:    mov    $0x0,%eax
	0x00000000004005d4 <+40>:    callq  0x40056e <t3>
	0x00000000004005d9 <+45>:    mov    $0x0,%eax
	0x00000000004005de <+50>:    callq  0x40058d <t4>
	0x00000000004005e3 <+55>:    mov    $0x0,%eax
	0x00000000004005e8 <+60>:    leaveq 
	0x00000000004005e9 <+61>:    retq   
	End of assembler dump.
 */
