#include <stdlib.h>
#include <stdio.h>
#include "morse.c"

int main(int argc, char *argv[]) {
	int i = 0;
	char *s = morseEncode(argv[1]);
	printf("%s\n", s);
	char *t = morseDecode(s);
	printf("%s\n", t);
	return 0;
}
