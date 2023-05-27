#ifndef C59EDDB3_ABE3_4715_8468_4266227916AB
#define C59EDDB3_ABE3_4715_8468_4266227916AB

#include <string.h>

const int key [] = {23, 32, 11, 3, 33, 5, 23, 55, 23, 45, 95, 100, 1, 11, 0, 38, 85, 13, 82}, mod = 1100000123;

void convert_pass (char *str) {
	long long hash = strlen(str);
	for (int i = hash; i--;) hash = hash * str[i] * key[i % 19] % mod, str[i] = (hash % 100) + 22;
}

#endif /* C59EDDB3_ABE3_4715_8468_4266227916AB */
