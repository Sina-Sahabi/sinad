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
	if (!strcmp(argv[1], "define-self")) { //!
		assert(argc == 10 || argc == 11);
		User *p = findUser(argv[2]);
		if (p == NULL || !p->online) {
			fprintf(fp, "not-found"); fclose(fp);
			free(p);
			return -1;
		} else if (!p->active || !p->privilege) {
			fprintf(fp, "premission-denied1"); fclose(fp);
			free(p);
			return -1;
		}
		free(p);
		Self *S = findSelf(argv[3]);
		if (S != NULL) {
			fprintf(fp, "premission-denied2"); fclose(fp);
			fprintf(stderr, "self id duplicate issue\n");
			free(S);
			return -1;
		}
		free(S);
		Self NS;
		sprintf(NS.id, "%s", argv[3]);
		for (int i = 0, n = strlen(NS.id); i < n; i++) if (NS.id[i] < '0' || '9' < NS.id[i]) {
			fprintf(fp, "invalid"); fclose(fp);
			return -1;
		}
		sprintf(NS.name, "%s", argv[4]);
		sprintf(NS.loc, "%s", argv[5]);
		if (!sscanf(argv[6], "%d", &(NS.cap))) {
			fprintf(fp, "invalid"); fclose(fp);
			return -1;
		}
		if (strcmp(argv[7], "boyish") && strcmp(argv[7], "girlish")) {
			fprintf(fp, "invalid"); fclose(fp);
			return -1;
		}
		NS.type = (strcmp(argv[7], "boyish") != 0);
		if (!strcmp(argv[8], "both")) {
			NS.mltp = 2;
			if (strlen(argv[9]) != 9 || strlen(argv[10]) != 9) {
				fprintf(fp, "invalid"); fclose(fp);
				return -1;
			}
			if (sscanf(argv[9], "%d-%d", &(NS.ml[0][0]), &(NS.ml[0][1])) != 2) {
				fprintf(fp, "invalid"); fclose(fp);
				return -1;
			}
			if (sscanf(argv[10], "%d-%d", &(NS.ml[1][0]), &(NS.ml[1][1])) != 2) {
				fprintf(fp, "invalid"); fclose(fp);
				return -1;
			}
		} else if (!strcmp(argv[8], "lunch") || !strcmp(argv[8], "dinner")) {
			NS.mltp = (strcmp(argv[8], "dinner") == 0);
			if (strlen(argv[9]) != 9) {
				fprintf(fp, "invalid"); fclose(fp);
				return -1;
			}
			if (sscanf(argv[9], "%d-%d", &(NS.ml[NS.mltp][0]), &(NS.ml[NS.mltp][1])) != 2) {
				fprintf(fp, "invalid"); fclose(fp);
				return -1;
			}
		} else {
			fprintf(fp, "invalid"); fclose(fp);
			return -1;
		}
		addSelf(NS);
		fprintf(fp, "success"); fclose(fp);
	} else if (!strcmp(argv[1], "define-food")) { //!
		assert(argc == 7);
		User *p = findUser(argv[2]);
		if (p == NULL || !p->online) {
			fprintf(fp, "not-found"); fclose(fp);
			free(p);
			return -1;
		} else if (!p->active || !p->privilege) {
			fprintf(fp, "premission-denied"); fclose(fp);
			free(p);
			return -1;
		}
		free(p);
		Food *f = findFood(argv[3]);
		if (f != NULL) {
			fprintf(fp, "premission-denied"); fclose(fp);
			fprintf(stderr, "food id duplicate issue\n");
			free(f);
			return -1;
		}
		free(f);
		Food NF;
		sprintf(NF.id, "%s", argv[3]);
		for (int i = 0, n = strlen(NF.id); i < n; i++) if (NF.id[i] < '0' || '9' < NF.id[i]) {
			fprintf(fp, "invalid"); fclose(fp);
			return -1;
		}
		sprintf(NF.name, "%s", argv[4]);
		if (!strcmp(argv[5], "food")) {
			NF.type = 0;
		} else if (!strcmp(argv[5], "dessert")) {
			NF.type = 1;
		} else {
			fprintf(fp, "invalid"); fclose(fp);
			return -1;
		}
		if (!sscanf(argv[6], "%d", &(NF.price))) {
			fprintf(fp, "invalid"); fclose(fp);
			return -1;
		}
		addFood(NF);
		fprintf(fp, "success"); fclose(fp);
	} else if (!strcmp(argv[1], "define-meal-plan")) { //!
		assert(argc == 8);
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
		Plan p;
		Self *S = findSelf(argv[3]);
		if (S == NULL) {
			fprintf(fp, "not-found"); fclose(fp);
			free(S);
			return -1;
		}
		strcat(p.self_id, argv[3]);
		p.d = convert_to_date(argv[4]);
		if (!checkdate(p.d)) {
			fprintf(fp, "invalid"); fclose(fp);
			free(S);
			return -1;
		}
		if (!strcmp(argv[5], "lunch")) p.type = 0;
		else if (!strcmp(argv[5], "dinner")) p.type = 1;
		else {
			fprintf(fp, "invalid"); fclose(fp);
			free(S);
			return -1;
		}
		if (S->mltp != 2 && S->mltp != p.type) {
			fprintf(fp, "premission-denied"); fclose(fp);
			fprintf(stderr, "meal type diff {plan/self}!\n");
			free(S);
			return -1;
		}
		p.d.T.h = S->ml[p.type][0] / 100; p.d.T.min = S->ml[p.type][0] % 100;
		Food *f = findFood(argv[6]);
		if (f == NULL) {
			fprintf(fp, "not-found\n"); fclose(fp);
			free(S); free(f);
			return -1;
		}
		strcpy(p.food_id, argv[6]);
		if (!sscanf(argv[7], "%d", &(p.cnt))) {
			fprintf(fp, "invalid"); fclose(fp);
			free(f); free(S);
			return -1;
		} else if (p.cnt > S->cap && 0) {
			fprintf(fp, "premission-denied"); fclose(fp);
			fprintf(stderr, "food amount > self capacity!\n");
			free(S); free(f);
			return -1;
		}
		free(S); free(f);
		addPlan(p);
		fprintf(fp, "success"); fclose(fp);
	} else if (!strcmp(argv[1], "reserve")) { //!
		assert(argc == 7);
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
		Self *s = findSelf(argv[3]);
		if (s == NULL) {
			fprintf(fp, "not-found"); fclose(fp);
			free(u); free(s);
			return -1;
		} else if (s->type != u->gender) {
			fprintf(fp, "premission-denied"); fclose(fp);
			free(u); free(s);
			return -1;
		}
		Food *f = findFood(argv[6]);
		if (f == NULL) {
			fprintf(fp, "not-found"); fclose(fp);
			free(u); free(s); free(f);
			return -1;
		}
		Plan tmp;
		strcmp(tmp.self_id, argv[2]);
		strcmp(tmp.food_id, argv[6]);
		tmp.d = convert_to_date(argv[4]);
		if (!checkdate(tmp.d)) {
			fprintf(fp, "invalid"); fclose(fp);
			free(u); free(s); free(f);
			return -1;
		}
		if (!strcmp(argv[5], "lunch")) tmp.type = 0;
		else if (!strcmp(argv[5], "dinner")) tmp.type = 1;
		else {
			fprintf(fp, "invalid"); fclose(fp);
			free(u); free(s); free(f);
			return -1;
		}
		Plan *P = findPlan(tmp);
		if (P == NULL) {
			fprintf(fp, "not-found"); fclose(fp);
			free(u); free(s); free(f); free(P);
			return -1;
		}
		if (P->cnt == P->rez) {
			fprintf(fp, "premission-denied"); fclose(fp);
			fprintf(stderr, "no food for you :(\n");
			free(u); free(s); free(f); free(P);
			return -1;
		}
		date dnow = rnow(), dlt = delta(dnow, P->d);
		if (dlt.year || dlt.month || dlt.day >= 14 || dlt.day < 2) {
			fprintf(fp, "premission-denied"); fclose(fp);
			fprintf(stderr, "deadline issue\n");
			free(u); free(s); free(f); free(P);
			return -1;
		}
		while (u->charge < f->price) {
			fprintf(fp, "premission-denied"); fclose(fp);
			fprintf(stderr, "not enough credit\n");
			if (!test) {
				fprintf(stderr, "Please enter the amount: ");
				int x;
				scanf("%d", &x);
				u->charge += x;
				free(getStr("Please enetr the card number"));
				free(getStr("Please enetr the pass code"));
			} else {
				free(u); free(s); free(f); free(P);
				return -1;
			}
		}
		u->charge -= f->price;
		P->rez++;
		changeUser(*u);
		changePlan(*P);
		char path [1000] = preAdd "log/"; CAT(path, argv[2]);
		FILE *l = fopen(path, "rb+");
		assert(l != NULL);
		fseek(l, 0, SEEK_END);
		Log lg; memset(lg.report, 0, sizeof lg.report);
		lg.d = rnow();
		sprintf(lg.report, "cost %d reserve %s in %s id: %ld", f->price, f->name, s->name, P->plan_id);
		fwrite(&lg, sizeof(lg), 1, l); fclose(l);
		free(u); free(s); free(f); free(P);
		fprintf(fp, "success"); fclose(fp);
	} else if (!strcmp(argv[1], "take-food")) { //!
		assert(argc == 6);
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
		Self *s = findSelf(argv[3]);
		if (s == NULL) {
			fprintf(fp, "not-found"); fclose(fp);
			free(u); free(s);
			return -1;
		} else if (s->mltp != 2 && s->mltp != (strcmp(argv[5], "dinner") == 0)) {
			fprintf(fp, "not-found"); fclose(fp);
			free(u); free(s);
			return -1;
		}
		int rn = rnow().T.h * 100 + rnow().T.min, tp = (strcmp(argv[5], "dinner") == 0);
		if (!(s->ml[tp][0] <= rn && rn <= s->ml[tp][1])) {
			fprintf(fp, "premission-denied"); fclose(fp);
			free(u); free(s);
			return -1;
		}
		date d = convert_to_date(argv[4]);
		if (!checkdate(d)) {
			fprintf(fp, "invalid"); fclose(fp);
			free(u); free(s);
			return -1;
		}
		int cnt = 0;
		char path [200]; sprintf(path, preAdd "log/%s-log.bin", u->username);
		FILE *pp = fopen(preAdd "plan-list.bin", "rb+");
		assert(pp != NULL);
		for (Plan p; fread(&p, sizeof(p), 1, pp);) if (Dcmp(p.d, d) && !strcmp(s->name, p.self_id) && p.type == tp) {
			char ID [101]; sprintf(ID, "%ld", p.plan_id);
			FILE *pl = fopen(path, "rb+");
			for (Log l; fread(&l, sizeof(l), 1, pl);)
				if (strstr(l.report, "cost") && strstr(l.report, ID) && strstr(l.report, "served") == NULL) {
					strcat(l.report, " & served");
					fseek(pl, -sizeof(l), SEEK_CUR);
					fwrite(&l, sizeof(l), 1, pl);
					cnt++;
					break;
				}
			fclose(pl);
			p.ate++;
			fseek(pp, -sizeof(p), SEEK_CUR);
			fwrite(&p, sizeof(p), 1, pp);
		}
		fclose(pp);
		free(u); free(s);
		if (!cnt) fprintf(fp, "not-found"), fprintf(stderr, "no reservation found\n");
		else fprintf(fp, "success");
		fclose(fp);
	} else if (!strcmp(argv[1], "cancel-reserve")) { //!
		assert(argc == 5);
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
		int tp = 2;
		if (!strcmp(argv[4], "lunch")) tp = 0;
		else if (!strcmp(argv[4], "dinner")) tp = 1;
		date d = convert_to_date(argv[3]);
		if (!checkdate(d) || tp == 2) {
			fprintf(fp, "invalid"); fclose(fp);
			free(u);
			return -1;
		}
		int cnt = 0;
		char path [200]; sprintf(path, preAdd "log/%s-log.bin", u->username);
		FILE *fin = fopen(path, "rb+");
		for (Log l; fread(&l, sizeof(l), 1, fin);)
			if (strstr(l.report, "reserve") != NULL && strstr(l.report, "served") == NULL && strstr(l.report, "cancel") == NULL) {
				Plan *p = findPlanById(strstr(l.report, "id:") + 4);
				if (Dcmp(p->d, d) && p->type == tp) {
					Self *s = findSelf(p->self_id);
					if (dcmp(rnow(), p->d) < 0 || delta(p->d, rnow()).T.h < 1) {
						fprintf(fp, "premission-denied"); fclose(fp);
						free(p); free(s); free(u);
					} else {
						Food *f = findFood(p->food_id);
						u->charge += 9 * f->price / 10;
						strcat(l.report, " & canceled");
						fseek(fin, -sizeof(l), SEEK_CUR);
						fwrite(&l, sizeof(l), 1, fin);
						p->rez--;
						changePlan(*p);
						cnt++;
						free(f);
					}
					free(s);
				}
				free(p);
			}
		fclose(fin);
		changeUser(*u);
		if (!cnt) fprintf(fp, "not-found");
		else fprintf(fp, "success");
		fclose(fp);
	} else {
		assert(false);
	}

	return 0;
}