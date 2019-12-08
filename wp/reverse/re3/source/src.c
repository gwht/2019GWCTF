#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "aes.h"
// gcc -s aes.c aes.h src.c -o re


// ads = 0x402219
// end = 0x4022F8
// while ads <= end:
// 	patch_byte(ads, get_byte(ads)^0x99)
// 	ads += 1
// print "OK"


// flag{924a9ab2163d390410d0a1f670}
uint8_t key[0x10];
uint8_t vdata[0x20] = {188,
 10,
 173,
 192,
 20,
 124,
 94,
 204,
 224,
 177,
 64,
 188,
 156,
 81,
 213,
 43,
 70,
 178,
 185,
 67,
 77,
 229,
 50,
 75,
 173,
 127,
 180,
 179,
 156,
 219,
 75,
 91};

uint8_t Prime_Constants_char[] = {
	3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251};

uint8_t CRC32_table[] = {
	0, 0, 0, 0, 150, 48, 7, 119, 44, 97, 14, 238, 186, 81, 9, 153, 25, 196, 109, 7};

uint8_t Base64_table[] = {
	65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 43, 47};

// Constants are the integer part of the sines of integers (in radians) * 2^32.
const uint32_t k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

// r specifies the per-round shift amounts
const uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
					  5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
					  4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
					  6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

void to_bytes(uint32_t val, uint8_t *bytes)
{
	bytes[0] = (uint8_t)val;
	bytes[1] = (uint8_t)(val >> 8);
	bytes[2] = (uint8_t)(val >> 16);
	bytes[3] = (uint8_t)(val >> 24);
}

uint32_t to_int32(const uint8_t *bytes)
{
	return (uint32_t)bytes[0] | ((uint32_t)bytes[1] << 8) | ((uint32_t)bytes[2] << 16) | ((uint32_t)bytes[3] << 24);
}

void md5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest)
{

	// These vars will contain the hash
	uint32_t h0, h1, h2, h3;

	// Message (to prepare)
	uint8_t *msg = NULL;

	size_t new_len, offset;
	uint32_t w[16];
	uint32_t a, b, c, d, i, f, g, temp;

	// Initialize variables - simple count in nibbles:
	h0 = 0x67452301;
	h1 = 0xefcdab89;
	h2 = 0x98badcfe;
	h3 = 0x10325476;

	//Pre-processing:
	//append "1" bit to message
	//append "0" bits until message length in bits ≡ 448 (mod 512)
	//append length mod (2^64) to message

	for (new_len = initial_len + 1; new_len % (512 / 8) != 448 / 8; new_len++)
		;

	msg = (uint8_t *)malloc(new_len + 8);
	memcpy(msg, initial_msg, initial_len);
	msg[initial_len] = 0x80; // append the "1" bit; most significant bit is "first"
	for (offset = initial_len + 1; offset < new_len; offset++)
		msg[offset] = 0; // append "0" bits

	// append the len in bits at the end of the buffer.
	to_bytes(initial_len * 8, msg + new_len);
	// initial_len>>29 == initial_len*8>>32, but avoids overflow.
	to_bytes(initial_len >> 29, msg + new_len + 4);

	// Process the message in successive 512-bit chunks:
	//for each 512-bit chunk of message:
	for (offset = 0; offset < new_len; offset += (512 / 8))
	{

		// break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
		for (i = 0; i < 16; i++)
			w[i] = to_int32(msg + offset + i * 4);

		// Initialize hash value for this chunk:
		a = h0;
		b = h1;
		c = h2;
		d = h3;

		// Main loop:
		for (i = 0; i < 64; i++)
		{

			if (i < 16)
			{
				f = (b & c) | ((~b) & d);
				g = i;
			}
			else if (i < 32)
			{
				f = (d & b) | ((~d) & c);
				g = (5 * i + 1) % 16;
			}
			else if (i < 48)
			{
				f = b ^ c ^ d;
				g = (3 * i + 5) % 16;
			}
			else
			{
				f = c ^ (b | (~d));
				g = (7 * i) % 16;
			}

			temp = d;
			d = c;
			c = b;
			b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
			a = temp;
		}

		// Add this chunk's hash to result so far:
		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
	}

	// cleanup
	free(msg);

	//var char digest[16] := h0 append h1 append h2 append h3 //(Output is in little-endian)
	to_bytes(h0, digest);
	to_bytes(h1, digest + 4);
	to_bytes(h2, digest + 8);
	to_bytes(h3, digest + 12);
}

void generatekey(uint8_t *key)
{
	uint8_t digest[0x40];
	md5(Base64_table, 64, digest);
	md5(CRC32_table, 20, digest + 0x10);
	md5(Prime_Constants_char, 53, digest + 0x20);
	md5(k, 64 * 4, digest + 0x30);
	md5(digest, 0x40, key);
}

int judge(uint8_t *ttt);

int main()
{
	uint8_t in[40];
	scanf("%39s", in);
	int len = strlen(in);
	if (len != 32)
	{
		printf("Wrong!\n");
		exit(0);
	}

	int (*p)(char *s);
	p = judge;
	mprotect(0x400000, 0xF000, PROT_READ | PROT_WRITE | PROT_EXEC);
	uint8_t *pt = (uint8_t *)p;
	/*decrypt here*/
	for (int i = 0; i < 224; i++)
	{
		uint8_t tmp = pt[i];
		pt[i] = tmp ^ 0x99;
	}

	generatekey(key);
	// key = [
	//	0xcb, 0x8d, 0x49, 0x35, 0x21, 0xb4, 0x7a, 0x4c, 
	//  0xc1, 0xae, 0x7e, 0x62, 0x22, 0x92, 0x66, 0xce
	//]

	if (judge(in))
	{
		printf("Correct!\n");
	}
	else
	{
		printf("Wrong!\n");
	}
	exit(0);
}

int judge(uint8_t *ttt)
{
	struct AES_ctx ctx;
	AES_init_ctx(&ctx, key);
	AES_ECB_encrypt(&ctx, ttt);
	AES_ECB_encrypt(&ctx, ttt + 0x10);

	int right = 1;
	for (int i = 0; i < 0x20; i++)
	{
		if (ttt[i] != vdata[i])
		{
			right = 0;
		}
	}
	return right;
}