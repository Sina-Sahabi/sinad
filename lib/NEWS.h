#ifndef CA8CC09B_B276_4AF0_ACA3_D33A2EFC1C5C
#define CA8CC09B_B276_4AF0_ACA3_D33A2EFC1C5C

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "GV.h"
#include "TIME.h"

#ifdef Test
#define __preAdd ""
#else
#define __preAdd "../"
#endif

typedef struct {
	char topic [101], content [1001];
	date d;
} NEWS;

void add_news (NEWS n) {
	FILE *fp = fopen(__preAdd "data/NEWS.bin", "rb+");
	if (fp == NULL) { fprintf(stderr, "%s %d: NEWS file lost!\n", __FILE__, __LINE__); exit(-1); }
	fseek(fp, 0, SEEK_END);
	fwrite(&n, sizeof(NEWS), 1, fp);
	fclose(fp);
}

int check_news () {
	FILE *fp = fopen(__preAdd "data/NEWS.bin", "rb");
	if (fp == NULL) { fprintf(stderr, "%s %d: NEWS file lost!\n", __FILE__, __LINE__); exit(-1); }
	int cnt = 0;
	for (NEWS n; fread(&n, sizeof(n), 1, fp);) /* if (dcmp(rnow(), n.d) > 1) */ {
		cnt++;
		fprintf(stderr, "%s: %s\n", n.topic, n.content);
	}
	fclose(fp);
	return cnt;
}

#endif /* CA8CC09B_B276_4AF0_ACA3_D33A2EFC1C5C */
