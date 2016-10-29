#include "error_handler.h"
#include <stdio.h>
#include <iostream>

void output_error(char *text, int exit_code) {
	printf("ERROR: %s", text);
	printf("\n\nPress ENTER to exit.");

	std::cin.get();

	exit(exit_code);
}