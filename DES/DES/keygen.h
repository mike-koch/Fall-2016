#ifndef KEYGEN_H
#define KEYGEN_H
#include <stdint.h>

// Generates the necessary keys needed and stores them in the key array provided. This also assumes that the provided_key is a valid key.
void generate_keys(char *provided_key, uint64_t *keys);
#endif