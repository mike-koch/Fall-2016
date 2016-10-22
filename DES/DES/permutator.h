#ifndef PERMUTATOR_H
#define PERMUTATOR_H
#include <stdint.h>

void apply_initial_permutation(uint64_t *source, uint64_t *destination);

void apply_expansion_permutation(uint32_t *source, uint64_t *destination);

void apply_final_permutation(uint64_t *source, uint64_t *destination);
#endif