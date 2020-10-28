#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include "morse.h"

char* morseEncode(char *str);
char* morseDecode(char *str);

/*int main(int argc, char *argv[]) {
	int i = 0;
	char *s = morseEncode(argv[1]);
	printf("%s\n", s);
	char *t = morseDecode(s);
	printf("%s\n", t);	
	return 0;
}*/

int strchar(char *str, char ch) {
	int i;
	int count = -1;
	int length = strlen(str);
	for (i = 0; i < length; i++) {
		if (str[i] == ch) {
			count = i;
			break;
		}
	}
	return count;
}

/**explode function**/
void explode(char str[], char seperator, char *data[]) {
	int len = strlen(str);
	int i;
	int pre_flag = 0;
	int count = 0;

	for(i = 0; i < len; i++) {
		if (str[i] == seperator) {
			str[i] = '\0';
			char * temp;
			temp = (char *)malloc(sizeof(char) * (i - pre_flag));
			strncpy(temp, str + pre_flag, i - pre_flag + 1);
			data[count] = temp;
			pre_flag = i + 1;
			count++;
		}
	}
	if (pre_flag < len) {
		data[count] = str + pre_flag;
	}
}

int getCharNum(char *str, char p) {
	int i = 0;
	unsigned int count = 0;
	while (*str) {
		if (*str == p)
			count++;
		str++;
	}
	return count;
}

/**encode morse code**/
char* morseEncode(char *str) {
	int i, count = 0;
	//char *result = (char *)malloc(sizeof(char) * 1000);
	//result[0] = '\0';
	char *segment = (char *)malloc(sizeof(char) * 10);
	segment[0] = '\0';
	int charlen = 0;
	for (i = 0; i < strlen(str); i++) {
		int flag = strchar(chartStr, toupper(str[i]));
		char *tmp = dot[flag];
		charlen = strlen(tmp);
		//printf("tmp = %s, strlen = %d\n", tmp, strlen(tmp));
		count += (charlen + 1);
		segment = (char *)realloc(segment, sizeof(char) * count);
		strncat(segment, tmp, charlen);
		strncat(segment, "/", 1);
		//printf("segment = %s, count = %d\n", segment);
	}
	//char *res = (char *)malloc(sizeof(char) * strlen(segment));
	//res[0] = '\0';
	//strncat(res, result, strlen(result));
	//free(result);
	return segment;
}

/**decode morse code**/
char* morseDecode(char *str) {
	int count = getCharNum(str, op);
	char **data = (char **)malloc(sizeof(char *) * count);
	char *result = (char *)malloc(sizeof(char *) * count);
	*result = '\0';
	explode(str, '/', data);
	int i,j = 0;
	for (i = 0; i < count; i++) {
		for (j = 0; j < passNum; j++) {
			if (strcmp(*(data + i), *(dot + j)) == 0) {
				strncat(result, *(chartMap + j), 1);
			}
		}
	}
	free(data);
	return result;
}
