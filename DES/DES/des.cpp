#include "keygen.h"
#include "file_processor.h"
#include "permutator.h"
#include "rounds.h"
#include "reverser.h"

// Function prototypes
void process_chunk(uint64_t *next_64_bits, uint64_t *keys, uint64_t *output, Mode mode);

int main(int argc, char *argv)
{
	// 1. Process args
	Mode mode = Mode::DECRYPTION;

	// 2. Generate keys
	uint64_t keys[16];
	generate_keys(0x133457799BBCDFF1, keys);

	// Open the file for processing
	char *input_file_path = "C:\\Users\\Mike\\Desktop\\DES\\encrypted.enc";
	char *output_file_path = "C:\\Users\\Mike\\Desktop\\DES\\decrypted.dec";
	std::fstream input_stream;
	std::fstream output_stream;
	input_stream.open(input_file_path, std::ios::in | std::ios::binary);

	input_stream.seekg(0, input_stream.end);
	int length_of_file = input_stream.tellg();
	input_stream.seekg(0, input_stream.beg);

	output_stream.open(output_file_path, std::ios::out | std::ios::binary | std::ios::trunc);
	if (input_stream.is_open() && output_stream.is_open()) {
		// If we're encrypting, encrypt the file size.
		if (mode == Mode::ENCRYPTION) {
			uint64_t file_size_block;
			build_file_size_block(length_of_file, &file_size_block);

			uint64_t output = 0;
			process_chunk(&file_size_block, keys, &output, mode);
			
			uint64_t reversed_output;
			reverse(&output, &reversed_output);
			
			output_stream.write((char*)&reversed_output, sizeof(uint64_t));
		}

		// Flag to indicate if we've reached the end of the input file.
		bool keep_going = false;
		int number_of_bytes_read = 0;

		// These two ints are used only for decryption. We only strip half of the first chunk during decryption, so we need to know when the first run is. We also need to know the file size.
		int first_iteration = true;
		int decrypted_file_size;
		do {
			// 3. Get next 64 bits (8 bytes)
			uint64_t next_64_bits;
			keep_going = get_next_64_bits(input_stream, &next_64_bits, &number_of_bytes_read, length_of_file);

			// The bytes read in are stored in reverse order. We need to flip them around first.
			uint64_t reversed_next_64_bits;
			reverse(&next_64_bits, &reversed_next_64_bits);
			
			uint64_t output = 0;
			process_chunk(&reversed_next_64_bits, keys, &output, mode);

			if (first_iteration && mode == Mode::DECRYPTION) {
				// The first chunk tells us how long the file is. We'll store this in decrypted_file_size so we know if we need to throw away any garbage bits.
				// ANDing the output with the below hex value to only retrieve the least-significant word; our file length
				decrypted_file_size = output & 0x00000000FFFFFFFF;

				first_iteration = false;
			} else {
				// Output to file
				uint64_t reversed_output;
				reverse(&output, &reversed_output);
				output_stream.write((char*)&reversed_output, sizeof(uint64_t));
			}
		} while (keep_going);
	}
}

void process_chunk(uint64_t *next_64_bits, uint64_t *keys, uint64_t *output, Mode mode) {
	// 3a. Initial permutation
	uint64_t initial_permutation;
	apply_initial_permutation(next_64_bits, &initial_permutation);

	// 3b - 3q. Rounds 1 - 16
	uint64_t round_output;
	apply_rounds(&initial_permutation, &round_output, keys, mode);

	// 3r. Final Permutation
	apply_final_permutation(&round_output, output);
}