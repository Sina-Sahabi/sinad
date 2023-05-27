#include "lib/generalHeader.h"

int main () {
	system("gcc bin/init.c -D Test -o bin/init && ./bin/init");
	printf("input file name: ");
	char comm [100] = "gcc bin/main.c -D Test -o bin/final_exe && ./bin/final_exe < input/";
	scanf("%s", comm + 67);
	strcat(comm, " > output/40131063.txt");
	fprintf(stderr, "%s\n", comm);
	system(comm);
	return 0;
}