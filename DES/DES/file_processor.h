#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H
#include <fstream>
bool get_next_64_bits(std::fstream &file_stream, uint64_t *destination, int *bytes_read, int file_size);
void build_file_size_block(int file_size, uint64_t *block);
#endif