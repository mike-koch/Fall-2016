/*
Mike Koch
EECS 4760 - Computer Security
DES
exit_code.h: An enum indicating the type of error that occurred, along with its exit code.
*/
#ifndef EXIT_CODE_H
#define EXIT_CODE_H

// A collection of exit codes, depending on what went wrong
enum ExitCode {
	INVALID_ARG_SYNTAX = 1,
	INVALID_ENCRYPT_DECRYPT_FLAG = 2,
	INVALID_PASSWORD = 3,
	INVALID_MODE = 4,
	CANNOT_OPEN_FILE = 5,

};
#endif