#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define rot(x, k) (((x) << (k)) | ((x) >> (32-(k))))

/** @internal Internal function. NOTE: Arguments are modified. */
#define __rte_jhash_mix(a, b, c) do { \
	a -= c; a ^= rot(c, 4); c += b; \
	b -= a; b ^= rot(a, 6); a += c; \
	c -= b; c ^= rot(b, 8); b += a; \
	a -= c; a ^= rot(c, 16); c += b; \
	b -= a; b ^= rot(a, 19); a += c; \
	c -= b; c ^= rot(b, 4); b += a; \
} while (0)

#define __rte_jhash_final(a, b, c) do { \
	c ^= b; c -= rot(b, 14); \
	a ^= c; a -= rot(c, 11); \
	b ^= a; b -= rot(a, 25); \
	c ^= b; c -= rot(b, 16); \
	a ^= c; a -= rot(c, 4);  \
	b ^= a; b -= rot(a, 14); \
	c ^= b; c -= rot(b, 24); \
} while (0)

/** The golden ratio: an arbitrary value. */
#define RTE_JHASH_GOLDEN_RATIO      0xdeadbeef

#define BIT_SHIFT(x, y, k) (((x) >> (k)) | ((uint64_t)(y) << (32-(k))))

#define LOWER8b_MASK (0xff)
#define LOWER16b_MASK (0xffff)
#define LOWER24b_MASK (0xffffff)

static void
__rte_jhash_2hashes(const void *key, uint32_t length, uint32_t *pc,
		uint32_t *pb, unsigned check_align)
{
	uint32_t a, b, c;

	/* Set up the internal state */
	a = b = c = RTE_JHASH_GOLDEN_RATIO + ((uint32_t)length) + *pc;
	c += *pb;

	/*
	 * Check key alignment. For x86 architecture, first case is always optimal
	 * If check_align is not set, first case will be used
	 */
	const uint32_t *k = (const uint32_t *)key;
	const uint32_t s = 0;
	if (!check_align || s == 0) {
		while (length > 12) {
			a += k[0];
			b += k[1];
			c += k[2];

			__rte_jhash_mix(a, b, c);

			k += 3;
			length -= 12;
		}

		switch (length) {
		case 12:
			c += k[2]; b += k[1]; a += k[0]; break;
		case 11:
			c += k[2] & LOWER24b_MASK; b += k[1]; a += k[0]; break;
		case 10:
			c += k[2] & LOWER16b_MASK; b += k[1]; a += k[0]; break;
		case 9:
			c += k[2] & LOWER8b_MASK; b += k[1]; a += k[0]; break;
		case 8:
			b += k[1]; a += k[0]; break;
		case 7:
			b += k[1] & LOWER24b_MASK; a += k[0]; break;
		case 6:
			b += k[1] & LOWER16b_MASK; a += k[0]; break;
		case 5:
			b += k[1] & LOWER8b_MASK; a += k[0]; break;
		case 4:
			a += k[0]; break;
		case 3:
			a += k[0] & LOWER24b_MASK; break;
		case 2:
			a += k[0] & LOWER16b_MASK; break;
		case 1:
			a += k[0] & LOWER8b_MASK; break;
		/* zero length strings require no mixing */
		case 0:
			*pc = c;
			*pb = b;
			return;
		};
	} else {
		/* all but the last block: affect some 32 bits of (a, b, c) */
		while (length > 12) {
			a += BIT_SHIFT(k[0], k[1], s);
			b += BIT_SHIFT(k[1], k[2], s);
			c += BIT_SHIFT(k[2], k[3], s);
			__rte_jhash_mix(a, b, c);

			k += 3;
			length -= 12;
		}

		/* last block: affect all 32 bits of (c) */
		switch (length) {
		case 12:
			a += BIT_SHIFT(k[0], k[1], s);
			b += BIT_SHIFT(k[1], k[2], s);
			c += BIT_SHIFT(k[2], k[3], s);
			break;
		case 11:
			a += BIT_SHIFT(k[0], k[1], s);
			b += BIT_SHIFT(k[1], k[2], s);
			c += BIT_SHIFT(k[2], k[3], s) & LOWER24b_MASK;
			break;
		case 10:
			a += BIT_SHIFT(k[0], k[1], s);
			b += BIT_SHIFT(k[1], k[2], s);
			c += BIT_SHIFT(k[2], k[3], s) & LOWER16b_MASK;
			break;
		case 9:
			a += BIT_SHIFT(k[0], k[1], s);
			b += BIT_SHIFT(k[1], k[2], s);
			c += BIT_SHIFT(k[2], k[3], s) & LOWER8b_MASK;
			break;
		case 8:
			a += BIT_SHIFT(k[0], k[1], s);
			b += BIT_SHIFT(k[1], k[2], s);
			break;
		case 7:
			a += BIT_SHIFT(k[0], k[1], s);
			b += BIT_SHIFT(k[1], k[2], s) & LOWER24b_MASK;
			break;
		case 6:
			a += BIT_SHIFT(k[0], k[1], s);
			b += BIT_SHIFT(k[1], k[2], s) & LOWER16b_MASK;
			break;
		case 5:
			a += BIT_SHIFT(k[0], k[1], s);
			b += BIT_SHIFT(k[1], k[2], s) & LOWER8b_MASK;
			break;
		case 4:
			a += BIT_SHIFT(k[0], k[1], s);
			break;
		case 3:
			a += BIT_SHIFT(k[0], k[1], s) & LOWER24b_MASK;
			break;
		case 2:
			a += BIT_SHIFT(k[0], k[1], s) & LOWER16b_MASK;
			break;
		case 1:
			a += BIT_SHIFT(k[0], k[1], s) & LOWER8b_MASK;
			break;
		/* zero length strings require no mixing */
		case 0:
			*pc = c;
			*pb = b;
			return;
		}
	}

	__rte_jhash_final(a, b, c);

	*pc = c;
	*pb = b;
}

static uint32_t
__rte_jhash_3words(uint32_t a, uint32_t b, uint32_t c, uint32_t initval)
{
	a += RTE_JHASH_GOLDEN_RATIO + initval;
	b += RTE_JHASH_GOLDEN_RATIO + initval;
	c += RTE_JHASH_GOLDEN_RATIO + initval;

	__rte_jhash_final(a, b, c);

	return c;
}

/**
 * A special ultra-optimized versions that knows it is hashing exactly
 * 3 words.
 *
 * @param a
 *   First word to calculate hash of.
 * @param b
 *   Second word to calculate hash of.
 * @param c
 *   Third word to calculate hash of.
 * @param initval
 *   Initialising value of hash.
 * @return
 *   Calculated hash value.
 */
static uint32_t
rte_jhash_3words(uint32_t a, uint32_t b, uint32_t c, uint32_t initval)
{
	return __rte_jhash_3words(a + 12, b + 12, c + 12, initval);
}


int compute_score()
{
	int score = -1;

	score = 2;
	score += 4;
	score += 4;

	return score;
}

unsigned int next_pseudo_random32(unsigned int seed)
{
	return seed * 1664525 + 1013904223;
}

unsigned int inet_ehashfn(unsigned int laddr, unsigned short int lport, unsigned int faddr, unsigned short int fport)
{
	return rte_jhash_3words(laddr, faddr, (lport<<16|fport), (unsigned int)(unsigned long long int)inet_ehashfn);
}

int choose(int cnt)
{
	int i = 0;
	int score = 0;
	int hiscore = 0;
	int matches = 0;
	unsigned int phash = 0;
	int result = 0;
	static unsigned short int sport = 1024;

	for( ; i < cnt; i++)
	{
		score = compute_score();
		if( score > hiscore )
		{
			result = i;
			hiscore = score;
			phash = inet_ehashfn( 0xca246b64, 34567, 0xca246b64, sport++);
			matches = 1;
		}
		else if( score == hiscore )
		{
			matches++;
			if( ((unsigned long long)phash*matches) >> 32 == 0 )
			{
				result = i;
			}
			phash = next_pseudo_random32(phash);
		}
	}

	return result;
}

int main(int argc, char *argv[])
{
	int workerCnt = 0;
	int packetCnt = 0;
	int *statis = NULL;
	int i = 0;
	int loopCnt = 0;
	int idx = 0;

	if( argc < 3 )
	{
		printf("Usage:%s WORKER_CNT PACKET_CNT\n", argv[0]);
		return 0;
	}

	workerCnt = atoi(argv[1]);
	packetCnt = atoi(argv[2]);
	statis = (int*)malloc(workerCnt*sizeof(int));
	loopCnt = workerCnt*packetCnt;
	for( ; i < loopCnt; i++)
	{
		idx = choose(workerCnt);
		statis[idx]++;
	}

	for( i = 0; i < workerCnt; i++)
	{
		printf("Worker:%d Cnt:%d\n", i, statis[i]);
	}

	return 0;
}

