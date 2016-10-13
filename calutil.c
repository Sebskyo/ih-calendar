/*
 * calutil.c
 * Utility functions for working with the clusterfuck
 * known as the Gregorian Calendar.
 */

#include "calendar.h"

int reference = 5; // Sa 1st Jan 2000
int day_offset[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

// https://cs.uwaterloo.ca/~alopez-o/math-faq/node73.html
int first_day(int year, int month)
{
	if (year < 2000 || month < 1 || month > 12) return 7;
	int day = reference;
	int leaps = count_leaps(2000, year);
	leaps -= month < 3 ? 1 : 0;
	day = (day+(year-2000)+leaps+day_offset[month-1])%7;
	return day;
}

int check_leap(int year)
{
	return year%4 == 0 ? year%100 == 0 ? year%400 == 0 ? 1 : 0 : 1 : 0;
}

int count_leaps(int first, int last)
{
	for (; first < first+4; first++) {
		if (check_leap(first)) break;
	}
	int count = 0;
	int i;
	for (i = first; i <= last; i += 4) {
		if (check_leap(i)) count++;
	}
	return count;
}

int get_monthlen(int month, int isleap) // 1=JAN, 2=FEB, etc.
{
	if (month > 12) return 0;
	int monthlen;
	if (month < 8) {
		monthlen =
		  month == 2 ? isleap ? 29 : 28 : month%2 == 0 ? 30 : 31;
	} else {
		monthlen = month%2 == 0 ? 31 : 30;
	}
	return monthlen;
}
