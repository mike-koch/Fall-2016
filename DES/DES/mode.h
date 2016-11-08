/*
Mike Koch
EECS 4760 - Computer Security
DES
mode.h: An enum to indicate whether or not to encrypt (Mode::ENCRYPTION) or to decrypt (Mode::DECRYPTION) the infile.
*/
#ifndef MODE_H
#define MODE_H

enum Mode {
	ENCRYPTION,
	DECRYPTION,
};
#endif