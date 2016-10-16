#include "keygen.h"
#include <stdio.h>

const int NUMBER_OF_KEYS_TO_GENERATE = 16;

void generate_keys(char *provided_key, uint64_t *keys)
{
	// 0 indicates to drop the bit
	const int BIT_MAP[64] = {
		8, 16, 24, 56, 52, 44, 36, 0, 7, 15, 23, 55, 51, 43, 35, 0, 
		6, 14, 22, 54, 50, 42, 34, 0, 5, 13, 21, 53, 49, 41, 33, 0,
		4, 12, 20, 28, 48, 40, 32, 0, 3, 11, 19, 27, 47, 39, 31, 0,
		2, 10, 18, 26, 46, 38, 30, 0, 1, 9, 17, 25, 45, 37, 29, 0};

	uint64_t last_key = (uint64_t) provided_key;
	for (int i = 0; i < NUMBER_OF_KEYS_TO_GENERATE; i++) {
		uint64_t next_key;
		for (int i = 0; i < 64; i++) {
			next_key &= ~(1 << i);
		}

		for (int j = 0; j < 64; j++) {
			int bit_is_set = (last_key >> j) & 1;

			// If the bit map value is not 0, then we need to transpose it properly
			if (BIT_MAP[j]) {
				int new_position = BIT_MAP[j];
				
				if (bit_is_set) {
					next_key |= INT64_C(1) << (new_position - 1);
				}
				else {
					next_key &= ~(INT64_C(1) << (new_position - 1));
				}
			}
		}

		// Set the new key in the keys array, then move it to be the last_key so we can use it next iteration
		keys[i] = next_key;
		last_key = next_key;
	}
}