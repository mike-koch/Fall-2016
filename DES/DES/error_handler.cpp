/*
Mike Koch
EECS 4760 - Computer Security
DES
error_handler.cpp: Handles outputting errors to the console (displaying the provided text) and exiting with the provided exit code
*/
#include "error_handler.h"
#include <stdio.h>
#include <iostream>

// Handle outputting an error message, as well as holding the application from exiting until input from the keyboard is received.
// Then the application exits with the provided exit_code.
void output_error(char *text, int exit_code) {
	printf("ERROR: %s", text);
	printf("\nUsage: ./des [-[d|D]|-[e|E]] [password] [ECB|ecb] [input file path] [output file path], where -d or -D is decryption and -e or -E is encryption");
	printf("\n\nPress ENTER to exit.");

	std::cin.get();

	exit(exit_code);
}