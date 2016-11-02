#include "error_handler.h"
#include <stdio.h>
#include <iostream>

// Handle outputting an error message, as well as holding the application from exiting until input from the keyboard is received.
// Then the application exits with the provided exit_code.
void output_error(char *text, int exit_code) {
	printf("ERROR: %s", text);
	printf("\n\nPress ENTER to exit.");

	std::cin.get();

	exit(exit_code);
}