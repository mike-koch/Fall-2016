/*
Mike Koch
EECS 4760 - Computer Security
DES
garbage_producer.cpp: Generates 64 random bits to be used by other functions
*/
#include "garbage_producer.h"
#include <stdlib.h>

// Generates eight bytes of garbage data. Why eight bytes? 
// The most garbage we'll ever need is 7 bytes (for padding plaintext), and only generating 7 bytes seemed strange to me. So I went with 8 bytes.
void generate_eight_bytes_of_garbage(uint64_t *destination) {
	for (int i = 0; i < 64; i++) {
		if (rand() % 2) {
			*destination |= (INT64_C(1) << i);
		}
	}
}