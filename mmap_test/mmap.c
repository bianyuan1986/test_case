#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define MMAP_SIZE 1024*1024*512

/*
   mmap前和mmap后可使用内存未改变
[root@VM_14_30_centos ~/python_embed]# cat /proc/meminfo |grep MemAvailable:
MemAvailable:   14737392 kB
   循环访问每一页后可使用内存的值最终变为如下所示
[root@VM_14_30_centos ~/python_embed]# cat /proc/meminfo |grep MemAvailable:
MemAvailable:   14213472 kB
   进程退出后可使用内存还原
[root@VM_14_30_centos ~/python_embed]# cat /proc/meminfo |grep MemAvailable:
MemAvailable:   14737872 kB
 */ 
int main(int argc, char *argv[])
{
	void *addr = NULL;
	unsigned int *begin = NULL;
	int i = 0;

	/*调用mmap后/proc/meminfo中的Mapped值并不会改变，因为此时只是分配了虚拟地址空间，还未进行实际的物理页面映射*/
	addr = mmap(NULL, MMAP_SIZE, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, -1, 0);
	sleep(20);
	begin = addr;
	/*直到访问对应的页面，产生缺页中断时才会进行实际的物理页面映射并且把统计数据添加到Mapped中*/
	for( ; i < 512*1024/4; i++)
	{
		//printf("Visit page %d\n", i);
		*begin = i;
		//sleep(3);
		begin += 1024;
	}
	sleep(10);

	return 0;
}

