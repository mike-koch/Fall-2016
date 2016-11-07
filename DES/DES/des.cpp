/*
DES Project (analysis portion)
Mike Koch

This source file does the following:

1. Calculates the character frequencies of the plaintext Shakespear file
2. Calculates the character frequencies of an encrypted Shakespeare file, using 0x0123456789ABCDEF as the password
3. "Encrypts" Shakespeare.txt by only XORing the document with the generated keys, then generates the character frequencies
4. "Encrypts" Shakespeare.txt by only calculating the permutations and S-Boxes (key is never used). Character frequencies are then generated
*/

#include "keygen.h"
#include "file_processor.h"
#include "permutator.h"
#include "rounds.h"
#include "reverser.h"
#include "garbage_producer.h"
#include "error_handler.h"
#include "exit_code.h"
#include <string.h>
#include <iomanip>
#include <iostream>

// Constants
const int ASCII_ZERO = 48;
const int ASCII_NINE = 57;
const int ASCII_A = 65;
const int ASCII_F = 70;

// Function prototypes
void process_chunk(uint64_t *next_64_bits, uint64_t *keys, uint64_t *output, Mode mode);
void set_ascii_characters_to_key(char most_significant_char, char least_significant_char, int bit_offset, uint64_t *destination);

int main(int argc, char *argv[])
{
	char *input_file_path = "C:\\Users\\Mike\\Desktop\\DES\\Shakespeare.txt";
	char *output_file_path = "C:\\Users\\Mike\\Desktop\\DES\\Shakespeare_an.enc";

	// Keep track of char frequencies
	unsigned int frequencies[256];

	for (int i = 0; i < 256; i++) {
		frequencies[i] = 0;
	}

	// Key parsing
	uint64_t password = 0x0123456789ABCDEF;

	// 2. Generate keys
	uint64_t keys[16];
	generate_keys(password, keys);

	// Open the file for processing
	std::fstream input_stream;
	std::fstream output_stream;
	input_stream.open(input_file_path, std::ios::in | std::ios::binary);

	// Get the length of the file by going to the end ofthe input stream and checking where the stream index is at. Then go back
	// to the beginning so we can actually read the data
	input_stream.seekg(0, input_stream.end);
	int length_of_file = input_stream.tellg();
	input_stream.seekg(0, input_stream.beg);

	output_stream.open(output_file_path, std::ios::out | std::ios::binary | std::ios::trunc);
	if (input_stream.is_open() && output_stream.is_open()) {
		// Encrypt the file size.
		uint64_t file_size_block;
		build_file_size_block(length_of_file, &file_size_block);

		uint64_t output = 0;
		process_chunk(&file_size_block, keys, &output, Mode::ENCRYPTION);
			
		// Reverse the output so the bytes are saved from MSB to LSB
		uint64_t reversed_output;
		reverse(&output, &reversed_output);
			
		output_stream.write((char*)&reversed_output, sizeof(uint64_t));

		// Flag to indicate if we've reached the end of the input file.
		bool keep_going = false;
		int number_of_bytes_read = 0;

		// These two ints are used only for decryption. We only strip half of the first chunk during decryption, so we need to know when the first run is. We also need to know the file size.
		int first_iteration = true;
		int decrypted_file_size;
		do {
			// 3. Get next 64 bits (8 bytes)
			uint64_t next_64_bits = 0;
			int previous_number_of_bytes_read = number_of_bytes_read;
			keep_going = get_next_64_bits(input_stream, &next_64_bits, &number_of_bytes_read, length_of_file);

			// Uncomment to calculate letter frequencies for the plaintext
			/*char *next_64_bits_as_string = (char *)&next_64_bits;
			for (int i = 0; i < 8; i++) {
			frequencies[next_64_bits_as_string[i]]++;
			}*/

			// If we fall into this block, this means our last read was (1) our final possible read, and (2) we read less than 8 bytes. We need to pad the rest of the bytes with garbage.
			// This will ONLY ever happen when encrypting. If we're decrypting and this if statement is true, very bad things have happened.
			if (!keep_going && number_of_bytes_read - previous_number_of_bytes_read != 8) {
				uint64_t garbage;
				generate_eight_bytes_of_garbage(&garbage);
				int number_of_bytes_filled = number_of_bytes_read - previous_number_of_bytes_read;
				
				// Now that we know how many bytes need garbage, push the garbage data into those bytes by shifting them to the left.
				//    *We haven't reversed yet, so the garbage will be the most significant byte(s)*
				next_64_bits |= garbage << (8 * number_of_bytes_filled);
			}

			// The bytes read in are stored in reverse order. We need to flip them around first.
			uint64_t reversed_next_64_bits;
			reverse(&next_64_bits, &reversed_next_64_bits);
			
			uint64_t output = 0;
			process_chunk(&reversed_next_64_bits, keys, &output, Mode::ENCRYPTION);

			// Output to file
			uint64_t reversed_output;
			reverse(&output, &reversed_output);

			// Uncomment to calculate letter frequencies for the encrypted output
			char *next_64_bits_as_string = (char *)&output;
			for (int i = 0; i < 8; i++) {
				frequencies[next_64_bits_as_string[i]]++;
			}

			output_stream.write((char*)&reversed_output, sizeof(uint64_t));
		} while (keep_going);
	} else {
		output_error("ERROR: Unable to open file. Make sure that both the input file and output file are accessible!", ExitCode::CANNOT_OPEN_FILE);
	}

	// Output the frequency to CSV
	std::fstream csv_output_stream;
	char *csv_dump_path = "C:\\Users\\Mike\\Desktop\\DES\\Shakespeare.csv";
	csv_output_stream.open(csv_dump_path, std::fstream::out);
	for (int i = 0; i < 256; i++) {
		csv_output_stream << frequencies[i] << std::endl;
		std::cout << frequencies[i] << std::endl;
	}

	// Halt here
	std::cout << "DONE";
	std::cin.get();
}

void process_chunk(uint64_t *next_64_bits, uint64_t *keys, uint64_t *output, Mode mode) {
	
	uint64_t initial_permutation;
	apply_initial_permutation(next_64_bits, &initial_permutation);

	// Rounds 1 - 16
	uint64_t round_output;
	apply_rounds(&initial_permutation, &round_output, keys, mode);

	// Final Permutation
	apply_final_permutation(&round_output, output);
}

void set_ascii_characters_to_key(char most_significant_char, char least_significant_char, int bit_offset, uint64_t *destination) {
	int left_hand_side = most_significant_char - '0';
	int right_hand_side = least_significant_char - '0';

	// Make sure the user entered a valid hex digit
	if ((left_hand_side < (ASCII_ZERO - 48) || (left_hand_side > (ASCII_NINE - 48) && left_hand_side < (ASCII_A - 48)) || left_hand_side > (ASCII_F - 48)) ||
		(right_hand_side < (ASCII_ZERO - 48) || (right_hand_side > (ASCII_NINE - 48) && right_hand_side < (ASCII_A - 48)) || right_hand_side >(ASCII_F - 48))) {
		output_error("One or more characters are not valid hex characters", ExitCode::INVALID_PASSWORD);
	}

	*destination |= (uint64_t)((left_hand_side * 16) + right_hand_side) << bit_offset;
}