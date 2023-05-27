#ifndef B7D87F5B_FAA8_455A_8613_123901C70ACE
#define B7D87F5B_FAA8_455A_8613_123901C70ACE

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
	char fname [51], lname [51], NIC [21];
	date birth; int gender;
	char username [maxL], password [maxL];
	int privilege, active, online, charge;
} User;

void clearUserList () { FILE *fp = fopen(__preAdd "data/user-list.bin", "wb"); fclose(fp); }

User* findUser (char *username) {
	FILE *fp = fopen(__preAdd "data/user-list.bin", "rb");
	if (fp == NULL) { fprintf(stderr, "%s %d: User file lost!\n", __FILE__, __LINE__); exit(-1); }
	User *u = (User*)calloc(1, sizeof(User));
	while (fread(u, sizeof(User), 1, fp)) if (strcmp(u->username, username) == 0) { fclose(fp); return u; }
	free(u);
	fclose(fp);
	return NULL;
}

void addUser (User p) {
	FILE *fp = fopen(__preAdd "data/user-list.bin", "rb+");
	if (fp == NULL) { fprintf(stderr, "%s %d: User file lost!\n", __FILE__, __LINE__); exit(-1); }
	fseek(fp, 0, SEEK_END);
	fwrite(&p, sizeof(User), 1, fp);
	fclose(fp);
	char path [1000] = __preAdd "data/log/"; strcat(path, p.username); strcat(path, "-log.bin");
	fp = fopen(path, "wb");
	fclose(fp);
}

void changeUser (User p) {
	FILE *fp = fopen(__preAdd "data/user-list.bin", "rb+");
	if (fp == NULL) { fprintf(stderr, "%s %d: User file lost!\n", __FILE__, __LINE__); exit(-1); }
	User *u = (User*)calloc(1, sizeof(User));
	while (fread(u, sizeof(User), 1, fp)) if (strcmp(u->username, p.username) == 0) {
		fseek(fp, -sizeof(User), SEEK_CUR);
		fwrite(&p, sizeof(User), 1, fp);
		free(u);
		fclose(fp);
		return;
	}
	free(u);
	fclose(fp);
	fprintf(stderr, "%s %d: User lost!\n", __FILE__, __LINE__);
	exit(-1);
}

void removeUser (User p) {
	FILE *fin = fopen(__preAdd "data/user-list.bin", "rb");
	if (fin == NULL) { fprintf(stderr, "%s %d: User file lost!\n", __FILE__, __LINE__); exit(-1); }
	FILE *fout = fopen(__preAdd "data/tmp.bin", "wb");
	User *u = (User*)calloc(1, sizeof(User));
	while (fread(u, sizeof(User), 1, fin)) if (strcmp(u->username, p.username)) fwrite(u, sizeof(User), 1, fout);
	free(u); fclose(fin); fclose(fout);
	remove(__preAdd "data/user-list.bin");
	rename(__preAdd "data/tmp.bin", __preAdd "data/user-list.bin");
}

#endif /* B7D87F5B_FAA8_455A_8613_123901C70ACE */
