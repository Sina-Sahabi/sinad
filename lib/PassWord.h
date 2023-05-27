#ifndef C315DE33_FE74_445E_AB87_4B8DB2E812E9
#define C315DE33_FE74_445E_AB87_4B8DB2E812E9

// <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "GV.h"

int getch (int echo) {
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~ICANON;
	if (echo) newt.c_lflag &= ECHO;
	else newt.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

char* getPassWord () {
	if (_test_ && _c_ == '\n') return NULL;
	fprintf(stderr, "Please enter your password: ");
	char *pass = (char*)calloc(maxL, sizeof(char));
	int len = 0;
	while ((_c_ = getch(0)) != '\n' && _c_ != '|' && _c_ != ' ' && _c_ != EOF && len < 100) pass[len++] = _c_, fprintf(stderr, "*");
	fprintf(stderr, "\n");
	if (len == 100) {
		fprintf(stderr, "password length limit exceeds!\n");
		free(pass);
		exit(-1);
	}
	return pass;
}

char* getStr (char *topic) {
	if (_test_ && _c_ == '\n') return NULL;
	fprintf(stderr, "%s: ", topic);
	char *user = (char*)calloc(maxL, sizeof(char));
	int len = 0;
	while ((_c_ = getchar()) != '\n' && _c_ != '|' && _c_ != ' ' && _c_ != EOF && len < 100) user[len++] = _c_;
	if (len == 100) {
		fprintf(stderr, "length limit exceeds!\n");
		free(user);
		exit(-1);
	}
	return user;
}

#endif /* C315DE33_FE74_445E_AB87_4B8DB2E812E9 */