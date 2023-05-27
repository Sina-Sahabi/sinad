#ifndef F9DAF804_FA72_4C88_AD53_8F63FB35E3EA
#define F9DAF804_FA72_4C88_AD53_8F63FB35E3EA

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
	char id [maxL], name [maxL];
	int type, price;
} Food;

void clearFoodList () { FILE *fp = fopen(__preAdd "data/food-list.bin", "wb"); fclose(fp); }

void addFood (Food f) {
	FILE *fp = fopen(__preAdd "data/food-list.bin", "rb+");
	if (fp == NULL) { fprintf(stderr, "%s %d: Food file lost!\n", __FILE__, __LINE__); exit(-1); }
	fseek(fp, 0, SEEK_END);
	fwrite(&f, sizeof(Food), 1, fp);
	fclose(fp);
}

Food* findFood (char *id) {
	FILE *fp = fopen(__preAdd "data/food-list.bin", "rb");
	if (fp == NULL) { fprintf(stderr, "%s %d: Food file lost!\n", __FILE__, __LINE__); exit(-1); }
	Food *f = (Food*)calloc(1, sizeof(Food));
	while (fread(f, sizeof(Food), 1, fp)) if (!strcmp(f->id, id)) { fclose(fp); return f; }
	free(f);
	fclose(fp);
	return NULL;
}

typedef struct {
	char id [maxL], name [maxL], loc [maxL];
	int cap, type, mltp, ml [2][2];
} Self;

void clearSelfList () { FILE *fp = fopen(__preAdd "data/self-list.bin", "wb"); fclose(fp); }

void addSelf (Self s) {
	FILE *fp = fopen(__preAdd "data/self-list.bin", "rb+");
	if (fp == NULL) { fprintf(stderr, "%s %d: Self file lost!\n", __FILE__, __LINE__); exit(-1); }
	fseek(fp, 0, SEEK_END);
	fwrite(&s, sizeof(Self), 1, fp);
	fclose(fp);
}

Self* findSelf (char *id) {
	FILE *fp = fopen(__preAdd "data/self-list.bin", "rb");
	if (fp == NULL) { fprintf(stderr, "%s %d: Self file lost!\n", __FILE__, __LINE__); exit(-1); }
	Self *s = (Self*)calloc(1, sizeof(Self));
	while (fread(s, sizeof(Self), 1, fp)) if (!strcmp(s->id, id)) { fclose(fp); return s; }
	free(s);
	fclose(fp);
	return NULL;
}

//!
typedef struct {
	char self_id [maxL], food_id [maxL];
	date d;
	int type, cnt, ate, rez;
	long plan_id;
} Plan;

int Pcmp (Plan x, Plan y) {
	return (!strcmp(x.self_id, y.self_id) && !strcmp(x.food_id, y.food_id) && x.type == y.type && Dcmp(x.d, y.d));
}

void clearPlanList () { FILE *fp = fopen(__preAdd "data/plan-list.bin", "wb"); fclose(fp); }

void addPlan (Plan p) {
	FILE *fp = fopen(__preAdd "data/plan-list.bin", "rb+");
	if (fp == NULL) { fprintf(stderr, "%s %d: Plan file lost!\n", __FILE__, __LINE__); exit(-1); }
	fseek(fp, 0, SEEK_END); p.ate = p.rez = 0, p.plan_id = time(NULL);
	fwrite(&p, sizeof(Plan), 1, fp);
	fclose(fp);
}

Plan* findPlan (Plan p) {
	FILE *fp = fopen(__preAdd "data/plan-list.bin", "rb");
	if (fp == NULL) { fprintf(stderr, "%s %d: Plan file lost!\n", __FILE__, __LINE__); exit(-1); }
	Plan *t = (Plan*)calloc(1, sizeof(Plan));
	while (fread(t, sizeof(Plan), 1, fp)) if (!Pcmp(*t, p)) { fclose(fp); return t; }
	free(t);
	fclose(fp);
	return NULL;
}

Plan* findPlanById (char *s) {
	long x; assert(sscanf(s, "%ld", &x));
	FILE *fp = fopen(__preAdd "data/plan-list.bin", "rb");
	if (fp == NULL) { fprintf(stderr, "%s %d: Plan file lost!\n", __FILE__, __LINE__); exit(-1); }
	Plan *t = (Plan*)calloc(1, sizeof(Plan));
	while (fread(t, sizeof(Plan), 1, fp)) if (x == t->plan_id) { fclose(fp); return t; }
	free(t);
	fclose(fp);
	return NULL;
}

void changePlan (Plan p) {
	FILE *fp = fopen(__preAdd "data/plan-list.bin", "rb+");
	if (fp == NULL) { fprintf(stderr, "%s %d: Plan file lost!\n", __FILE__, __LINE__); exit(-1); }
	Plan *t = (Plan*)calloc(1, sizeof(Plan));
	while (fread(t, sizeof(Plan), 1, fp)) if (Pcmp(*t, p)) {
		fseek(fp, -sizeof(Plan), SEEK_CUR);
		fwrite(&p, sizeof(Plan), 1, fp);
		free(t);
		fclose(fp);
		return;
	}
	free(t);
	fclose(fp);
	fprintf(stderr, "%s %d: Plan lost!\n", __FILE__, __LINE__);
	exit(-1);
}

#endif /* F9DAF804_FA72_4C88_AD53_8F63FB35E3EA */
