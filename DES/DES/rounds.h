/*
Mike Koch
EECS 4760 - Computer Security
DES
rounds.h: Consult rounds.cpp
*/
#ifndef ROUNDS_H
#define ROUNDS_H
#include <fstream>
#include "mode.h"

void apply_rounds(uint64_t *initial_permutation, uint64_t *output, uint64_t *keys, Mode mode);
#endif