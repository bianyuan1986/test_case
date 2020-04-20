#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/syscall.h>

#define FILE_CONTENT_LEN 1024*6
#define ROUND_CNT 64

static char fileContent[FILE_CONTENT_LEN];
static int fileContentLen;

/**********************md5 init*************************/
#define MD5_DIGEST_SIZE		16
#define MD5_HMAC_BLOCK_SIZE	64
#define MD5_BLOCK_WORDS		16
#define MD5_HASH_WORDS		4
//#define SECTION_VAR __attribute__((section(".data"))) 
#define SECTION_VAR 

typedef unsigned int u32;
typedef unsigned long long int u64;
typedef unsigned char u8;

struct md5_ctx
{
	u32 hash[MD5_HASH_WORDS];
	u64 byte_count;
	u32 *block;
};

typedef unsigned int (*f)(u32 x, u32 y, u32 z);

static unsigned int F1(u32 x, u32 y, u32 z)
{
	return (z ^ (x & (y ^ z)));
}

static unsigned int F2(u32 x, u32 y, u32 z)
{
	return (y ^ (z & (x ^ y))); 
}

static unsigned int F3(u32 x, u32 y, u32 z)
{
	return x ^ y ^ z;
}

static unsigned int F4(u32 x, u32 y, u32 z)
{
	return y ^ (x | ~z);
}


static void md5_transform(u32 *hash, u32 const *in, u32 len)
{
	u32 a, b, c, d;
	int i = 0;
	int j = 0;
	u32 tmp, res;

	static unsigned char g[] SECTION_VAR = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
								1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
								5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
								0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9};

	static unsigned int k[] SECTION_VAR = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
								0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
								0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
								0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};

	static unsigned char shift[] SECTION_VAR = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
									5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
									4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
									6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
									};

	static f fTable[] SECTION_VAR = {F1, F2, F3, F4};

	/*blockCnt = len/4/16*/
	len >>= 6;
	for( ; j < len; j++)
	{
		a = hash[0];
		b = hash[1];
		c = hash[2];
		d = hash[3];

		for( i = 0; i < 64; i++)
		{
			res = fTable[i>>4](b, c, d);

			tmp = d;
			d = c;
			c = b;
			a += res + k[i] + in[g[i]];
			b += (a<<shift[i]|a>>(32-shift[i])); 
			a = tmp;
		}

		hash[0] += a;
		hash[1] += b;
		hash[2] += c;
		hash[3] += d;

		in += 16;
	}
}

static void md5_calculate(struct md5_ctx *ctx)
{
	int padLen;
	char *p = NULL;

	ctx->hash[0] = 0x67452301;
	ctx->hash[1] = 0xefcdab89;
	ctx->hash[2] = 0x98badcfe;
	ctx->hash[3] = 0x10325476;
	ctx->block = (u32*)fileContent;
	ctx->byte_count = fileContentLen;

	padLen = (56 - ((fileContentLen&0x3f)+1));
	/*padding is mandatory, even if len%64=56*/
	fileContent[fileContentLen++] = 0x80;
	p = &fileContent[fileContentLen];
	if( padLen < 0 )
	{
		memset(p, 0x00, padLen + sizeof(u64));
		fileContentLen += (padLen+sizeof(u64));
		p = &fileContent[fileContentLen];
		padLen = 56;
	}
	memset(p, 0x00, padLen);
	fileContentLen += padLen;
	/*store len in bits count*/
	*(u32*)&fileContent[fileContentLen] = ctx->byte_count << 3;
	*(u32*)&fileContent[fileContentLen+4] = ctx->byte_count >> 29;
	fileContentLen += 8;
	md5_transform(ctx->hash, ctx->block, fileContentLen);
}

/**********************md5 init end*************************/

char *getExeFile(char *filename)
{
#define PATH_LEN 20
	pid_t pid = 0;
	int fd = -1;
	struct stat st;
	static char path[PATH_LEN];

	/*asm volatile( "mov $0x14, %%eax\n\t"
					"int $0x80\n\t"
					"mov %eax, %0;"
					:"=r"(pid)
					:
			);*/
	/*pid = getpid();
	snprintf(path, PATH_LEN, "/proc/%d/exe", pid);*/
	/*stat(filename, &st);
	fd = open(filename, O_RDONLY);
	read(fd, fileContent, st.st_size);
	*/
	syscall(SYS_stat, filename, &st);
	fd = syscall(SYS_open, filename, O_RDONLY);
	syscall(SYS_read, fd, fileContent, st.st_size);
	fileContentLen = st.st_size;
}

int main(int argc, char *argv[])
{
	struct md5_ctx ctx;
	int i = 0;
	unsigned char *md5 = NULL;

	getExeFile(argv[0]);
	md5_calculate(&ctx);
	md5 = (unsigned char*)ctx.hash;
	printf("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
			md5[0], md5[1], md5[2], md5[3],
			md5[4], md5[5], md5[6], md5[7],
			md5[8], md5[9], md5[10], md5[11],
			md5[12], md5[13], md5[14], md5[15]);

	return 0;
}

