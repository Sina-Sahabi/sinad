#ifdef Test
int test = 1;
#define preAdd "/bin"
#else
int test = 0;
#define preAdd ""
#endif

#include "../lib/generalHeader.h"

//!
//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
//!

#define CAT(x, y) strcat(x, " "), strcat(x, y)

char cur [101];

bool badBehavior (char **x, char *name, char *tag) {
	*x = NULL;
	if (test) {
		*x = Split(':');
		if (*x == NULL || strcmp(*x, name)) return true;
		free(*x);
	}
	*x = getStr(tag);
	if (*x == NULL) return true;
	return false;
}

int main ()
{
	fprintf(stderr, BOLDGREEN "Sinad " BOLDBLUE "(Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0" RESET "\n");
	fprintf(stderr, BOLDRED "Copyright (C) 2023 Free Software Foundation, Inc." RESET "\n");
	fprintf(stderr, BOLDYELLOW "This is free software;" RESET YELLOW " see the source for copying conditions. There is NO\n");
	fprintf(stderr, "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE." RESET "\n");
	if (!test) { fprintf(stderr, "Press any key to continue... "); getchar(); }

	if (test) {
		system("gcc bin/admin-user.c -D Test -o bin/admin");
		system("gcc bin/self-utility.c -D Test -o bin/self");
		system("gcc bin/sys.c -D Test -o bin/sys");
		_test_ = 1;
	} else {
		system("gcc admin-user.c -o admin");
		system("gcc self-utility.c -o self");
		system("gcc sys.c -o sys");
		_test_ = 0;
	}

	while (_c_ != EOF) {
		newLine();
		fprintf(stderr, "\n>>> ");
		if (test) {
			char *id = Split('#');
			if (id == NULL) break;
			printf("%s#", id);
			fprintf(stderr, "%s#\n", id);
			free(id);
		}
		char *command = Split('#');
		if (!test && command == NULL) break;
		if (command == NULL) {
			printf("invalid\n");
			free(command);
			endLine(); continue;
		} else if (!strcmp(command, "menu")) { //!
			free(command);
			system("cat ../README.md");
		} else if (!strcmp(command, "login")) { //!
			free(command);
			char *in1 = NULL;
			if (test) in1 = Split(':');
			if (test && (in1 == NULL || strcmp(in1, "user"))) {
				free(in1);
				printf("invalid\n");
				endLine(); continue;
			} else {
				free(in1);
				in1 = getStr("Please enter your username");
				if (in1 == NULL) { free(in1); printf("invalid\n"); endLine(); continue; }
				char *in2 = NULL;
				if (test) in2 = Split(':');
				if (test && (in2 == NULL || strcmp(in2, "password"))) {
					free(in1);
					free(in2);
					printf("invalid\n");
					endLine(); continue;
				} else {
					free(in2);
					in2 = getPassWord();
					if (in2 == NULL || _c_ != '\n') { free(in1); free(in2); printf("invalid\n"); endLine(); continue; }
					char arg [300] = "." preAdd "/admin login ";
					strcat(arg, in1); strcat(arg, " "); strcat(arg, in2);
					if (!system(arg)) sprintf(cur, "%s", in1);
					free(in1); free(in2);
				}
			}
		} else if (!strcmp(command, "logout")) { //!
			free(command);
			char *in = NULL;
			if (test) in = Split(':');
			if (test && (in == NULL || strcmp(in, "user"))) {
				free(in);
				printf("invalid\n");
				endLine(); continue;
			} else {
				free(in);
				in = getStr("Please enter your username");
				if (in == NULL || _c_ != '\n') { free(in); printf("invalid\n"); endLine(); continue; }
				char arg [300] = "." preAdd "/admin logout ";
				strcat(arg, in);
				free(in);
				if (!system(arg)) cur[0] = '\0';
			}
		} else if (!strcmp(command, "change-pass")) { //!
			free(command);
			char *in1 = NULL;
			if (test) in1 = Split(':');
			if (test && (in1 == NULL || strcmp(in1, "user"))) {
				free(in1);
				printf("invalid\n");
				endLine();
				continue;
			}
			free(in1);
			in1 = getStr("Please enter your username");
			if (in1 == NULL) { free(in1); printf("invalid\n"); endLine(); continue; }
			char *in2 = NULL;
			if (test) in2 = Split(':');
			if (test && (in2 == NULL || strcmp(in2, "old-pass"))) {
				free(in1); free(in2);
				printf("invalid\n");
				endLine();
				continue;
			}
			free(in2);
			in2 = getPassWord();
			if (in2 == NULL) { free(in1); free(in2); printf("invalid\n"); endLine(); continue; }
			char *in3 = NULL;
			if (test) in3 = Split(':');
			if (test && (in3 == NULL || strcmp(in3, "new-pass"))) {
				free(in1); free(in2); free(in3);
				printf("invalid\n");
				endLine();
				continue;
			}
			free(in3);
			in3 = getStr("Please enter your new password");
			if (in3 == NULL || _c_ != '\n') { free(in1); free(in2); free(in3); printf("invalid\n"); endLine(); continue; }
			char arg [300] = "." preAdd "/admin change-pass ";
			strcat(arg, in1); strcat(arg, " "); strcat(arg, in2); strcat(arg, " "); strcat(arg, in3);
			free(in1); free(in2); free(in3);
			system(arg);
			// fprintf(stderr, "hello\n");
		} else if (!strcmp(command, "approve")) { //!
			free(command);
			int idx = 0;
			fprintf(stderr, "list:\n");
			FILE *fin;
			if (test) fin = fopen("data/user-list.bin", "rb");
			else fin = fopen("../data/user-list.bin", "rb");
			assert(fin != NULL);
			for (User u; fread(&u, sizeof(u), 1, fin);) if (!u.active && !u.privilege) {
				fprintf(stderr, "%d- %s %s %s %s %d %d\n", ++idx, u.fname, u.lname, u.username, u.NIC, u.active, u.privilege);
			}
			fclose(fin);
			fprintf(stderr, "><><><><><><><><><><><><><><>< %s\n", cur);
			if (cur[0] == '\0') {
				printf("invalid\n");
				endLine(); continue;
			}
			bool invalid = false;
			char arg [5000]; memset(arg, 0, sizeof arg);
			strcat(arg, "." preAdd "/admin approve "); strcat(arg, cur);
			for (char c = '|', *in; c != '\n';) {
				if (test) in = Split(':');
				if (test && (in == NULL || strcmp(in, "user"))) invalid = true;
				free(in);
				in = (char*)calloc(101, sizeof(char)); int len = 0;
				while ((c = getchar()) != '|' && c != '\n' && c != ' ' && len < 100) in[len++] = c;
				if (len == 100) {
					while ((c = getchar()) != '\n');
					printf("invalid\n");
					fprintf(stderr, "input length limit exceed!\n");
					free(in);
					continue;
				}
				strcat(arg, " "); strcat(arg, in);
				free(in);
			}
			if (invalid) { printf("invalid\n"); continue; }
			else system(arg);
		} else if (!strcmp(command, "change-student-pass")) { //!
			free(command);
			char *in1 = NULL;
			if (test) in1 = Split(':');
			if (test && (in1 == NULL || strcmp(in1, "user"))) {
				printf("invalid\n");
				free(in1);
				endLine();
				continue;
			}
			free(in1);
			in1 = getStr("Please enter the username");
			if (in1 == NULL) { free(in1); printf("invalid\n"); endLine(); continue; }
			char *in2 = NULL;
			if (test) in2 = Split(':');
			if (test && (in2 == NULL || strcmp(in2, "new-pass"))) {
				printf("invalid\n");
				endLine();
				free(in1); free(in2);
				continue;
			}
			free(in2);
			in2 = getStr("Please enetr the new password");
			if (in2 == NULL) { free(in1); free(in2); printf("invalid\n"); endLine(); continue; }
			char arg [400] = "." preAdd "/admin change-student-pass ";
			strcat(arg, cur); strcat(arg, " "); strcat(arg, in1); strcat(arg, " "); strcat(arg, in2);
			free(in1); free(in2);
			if (cur[0] == '\0' || _c_ != '\n') printf("invalid\n");
			else system(arg);
		} else if (!strcmp(command, "remove-user")) { //!
			free(command);
			char *in = NULL;
			if (test) {
				in = Split(':');
				if (in == NULL || strcmp(in, "user")) {
					printf("invalid\n");
					endLine();
					free(in);
					continue;
				}
			}
			free(in);
			in = getStr("Please enetr the username");
			if (in == NULL || cur[0] == '\0' || _c_ != '\n') { free(in); printf("invalid\n"); endLine(); continue; }
			char arg [300] = "." preAdd "/admin remove-user ";
			strcat(arg, cur); strcat(arg, " "); strcat(arg, in);
			free(in);
			if (!test) {
				fprintf(stderr, "Are you sure? [y/n]: ");
				_c_ = getchar();
				if (_c_ == 'n' || _c_ == 'N') {
					endLine();
					continue;
				} else if (_c_ != 'Y' && _c_ != 'y') {
					fprintf(stderr, "invalid\n");
					endLine();
					continue;
				}
			}
			system(arg);
		} else if (!strcmp(command, "deactive")) { //!
			free(command);
			char *in = NULL;
			if (test) {
				in = Split(':');
				if (in == NULL || strcmp(in, "user")) {
					free(in);
					printf("invalid\n");
					endLine();
					continue;
				}
				free(in);
			}
			in = getStr("Please enter the username");
			if (in == NULL || _c_ != '\n' || cur[0] == '\0') {
				printf("invalid\n");
				endLine();
				free(in);
				continue;
			}
			char arg [300] = "." preAdd "/admin deactive ";
			strcat(arg, cur); strcat(arg, " "); strcat(arg, in);
			free(in);
			system(arg);
		} else if (!strcmp(command, "register")) { //!
			char *fname = NULL;
			if (test) {
				fname = Split(':');
				if (fname == NULL || strcmp(fname, "name")) {
					printf("invalid\n");
					free(fname); free(command);
					endLine();
					continue;
				}
				free(fname);
			}
			fname = getStr("Please enter your first name");
			if (fname == NULL) {
				printf("invalid\n");
				free(fname); free(command);
				endLine();
				continue;
			}
			char *lname = NULL;
			if (test) {
				lname = Split(':');
				if (lname == NULL || strcmp(lname, "family")) {
					printf("invalid\n");
					free(fname); free(lname); free(command);
					endLine();
					continue;
				}
				free(lname);
			}
			lname = getStr("Please enter your last name");
			if (lname == NULL) {
				printf("invalid\n");
				free(fname); free(lname); free(command);
				endLine();
				continue;
			}
			char *username = NULL;
			if (test) {
				username = Split(':');
				if (username == NULL || strcmp(username, "user-id")) {
					printf("invalid\n");
					free(fname); free(lname); free(username); free(command);
					endLine();
					continue;
				}
				free(username);
			}
			username = getStr("Please enter your username");
			if (username == NULL) {
				printf("invalid\n");
				free(fname); free(lname); free(username); free(command);
				endLine();
				continue;
			}
			char *password = NULL;
			if (test) {
				password = Split(':');
				if (password == NULL || strcmp(password, "password")) {
					printf("invalid\n");
					free(fname); free(lname); free(username); free(password); free(command);
					endLine();
					continue;
				}
				free(password);
			}
			password = getStr("Please enter your password");
			if (password == NULL) {
				printf("invalid\n");
				free(fname); free(lname); free(username); free(password); free(command);
				endLine();
				continue;
			}
			char *nic = NULL;
			if (test) {
				nic = Split(':');
				if (nic == NULL || strcmp(nic, "national-id-code")) {
					printf("invalid\n");
					free(fname); free(lname); free(username); free(password); free(nic); free(command);
					endLine();
					continue;
				}
				free(nic);
			}
			nic = getStr("Please enter your national id code");
			if (nic == NULL) {
				printf("invalid\n");
				free(fname); free(lname); free(username); free(password); free(nic); free(command);
				endLine();
				continue;
			}
			char *bid = NULL;
			if (test) {
				bid = Split(':');
				if (bid == NULL || strcmp(bid, "birthdate")) {
					printf("invalid\n");
					free(fname); free(lname); free(username); free(password); free(nic); free(bid); free(command);
					endLine();
					continue;
				}
				free(bid);
			}
			bid = getStr("Please enter your birthdate");
			if (bid == NULL) {
				printf("invalid\n");
				free(fname); free(lname); free(username); free(password); free(nic); free(bid); free(command);
				endLine();
				continue;
			}
			char *gen = NULL;
			if (test) {
				gen = Split(':');
				if (gen == NULL || strcmp(gen, "gender")) {
					printf("invalid\n");
					free(fname); free(lname); free(username); free(password); free(nic); free(bid); free(gen);
					free(command);
					endLine();
					continue;
				}
				free(gen);
			}
			gen = getStr("Please enter your gender");
			if (gen == NULL) {
				printf("invalid\n");
				free(fname); free(lname); free(username); free(password); free(nic); free(bid); free(gen);
				free(command);
				endLine();
				continue;
			}
			char *tp = NULL;
			if (test) {
				tp = Split(':');
				if (tp == NULL || strcmp(tp, "type")) {
					printf("invalid\n");
					free(fname); free(lname); free(username); free(password); free(nic); free(bid); free(gen); free(tp);
					free(command);
					endLine();
					continue;
				}
				free(tp);
			}
			tp = getStr("Please enter user type [student/admin]");
			if (tp == NULL || _c_ != '\n') {
				printf("invalid\n");
				free(fname); free(lname); free(username); free(password); free(nic); free(bid); free(gen); free(tp);
				free(command);
				endLine();
				continue;
			}
			char arg [2000] = "." preAdd "/admin register ";
			if (cur[0] == '\0') strcat(arg, "!");
			else strcat(arg, cur);
			CAT(arg, fname); CAT(arg, lname); CAT(arg, username); CAT(arg, password);
			CAT(arg, nic); CAT(arg, bid); CAT(arg, gen); CAT(arg, tp);
			free(fname); free(lname); free(username); free(password); free(nic); free(bid); free(gen); free(tp);
			system(arg);
		} else if (!strcmp(command, "define-self")) { //!
			char *id;
			if (badBehavior(&id, "id", "Please enter self id")) {
				printf("invalid\n");
				free(command); free(id);
				endLine(); continue;
			}
			char *name;
			if (badBehavior(&name, "name", "Please enter self name")) {
				printf("invalid\n");
				free(command); free(id); free(name);
				endLine(); continue;
			}
			char *loc;
			if (badBehavior(&loc, "location", "Please enter self location")) {
				printf("invalid\n");
				free(command); free(id); free(name); free(loc);
				endLine(); continue;
			}
			char *cap;
			if (badBehavior(&cap, "capacity", "Please enter self capacity")) {
				printf("invalid\n");
				free(command); free(id); free(name); free(loc); free(cap);
				endLine(); continue;
			}
			char *tp;
			if (badBehavior(&tp, "type", "Please enter self type")) {
				printf("invalid\n");
				free(command); free(id); free(name); free(loc); free(cap); free(tp);
				endLine(); continue;
			}
			char *meal;
			if (badBehavior(&meal, "meal", "Please enter self meal [lunch/dinner/both]")) {
				printf("invalid\n");
				free(command); free(id); free(name); free(loc); free(cap); free(tp); free(meal);
				endLine(); continue;
			}
			if (!strcmp(meal, "both")) {
				char *lun;
				if (badBehavior(&lun, "lunch-time-limit", "Please enter self lunch time limit")) {
					printf("invalid\n");
					free(command); free(id); free(name); free(loc); free(cap); free(tp); free(meal); free(lun);
					endLine(); continue;
				}
				char *din;
				if (badBehavior(&din, "dinner-time-limit", "Please enter self dinner time limit")) {
					printf("invalid\n");
					free(command); free(id); free(name); free(loc); free(cap); free(tp); free(meal); free(lun); free(din);
					endLine(); continue;
				}
				if (_c_ != '\n' || cur[0] == '\0') {
					printf("invalid\n");
					free(command); free(id); free(name); free(loc); free(cap); free(tp); free(meal); free(lun); free(din);
					endLine(); continue;
				}
				char arg [2000] = "." preAdd "/self"; CAT(arg, command);
				CAT(arg, cur); CAT(arg, id); CAT(arg, name); CAT(arg, loc); CAT(arg, cap); CAT(arg, tp);
				CAT(arg, meal); CAT(arg, lun); CAT(arg, din);
				free(command); free(id); free(name); free(loc); free(cap); free(tp); free(meal); free(lun); free(din);
				system(arg);
			} else {
				char *lun;
				if (badBehavior(&lun, "lunch-time-limit", "Please enter self lunch time limit")) {
					printf("invalid\n");
					free(command); free(id); free(name); free(loc); free(cap); free(tp); free(meal); free(lun);
					endLine(); continue;
				}
				char *din;
				if (badBehavior(&din, "dinner-time-limit", "Please enter self dinner time limit")) {
					printf("invalid\n");
					free(command); free(id); free(name); free(loc); free(cap); free(tp); free(meal); free(lun); free(din);
					endLine(); continue;
				}
				if (_c_ != '\n' || cur[0] == '\0') {
					printf("invalid\n");
					free(command); free(id); free(name); free(loc); free(cap); free(tp); free(meal); free(lun); free(din);
					endLine(); continue;
				}
				char arg [2000] = "." preAdd "/self"; CAT(arg, command);
				CAT(arg, cur); CAT(arg, id); CAT(arg, name); CAT(arg, loc); CAT(arg, cap); CAT(arg, tp);
				CAT(arg, meal);
				if (!strcmp(meal, "lunch")) CAT(arg, lun);
				else CAT(arg, din);
				free(command); free(id); free(name); free(loc); free(cap); free(tp); free(meal); free(lun); free(din);
				system(arg);
			}
		} else if (!strcmp(command, "define-food")) { //!
			char *id;
			if (badBehavior(&id, "id", "Please enter food id")) {
				printf("invalid\n");
				free(command); free(id);
				endLine(); continue;
			}
			char *name;
			if (badBehavior(&name, "name", "Please enter food name")) {
				printf("invalid\n");
				free(command); free(id); free(name);
				endLine(); continue;
			}
			char *tp;
			if (badBehavior(&tp, "type", "Please enter food type")) {
				printf("invalid\n");
				free(command); free(id); free(name); free(tp);
				endLine(); continue;
			}
			char *prc;
			if (badBehavior(&prc, "price", "Please enter food price")) {
				printf("invalid\n");
				free(command); free(id); free(name); free(tp); free(prc);
				endLine(); continue;
			}
			if (_c_ != '\n' || cur[0] == '\0') {
				printf("invalid\n");
				free(command); free(id); free(name); free(tp); free(prc);
				endLine(); continue;
			}
			char arg [2000] = "." preAdd "/self"; CAT(arg, command);
			CAT(arg, cur); CAT (arg, id); CAT(arg, name); CAT(arg, tp); CAT(arg, prc);
			system(arg);
		} else if (!strcmp(command, "define-meal-plan")) { //!
			char *sid;
			if (badBehavior(&sid, "self-id", "Please enter the self id")) {
				printf("invalid\n");
				free(command); free(sid);
				endLine(); continue;
			}
			char *d;
			if (badBehavior(&d, "date", "Please enter the date")) {
				printf("invalid\n");
				free(command); free(sid); free(d);
				endLine(); continue;
			}
			char *tp;
			if (badBehavior(&tp, "type", "Please enter the type")) {
				printf("invalid\n");
				free(command); free(sid); free(d); free(tp);
				endLine(); continue;
			}
			char *fid;
			if (badBehavior(&fid, "food-id", "Please enter the food id")) {
				printf("invalid\n");
				free(command); free(sid); free(d); free(tp), free(fid);
				endLine(); continue;
			}
			char *cnt;
			if (badBehavior(&cnt, "count", "Please enter the amount")) {
				printf("invalid\n");
				free(command); free(sid); free(d); free(tp), free(fid); free(cnt);
				endLine(); continue;
			}
			if (_c_ != '\n' || cur[0] == '\0') {
				printf("invalid\n");
				free(command); free(sid); free(d); free(tp), free(fid); free(cnt);
				endLine(); continue;
			}
			char arg [2000] = "." preAdd "/self"; CAT(arg, command);
			CAT(arg, cur); CAT(arg, sid); CAT(arg, d); CAT(arg, tp); CAT(arg, fid); CAT(arg, cnt);
			system(arg);
		} else if (!strcmp(command, "charge-student-account")) { //!
			char *u;
			if (badBehavior(&u, "user", "Please enter the username")) {
				printf("invalid\n");
				free(command); free(u);
				endLine(); continue;
			}
			char *m;
			if (badBehavior(&m, "amount", "Please enter the amount")) {
				printf("invalid\n");
				free(command); free(u); free(m);
				endLine(); continue;
			}
			if (_c_ != '\n' || cur[0] == '\0') {
				printf("invalid\n");
				free(command); free(u); free(m);
				endLine(); continue;
			}
			char arg [1000] = "." preAdd "/admin"; CAT(arg, command);
			CAT(arg, cur); CAT(arg, u); CAT(arg, m);
			free(u); free(m);
			system(arg);
		} else if (!strcmp(command, "change-datetime")) { //!
			char *d;
			if (badBehavior(&d, "date", "Please enetr the date")) {
				printf("invalid\n");
				free(command); free(d);
				endLine(); continue;
			}
			char *t;
			if (badBehavior(&t, "time", "Please enetr the time")) {
				printf("invalid\n");
				free(command); free(d); free(t);
				endLine(); continue;
			}
			if (_c_ != '\n') {
				printf("invalid\n");
				free(command); free(d); free(t);
				endLine(); continue;
			}
			char arg [1000] = "." preAdd "/sys"; CAT(arg, command);
			CAT(arg, d); CAT(arg, t);
			system(arg);
		} else if (!strcmp(command, "reserve")) { //!
			char *sid;
			if (badBehavior(&sid, "self-id", "Please enter the self id")) {
				printf("invalid\n");
				free(command); free(sid);
				endLine(); continue;
			}
			char *d;
			if (badBehavior(&d, "date", "Please enter the date")) {
				printf("invalid\n");
				free(command); free(sid); free(d);
				endLine(); continue;
			}
			char *ml;
			if (badBehavior(&ml, "meal", "Please enter the meal type [lunch/dinner]")) {
				printf("invalid\n");
				free(command); free(sid); free(d); free(ml);
				endLine(); continue;
			}
			char *fid;
			if (badBehavior(&fid, "food-id", "Please enter the food id")) {
				printf("invalid\n");
				free(command); free(sid); free(d); free(ml); free(fid);
				endLine(); continue;
			}
			if (_c_ != '\n' || cur[0] == '\0') {
				printf("invalid\n");
				free(command); free(sid); free(d); free(ml); free(fid);
				endLine(); continue;
			}
			char arg [1000] = "." preAdd "/self"; CAT(arg, command);
			CAT(arg, cur); CAT(arg, sid); CAT(arg, d); CAT(arg, ml); CAT(arg, fid);
			system(arg);
		} else if (!strcmp(command, "self-status")) { //!
			free(command);
			if (_c_ != '\n' || cur[0] == '\0') {
				printf("invalid\n");
				continue;
			}
			User *u = findUser(cur);
			if (u == NULL || !u->online || !u->active || !u->privilege) {
				printf("premission denied\n");
				free(u);
				continue;
			}
			char *sid = getStr("self name");
			char *fid = getStr("food name");
			char *d = getStr("date");
			char *t = getStr("meal type");
			Plan p;
			strcat(p.self_id, sid); free(sid);
			strcat(p.food_id, fid); free(fid);
			p.d = convert_to_date(d); free(d);
			if (!strcmp(t, "lunch")) p.type = 0;
			else if (!strcmp(t, "dinner")) p.type = 1;
			else {
				free(t);
				fprintf(stderr, "not-found\n");
				continue;
			}
			free(t);
			Plan *P = findPlan(p);
			if (P == NULL) {
				fprintf(stderr, "not found\n");
				free(P);
				continue;
			}
			printf("reserved: %d  -  served: %d  -  rem: %d\n", P->rez, P->ate, P->cnt - P->ate);
			continue;
		} else if (!strcmp(command, "user-status")) { //!
			free(command);
			if (_c_ != '\n' || cur[0] == '\0') {
				printf("invalid\n");
				continue;
			}
			User *u = findUser(cur);
			if (u == NULL || !u->online || !u->active || !u->privilege) {
				printf("premission denied\n");
				free(u);
				continue;
			}
			char *name = getStr("Please enter username");
			free(u);
			u = findUser(name);
			free(name);
			if (u == NULL) {
				fprintf(stderr, "not found\n");
				continue;
			}
			char *sd = getStr("Please enter start date");
			char *fd = getStr("Please enter end date");
			date Sd = convert_to_date(sd); free(sd);
			date Fd = convert_to_date(fd); free(fd);
			char path [1000] = "../data/log"; strcat(path, u->username); strcat(path, "-log.bin");
			FILE *fin = fopen(path, "rb");
			assert(fin != NULL);
			for (Log l; fread(&l, sizeof(l), 1, fin);) if (dcmp(Sd, l.d) >= 0 && dcmp(Fd, l.d) <= 0)
				printf("> %s\n", l.report);
			fclose(fin);
			continue;
		} else if (!strcmp(command, "total-status")) { //!
			char *sd = getStr("Please enter start date");
			char *fd = getStr("Please enter end date");
			date Sd = convert_to_date(sd); free(sd);
			date Fd = convert_to_date(fd); free(fd);
			FILE *fin = fopen("../data/plan-list.bin", "rb");
			assert(fin != NULL);
			int fcost = 0, dcost = 0, rz = 0, at = 0;
			for (Plan p; fread(&p, sizeof(p), 1, fin);) if (dcmp(Sd, p.d) >= 0 && dcmp(Fd, p.d) <= 0) {
				Food *f = findFood(p.food_id);
				assert(f != NULL);
				rz += p.rez;
				at += p.ate;
				if (f->type) dcost += p.rez * f->price;
				else fcost += p.rez * f->price;
				free(f);
			}
			fclose(fin);
			printf("(total)  reserved:%d  ate:%d  food-cost:%d  dessert-cost:%d\n", rz, at, fcost, dcost);
			continue;
		} else if (!strcmp(command, "take-food")) { //!
			char *sid;
			if (badBehavior(&sid, "self-id", "Please enter the self id")) {
				printf("invalid\n");
				free(command); free(sid);
				endLine(); continue;
			}
			char *dt;
			if (badBehavior(&dt, "date", "Please enter the date")) {
				printf("invalid\n");
				free(command); free(sid); free(dt);
				endLine(); continue;
			}
			char *ml;
			if (badBehavior(&ml, "meal", "Please enter the meal")) {
				printf("invalid\n");
				free(command); free(sid); free(dt); free(ml);
				endLine(); continue;
			}
			if (_c_ != '\n' || cur[0] == '\0') {
				printf("invalid\n");
				free(command); free(sid); free(dt); free(ml);
				endLine(); continue;
			}
			char arg [1000]; sprintf(arg, "." preAdd "/self %s %s %s %s %s", command, cur, sid, dt, ml);
			system(arg);
		} else if (!strcmp(command, "charge-account")) { //!
			char *am;
			if (badBehavior(&am, "amount", "Please enter the amount")) {
				printf("invalid\n");
				free(command); free(am);
				endLine(); continue;
			}
			char *tmp;
			if (badBehavior(&tmp, "card-number", "Please enter your card number")) {
				printf("invalid\n");
				free(command); free(am); free(tmp);
				endLine(); continue;
			}
			free(tmp);
			if (badBehavior(&tmp, "pass-code", "Please enter your pass code")) {
				printf("invalid\n");
				free(command); free(am); free(tmp);
				endLine(); continue;
			}
			free(tmp);
			if (_c_ != '\n' || cur[0] == '\0') {
				printf("invalid\n");
				free(command); free(am);
				endLine(); continue;
			}
			char arg [1000]; sprintf(arg, "." preAdd "/admin %s %s %s", command, cur, am);
			free(command); free(am);
			system(arg);
		} else if (!strcmp(command, "add-news")) { //!
			char *title;
			if (badBehavior(&title, "title", "Please enter the title")) {
				printf("invalid\n");
				free(command); free(title);
				endLine(); continue;
			}
			char *content;
			if (badBehavior(&content, "content", "Please enter the content")) {
				printf("invalid\n");
				free(command); free(title); free(content);
				endLine(); continue;
			}
			char *ed;
			if (badBehavior(&ed, "end-date", "Please enter the end date")) {
				printf("invalid\n");
				free(command); free(title); free(content); free(ed);
				endLine(); continue;
			}
			if (_c_ != '\n' || cur[0] == '\0') {
				printf("invalid\n");
				free(command); free(title); free(content); free(ed);
				endLine(); continue;
			}
			char arg [1000]; sprintf(arg, "." preAdd "/sys %s %s %s %s %s", command, cur, title, content, ed);
			system(arg);
		} else if (!strcmp(command, "check-news")) { //!
			if (_c_ != '\n' || cur[0] == '\0') {
				printf("invalid1 %c %s\n", _c_, cur);
				free(command);
				endLine(); continue;
			}
			char arg [1000]; sprintf(arg, "." preAdd "/sys %s %s", command, cur);
			system(arg);
		} else if (!strcmp(command, "show-my-plan")) { //!
			free(command);
			if (cur[0] == '\0') {
				printf("Please login first, try later\n");
				endLine(); continue;
			}
			char path [200]; sprintf(path, "data/log/%s-log.bin", cur);
			FILE *fin = fopen(path, "rb");
			for (Log l; fread(&l, sizeof(l), 1, fin);) if (strstr(l.report, "reserve") != NULL) {
				Plan *p = findPlanById(strstr(l.report, "id:") + 4);
				if (dcmp(rnow(), p->d) > 0) printf("%s\n", l.report);
				free(p);
			}
			fclose(fin);
		} else if (!strcmp(command, "cancel-reserve")) { //!
			char *d;
			if (badBehavior(&d, "date", "Please enter the date")) {
				printf("invalid\n");
				free(command); free(d);
				endLine(); continue;
			}
			char *ml;
			if (badBehavior(&ml, "meal", "Please enter the meal")) {
				printf("invalid\n");
				free(command); free(d); free(ml);
				endLine(); continue;
			}
			if (_c_ != '\n' || cur[0] == '\0') {
				printf("invalid\n");
				free(command); free(d); free(ml);
				endLine(); continue;
			}
			char arg [1000]; sprintf(arg, "." preAdd "/self %s %s %s %s", command, cur, d, ml);
			system(arg);
		} else {
			printf("invalid\n");
			endLine(); continue;
		}

		FILE *fp;
		if (test) fp = fopen("data/IPC.txt", "r");
		else fp = fopen("../data/IPC.txt", "r");
		fscanf(fp, "%s", resualt); fclose(fp);
		printf("%s\n", resualt);
	}

	return 0;
}
/*

*/