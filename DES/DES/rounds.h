#ifndef ROUNDS_H
#define ROUNDS_H
#include <fstream>

void apply_rounds(uint64_t *initial_permutation, std::fstream &output_file_stream, uint64_t *keys);
#endif