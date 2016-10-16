#include "keygen.h"

int main(int argc, char *argv)
{
	uint64_t keys[16];

	generate_keys("PA$$W0RD", keys);

	char c = 'a';

	// 1. Process args

	// 2. Generate keys

	// 3. Get next 64 bits (8 bytes)

	// 3a. Initial permutation

	// 3b - 3q. Rounds 1 - 16

	// 3r. Final Permutation

	// 4. Output
}