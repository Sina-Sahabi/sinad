#ifndef D5999B97_0277_458B_BD25_B4CA85466069
#define D5999B97_0277_458B_BD25_B4CA85466069

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef Test
#define __preAdd ""
#else
#define __preAdd "../"
#endif

typedef struct {
	time_t t;
	int h, min;
} TiMe;

typedef struct {
	int year, month, day;
	TiMe T;
} date;

int Dcmp (date x, date y) { return (x.year == y.year && x.month == y.month && x.day == y.day); }

date convert_to_date (char *s) {
	date d, bad = {-1, -1, -1};
	if (sscanf(s, "%d-%d-%d", &(d.year), &(d.month), &(d.day)) != 3) { return bad; }
	return d;
}

TiMe convert_to_time (char *s, time_t rt) {
	TiMe t = {rt, -1, -1};
	int x;
	if (!sscanf(s, "%d", &x)) return t;
	if (strlen(s) != 4 || x / 100 >= 24 || (x % 100) >= 60) return t;
	t.h = x / 100; t.min = x % 100;
	return t;
}

int checkdate (date d) {
	return (0 <= d.year && 0 < d.month && d.month < 13 && 0 < d.day && d.day < 31);
}

void _ok (date *x) {
	x->T.h += x->T.min / 60,	x->T.min %= 60;
	x->day += x->T.h / 24,		x->T.h %= 24;
	x->month += x->day / 30,	x->day %= 30;
	x->year += x->month / 12,	x->month %= 12;
}

date rnow () {
	date old;
	FILE *fp = fopen(__preAdd "data/datetime.bin", "rb");
	assert(fp != NULL);
	fread(&old, sizeof(old), 1, fp); fclose(fp);
	date n = old;
	time_t sec = (n.T.t = time(NULL)) - old.T.t;
	n.T.min += sec / 60;
	_ok(&n);
	return n;
}

date delta (date x, date y) {
	date ret = {x.year - y.year, x.month - y.month, x.day - y.day, {x.T.h - y.T.h, x.T.min - y.T.min, 0}};
	if (ret.month < 0) ret.year--, ret.month += 12;
	if (ret.day < 0) ret.month--, ret.day += 30;
	if (ret.T.h < 0) ret.day--, ret.T.h += 24;
	if (ret.T.min < 0) ret.T.h--, ret.T.min += 60;
	return ret;
}

int dcmp (date x, date y) { // <
	if (Dcmp(x, y)) return 0;
	if (x.year < y.year || x.month < y.month || x.day < y.day) return 1;
	return -1;
}

#endif /* D5999B97_0277_458B_BD25_B4CA85466069 */
