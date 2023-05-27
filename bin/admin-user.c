#ifdef Test
int test = 1;
#define preAdd "data/"
#else
int test = 0;
#define preAdd "../data/"
#endif

#include "../lib/generalHeader.h"

#define CAT(x, y) strcat(x, y), strcat(x, "-log.bin")

int main (int argc, char *argv[])
{
	if (test) _test_ = 1;
	else _test_ = 0;
	assert(argc > 1);
	FILE *fp = fopen(preAdd "IPC.txt", "w");
	if (!strcmp(argv[1], "login")) { //!
		assert(argc == 4);
		char *user = argv[2];
		User *p = findUser(user);
		if (p == NULL) {
			fprintf(fp, "not-found");
			fclose(fp);
			return -1;
		} else if (!p->active) {
			fprintf(fp, "permission-denied");
			fclose(fp);
			free(p);
			return -1;
		}
		char pass [101] = {'\0'};
		strcpy(pass, argv[3]);
		convert_pass(pass);
		if (strcmp(pass, p->password)) {
			fprintf(fp, "not-found");
			fclose(fp);
			free(p);
			return -1;
		}
		fprintf(fp, "success");
		fclose(fp);
		if (p->online) {
			fprintf(stderr, "User has already logged in!\n");
			free(p);
			return 0;
		}
		p->online = 1;
		changeUser(*p);
		free(p);
	} else if (!strcmp(argv[1], "logout")) { //!
		assert(argc == 3);
		char *user = argv[2];
		User *p = findUser(user);
		if (p == NULL) {
			fprintf(fp, "not-found");
			fclose(fp);
			free(p);
			return -1;
		} else if (!p->online) {
			fprintf(fp, "not-found");
			fclose(fp);
			free(p);
			return -1;
		}
		p->online = 0;
		changeUser(*p);
		free(p);
		fprintf(fp, "success");
		fclose(fp);
	} else if (!strcmp(argv[1], "change-pass")) { //!
		assert(argc == 5);
		char *user = argv[2];
		User *p = findUser(user);
		if (p == NULL) {
			fprintf(fp, "not-found");
			fclose(fp);
			free(p);
			return -1;
		} else if (!p->active) {
			fprintf(stderr, "User is deactive!\n");
			fprintf(fp, "not-found");
			fclose(fp);
			free(p);
			return -1;
		} else if (!p->online) {
			fprintf(stderr, "User isn\'t login!\n");
			fprintf(fp, "not-found");
			fclose(fp);
			free(p);
			return -1;
		}
		char pass [101] = {'\0'};
		strcat(pass, argv[3]);
		convert_pass(pass);
		if (strcmp(pass, p->password)) {
			fprintf(stderr, "Password is incorrect!\n");
			fprintf(fp, "permission-denied");
			fclose(fp);
			free(p);
			return -1;
		}
		p->password[0] = '\0'; strcat(p->password, argv[4]);
		convert_pass(p->password);
		changeUser(*p);
		free(p);
		fprintf(fp, "success");
		fclose(fp);
	} else if (!strcmp(argv[1], "approve")) { //!
		assert(argc > 3);
		bool not_found = false;
		char *user = argv[2];
		User *p = findUser(user);
		if (p == NULL) {
			fprintf(fp, "not-found");
			fclose(fp);
			free(p);
			return -1;
		}
		if (!p->active) {
			fprintf(fp, "permission-denied");
			fclose(fp);
			free(p);
			return -1;
		}
		if (!p->privilege) {
			fprintf(fp, "permission-denied");
			fclose(fp);
			free(p);
			return -1;
		}
		free(p);
		for (int i = 3; i < argc; i++) {
			user = argv[i];
			p = findUser(user);
			if (p == NULL) { not_found = true; continue; }
			p->active = 1;
			changeUser(*p);
			free(p);
		}
		if (not_found) {
			fprintf(fp, "not-found");
			fclose(fp);
			return -1;
		}
		fprintf(fp, "success");
		fclose(fp);
	} else if (!strcmp(argv[1], "change-student-pass")) { //!
		assert(argc == 5);
		char *user = argv[2];
		User *p = findUser(user);
		if (p == NULL || !p->online) {
			fprintf(fp, "not-found");
			fclose(fp);
			free(p);
			return -1;
		} else if (!p->active || !p->privilege) {
			fprintf(fp, "permission-denied");
			fclose(fp);
			free(p);
			return -1;
		}
		user = argv[3];
		p = findUser(user);
		if (p == NULL) {
			fprintf(fp, "not-found");
			fclose(fp);
			free(p);
			return -1;
		}
		strcpy(p->password, argv[4]);
		convert_pass(p->password);
		changeUser(*p);
		free(p);
		fprintf(fp, "success");
		fclose(fp);
	} else if (!strcmp(argv[1], "remove-user")) { //!
		assert(argc == 4);
		char *user = argv[2];
		User *p = findUser(user);
		if (p == NULL) {
			fprintf(fp, "not-found");
			fclose(fp);
			free(p);
			return -1;
		}
		if (!p->active || !p->privilege) {
			fprintf(fp, "permission-denied");
			fclose(fp);
			free(p);
			return -1;
		}
		free(p);
		user = argv[3];
		p = findUser(user);
		if (p == NULL) {
			fprintf(fp, "not-found");
			fclose(fp);
			free(p);
			return -1;
		}
		if (p->privilege) {
			fprintf(fp, "permission-denied");
			fclose(fp);
			free(p);
			return -1;
		}
		removeUser(*p);
		free(p);
		fprintf(fp, "success");
		fclose(fp);
	} else if (!strcmp(argv[1], "deactive")) { //!
		assert(argc == 4);
		char *user = argv[2];
		User *p = findUser(user);
		if (p == NULL || !p->online) {
			fprintf(fp, "not-found");
			fclose(fp);
			free(p);
			return -1;
		} else if (!p->active || !p->privilege) {
			fprintf(fp, "permission-denied");
			fclose(fp);
			free(p);
			return -1;
		}
		user = argv[3];
		p = findUser(user);
		if (p == NULL) {
			fprintf(fp, "not-found");
			fclose(fp);
			free(p);
			return -1;
		} else if (p->privilege) {
			fprintf(fp, "permission-denied");
			fclose(fp);
			free(p);
			return -1;
		}
		p->active = 0;
		changeUser(*p);
		free(p);
		fprintf(fp, "success");
		fclose(fp);
	} else if (!strcmp(argv[1], "register")) { //!
		assert(argc == 11);
		User p;
		sprintf(p.fname, "%s", argv[3]);
		sprintf(p.lname, "%s", argv[4]);
		sprintf(p.username, "%s", argv[5]);
		// for (int i = 0, n = strlen(p.username); i < n; i++) if (p.username[i] < '0' || '9' < p.username[i]) {
		// 	fprintf(fp, "invalid"); fclose(fp);
		// 	return -1;
		// }
		sprintf(p.password, "%s", argv[6]); convert_pass(p.password);
		sprintf(p.NIC, "%s", argv[7]);
		for (int i = 0, n = strlen(p.NIC); i < n; i++) if (p.NIC[i] < '0' || '9' < p.NIC[i]) {
			fprintf(fp, "invalid"); fclose(fp);
			return -1;
		}
		p.birth = convert_to_date(argv[8]);
		if (!checkdate(p.birth)) {
			fprintf(fp, "invalid"); fclose(fp);
			return -1;
		}
		if (!strcmp(argv[9], "male")) p.gender = 0;
		else if (!strcmp(argv[9], "female")) p.gender = 1;
		else p.gender = 2;
		if (!strcmp(argv[10], "student")) {
			p.privilege = 0;
			for (int i = 0, n = strlen(p.username); i < n; i++) if (p.username[i] < '0' || '9' < p.username[i]) {
				fprintf(fp, "invalid"); fclose(fp);
				return -1;
			}
		} else if (!strcmp(argv[10], "admin")) p.privilege = 1;
		else p.privilege = 2;
		if (p.gender == 2 || p.privilege == 2) {
			fprintf(fp, "invalid");
			fclose(fp);
			return -1;
		} else if (findUser(p.username) != NULL) {
			fprintf(fp, "permission-denied");
			fclose(fp);
			return -1;
		}
		p.active = 0; p.online = 0;
		User *p2 = findUser(argv[2]);
		if (p2 != NULL && p2->privilege) p.active = 1;
		free(p2);
		addUser(p);
		fprintf(fp, "success");
		fclose(fp);
	} else if (!strcmp(argv[1], "charge-student-account")) { //!
		assert(argc == 5);
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
		u = findUser(argv[3]);
		if (u == NULL) {
			fprintf(fp, "not-found"); fclose(fp);
			free(u);
			return -1;
		} else if (u->privilege) {
			fprintf(fp, "premission-denied"); fclose(fp);
			free(u);
			return -1;
		}
		int x;
		if (!sscanf(argv[4], "%d", &x)) {
			fprintf(fp, "invalid"); fclose(fp);
			free(u);
			return -1;
		}
		u->charge += x;
		char path [1000] = preAdd "log/"; CAT(path, argv[3]);
		FILE *l = fopen(path, "rb+");
		assert(l != NULL);
		fseek(l, 0, SEEK_END);
		Log lg;
		lg.d = rnow();
		strcat(lg.report, "charge "); strcat(lg.report, argv[4]);
		fwrite(&lg, sizeof(lg), 1, l); fclose(l);
		changeUser(*u); free(u);
		fprintf(fp, "success"); fclose(fp);
	} else if (!strcmp(argv[1], "charge-account")) { //!
		assert(argc == 4);
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
		int x;
		if (!sscanf(argv[3], "%d", &x)) {
			fprintf(fp, "invalid"); fclose(fp);
			free(u);
			return -1;
		}
		char path [1000] = preAdd "log/"; CAT(path, u->username);
		FILE *l = fopen(path, "rb+");
		assert(l != NULL);
		fseek(l, 0, SEEK_END);
		Log lg;
		lg.d = rnow();
		strcat(lg.report, "self-charge "); strcat(lg.report, argv[3]);
		fwrite(&lg, sizeof(lg), 1, l); fclose(l);
		u->charge += x;
		changeUser(*u); free(u);
		fprintf(fp, "success"); fclose(fp);
	} else {
		assert(false);
	}

	return 0;
}