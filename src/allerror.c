#include "minilib.h"

void mx_printerror(char *str) {
	write(2, "endgame: ", 9);                
	for (int i = 0; str[i] != '\0'; i++)
		write(2, &str[i], 1);                
	write(2, "\n", 1);
}

void print_all_error(void) {
	int err = errno;
	mx_printerror(strerror(err));
	exit(err);
}

void print_error(void) {
	mx_printerror((char*)SDL_GetError());
	exit(2);
}
