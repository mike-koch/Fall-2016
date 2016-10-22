#include "rounds.h"
#include "mode.h"
#include "permutator.h"

void apply_rounds(uint64_t *initial_permutation, std::fstream &output_file_stream, uint64_t *keys, Mode mode) {
	// Divide the initial permutation into 2 32-bit blocks
	uint32_t left_half = (*initial_permutation & 0xFFFFFFFF00000000) >> 32;
	uint32_t right_half = *initial_permutation & 0x00000000FFFFFFFF;

	int keyIndex = 0;
	int keyIncrementer = 1;

	if (mode == Mode::DECRYPTION) {
		//-- TODO!
	}

	// Round 1
	for (int i = 0; i < 15; i++) {
		uint64_t key = keys[keyIndex];
		uint32_t original_right_half = right_half;

		uint64_t expanded_right_half;
		apply_expansion_permutation(&right_half, &expanded_right_half);
		uint64_t right_and_key = key ^ expanded_right_half;

		uint8_t six_bit_one = (right_and_key & 0xFC00000000000000) >> 56;
		uint8_t six_bit_two = (right_and_key & 0x03F0000000000000) >> 50;
		uint8_t six_bit_three = (right_and_key & 0x000FC00000000000) >> 44;
		uint8_t six_bit_four = (right_and_key & 0x00003F0000000000) >> 38;
		uint8_t six_bit_five = (right_and_key & 0x000000FC00000000) >> 32;
		uint8_t six_bit_six = (right_and_key & 0x00000003F0000000) >> 26;
		uint8_t six_bit_seven = (right_and_key & 0x000000000FC00000) >> 20;
		uint8_t six_bit_eight = (right_and_key & 0x00000000003F0000) >> 14;

		int row_number = -1;
		if ((six_bit_one & (1 << 5)) && (six_bit_one & (1 << 0))) row_number = 3;
		if ((six_bit_one & (1 << 5)) && (six_bit_one & (1 << 0)) == 0) row_number = 2;
		if ((six_bit_one & (1 << 5)) == 0 && (six_bit_one & (1 << 0))) row_number = 1;
		else row_number = 0;

		int s_box_value = -1;
		int s_box_one[4][16] = {
			{ 14, 4, 3, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
			{ 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
			{ 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
			{ 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }
		};
		/*
		S-Box 1

		Row
		No. 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
		0   14 04 13 01 02 15 11 08 03 10 06 12 05 09 00 07
		1   00 15 07 04 14 02 13 01 10 06 12 11 09 05 03 08
		2   04 01 14 08 13 06 02 11 15 12 09 07 03 10 05 00
		3   15 12 08 02 04 09 01 07 05 11 03 14 10 00 06 13
		*/
		int bit_two_value = (six_bit_one & (1 << 4)) ? 8 : 0;
		int bit_three_value = (six_bit_one & (1 << 3)) ? 4 : 0;
		int bit_four_value = (six_bit_one & (1 << 2)) ? 2 : 0;
		int bit_five_value = (six_bit_one & (1 << 1)) ? 1 : 0;
		int sum = bit_two_value + bit_three_value + bit_four_value + bit_five_value;
		s_box_value = s_box_one[row_number][sum];
		/*if ((row_number == 0 && sum == 0) || (row_number == 1 && sum == 4) || (row_number == 2 && sum == 2) || (row_number == 3 && sum == 11)) {
			s_box_value = 14;
		} else if ((row_number == 0 && sum == 1) || (row_number == 1 && sum == 3) || (row_number == 2 && sum == 0) || (row_number == 3 && sum == 4)) {
			s_box_value = 4;
		} else if ((row_number == 0 && sum == 2) || (row_number == 1 && sum == 6) || (row_number == 2 && sum == 4) || (row_number == 3 && sum == 15)) {
			s_box_value = 13;
		} else if ((row_number == 0 && sum == 3) || (row_number == 1 && sum == 7) || (row_number == 2 && sum == 1) || (row_number == 3 && sum == 6)) {
			s_box_value = 1;
		} else if ((row_number == 0 && sum == 4) || (row_number == 1 && sum == 5) || (row_number == 2 && sum == 6) || (row_number == 3 && sum == 3)) {
			s_box_value = 2;
		} else if ((row_number == 0 && sum == 5) || (row_number == 1 && sum == 1) || (row_number == 2 && sum == 8) || (row_number == 3 && sum == 0)) {
			s_box_value = 15;
		} else if ((row_number == 0 && sum == 6) || (row_number == 1 && sum == 11) || (row_number == 2 && sum == 7) || (row_number == 3 && sum == 9)) {
			s_box_value = 11;
		} else if ((row_number == 0 && sum == 7) || (row_number == 1 && sum == 15) || (row_number == 2 && sum == 3) || (row_number == 3 && sum == 2)) {
			s_box_value = 8;
		} else if ((row_number == 0 && sum == 8) || (row_number == 1 && sum == 14) || (row_number == 2 && sum == 12) || (row_number == 3 && sum == 10)) {
			s_box_value = 3;
		} else if ((row_number == 0 && sum == 9) || (row_number == 1 && sum == 8) || (row_number == 2 && sum == 13) || (row_number == 3 && sum == 12)) {
			s_box_value = 10;
		} else if ((row_number == 0 && sum == 10) || (row_number == 1 && sum == 9) || (row_number == 2 && sum == 5) || (row_number == 3 && sum == 14)) {
			s_box_value = 6;
		} else if ((row_number == 0 && sum == 11) || (row_number == 1 && sum == 10) || (row_number == 2 && sum == 9) || (row_number == 3 && sum == 1)) {
			s_box_value = 12;
		} else if ((row_number == 0 && sum == 12) || (row_number == 1 && sum == 13) || (row_number == 2 && sum == 14) || (row_number == 3 && sum == 8)) {
			s_box_value = 5;
		} else if ((row_number == 0 && sum == 13) || (row_number == 1 && sum == 12) || (row_number == 2 && sum == 10) || (row_number == 3 && sum == 5)) {
			s_box_value = 9;
		} else if ((row_number == 0 && sum == 14) || (row_number == 1 && sum == 0) || (row_number == 2 && sum == 15) || (row_number == 3 && sum == 13)) {
			s_box_value = 0;
		} else {
			s_box_value = 7;
		}*/
	}
	

	//keyIndex += keyIncrementer;
	// Round 2
	/*key = keys[keyIndex];
	original_right_half = right_half;

	keyIndex += keyIncrementer;

	// Round 3
	key = keys[keyIndex];
	original_right_half = right_half;

	keyIndex += keyIncrementer;
	
	// Round 4
	key = keys[keyIndex];
	original_right_half = right_half;

	keyIndex += keyIncrementer;

	// Round 5
	key = keys[keyIndex];
	original_right_half = right_half;

	keyIndex += keyIncrementer;

	// Round 6
	key = keys[keyIndex];
	original_right_half = right_half;

	keyIndex += keyIncrementer;

	// Round 7
	key = keys[keyIndex];
	original_right_half = right_half;

	keyIndex += keyIncrementer;

	// Round 8
	key = keys[keyIndex];
	original_right_half = right_half;

	keyIndex += keyIncrementer;

	// Round 9
	key = keys[keyIndex];
	original_right_half = right_half;

	keyIndex += keyIncrementer;

	// Round 10
	key = keys[keyIndex];
	original_right_half = right_half;

	keyIndex += keyIncrementer;

	// Round 11
	key = keys[keyIndex];
	original_right_half = right_half;

	keyIndex += keyIncrementer;

	// Round 12
	key = keys[keyIndex];
	original_right_half = right_half;

	keyIndex += keyIncrementer;

	// Round 13
	key = keys[keyIndex];
	original_right_half = right_half;

	keyIndex += keyIncrementer;

	// Round 14
	key = keys[keyIndex];
	original_right_half = right_half;

	keyIndex += keyIncrementer;

	// Round 15
	key = keys[keyIndex];
	original_right_half = right_half;

	keyIndex += keyIncrementer;

	// Round 16
	key = keys[keyIndex];
	original_right_half = right_half;*/
}