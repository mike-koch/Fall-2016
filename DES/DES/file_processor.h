#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H
#include <fstream>
bool get_next_64_bits(std::fstream &file_stream, uint64_t *destination);
#endif