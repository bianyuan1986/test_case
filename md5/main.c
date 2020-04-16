#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define FILE_CONTENT_LEN 1024*15
#define ROUND_CNT 64

static char fileContent[FILE_CONTENT_LEN];
static int fileContentLen;

static unsigned int constant[64];
static unsigned char shift[64];

/**********************md5 init*************************/
#define MD5_DIGEST_SIZE		16
#define MD5_HMAC_BLOCK_SIZE	64
#define MD5_BLOCK_WORDS		16
#define MD5_HASH_WORDS		4

#define MD5STEP(f, w, x, y, z, in, s) \
	(w += f(x, y, z) + in, w = (w<<s | w>>(32-s)) + x)

typedef unsigned int u32;
typedef unsigned long long int u64;
typedef unsigned char u8;

struct md5_ctx
{
	u32 hash[MD5_HASH_WORDS];
	u32 block[MD5_BLOCK_WORDS];
	u64 byte_count;
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


static void md5_transform(u32 *hash, u32 const *in)
{
	u32 a, b, c, d;
	int i = 0;
	u32 tmp, res;

	a = hash[0];
	b = hash[1];
	c = hash[2];
	d = hash[3];


	static unsigned char g[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
								1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
								5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
								0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9};

	static unsigned int k[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
								0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
								0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
								0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};

	static unsigned char shift[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
									5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
									4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
									6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
									};

	static f fTable[] = {F1, F2, F3, F4};

	for( ; i < 64; i++)
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
}

static void md5_init(struct md5_ctx *ctx)
{
	ctx->hash[0] = 0x67452301;
	ctx->hash[1] = 0xefcdab89;
	ctx->hash[2] = 0x98badcfe;
	ctx->hash[3] = 0x10325476;
	ctx->byte_count = 0;
}

static void md5_update(struct md5_ctx *mctx, const u8 *data, unsigned int len)
{
	const u32 avail = sizeof(mctx->block) - (mctx->byte_count & 0x3f);

	mctx->byte_count += len;

	if (avail > len) {
		memcpy((char *)mctx->block + (sizeof(mctx->block) - avail),
		       data, len);
		return;
	}

	memcpy((char *)mctx->block + (sizeof(mctx->block) - avail),
	       data, avail);

	md5_transform(mctx->hash, mctx->block);
	data += avail;
	len -= avail;

	while (len >= sizeof(mctx->block)) {
		memcpy(mctx->block, data, sizeof(mctx->block));
		md5_transform(mctx->hash, mctx->block);
		data += sizeof(mctx->block);
		len -= sizeof(mctx->block);
	}

	memcpy(mctx->block, data, len);
}

static void md5_final(struct md5_ctx *mctx)
{
	const unsigned int offset = mctx->byte_count & 0x3f;
	char *p = (char *)mctx->block + offset;
	int padding = 56 - (offset + 1);

	*p++ = 0x80;
	if (padding < 0) {
		memset(p, 0x00, padding + sizeof (u64));
		md5_transform(mctx->hash, mctx->block);
		p = (char *)mctx->block;
		padding = 56;
	}

	memset(p, 0, padding);
	mctx->block[14] = mctx->byte_count << 3;
	mctx->block[15] = mctx->byte_count >> 29;
	md5_transform(mctx->hash, mctx->block);
}
/**********************md5 init end*************************/

char *getExeFile()
{
#define PATH_LEN 20
	pid_t pid = 0;
	int fd = -1;
	struct stat st;
	static char path[PATH_LEN];

	pid = getpid();
	snprintf(path, PATH_LEN, "/proc/%d/exe", pid);
	stat(path, &st);
	fd = open(path, O_RDONLY);
	read(fd, fileContent, st.st_size);
	fileContentLen = st.st_size;
}

int main(int argc, char *argv[])
{
	struct md5_ctx ctx;
	int i = 0;
	unsigned char *md5 = NULL;

	getExeFile();
	md5_init(&ctx);
	md5_update(&ctx, fileContent, fileContentLen);
	md5_final(&ctx);
	md5 = (unsigned char*)ctx.hash;
	for( ; i < 16; i += 4)
	{
		printf("%02x%02x%02x%02x", md5[i], md5[i+1], md5[i+2], md5[i+3]);
	}
	printf("\n");

	return 0;
}

