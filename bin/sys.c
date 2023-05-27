#ifdef Test
int test = 1;
#define preAdd "data/"
#else
int test = 0;
#define preAdd "../data/"
#endif

#include "../lib/generalHeader.h"

int main (int argc, char *argv[])
{
	if (test) _test_ = 1;
	else _test_ = 0;
	assert(argc > 1);
	FILE *fp = fopen(preAdd "IPC.txt", "w");
	if (!strcmp(argv[1], "change-datetime")) { //!
		assert(argc == 4);
		date d = convert_to_date(argv[2]);
		d.T = convert_to_time(argv[3], time(NULL));
		if (!checkdate(d) || d.T.h < 0) {
			fprintf(fp, "invalid"); fclose(fp);
			return -1;
		}
		FILE *fout = fopen(preAdd "datetime.bin", "wb");
		assert(fout != NULL);
		fwrite(&d, sizeof(d), 1, fout); fclose(fout);
		fprintf(fp, "success"); fclose(fp);
	} else if (!strcmp(argv[1], "add-news")) { //!
		assert(argc == 6);
		User *u = findUser(argv[2]);
		if (u == NULL || !u->online) {
			fprintf(fp, "not-found"); fclose(fp);
			free(u);
			return -1;
		} else if (!u->active || !u->privilege) {
			fprintf(fp, "premission-denied"); fclose(fp);
			free(u);
			return -1;
		}
		free(u);
		NEWS n;
		sprintf(n.topic, "%s", argv[3]); sprintf(n.content, "%s", argv[4]);
		n.d = convert_to_date(argv[5]);
		if (!checkdate(n.d)) {
			fprintf(fp, "invalid"); fclose(fp);
			return -1;
		}
		add_news(n);
		fprintf(fp, "success"); fclose(fp);
	} else if (!strcmp(argv[1], "check-news")) { //!
		assert(argc == 3);
		User *u = findUser(argv[2]);
		if (u == NULL || !u->online) {
			fprintf(fp, "not-found"); fclose(fp);
			free(u);
			return -1;
		} else if (!u->active || u->privilege) {
			fprintf(fp, "premission-denied"); fclose(fp);
			free(u);
			return -1;
		}
		free(u);
		if (check_news()) fprintf(fp, "success");
		else fprintf(fp, "not-found");
		fclose(fp);
	} else {
		assert(false);
	}

	return 0;
}