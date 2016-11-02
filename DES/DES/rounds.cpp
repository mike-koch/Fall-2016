#include "rounds.h"
#include "permutator.h"
#include "sbox.h"

void apply_rounds(uint64_t *initial_permutation, uint64_t *output, uint64_t *keys, Mode mode) {
	// Divide the initial permutation into 2 32-bit blocks
	uint32_t left_half = (*initial_permutation & 0xFFFFFFFF00000000) >> 32;
	uint32_t right_half = *initial_permutation & 0x00000000FFFFFFFF;

	int startIndex = 0;
	int endIndex = 16;
	int incrementer = 1;

	if (mode == Mode::DECRYPTION) {
		// If we're decrypting, we should start at the last key and loop until we get to the first key
		startIndex = 15;
		endIndex = -1;
		incrementer = -1;
	}

	// Rounds
	for (int i = startIndex; i != endIndex; i += incrementer) {
		uint64_t key = keys[i];
		uint32_t original_right_half = right_half;

		// Apply the initial permutation (the expansion permutation)
		uint64_t expanded_right_half;
		apply_expansion_permutation(&right_half, &expanded_right_half);

		// XOR the result of the expansion permutation with the current key
		uint64_t right_and_key = key ^ expanded_right_half;

		// Splitting the result of the XOR operation into eight sets of 6.
		uint8_t six_bit_one = (uint8_t) ((right_and_key & 0xFC00000000000000) >> 56);
		uint8_t six_bit_two = (uint8_t)((right_and_key & 0x03F0000000000000) >> 50);
		uint8_t six_bit_three = (uint8_t)((right_and_key & 0x000FC00000000000) >> 44);
		uint8_t six_bit_four = (uint8_t)((right_and_key & 0x00003F0000000000) >> 38);
		uint8_t six_bit_five = (uint8_t)((right_and_key & 0x000000FC00000000) >> 32);
		uint8_t six_bit_six = (uint8_t)((right_and_key & 0x00000003F0000000) >> 26);
		uint8_t six_bit_seven = (uint8_t)((right_and_key & 0x000000000FC00000) >> 20);
		uint8_t six_bit_eight = (uint8_t)((right_and_key & 0x00000000003F0000) >> 14);

		/* The code below is repetitive, and here's what it does:
		   1) Get the current row by checking the value of the first and 6th bit
		   2) Get the value of bits 2 through 5, and add them accordingly to get a decimal value
		   3) Consult the correct S_BOX 2D array to get the value of the row and column.
		*/
		// Six bit one, S-Box 1
		int row_number = 0;
		if ((six_bit_one & (1 << 7)) && (six_bit_one & (1 << 2))) row_number = 3;
		if ((six_bit_one & (1 << 7)) && (six_bit_one & (1 << 2)) == 0) row_number = 2;
		if ((six_bit_one & (1 << 7)) == 0 && (six_bit_one & (1 << 2))) row_number = 1;

		uint8_t s_box_one_value;
		int bit_two_value = (six_bit_one & (1 << 6)) ? 8 : 0;
		int bit_three_value = (six_bit_one & (1 << 5)) ? 4 : 0;
		int bit_four_value = (six_bit_one & (1 << 4)) ? 2 : 0;
		int bit_five_value = (six_bit_one & (1 << 3)) ? 1 : 0;
		int sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_one_value = S_BOX_ONE[row_number][sum];

		// Six bit two, S-Box 2
		row_number = 0;
		if ((six_bit_two & (1 << 7)) && (six_bit_two & (1 << 2))) row_number = 3;
		if ((six_bit_two & (1 << 7)) && (six_bit_two & (1 << 2)) == 0) row_number = 2;
		if ((six_bit_two & (1 << 7)) == 0 && (six_bit_two & (1 << 2))) row_number = 1;

		uint8_t s_box_two_value;
		bit_two_value = (six_bit_two & (1 << 6)) ? 8 : 0;
		bit_three_value = (six_bit_two & (1 << 5)) ? 4 : 0;
		bit_four_value = (six_bit_two & (1 << 4)) ? 2 : 0;
		bit_five_value = (six_bit_two & (1 << 3)) ? 1 : 0;
		sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_two_value = S_BOX_TWO[row_number][sum];

		// Six bit three, S-Box 3
		row_number = 0;
		if ((six_bit_three & (1 << 7)) && (six_bit_three & (1 << 2))) row_number = 3;
		if ((six_bit_three & (1 << 7)) && (six_bit_three & (1 << 2)) == 0) row_number = 2;
		if ((six_bit_three & (1 << 7)) == 0 && (six_bit_three & (1 << 2))) row_number = 1;

		uint8_t s_box_three_value;
		bit_two_value = (six_bit_three & (1 << 6)) ? 8 : 0;
		bit_three_value = (six_bit_three & (1 << 5)) ? 4 : 0;
		bit_four_value = (six_bit_three & (1 << 4)) ? 2 : 0;
		bit_five_value = (six_bit_three & (1 << 3)) ? 1 : 0;
		sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_three_value = S_BOX_THREE[row_number][sum];

		// Six bit four, S-Box 4
		row_number = 0;
		if ((six_bit_four & (1 << 7)) && (six_bit_four & (1 << 2))) row_number = 3;
		if ((six_bit_four & (1 << 7)) && (six_bit_four & (1 << 2)) == 0) row_number = 2;
		if ((six_bit_four & (1 << 7)) == 0 && (six_bit_four & (1 << 2))) row_number = 1;

		uint8_t s_box_four_value;
		bit_two_value = (six_bit_four & (1 << 6)) ? 8 : 0;
		bit_three_value = (six_bit_four & (1 << 5)) ? 4 : 0;
		bit_four_value = (six_bit_four & (1 << 4)) ? 2 : 0;
		bit_five_value = (six_bit_four & (1 << 3)) ? 1 : 0;
		sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_four_value = S_BOX_FOUR[row_number][sum];

		// Six bit five, S-Box 5
		row_number = 0;
		if ((six_bit_five & (1 << 7)) && (six_bit_five & (1 << 2))) row_number = 3;
		if ((six_bit_five & (1 << 7)) && (six_bit_five & (1 << 2)) == 0) row_number = 2;
		if ((six_bit_five & (1 << 7)) == 0 && (six_bit_five & (1 << 2))) row_number = 1;

		uint8_t s_box_five_value;
		bit_two_value = (six_bit_five & (1 << 6)) ? 8 : 0;
		bit_three_value = (six_bit_five & (1 << 5)) ? 4 : 0;
		bit_four_value = (six_bit_five & (1 << 4)) ? 2 : 0;
		bit_five_value = (six_bit_five & (1 << 3)) ? 1 : 0;
		sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_five_value = S_BOX_FIVE[row_number][sum];

		// Six bit six, S-Box 6
		row_number = 0;
		if ((six_bit_six & (1 << 7)) && (six_bit_six & (1 << 2))) row_number = 3;
		if ((six_bit_six & (1 << 7)) && (six_bit_six & (1 << 2)) == 0) row_number = 2;
		if ((six_bit_six & (1 << 7)) == 0 && (six_bit_six & (1 << 2))) row_number = 1;

		uint8_t s_box_six_value;
		bit_two_value = (six_bit_six & (1 << 6)) ? 8 : 0;
		bit_three_value = (six_bit_six & (1 << 5)) ? 4 : 0;
		bit_four_value = (six_bit_six & (1 << 4)) ? 2 : 0;
		bit_five_value = (six_bit_six & (1 << 3)) ? 1 : 0;
		sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_six_value = S_BOX_SIX[row_number][sum];

		// Six bit seven, S-Box 7
		row_number = 0;
		if ((six_bit_seven & (1 << 7)) && (six_bit_seven & (1 << 2))) row_number = 3;
		if ((six_bit_seven & (1 << 7)) && (six_bit_seven & (1 << 2)) == 0) row_number = 2;
		if ((six_bit_seven & (1 << 7)) == 0 && (six_bit_seven & (1 << 2))) row_number = 1;

		uint8_t s_box_seven_value;
		bit_two_value = (six_bit_seven & (1 << 6)) ? 8 : 0;
		bit_three_value = (six_bit_seven & (1 << 5)) ? 4 : 0;
		bit_four_value = (six_bit_seven & (1 << 4)) ? 2 : 0;
		bit_five_value = (six_bit_seven & (1 << 3)) ? 1 : 0;
		sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_seven_value = S_BOX_SEVEN[row_number][sum];

		// Six bit eight, S-Box 8
		row_number = 0;
		if ((six_bit_eight & (1 << 7)) && (six_bit_eight & (1 << 2))) row_number = 3;
		if ((six_bit_eight & (1 << 7)) && (six_bit_eight & (1 << 2)) == 0) row_number = 2;
		if ((six_bit_eight & (1 << 7)) == 0 && (six_bit_eight & (1 << 2))) row_number = 1;

		uint8_t s_box_eight_value;
		bit_two_value = (six_bit_eight & (1 << 6)) ? 8 : 0;
		bit_three_value = (six_bit_eight & (1 << 5)) ? 4 : 0;
		bit_four_value = (six_bit_eight & (1 << 4)) ? 2 : 0;
		bit_five_value = (six_bit_eight & (1 << 3)) ? 1 : 0;
		sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_eight_value = S_BOX_EIGHT[row_number][sum];

		// Use a straight P box to convert our 32-bit value (8 4-bit S box vlaues) to a new 32-bit value
		// I'm too lazy to convert the S box values into one 32-bit value, so I'm going to treat bit "5" as sbox 2, bit 1, etc.
		uint32_t straight_p_box_result = 0;
		if (s_box_four_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 1));
		if (s_box_two_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 2));
		if (s_box_five_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 3));
		if (s_box_six_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 4));
		if (s_box_eight_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 5));
		if (s_box_three_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 6));
		if (s_box_seven_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 7));
		if (s_box_five_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 8));
		if (s_box_one_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 9));
		if (s_box_four_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 10));
		if (s_box_six_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 11));
		if (s_box_seven_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 12));
		if (s_box_two_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 13));
		if (s_box_five_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 14));
		if (s_box_eight_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 15));
		if (s_box_three_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 16));
		if (s_box_one_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 17));
		if (s_box_two_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 18));
		if (s_box_six_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 19));
		if (s_box_four_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 20));
		if (s_box_eight_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 21));
		if (s_box_seven_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 22));
		if (s_box_one_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 23));
		if (s_box_three_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 24));
		if (s_box_five_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 25));
		if (s_box_four_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 26));
		if (s_box_eight_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 27));
		if (s_box_two_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 28));
		if (s_box_six_value & (1 << (4 - 2))) straight_p_box_result |= (1 << (32 - 29));
		if (s_box_three_value & (1 << (4 - 3))) straight_p_box_result |= (1 << (32 - 30));
		if (s_box_one_value & (1 << (4 - 4))) straight_p_box_result |= (1 << (32 - 31));
		if (s_box_seven_value & (1 << (4 - 1))) straight_p_box_result |= (1 << (32 - 32));


		// XOR the straight_p_box_result with the left half
		right_half = left_half ^ straight_p_box_result;

		left_half = original_right_half;
	}

	// Since we're done, combine the left and right halves to make our output
	*output = (uint64_t) right_half << 32 | left_half;
}