#ifndef BBB2CE26_606B_4802_BB48_0A038AA4EE0F
#define BBB2CE26_606B_4802_BB48_0A038AA4EE0F

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GV.h"

char* Split (char bp) {
	if (_test_ && _c_ == '\n') return NULL;
	char *input = (char*)calloc(maxL, sizeof(char));
	int len = 0;
	while ((_c_ = getchar()) != bp && _c_ != '\n' && _c_ != ' ' && _c_ != EOF && len <= 100) input[len++] = _c_;
	if (len > 100) {
		fprintf(stderr, "input length limit exceed!\n");
		free(input);
		exit(-1);
	}
	if (!len) return NULL;
	input = (char*)realloc(input, len);
	return input;
}

#endif /* BBB2CE26_606B_4802_BB48_0A038AA4EE0F */
