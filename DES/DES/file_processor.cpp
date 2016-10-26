#include "file_processor.h"
#include "garbage_producer.h"

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
	uint64_t garbage;
	generate_eight_bytes_of_garbage(&garbage);

	// Clear the least significant word so we can put the file size there
	*block |= garbage << 32;

	// The next 32 bits are the file size
	*block |= file_size;
}