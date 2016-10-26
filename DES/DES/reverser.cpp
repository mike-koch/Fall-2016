#include "reverser.h"

void reverse(uint64_t *source, uint64_t *destination) {
	*destination = 0;
	
	// Everything is going to be reversed at the *byte* level, not the bit level
	// 01-08 -> 57-64     09-16 -> 49-56     17-24 -> 41-48
	// 25-32 -> 33-40     33-40 -> 25-32     41-48 -> 17-24
	// 49-56 -> 09-16     57-64 -> 01-08
	if (*source & (INT64_C(1) << 0)) *destination |= (INT64_C(1) << 56);
	if (*source & (INT64_C(1) << 1)) *destination |= (INT64_C(1) << 57);
	if (*source & (INT64_C(1) << 2)) *destination |= (INT64_C(1) << 58);
	if (*source & (INT64_C(1) << 3)) *destination |= (INT64_C(1) << 59);
	if (*source & (INT64_C(1) << 4)) *destination |= (INT64_C(1) << 60);
	if (*source & (INT64_C(1) << 5)) *destination |= (INT64_C(1) << 61);
	if (*source & (INT64_C(1) << 6)) *destination |= (INT64_C(1) << 62);
	if (*source & (INT64_C(1) << 7)) *destination |= (INT64_C(1) << 63);
	if (*source & (INT64_C(1) << 8)) *destination |= (INT64_C(1) << 48);
	if (*source & (INT64_C(1) << 9)) *destination |= (INT64_C(1) << 49);
	if (*source & (INT64_C(1) << 10)) *destination |= (INT64_C(1) << 50);
	if (*source & (INT64_C(1) << 11)) *destination |= (INT64_C(1) << 51);
	if (*source & (INT64_C(1) << 12)) *destination |= (INT64_C(1) << 52);
	if (*source & (INT64_C(1) << 13)) *destination |= (INT64_C(1) << 53);
	if (*source & (INT64_C(1) << 14)) *destination |= (INT64_C(1) << 54);
	if (*source & (INT64_C(1) << 15)) *destination |= (INT64_C(1) << 55);
	if (*source & (INT64_C(1) << 16)) *destination |= (INT64_C(1) << 40);
	if (*source & (INT64_C(1) << 17)) *destination |= (INT64_C(1) << 41);
	if (*source & (INT64_C(1) << 18)) *destination |= (INT64_C(1) << 42);
	if (*source & (INT64_C(1) << 19)) *destination |= (INT64_C(1) << 43);
	if (*source & (INT64_C(1) << 20)) *destination |= (INT64_C(1) << 44);
	if (*source & (INT64_C(1) << 21)) *destination |= (INT64_C(1) << 45);
	if (*source & (INT64_C(1) << 22)) *destination |= (INT64_C(1) << 46);
	if (*source & (INT64_C(1) << 23)) *destination |= (INT64_C(1) << 47);
	if (*source & (INT64_C(1) << 24)) *destination |= (INT64_C(1) << 32);
	if (*source & (INT64_C(1) << 25)) *destination |= (INT64_C(1) << 33);
	if (*source & (INT64_C(1) << 26)) *destination |= (INT64_C(1) << 34);
	if (*source & (INT64_C(1) << 27)) *destination |= (INT64_C(1) << 35);
	if (*source & (INT64_C(1) << 28)) *destination |= (INT64_C(1) << 36);
	if (*source & (INT64_C(1) << 29)) *destination |= (INT64_C(1) << 37);
	if (*source & (INT64_C(1) << 30)) *destination |= (INT64_C(1) << 38);
	if (*source & (INT64_C(1) << 31)) *destination |= (INT64_C(1) << 39);
	if (*source & (INT64_C(1) << 32)) *destination |= (INT64_C(1) << 24);
	if (*source & (INT64_C(1) << 33)) *destination |= (INT64_C(1) << 25);
	if (*source & (INT64_C(1) << 34)) *destination |= (INT64_C(1) << 26);
	if (*source & (INT64_C(1) << 35)) *destination |= (INT64_C(1) << 27);
	if (*source & (INT64_C(1) << 36)) *destination |= (INT64_C(1) << 28);
	if (*source & (INT64_C(1) << 37)) *destination |= (INT64_C(1) << 29);
	if (*source & (INT64_C(1) << 38)) *destination |= (INT64_C(1) << 30);
	if (*source & (INT64_C(1) << 39)) *destination |= (INT64_C(1) << 31);
	if (*source & (INT64_C(1) << 40)) *destination |= (INT64_C(1) << 16);
	if (*source & (INT64_C(1) << 41)) *destination |= (INT64_C(1) << 17);
	if (*source & (INT64_C(1) << 42)) *destination |= (INT64_C(1) << 18);
	if (*source & (INT64_C(1) << 43)) *destination |= (INT64_C(1) << 19);
	if (*source & (INT64_C(1) << 44)) *destination |= (INT64_C(1) << 20);
	if (*source & (INT64_C(1) << 45)) *destination |= (INT64_C(1) << 21);
	if (*source & (INT64_C(1) << 46)) *destination |= (INT64_C(1) << 22);
	if (*source & (INT64_C(1) << 47)) *destination |= (INT64_C(1) << 23);
	if (*source & (INT64_C(1) << 48)) *destination |= (INT64_C(1) << 8);
	if (*source & (INT64_C(1) << 49)) *destination |= (INT64_C(1) << 9);
	if (*source & (INT64_C(1) << 50)) *destination |= (INT64_C(1) << 10);
	if (*source & (INT64_C(1) << 51)) *destination |= (INT64_C(1) << 11);
	if (*source & (INT64_C(1) << 52)) *destination |= (INT64_C(1) << 12);
	if (*source & (INT64_C(1) << 53)) *destination |= (INT64_C(1) << 13);
	if (*source & (INT64_C(1) << 54)) *destination |= (INT64_C(1) << 14);
	if (*source & (INT64_C(1) << 55)) *destination |= (INT64_C(1) << 15);
	if (*source & (INT64_C(1) << 56)) *destination |= (INT64_C(1) << 0);
	if (*source & (INT64_C(1) << 57)) *destination |= (INT64_C(1) << 1);
	if (*source & (INT64_C(1) << 58)) *destination |= (INT64_C(1) << 2);
	if (*source & (INT64_C(1) << 59)) *destination |= (INT64_C(1) << 3);
	if (*source & (INT64_C(1) << 60)) *destination |= (INT64_C(1) << 4);
	if (*source & (INT64_C(1) << 61)) *destination |= (INT64_C(1) << 5);
	if (*source & (INT64_C(1) << 62)) *destination |= (INT64_C(1) << 6);
	if (*source & (INT64_C(1) << 63)) *destination |= (INT64_C(1) << 7);
}