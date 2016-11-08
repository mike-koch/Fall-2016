/*
Mike Koch
EECS 4760 - Computer Security
DES
garbage_producer.h: Consult garbage_producer.cpp
*/
#ifndef GARBAGE_PRODUCER_H
#define GARBAGE_PRODUCER_H
#include <stdint.h>

void generate_eight_bytes_of_garbage(uint64_t *destination);
#endif