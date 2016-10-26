#include "file_processor.h"

bool get_next_64_bits(std::fstream &file_stream, uint64_t *destination, int *bytes_read, int file_size) {
	int number_of_bytes_to_read = 8;
	if (*bytes_read + number_of_bytes_to_read > file_size) {
		number_of_bytes_to_read = file_size - *bytes_read;
	}

	file_stream.read((char *)destination, number_of_bytes_to_read);
	*bytes_read += number_of_bytes_to_read;

	return *bytes_read != file_size;
}

void build_file_size_block(int file_size, uint64_t *block) {
	*block = 0;

	// The first 32 bits (left-hand side) are garbage
	for (int i = 0; i < 32; i++) {
		if (rand() % 2) {
			*block |= (INT64_C(1) << (32 + i));
		}
	}

	// The next 32 bits are the file size
	*block |= file_size;
}