#include "keygen.h"
#include "file_processor.h"
#include "permutator.h"
#include "rounds.h"

int main(int argc, char *argv)
{
	// 1. Process args

	// 2. Generate keys
	uint64_t keys[16];

	generate_keys(0x133457799BBCDFF1, keys);

	// Open the file for processing
	char *input_file_path = "C:\\Shakespeare.txt";
	char *output_file_path = "C:\\Users\\Mike\\Desktop\\Shakespear.enc";
	std::fstream input_stream;
	std::fstream output_stream;
	input_stream.open(input_file_path, std::ios::in | std::ios::binary);
	output_stream.open(output_file_path, std::ios::out | std::ios::binary | std::ios::trunc);
	//if (input_stream.is_open() && output_stream.is_open()) {
		bool end_of_file_found = false;
		while (!end_of_file_found) {
			end_of_file_found = true;
			// 3. Get next 64 bits (8 bytes)
			uint64_t next_64_bits = 0x123456789ABCDEF;
			//end_of_file_found = get_next_64_bits(input_stream, &next_64_bits);



			// 3a. Initial permutation
			uint64_t initial_permutation;
			apply_initial_permutation(&next_64_bits, &initial_permutation);

			// 3b - 3q. Rounds 1 - 16
			uint64_t round_output;
			apply_rounds(&initial_permutation, &round_output, keys, Mode::ENCRYPTION);
			
			// 3r. Final Permutation
			uint64_t final_permutation;
			apply_final_permutation(&round_output, &final_permutation);

			// 4. Output
			output_stream.write((char*)&final_permutation, sizeof(uint64_t));
		}
	//}
}