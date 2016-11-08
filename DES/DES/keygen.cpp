/*
Mike Koch
EECS 4760 - Computer Security
DES
keygen.cpp: Generates the 16 keys needed for each Feistel round, based on the key provided. Handles the compression permutations and rotations
*/
#include "keygen.h"
#include <stdio.h>

const int NUMBER_OF_KEYS_TO_GENERATE = 16;

// Function prototypes
void compress_original_key(uint64_t provided_key, uint64_t *compressed_key);
uint32_t rotate_left(uint32_t original, int number_of_bits_to_rotate);
void compress_rotated_key(uint64_t *combined_key, uint64_t *compressed_key);

void generate_keys(uint64_t provided_key, uint64_t *keys)
{
	uint64_t compressed_key = 0;
	compress_original_key(provided_key, &compressed_key);

	// Split the 56-bit key into two chunks, both 28 bits long.
	uint32_t original_left_side = (uint32_t)((compressed_key & 0xFFFFFFF000000000) >> 32);
	uint32_t original_right_side = (uint32_t)((compressed_key & 0x0000000FFFFFFF00) >> 4);

	for (int i = 0; i < NUMBER_OF_KEYS_TO_GENERATE; i++) {
		int rotation_amount = (i == 0 || i == 1 || i == 8 || i == 15) 
			? 1 
			: 2;

		uint32_t left_side_rotated = rotate_left(original_left_side, rotation_amount);
		uint32_t right_side_rotated = rotate_left(original_right_side, rotation_amount);

		uint64_t combined_key = 0;

		//-- Taking our two halfs, combine them into the combined key
		if (left_side_rotated & (1 << (32 - 1))) combined_key |= (INT64_C(1) << (64 - 1));
		if (left_side_rotated & (1 << (32 - 2))) combined_key |= (INT64_C(1) << (64 - 2));
		if (left_side_rotated & (1 << (32 - 3))) combined_key |= (INT64_C(1) << (64 - 3));
		if (left_side_rotated & (1 << (32 - 4))) combined_key |= (INT64_C(1) << (64 - 4));
		if (left_side_rotated & (1 << (32 - 5))) combined_key |= (INT64_C(1) << (64 - 5));
		if (left_side_rotated & (1 << (32 - 6))) combined_key |= (INT64_C(1) << (64 - 6));
		if (left_side_rotated & (1 << (32 - 7))) combined_key |= (INT64_C(1) << (64 - 7));
		if (left_side_rotated & (1 << (32 - 8))) combined_key |= (INT64_C(1) << (64 - 8));
		if (left_side_rotated & (1 << (32 - 9))) combined_key |= (INT64_C(1) << (64 - 9));
		if (left_side_rotated & (1 << (32 - 10))) combined_key |= (INT64_C(1) << (64 - 10));
		if (left_side_rotated & (1 << (32 - 11))) combined_key |= (INT64_C(1) << (64 - 11));
		if (left_side_rotated & (1 << (32 - 12))) combined_key |= (INT64_C(1) << (64 - 12));
		if (left_side_rotated & (1 << (32 - 13))) combined_key |= (INT64_C(1) << (64 - 13));
		if (left_side_rotated & (1 << (32 - 14))) combined_key |= (INT64_C(1) << (64 - 14));
		if (left_side_rotated & (1 << (32 - 15))) combined_key |= (INT64_C(1) << (64 - 15));
		if (left_side_rotated & (1 << (32 - 16))) combined_key |= (INT64_C(1) << (64 - 16));
		if (left_side_rotated & (1 << (32 - 17))) combined_key |= (INT64_C(1) << (64 - 17));
		if (left_side_rotated & (1 << (32 - 18))) combined_key |= (INT64_C(1) << (64 - 18));
		if (left_side_rotated & (1 << (32 - 19))) combined_key |= (INT64_C(1) << (64 - 19));
		if (left_side_rotated & (1 << (32 - 20))) combined_key |= (INT64_C(1) << (64 - 20));
		if (left_side_rotated & (1 << (32 - 21))) combined_key |= (INT64_C(1) << (64 - 21));
		if (left_side_rotated & (1 << (32 - 22))) combined_key |= (INT64_C(1) << (64 - 22));
		if (left_side_rotated & (1 << (32 - 23))) combined_key |= (INT64_C(1) << (64 - 23));
		if (left_side_rotated & (1 << (32 - 24))) combined_key |= (INT64_C(1) << (64 - 24));
		if (left_side_rotated & (1 << (32 - 25))) combined_key |= (INT64_C(1) << (64 - 25));
		if (left_side_rotated & (1 << (32 - 26))) combined_key |= (INT64_C(1) << (64 - 26));
		if (left_side_rotated & (1 << (32 - 27))) combined_key |= (INT64_C(1) << (64 - 27));
		if (left_side_rotated & (1 << (32 - 28))) combined_key |= (INT64_C(1) << (64 - 28));
		if (right_side_rotated & (1 << (32 - 1))) combined_key |= (INT64_C(1) << (64 - 29));
		if (right_side_rotated & (1 << (32 - 2))) combined_key |= (INT64_C(1) << (64 - 30));
		if (right_side_rotated & (1 << (32 - 3))) combined_key |= (INT64_C(1) << (64 - 31));
		if (right_side_rotated & (1 << (32 - 4))) combined_key |= (INT64_C(1) << (64 - 32));
		if (right_side_rotated & (1 << (32 - 5))) combined_key |= (INT64_C(1) << (64 - 33));
		if (right_side_rotated & (1 << (32 - 6))) combined_key |= (INT64_C(1) << (64 - 34));
		if (right_side_rotated & (1 << (32 - 7))) combined_key |= (INT64_C(1) << (64 - 35));
		if (right_side_rotated & (1 << (32 - 8))) combined_key |= (INT64_C(1) << (64 - 36));
		if (right_side_rotated & (1 << (32 - 9))) combined_key |= (INT64_C(1) << (64 - 37));
		if (right_side_rotated & (1 << (32 - 10))) combined_key |= (INT64_C(1) << (64 - 38));
		if (right_side_rotated & (1 << (32 - 11))) combined_key |= (INT64_C(1) << (64 - 39));
		if (right_side_rotated & (1 << (32 - 12))) combined_key |= (INT64_C(1) << (64 - 40));
		if (right_side_rotated & (1 << (32 - 13))) combined_key |= (INT64_C(1) << (64 - 41));
		if (right_side_rotated & (1 << (32 - 14))) combined_key |= (INT64_C(1) << (64 - 42));
		if (right_side_rotated & (1 << (32 - 15))) combined_key |= (INT64_C(1) << (64 - 43));
		if (right_side_rotated & (1 << (32 - 16))) combined_key |= (INT64_C(1) << (64 - 44));
		if (right_side_rotated & (1 << (32 - 17))) combined_key |= (INT64_C(1) << (64 - 45));
		if (right_side_rotated & (1 << (32 - 18))) combined_key |= (INT64_C(1) << (64 - 46));
		if (right_side_rotated & (1 << (32 - 19))) combined_key |= (INT64_C(1) << (64 - 47));
		if (right_side_rotated & (1 << (32 - 20))) combined_key |= (INT64_C(1) << (64 - 48));
		if (right_side_rotated & (1 << (32 - 21))) combined_key |= (INT64_C(1) << (64 - 49));
		if (right_side_rotated & (1 << (32 - 22))) combined_key |= (INT64_C(1) << (64 - 50));
		if (right_side_rotated & (1 << (32 - 23))) combined_key |= (INT64_C(1) << (64 - 51));
		if (right_side_rotated & (1 << (32 - 24))) combined_key |= (INT64_C(1) << (64 - 52));
		if (right_side_rotated & (1 << (32 - 25))) combined_key |= (INT64_C(1) << (64 - 53));
		if (right_side_rotated & (1 << (32 - 26))) combined_key |= (INT64_C(1) << (64 - 54));
		if (right_side_rotated & (1 << (32 - 27))) combined_key |= (INT64_C(1) << (64 - 55));
		if (right_side_rotated & (1 << (32 - 28))) combined_key |= (INT64_C(1) << (64 - 56));



		//-- Pass our combined key into another P-Box to strip this to 48 bits
		uint64_t permutated_key;
		compress_rotated_key(&combined_key, &permutated_key);

		//-- store in keys array
		keys[i] = permutated_key;

		//-- Our "new" 56 bit key is the one we rotated earlier
		original_left_side = left_side_rotated;
		original_right_side = right_side_rotated;
	}
}

void compress_original_key(uint64_t provided_key, uint64_t *compressed_key) {
	// Compression P-Box: 64 -> 56 bits
	if (provided_key & (INT64_C(1) << (64 - 57))) *compressed_key |= (INT64_C(1) << (64 - 1));
	if (provided_key & (INT64_C(1) << (64 - 49))) *compressed_key |= (INT64_C(1) << (64 - 2));
	if (provided_key & (INT64_C(1) << (64 - 41))) *compressed_key |= (INT64_C(1) << (64 - 3));
	if (provided_key & (INT64_C(1) << (64 - 33))) *compressed_key |= (INT64_C(1) << (64 - 4));
	if (provided_key & (INT64_C(1) << (64 - 25))) *compressed_key |= (INT64_C(1) << (64 - 5));
	if (provided_key & (INT64_C(1) << (64 - 17))) *compressed_key |= (INT64_C(1) << (64 - 6));
	if (provided_key & (INT64_C(1) << (64 - 9))) *compressed_key |= (INT64_C(1) << (64 - 7));
	if (provided_key & (INT64_C(1) << (64 - 1))) *compressed_key |= (INT64_C(1) << (64 - 8));
	if (provided_key & (INT64_C(1) << (64 - 58))) *compressed_key |= (INT64_C(1) << (64 - 9));
	if (provided_key & (INT64_C(1) << (64 - 50))) *compressed_key |= (INT64_C(1) << (64 - 10));
	if (provided_key & (INT64_C(1) << (64 - 42))) *compressed_key |= (INT64_C(1) << (64 - 11));
	if (provided_key & (INT64_C(1) << (64 - 34))) *compressed_key |= (INT64_C(1) << (64 - 12));
	if (provided_key & (INT64_C(1) << (64 - 26))) *compressed_key |= (INT64_C(1) << (64 - 13));
	if (provided_key & (INT64_C(1) << (64 - 18))) *compressed_key |= (INT64_C(1) << (64 - 14));
	if (provided_key & (INT64_C(1) << (64 - 10))) *compressed_key |= (INT64_C(1) << (64 - 15));
	if (provided_key & (INT64_C(1) << (64 - 2))) *compressed_key |= (INT64_C(1) << (64 - 16));
	if (provided_key & (INT64_C(1) << (64 - 59))) *compressed_key |= (INT64_C(1) << (64 - 17));
	if (provided_key & (INT64_C(1) << (64 - 51))) *compressed_key |= (INT64_C(1) << (64 - 18));
	if (provided_key & (INT64_C(1) << (64 - 43))) *compressed_key |= (INT64_C(1) << (64 - 19));
	if (provided_key & (INT64_C(1) << (64 - 35))) *compressed_key |= (INT64_C(1) << (64 - 20));
	if (provided_key & (INT64_C(1) << (64 - 27))) *compressed_key |= (INT64_C(1) << (64 - 21));
	if (provided_key & (INT64_C(1) << (64 - 19))) *compressed_key |= (INT64_C(1) << (64 - 22));
	if (provided_key & (INT64_C(1) << (64 - 11))) *compressed_key |= (INT64_C(1) << (64 - 23));
	if (provided_key & (INT64_C(1) << (64 - 3))) *compressed_key |= (INT64_C(1) << (64 - 24));
	if (provided_key & (INT64_C(1) << (64 - 60))) *compressed_key |= (INT64_C(1) << (64 - 25));
	if (provided_key & (INT64_C(1) << (64 - 52))) *compressed_key |= (INT64_C(1) << (64 - 26));
	if (provided_key & (INT64_C(1) << (64 - 44))) *compressed_key |= (INT64_C(1) << (64 - 27));
	if (provided_key & (INT64_C(1) << (64 - 36))) *compressed_key |= (INT64_C(1) << (64 - 28));
	if (provided_key & (INT64_C(1) << (64 - 63))) *compressed_key |= (INT64_C(1) << (64 - 29));
	if (provided_key & (INT64_C(1) << (64 - 55))) *compressed_key |= (INT64_C(1) << (64 - 30));
	if (provided_key & (INT64_C(1) << (64 - 47))) *compressed_key |= (INT64_C(1) << (64 - 31));
	if (provided_key & (INT64_C(1) << (64 - 39))) *compressed_key |= (INT64_C(1) << (64 - 32));
	if (provided_key & (INT64_C(1) << (64 - 31))) *compressed_key |= (INT64_C(1) << (64 - 33));
	if (provided_key & (INT64_C(1) << (64 - 23))) *compressed_key |= (INT64_C(1) << (64 - 34));
	if (provided_key & (INT64_C(1) << (64 - 15))) *compressed_key |= (INT64_C(1) << (64 - 35));
	if (provided_key & (INT64_C(1) << (64 - 7))) *compressed_key |= (INT64_C(1) << (64 - 36));
	if (provided_key & (INT64_C(1) << (64 - 62))) *compressed_key |= (INT64_C(1) << (64 - 37));
	if (provided_key & (INT64_C(1) << (64 - 54))) *compressed_key |= (INT64_C(1) << (64 - 38));
	if (provided_key & (INT64_C(1) << (64 - 46))) *compressed_key |= (INT64_C(1) << (64 - 39));
	if (provided_key & (INT64_C(1) << (64 - 38))) *compressed_key |= (INT64_C(1) << (64 - 40));
	if (provided_key & (INT64_C(1) << (64 - 30))) *compressed_key |= (INT64_C(1) << (64 - 41));
	if (provided_key & (INT64_C(1) << (64 - 22))) *compressed_key |= (INT64_C(1) << (64 - 42));
	if (provided_key & (INT64_C(1) << (64 - 14))) *compressed_key |= (INT64_C(1) << (64 - 43));
	if (provided_key & (INT64_C(1) << (64 - 6))) *compressed_key |= (INT64_C(1) << (64 - 44));
	if (provided_key & (INT64_C(1) << (64 - 61))) *compressed_key |= (INT64_C(1) << (64 - 45));
	if (provided_key & (INT64_C(1) << (64 - 53))) *compressed_key |= (INT64_C(1) << (64 - 46));
	if (provided_key & (INT64_C(1) << (64 - 45))) *compressed_key |= (INT64_C(1) << (64 - 47));
	if (provided_key & (INT64_C(1) << (64 - 37))) *compressed_key |= (INT64_C(1) << (64 - 48));
	if (provided_key & (INT64_C(1) << (64 - 29))) *compressed_key |= (INT64_C(1) << (64 - 49));
	if (provided_key & (INT64_C(1) << (64 - 21))) *compressed_key |= (INT64_C(1) << (64 - 50));
	if (provided_key & (INT64_C(1) << (64 - 13))) *compressed_key |= (INT64_C(1) << (64 - 51));
	if (provided_key & (INT64_C(1) << (64 - 5))) *compressed_key |= (INT64_C(1) << (64 - 52));
	if (provided_key & (INT64_C(1) << (64 - 28))) *compressed_key |= (INT64_C(1) << (64 - 53));
	if (provided_key & (INT64_C(1) << (64 - 20))) *compressed_key |= (INT64_C(1) << (64 - 54));
	if (provided_key & (INT64_C(1) << (64 - 12))) *compressed_key |= (INT64_C(1) << (64 - 55));
	if (provided_key & (INT64_C(1) << (64 - 4))) *compressed_key |= (INT64_C(1) << (64 - 56));
}

/* Helper methods to rotate our 28 bit value left or right:

	The first part of the rotate blindly rotates everything to the left (or right) by the number of bits specified (in our case, 1 or 2)
	Then, because we lost at least 1 bit during the rotate (if left-rotate, the MS bits; if right-rotate, the LS bits), we rotate right by the number of bits lost to push them to the other end
*/
uint32_t rotate_left(uint32_t original, int number_of_bits_to_rotate) {
	uint32_t rotated = ((original << number_of_bits_to_rotate) | (original >> (28 - number_of_bits_to_rotate)));

	// Clear bits 29-32 just to be safe
	rotated &= ~(1 << (32 - 29));
	rotated &= ~(1 << (32 - 30));
	rotated &= ~(1 << (32 - 31));
	rotated &= ~(1 << (32 - 32));
	return rotated;
}

void compress_rotated_key(uint64_t *combined_key, uint64_t *compressed_key) {
	*compressed_key = 0;

	if (*combined_key & (INT64_C(1) << (64 - 14))) *compressed_key |= (INT64_C(1) << (64 - 1));
	if (*combined_key & (INT64_C(1) << (64 - 17))) *compressed_key |= (INT64_C(1) << (64 - 2));
	if (*combined_key & (INT64_C(1) << (64 - 11))) *compressed_key |= (INT64_C(1) << (64 - 3));
	if (*combined_key & (INT64_C(1) << (64 - 24))) *compressed_key |= (INT64_C(1) << (64 - 4));
	if (*combined_key & (INT64_C(1) << (64 - 1))) *compressed_key |= (INT64_C(1) << (64 - 5));
	if (*combined_key & (INT64_C(1) << (64 - 5))) *compressed_key |= (INT64_C(1) << (64 - 6));
	if (*combined_key & (INT64_C(1) << (64 - 3))) *compressed_key |= (INT64_C(1) << (64 - 7));
	if (*combined_key & (INT64_C(1) << (64 - 28))) *compressed_key |= (INT64_C(1) << (64 - 8));
	if (*combined_key & (INT64_C(1) << (64 - 15))) *compressed_key |= (INT64_C(1) << (64 - 9));
	if (*combined_key & (INT64_C(1) << (64 - 6))) *compressed_key |= (INT64_C(1) << (64 - 10));
	if (*combined_key & (INT64_C(1) << (64 - 21))) *compressed_key |= (INT64_C(1) << (64 - 11));
	if (*combined_key & (INT64_C(1) << (64 - 10))) *compressed_key |= (INT64_C(1) << (64 - 12));
	if (*combined_key & (INT64_C(1) << (64 - 23))) *compressed_key |= (INT64_C(1) << (64 - 13));
	if (*combined_key & (INT64_C(1) << (64 - 19))) *compressed_key |= (INT64_C(1) << (64 - 14));
	if (*combined_key & (INT64_C(1) << (64 - 12))) *compressed_key |= (INT64_C(1) << (64 - 15));
	if (*combined_key & (INT64_C(1) << (64 - 4))) *compressed_key |= (INT64_C(1) << (64 - 16));
	if (*combined_key & (INT64_C(1) << (64 - 26))) *compressed_key |= (INT64_C(1) << (64 - 17));
	if (*combined_key & (INT64_C(1) << (64 - 8))) *compressed_key |= (INT64_C(1) << (64 - 18));
	if (*combined_key & (INT64_C(1) << (64 - 16))) *compressed_key |= (INT64_C(1) << (64 - 19));
	if (*combined_key & (INT64_C(1) << (64 - 7))) *compressed_key |= (INT64_C(1) << (64 - 20));
	if (*combined_key & (INT64_C(1) << (64 - 27))) *compressed_key |= (INT64_C(1) << (64 - 21));
	if (*combined_key & (INT64_C(1) << (64 - 20))) *compressed_key |= (INT64_C(1) << (64 - 22));
	if (*combined_key & (INT64_C(1) << (64 - 13))) *compressed_key |= (INT64_C(1) << (64 - 23));
	if (*combined_key & (INT64_C(1) << (64 - 2))) *compressed_key |= (INT64_C(1) << (64 - 24));
	if (*combined_key & (INT64_C(1) << (64 - 41))) *compressed_key |= (INT64_C(1) << (64 - 25));
	if (*combined_key & (INT64_C(1) << (64 - 52))) *compressed_key |= (INT64_C(1) << (64 - 26));
	if (*combined_key & (INT64_C(1) << (64 - 31))) *compressed_key |= (INT64_C(1) << (64 - 27));
	if (*combined_key & (INT64_C(1) << (64 - 37))) *compressed_key |= (INT64_C(1) << (64 - 28));
	if (*combined_key & (INT64_C(1) << (64 - 47))) *compressed_key |= (INT64_C(1) << (64 - 29));
	if (*combined_key & (INT64_C(1) << (64 - 55))) *compressed_key |= (INT64_C(1) << (64 - 30));
	if (*combined_key & (INT64_C(1) << (64 - 30))) *compressed_key |= (INT64_C(1) << (64 - 31));
	if (*combined_key & (INT64_C(1) << (64 - 40))) *compressed_key |= (INT64_C(1) << (64 - 32));
	if (*combined_key & (INT64_C(1) << (64 - 51))) *compressed_key |= (INT64_C(1) << (64 - 33));
	if (*combined_key & (INT64_C(1) << (64 - 45))) *compressed_key |= (INT64_C(1) << (64 - 34));
	if (*combined_key & (INT64_C(1) << (64 - 33))) *compressed_key |= (INT64_C(1) << (64 - 35));
	if (*combined_key & (INT64_C(1) << (64 - 48))) *compressed_key |= (INT64_C(1) << (64 - 36));
	if (*combined_key & (INT64_C(1) << (64 - 44))) *compressed_key |= (INT64_C(1) << (64 - 37));
	if (*combined_key & (INT64_C(1) << (64 - 49))) *compressed_key |= (INT64_C(1) << (64 - 38));
	if (*combined_key & (INT64_C(1) << (64 - 39))) *compressed_key |= (INT64_C(1) << (64 - 39));
	if (*combined_key & (INT64_C(1) << (64 - 56))) *compressed_key |= (INT64_C(1) << (64 - 40));
	if (*combined_key & (INT64_C(1) << (64 - 34))) *compressed_key |= (INT64_C(1) << (64 - 41));
	if (*combined_key & (INT64_C(1) << (64 - 53))) *compressed_key |= (INT64_C(1) << (64 - 42));
	if (*combined_key & (INT64_C(1) << (64 - 46))) *compressed_key |= (INT64_C(1) << (64 - 43));
	if (*combined_key & (INT64_C(1) << (64 - 42))) *compressed_key |= (INT64_C(1) << (64 - 44));
	if (*combined_key & (INT64_C(1) << (64 - 50))) *compressed_key |= (INT64_C(1) << (64 - 45));
	if (*combined_key & (INT64_C(1) << (64 - 36))) *compressed_key |= (INT64_C(1) << (64 - 46));
	if (*combined_key & (INT64_C(1) << (64 - 29))) *compressed_key |= (INT64_C(1) << (64 - 47));
	if (*combined_key & (INT64_C(1) << (64 - 32))) *compressed_key |= (INT64_C(1) << (64 - 48));
}