#include "keygen.h"
#include <stdio.h>

const int NUMBER_OF_KEYS_TO_GENERATE = 16;

// Function prototypes
void compress_original_key(char *provided_key, uint64_t *compressed_key);
void clear_key(uint64_t *key);
void split_for_rotation(uint64_t *compressed_key, uint64_t *half, bool left_side);
uint64_t rotate_left(uint64_t original, int number_of_bits_to_rotate);
void compress_rotated_key(uint64_t *combined_key, uint64_t *compressed_key);

void generate_keys(char *provided_key, uint64_t *keys)
{
	uint64_t compressed_key;
	compress_original_key(provided_key, &compressed_key);

	// Split the 56-bit key into two chunks, both 28 bits long.
	uint64_t original_left_side;
	uint64_t original_right_side;
	split_for_rotation(&compressed_key, &original_left_side, true);
	split_for_rotation(&compressed_key, &original_right_side, false);

	for (int i = 0; i < NUMBER_OF_KEYS_TO_GENERATE; i++) {
		int rotation_amount = (i == 0 || i == 1 || i == 8 || i == 15) 
			? 1 
			: 2;

		uint64_t left_side_rotated = rotate_left(original_left_side, rotation_amount);
		uint64_t right_side_rotated = rotate_left(original_right_side, rotation_amount);

		uint64_t combined_key;
		clear_key(&combined_key);

		//-- Taking our two halfs, combine them into the combined key
		for (int j = 0; j < 28; j++) {
			int bit_is_set = (right_side_rotated >> j) & 1;

			if (bit_is_set) {
				combined_key |= INT64_C(1) << j;
			}
			else {
				combined_key &= ~(INT64_C(1) << j);
			}
		}
		for (int j = 28; j < 56; j++) {
			int bit_is_set = (left_side_rotated >> (j - 28)) & 1;

			if (bit_is_set) {
				combined_key |= INT64_C(1) << j;
			}
			else {
				combined_key &= ~(INT64_C(1) << j);
			}
		}

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

void compress_original_key(char *provided_key, uint64_t *compressed_key) {
	// 0 indicates to drop the bit
	const int BIT_MAP[64] = {
		8, 16, 24, 56, 52, 44, 36, 0, 7, 15, 23, 55, 51, 43, 35, 0,
		6, 14, 22, 54, 50, 42, 34, 0, 5, 13, 21, 53, 49, 41, 33, 0,
		4, 12, 20, 28, 48, 40, 32, 0, 3, 11, 19, 27, 47, 39, 31, 0,
		2, 10, 18, 26, 46, 38, 30, 0, 1, 9, 17, 25, 45, 37, 29, 0 };

	//uint64_t provided_key_as_int = (uint64_t)provided_key;
	uint64_t provided_key_as_int = 0x133457799BBCDFF1;

	clear_key(compressed_key);

	// Compression P-Box: 64 -> 56 bits
	for (int i = 0; i < 64; i++) {
		int bit_is_set = (provided_key_as_int >> (63 - i)) & 1;

		// If the bit map value is not 0, then we need to transpose it properly
		if (BIT_MAP[i]) {
			int new_position = BIT_MAP[i];

			if (bit_is_set) {
				*compressed_key |= INT64_C(1) << (56 - new_position);
			} else {
				*compressed_key &= ~(INT64_C(1) << (56 - new_position));
			}
		}
	}
}

void clear_key(uint64_t *key) {
	for (int i = 0; i < 64; i++) {
		*key &= ~(1 << i);
	}
}

void split_for_rotation(uint64_t *compressed_key, uint64_t *half, bool left_side) {
	int starting_index = left_side ? 28 : 0;
	int ending_index = starting_index + 28;

	clear_key(half);
	for (int i = starting_index; i < ending_index; i++) {
		int bit_is_set = (*compressed_key >> i) & 1;

		if (bit_is_set) {
			*half |= INT64_C(1) << (i - starting_index);
		}
		else {
			*half &= ~(INT64_C(1) << (i - starting_index));
		}
	}
}

/* Helper methods to rotate our 28 bit value left or right:

	The first part of the rotate blindly rotates everything to the left (or right) by the number of bits specified (in our case, 1 or 2)
	Then, because we lost at least 1 bit during the rotate (if left-rotate, the MS bits; if right-rotate, the LS bits), we rotate right by the number of bits lost to push them to the other end

	KNOWN ISSUE: Because I'm rotating a 28-bit value in a 64-bit unsigned int, the MSB (for left rotations) will "bleed" into the 29th bit. This isn't a problem since we won't use the 29th bit anyway.
*/
uint64_t rotate_left(uint64_t original, int number_of_bits_to_rotate) {
	uint64_t rotated = ((original << number_of_bits_to_rotate) | (original >> (28 - number_of_bits_to_rotate)));
	rotated &= ~(1 << 28);
	return rotated;
}

void compress_rotated_key(uint64_t *combined_key, uint64_t *compressed_key) {
	// 0 indicates to drop the bit
	const int BIT_MAP[56] = {
		5, 24, 7, 16, 6, 10, 20, 18, 0, 12, 3, 15, 23, 1,
		9, 19, 2, 0, 14, 22, 11, 0, 13, 4, 0, 17, 21, 8,
		47, 31, 27, 48, 35, 41, 0, 46, 28, 0, 39, 32, 25, 44,
		0, 37, 34, 43, 29, 36, 38, 45, 33, 26, 42, 0, 30, 40
	};

	clear_key(compressed_key);

	// Compression P-Box: 56 -> 48 bits
	for (int i = 0; i < 56; i++) {
		int bit_is_set = (*combined_key >> (55 - i)) & 1;

		// If the bit map value is not 0, then we need to transpose it properly
		if (BIT_MAP[i]) {
			int new_position = BIT_MAP[i];

			if (bit_is_set) {
				*compressed_key |= INT64_C(1) << (48 - new_position);
			}
			else {
				*compressed_key &= ~(INT64_C(1) << (48 - new_position));
			}
		}
	}
}