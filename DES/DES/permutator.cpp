#include "permutator.h"
#include <stdio.h>

void apply_initial_permutation(uint64_t *source, uint64_t *destination) {
	/*
	Applies the following permutation based on the following chart:

	                58 50 42 34 26 18 10 02
	                60 52 44 36 28 20 12 04
	                62 54 46 38 30 22 14 06
	                64 56 48 40 32 24 16 08
	                57 49 41 33 25 17 09 01
	                59 51 43 35 27 19 11 03
	                61 53 45 37 29 21 13 05
	                63 55 47 39 31 23 15 07
	*/
	*destination = 0;
	if (*source & (1 << (64 - 58))) *destination |= (1 << (64 - 1));
	if (*source & (1 << (64 - 50))) *destination |= (1 << (64 - 2));
	if (*source & (1 << (64 - 42))) *destination |= (1 << (64 - 3));
	if (*source & (1 << (64 - 34))) *destination |= (1 << (64 - 4));
	if (*source & (1 << (64 - 26))) *destination |= (1 << (64 - 5));
	if (*source & (1 << (64 - 18))) *destination |= (1 << (64 - 6));
	if (*source & (1 << (64 - 10))) *destination |= (1 << (64 - 7));
	if (*source & (1 << (64 - 2))) *destination |= (1 << (64 - 8));
	if (*source & (1 << (64 - 60))) *destination |= (1 << (64 - 9));
	if (*source & (1 << (64 - 52))) *destination |= (1 << (64 - 10));
	if (*source & (1 << (64 - 44))) *destination |= (1 << (64 - 11));
	if (*source & (1 << (64 - 36))) *destination |= (1 << (64 - 12));
	if (*source & (1 << (64 - 28))) *destination |= (1 << (64 - 13));
	if (*source & (1 << (64 - 20))) *destination |= (1 << (64 - 14));
	if (*source & (1 << (64 - 12))) *destination |= (1 << (64 - 15));
	if (*source & (1 << (64 - 4))) *destination |= (1 << (64 - 16));
	if (*source & (1 << (64 - 62))) *destination |= (1 << (64 - 17));
	if (*source & (1 << (64 - 54))) *destination |= (1 << (64 - 18));
	if (*source & (1 << (64 - 46))) *destination |= (1 << (64 - 19));
	if (*source & (1 << (64 - 38))) *destination |= (1 << (64 - 20));
	if (*source & (1 << (64 - 30))) *destination |= (1 << (64 - 21));
	if (*source & (1 << (64 - 22))) *destination |= (1 << (64 - 22));
	if (*source & (1 << (64 - 14))) *destination |= (1 << (64 - 23));
	if (*source & (1 << (64 - 6))) *destination |= (1 << (64 - 24));
	if (*source & (1 << (64 - 64))) *destination |= (1 << (64 - 25));
	if (*source & (1 << (64 - 56))) *destination |= (1 << (64 - 26));
	if (*source & (1 << (64 - 48))) *destination |= (1 << (64 - 27));
	if (*source & (1 << (64 - 40))) *destination |= (1 << (64 - 28));
	if (*source & (1 << (64 - 32))) *destination |= (1 << (64 - 29));
	if (*source & (1 << (64 - 24))) *destination |= (1 << (64 - 30));
	if (*source & (1 << (64 - 16))) *destination |= (1 << (64 - 31));
	if (*source & (1 << (64 - 8))) *destination |= (1 << (64 - 32));
	if (*source & (1 << (64 - 57))) *destination |= (1 << (64 - 33));
	if (*source & (1 << (64 - 49))) *destination |= (1 << (64 - 34));
	if (*source & (1 << (64 - 41))) *destination |= (1 << (64 - 35));
	if (*source & (1 << (64 - 33))) *destination |= (1 << (64 - 36));
	if (*source & (1 << (64 - 25))) *destination |= (1 << (64 - 37));
	if (*source & (1 << (64 - 17))) *destination |= (1 << (64 - 38));
	if (*source & (1 << (64 - 9))) *destination |= (1 << (64 - 39));
	if (*source & (1 << (64 - 1))) *destination |= (1 << (64 - 40));
	if (*source & (1 << (64 - 59))) *destination |= (1 << (64 - 41));
	if (*source & (1 << (64 - 51))) *destination |= (1 << (64 - 42));
	if (*source & (1 << (64 - 43))) *destination |= (1 << (64 - 43));
	if (*source & (1 << (64 - 35))) *destination |= (1 << (64 - 44));
	if (*source & (1 << (64 - 27))) *destination |= (1 << (64 - 45));
	if (*source & (1 << (64 - 19))) *destination |= (1 << (64 - 46));
	if (*source & (1 << (64 - 11))) *destination |= (1 << (64 - 47));
	if (*source & (1 << (64 - 3))) *destination |= (1 << (64 - 48));
	if (*source & (1 << (64 - 61))) *destination |= (1 << (64 - 49));
	if (*source & (1 << (64 - 53))) *destination |= (1 << (64 - 50));
	if (*source & (1 << (64 - 45))) *destination |= (1 << (64 - 51));
	if (*source & (1 << (64 - 37))) *destination |= (1 << (64 - 52));
	if (*source & (1 << (64 - 29))) *destination |= (1 << (64 - 53));
	if (*source & (1 << (64 - 21))) *destination |= (1 << (64 - 54));
	if (*source & (1 << (64 - 13))) *destination |= (1 << (64 - 55));
	if (*source & (1 << (64 - 5))) *destination |= (1 << (64 - 56));
	if (*source & (1 << (64 - 63))) *destination |= (1 << (64 - 57));
	if (*source & (1 << (64 - 55))) *destination |= (1 << (64 - 58));
	if (*source & (1 << (64 - 47))) *destination |= (1 << (64 - 59));
	if (*source & (1 << (64 - 39))) *destination |= (1 << (64 - 60));
	if (*source & (1 << (64 - 31))) *destination |= (1 << (64 - 61));
	if (*source & (1 << (64 - 23))) *destination |= (1 << (64 - 62));
	if (*source & (1 << (64 - 15))) *destination |= (1 << (64 - 63));
	if (*source & (1 << (64 - 7))) *destination |= (1 << (64 - 64));

}

void apply_expansion_permutation(uint32_t *source, uint64_t *destination) {
	/*
	Applies the following permutation based on the following chart:

	               32 01 02 03 04 05
                   04 05 06 07 08 09
                   08 09 10 11 12 13
                   12 13 14 15 16 17
				   16 17 18 19 20 21
				   20 21 22 23 24 25
				   24 25 26 27 28 29
				   28 29 30 31 32 01
	*/
	*destination = 0;
	if (*source & (1 << (32 - 32))) *destination |= (1 << (64 - 1));
	if (*source & (1 << (32 - 1))) *destination |= (1 << (64 - 2));
	if (*source & (1 << (32 - 2))) *destination |= (1 << (64 - 3));
	if (*source & (1 << (32 - 3))) *destination |= (1 << (64 - 4));
	if (*source & (1 << (32 - 4))) *destination |= (1 << (64 - 5));
	if (*source & (1 << (32 - 5))) *destination |= (1 << (64 - 6));
	if (*source & (1 << (32 - 4))) *destination |= (1 << (64 - 7));
	if (*source & (1 << (32 - 5))) *destination |= (1 << (64 - 8));
	if (*source & (1 << (32 - 6))) *destination |= (1 << (64 - 9));
	if (*source & (1 << (32 - 7))) *destination |= (1 << (64 - 10));
	if (*source & (1 << (32 - 8))) *destination |= (1 << (64 - 11));
	if (*source & (1 << (32 - 9))) *destination |= (1 << (64 - 12));
	if (*source & (1 << (32 - 8))) *destination |= (1 << (64 - 13));
	if (*source & (1 << (32 - 9))) *destination |= (1 << (64 - 14));
	if (*source & (1 << (32 - 10))) *destination |= (1 << (64 - 15));
	if (*source & (1 << (32 - 11))) *destination |= (1 << (64 - 16));
	if (*source & (1 << (32 - 12))) *destination |= (1 << (64 - 17));
	if (*source & (1 << (32 - 13))) *destination |= (1 << (64 - 18));
	if (*source & (1 << (32 - 12))) *destination |= (1 << (64 - 19));
	if (*source & (1 << (32 - 13))) *destination |= (1 << (64 - 20));
	if (*source & (1 << (32 - 14))) *destination |= (1 << (64 - 21));
	if (*source & (1 << (32 - 15))) *destination |= (1 << (64 - 22));
	if (*source & (1 << (32 - 16))) *destination |= (1 << (64 - 23));
	if (*source & (1 << (32 - 17))) *destination |= (1 << (64 - 24));
	if (*source & (1 << (32 - 16))) *destination |= (1 << (64 - 25));
	if (*source & (1 << (32 - 17))) *destination |= (1 << (64 - 26));
	if (*source & (1 << (32 - 18))) *destination |= (1 << (64 - 27));
	if (*source & (1 << (32 - 19))) *destination |= (1 << (64 - 28));
	if (*source & (1 << (32 - 20))) *destination |= (1 << (64 - 29));
	if (*source & (1 << (32 - 21))) *destination |= (1 << (64 - 30));
	if (*source & (1 << (32 - 20))) *destination |= (1 << (64 - 31));
	if (*source & (1 << (32 - 21))) *destination |= (1 << (64 - 32));
	if (*source & (1 << (32 - 22))) *destination |= (1 << (64 - 33));
	if (*source & (1 << (32 - 23))) *destination |= (1 << (64 - 34));
	if (*source & (1 << (32 - 24))) *destination |= (1 << (64 - 35));
	if (*source & (1 << (32 - 25))) *destination |= (1 << (64 - 36));
	if (*source & (1 << (32 - 24))) *destination |= (1 << (64 - 37));
	if (*source & (1 << (32 - 25))) *destination |= (1 << (64 - 38));
	if (*source & (1 << (32 - 26))) *destination |= (1 << (64 - 39));
	if (*source & (1 << (32 - 27))) *destination |= (1 << (64 - 40));
	if (*source & (1 << (32 - 28))) *destination |= (1 << (64 - 41));
	if (*source & (1 << (32 - 29))) *destination |= (1 << (64 - 42));
	if (*source & (1 << (32 - 28))) *destination |= (1 << (64 - 43));
	if (*source & (1 << (32 - 29))) *destination |= (1 << (64 - 44));
	if (*source & (1 << (32 - 30))) *destination |= (1 << (64 - 45));
	if (*source & (1 << (32 - 31))) *destination |= (1 << (64 - 46));
	if (*source & (1 << (32 - 32))) *destination |= (1 << (64 - 47));
	if (*source & (1 << (32 - 1))) *destination |= (1 << (64 - 48));
}

void apply_final_permutation(uint64_t *source, uint64_t *destination) {
	/*
	Applies the following permutation based on the following chart:
						40 08 48 16 56 24 64 32
						39 07 47 15 55 23 63 31
						38 06 46 14 54 22 62 30
						37 05 45 13 53 21 61 29
						36 04 44 12 52 20 60 28
						35 03 43 11 51 19 59 27
						34 02 42 10 50 18 58 26
						33 01 41 09 49 17 57 25
	*/
	*destination = 0;
	if (*source & (1 << (64 - 40))) *destination |= (1 << (64 - 1));
	if (*source & (1 << (64 - 8))) *destination |= (1 << (64 - 2));
	if (*source & (1 << (64 - 48))) *destination |= (1 << (64 - 3));
	if (*source & (1 << (64 - 16))) *destination |= (1 << (64 - 4));
	if (*source & (1 << (64 - 56))) *destination |= (1 << (64 - 5));
	if (*source & (1 << (64 - 24))) *destination |= (1 << (64 - 6));
	if (*source & (1 << (64 - 64))) *destination |= (1 << (64 - 7));
	if (*source & (1 << (64 - 32))) *destination |= (1 << (64 - 8));
	if (*source & (1 << (64 - 39))) *destination |= (1 << (64 - 9));
	if (*source & (1 << (64 - 7))) *destination |= (1 << (64 - 10));
	if (*source & (1 << (64 - 47))) *destination |= (1 << (64 - 11));
	if (*source & (1 << (64 - 15))) *destination |= (1 << (64 - 12));
	if (*source & (1 << (64 - 55))) *destination |= (1 << (64 - 13));
	if (*source & (1 << (64 - 23))) *destination |= (1 << (64 - 14));
	if (*source & (1 << (64 - 63))) *destination |= (1 << (64 - 15));
	if (*source & (1 << (64 - 31))) *destination |= (1 << (64 - 16));
	if (*source & (1 << (64 - 38))) *destination |= (1 << (64 - 17));
	if (*source & (1 << (64 - 6))) *destination |= (1 << (64 - 18));
	if (*source & (1 << (64 - 46))) *destination |= (1 << (64 - 19));
	if (*source & (1 << (64 - 14))) *destination |= (1 << (64 - 20));
	if (*source & (1 << (64 - 54))) *destination |= (1 << (64 - 21));
	if (*source & (1 << (64 - 22))) *destination |= (1 << (64 - 22));
	if (*source & (1 << (64 - 62))) *destination |= (1 << (64 - 23));
	if (*source & (1 << (64 - 30))) *destination |= (1 << (64 - 24));
	if (*source & (1 << (64 - 37))) *destination |= (1 << (64 - 25));
	if (*source & (1 << (64 - 5))) *destination |= (1 << (64 - 26));
	if (*source & (1 << (64 - 45))) *destination |= (1 << (64 - 27));
	if (*source & (1 << (64 - 13))) *destination |= (1 << (64 - 28));
	if (*source & (1 << (64 - 53))) *destination |= (1 << (64 - 29));
	if (*source & (1 << (64 - 21))) *destination |= (1 << (64 - 30));
	if (*source & (1 << (64 - 61))) *destination |= (1 << (64 - 31));
	if (*source & (1 << (64 - 29))) *destination |= (1 << (64 - 32));
	if (*source & (1 << (64 - 36))) *destination |= (1 << (64 - 33));
	if (*source & (1 << (64 - 4))) *destination |= (1 << (64 - 34));
	if (*source & (1 << (64 - 44))) *destination |= (1 << (64 - 35));
	if (*source & (1 << (64 - 12))) *destination |= (1 << (64 - 36));
	if (*source & (1 << (64 - 52))) *destination |= (1 << (64 - 37));
	if (*source & (1 << (64 - 20))) *destination |= (1 << (64 - 38));
	if (*source & (1 << (64 - 60))) *destination |= (1 << (64 - 39));
	if (*source & (1 << (64 - 28))) *destination |= (1 << (64 - 40));
	if (*source & (1 << (64 - 35))) *destination |= (1 << (64 - 41));
	if (*source & (1 << (64 - 3))) *destination |= (1 << (64 - 42));
	if (*source & (1 << (64 - 43))) *destination |= (1 << (64 - 43));
	if (*source & (1 << (64 - 11))) *destination |= (1 << (64 - 44));
	if (*source & (1 << (64 - 51))) *destination |= (1 << (64 - 45));
	if (*source & (1 << (64 - 19))) *destination |= (1 << (64 - 46));
	if (*source & (1 << (64 - 59))) *destination |= (1 << (64 - 47));
	if (*source & (1 << (64 - 27))) *destination |= (1 << (64 - 48));
	if (*source & (1 << (64 - 34))) *destination |= (1 << (64 - 49));
	if (*source & (1 << (64 - 2))) *destination |= (1 << (64 - 50));
	if (*source & (1 << (64 - 42))) *destination |= (1 << (64 - 51));
	if (*source & (1 << (64 - 10))) *destination |= (1 << (64 - 52));
	if (*source & (1 << (64 - 50))) *destination |= (1 << (64 - 53));
	if (*source & (1 << (64 - 18))) *destination |= (1 << (64 - 54));
	if (*source & (1 << (64 - 58))) *destination |= (1 << (64 - 55));
	if (*source & (1 << (64 - 26))) *destination |= (1 << (64 - 56));
	if (*source & (1 << (64 - 33))) *destination |= (1 << (64 - 57));
	if (*source & (1 << (64 - 1))) *destination |= (1 << (64 - 58));
	if (*source & (1 << (64 - 41))) *destination |= (1 << (64 - 59));
	if (*source & (1 << (64 - 9))) *destination |= (1 << (64 - 60));
	if (*source & (1 << (64 - 49))) *destination |= (1 << (64 - 61));
	if (*source & (1 << (64 - 17))) *destination |= (1 << (64 - 62));
	if (*source & (1 << (64 - 57))) *destination |= (1 << (64 - 63));
	if (*source & (1 << (64 - 25))) *destination |= (1 << (64 - 64));
}