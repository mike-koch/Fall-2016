#include "rounds.h"
#include "permutator.h"

void apply_rounds(uint64_t *initial_permutation, uint64_t *output, uint64_t *keys, Mode mode) {
	// Divide the initial permutation into 2 32-bit blocks
	uint32_t left_half = (*initial_permutation & 0xFFFFFFFF00000000) >> 32;
	uint32_t right_half = *initial_permutation & 0x00000000FFFFFFFF;

	int keyIndex = 0;
	int keyIncrementer = 1;

	if (mode == Mode::DECRYPTION) {
		//-- TODO!
	}

	// Rounds
	for (int i = 0; i < 15; i++) {
		uint64_t key = keys[keyIndex];
		uint32_t original_right_half = right_half;

		uint64_t expanded_right_half;
		apply_expansion_permutation(&right_half, &expanded_right_half);
		uint64_t right_and_key = key ^ expanded_right_half;

		uint8_t six_bit_one = (uint8_t) ((right_and_key & 0xFC00000000000000) >> 56);
		uint8_t six_bit_two = (uint8_t)((right_and_key & 0x03F0000000000000) >> 50);
		uint8_t six_bit_three = (uint8_t)((right_and_key & 0x000FC00000000000) >> 44);
		uint8_t six_bit_four = (uint8_t)((right_and_key & 0x00003F0000000000) >> 38);
		uint8_t six_bit_five = (uint8_t)((right_and_key & 0x000000FC00000000) >> 32);
		uint8_t six_bit_six = (uint8_t)((right_and_key & 0x00000003F0000000) >> 26);
		uint8_t six_bit_seven = (uint8_t)((right_and_key & 0x000000000FC00000) >> 20);
		uint8_t six_bit_eight = (uint8_t)((right_and_key & 0x00000000003F0000) >> 14);

		// Six bit one, S-Box 1
		int row_number = -1;
		if ((six_bit_one & (1 << 5)) && (six_bit_one & (1 << 0))) row_number = 3;
		if ((six_bit_one & (1 << 5)) && (six_bit_one & (1 << 0)) == 0) row_number = 2;
		if ((six_bit_one & (1 << 5)) == 0 && (six_bit_one & (1 << 0))) row_number = 1;
		else row_number = 0;

		uint8_t s_box_one_value;
		int s_box_one[4][16] = {
			{ 14, 4, 3, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
			{ 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
			{ 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
			{ 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }
		};
		int bit_two_value = (six_bit_one & (1 << 4)) ? 8 : 0;
		int bit_three_value = (six_bit_one & (1 << 3)) ? 4 : 0;
		int bit_four_value = (six_bit_one & (1 << 2)) ? 2 : 0;
		int bit_five_value = (six_bit_one & (1 << 1)) ? 1 : 0;
		int sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_one_value = s_box_one[row_number][sum];

		// Six bit two, S-Box 2
		row_number = -1;
		if ((six_bit_two & (1 << 5)) && (six_bit_two & (1 << 0))) row_number = 3;
		if ((six_bit_two & (1 << 5)) && (six_bit_two & (1 << 0)) == 0) row_number = 2;
		if ((six_bit_two & (1 << 5)) == 0 && (six_bit_two & (1 << 0))) row_number = 1;
		else row_number = 0;

		uint8_t s_box_two_value;
		int s_box_two[4][16] = {
			{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
			{ 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
			{ 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
			{ 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }
		};
		bit_two_value = (six_bit_two & (1 << 4)) ? 8 : 0;
		bit_three_value = (six_bit_two & (1 << 3)) ? 4 : 0;
		bit_four_value = (six_bit_two & (1 << 2)) ? 2 : 0;
		bit_five_value = (six_bit_two & (1 << 1)) ? 1 : 0;
		sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_two_value = s_box_two[row_number][sum];

		// Six bit three, S-Box 3
		row_number = -1;
		if ((six_bit_three & (1 << 5)) && (six_bit_three & (1 << 0))) row_number = 3;
		if ((six_bit_three & (1 << 5)) && (six_bit_three & (1 << 0)) == 0) row_number = 2;
		if ((six_bit_three & (1 << 5)) == 0 && (six_bit_three & (1 << 0))) row_number = 1;
		else row_number = 0;

		uint8_t s_box_three_value;
		int s_box_three[4][16] = {
			{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
			{ 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
			{ 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
			{ 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }
		};
		bit_two_value = (six_bit_three & (1 << 4)) ? 8 : 0;
		bit_three_value = (six_bit_three & (1 << 3)) ? 4 : 0;
		bit_four_value = (six_bit_three & (1 << 2)) ? 2 : 0;
		bit_five_value = (six_bit_three & (1 << 1)) ? 1 : 0;
		sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_three_value = s_box_three[row_number][sum];

		// Six bit four, S-Box 4
		row_number = -1;
		if ((six_bit_four & (1 << 5)) && (six_bit_four & (1 << 0))) row_number = 3;
		if ((six_bit_four & (1 << 5)) && (six_bit_four & (1 << 0)) == 0) row_number = 2;
		if ((six_bit_four & (1 << 5)) == 0 && (six_bit_four & (1 << 0))) row_number = 1;
		else row_number = 0;

		uint8_t s_box_four_value;
		int s_box_four[4][16] = {
			{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
			{ 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
			{ 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
			{ 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }
		};
		bit_two_value = (six_bit_four & (1 << 4)) ? 8 : 0;
		bit_three_value = (six_bit_four & (1 << 3)) ? 4 : 0;
		bit_four_value = (six_bit_four & (1 << 2)) ? 2 : 0;
		bit_five_value = (six_bit_four & (1 << 1)) ? 1 : 0;
		sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_four_value = s_box_four[row_number][sum];

		// Six bit five, S-Box 5
		row_number = -1;
		if ((six_bit_five & (1 << 5)) && (six_bit_five & (1 << 0))) row_number = 3;
		if ((six_bit_five & (1 << 5)) && (six_bit_five & (1 << 0)) == 0) row_number = 2;
		if ((six_bit_five & (1 << 5)) == 0 && (six_bit_five & (1 << 0))) row_number = 1;
		else row_number = 0;

		uint8_t s_box_five_value;
		int s_box_five[4][16] = {
			{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
			{ 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
			{ 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
			{ 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }
		};
		bit_two_value = (six_bit_five & (1 << 4)) ? 8 : 0;
		bit_three_value = (six_bit_five & (1 << 3)) ? 4 : 0;
		bit_four_value = (six_bit_five & (1 << 2)) ? 2 : 0;
		bit_five_value = (six_bit_five & (1 << 1)) ? 1 : 0;
		sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_five_value = s_box_five[row_number][sum];

		// Six bit six, S-Box 6
		row_number = -1;
		if ((six_bit_six & (1 << 5)) && (six_bit_six & (1 << 0))) row_number = 3;
		if ((six_bit_six & (1 << 5)) && (six_bit_six & (1 << 0)) == 0) row_number = 2;
		if ((six_bit_six & (1 << 5)) == 0 && (six_bit_six & (1 << 0))) row_number = 1;
		else row_number = 0;

		uint8_t s_box_six_value;
		int s_box_six[4][16] = {
			{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
			{ 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
			{ 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
			{ 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }
		};
		bit_two_value = (six_bit_six & (1 << 4)) ? 8 : 0;
		bit_three_value = (six_bit_six & (1 << 3)) ? 4 : 0;
		bit_four_value = (six_bit_six & (1 << 2)) ? 2 : 0;
		bit_five_value = (six_bit_six & (1 << 1)) ? 1 : 0;
		sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_six_value = s_box_six[row_number][sum];

		// Six bit seven, S-Box 7
		row_number = -1;
		if ((six_bit_seven & (1 << 5)) && (six_bit_seven & (1 << 0))) row_number = 3;
		if ((six_bit_seven & (1 << 5)) && (six_bit_seven & (1 << 0)) == 0) row_number = 2;
		if ((six_bit_seven & (1 << 5)) == 0 && (six_bit_seven & (1 << 0))) row_number = 1;
		else row_number = 0;

		uint8_t s_box_seven_value;
		int s_box_seven[4][16] = {
			{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
			{ 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
			{ 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
			{ 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }
		};
		bit_two_value = (six_bit_seven & (1 << 4)) ? 8 : 0;
		bit_three_value = (six_bit_seven & (1 << 3)) ? 4 : 0;
		bit_four_value = (six_bit_seven & (1 << 2)) ? 2 : 0;
		bit_five_value = (six_bit_seven & (1 << 1)) ? 1 : 0;
		sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_seven_value = s_box_seven[row_number][sum];

		// Six bit eight, S-Box 8
		row_number = -1;
		if ((six_bit_eight & (1 << 5)) && (six_bit_eight & (1 << 0))) row_number = 3;
		if ((six_bit_eight & (1 << 5)) && (six_bit_eight & (1 << 0)) == 0) row_number = 2;
		if ((six_bit_eight & (1 << 5)) == 0 && (six_bit_eight & (1 << 0))) row_number = 1;
		else row_number = 0;

		uint8_t s_box_eight_value;
		int s_box_eight[4][16] = {
			{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
			{ 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
			{ 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
			{ 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }
		};
		bit_two_value = (six_bit_eight & (1 << 4)) ? 8 : 0;
		bit_three_value = (six_bit_eight & (1 << 3)) ? 4 : 0;
		bit_four_value = (six_bit_eight & (1 << 2)) ? 2 : 0;
		bit_five_value = (six_bit_eight & (1 << 1)) ? 1 : 0;
		sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_eight_value = s_box_eight[row_number][sum];

		// Use a straight P box to convert our 32-bit value (8 4-bit S box vlaues) to a new 32-bit value
		// I'm too lazy to convert the S box values into one 32-bit value, so I'm going to treat bit "5" as sbox 2, bit 1, etc.
		uint32_t straight_p_box_result = 0;
		if (s_box_one_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 16));
		if (s_box_one_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 7));
		if (s_box_one_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 20));
		if (s_box_one_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 21));
		if (s_box_two_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 29));
		if (s_box_two_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 12));
		if (s_box_two_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 28));
		if (s_box_two_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 17));
		if (s_box_three_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 1));
		if (s_box_three_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 15));
		if (s_box_three_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 23));
		if (s_box_three_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 26));
		if (s_box_four_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 5));
		if (s_box_four_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 18));
		if (s_box_four_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 31));
		if (s_box_four_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 10));
		if (s_box_five_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 2));
		if (s_box_five_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 8));
		if (s_box_five_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 24));
		if (s_box_five_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 14));
		if (s_box_six_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 32));
		if (s_box_six_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 27));
		if (s_box_six_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 3));
		if (s_box_six_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 9));
		if (s_box_seven_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 19));
		if (s_box_seven_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 13));
		if (s_box_seven_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 30));
		if (s_box_seven_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 6));
		if (s_box_eight_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 22));
		if (s_box_eight_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 11));
		if (s_box_eight_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 4));
		if (s_box_eight_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 25));

		// XOR the straight_p_box_result with the left half
		uint32_t right_half = left_half ^ straight_p_box_result;

		left_half = original_right_half;
	}

	// Since we're done, combine the left and right halves to make our output
	*output = (uint64_t) left_half << 32 | right_half;
}