#include <stdint.h>
#include <string.h>
#include <limits.h>


/* jhash.h: Jenkins hash support.
 *
 * Copyright (C) 2006 Bob Jenkins (bob_jenkins@burtleburtle.net)
 *
 * http://burtleburtle.net/bob/hash/
 *
 * These are the credits from Bob's sources:
 *
 * lookup3.c, by Bob Jenkins, May 2006, Public Domain.
 *
 * These are functions for producing 32-bit hashes for hash table lookup.
 * hashword(), hashlittle(), hashlittle2(), hashbig(), mix(), and final()
 * are externally useful functions.  Routines to test the hash are included
 * if SELF_TEST is defined.  You can use this free for any purpose.  It's in
 * the public domain.  It has no warranty.
 *
 * $FreeBSD$
 */

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

#define LOWER8b_MASK rte_le_to_cpu_32(0xff)
#define LOWER16b_MASK rte_le_to_cpu_32(0xffff)
#define LOWER24b_MASK rte_le_to_cpu_32(0xffffff)

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

