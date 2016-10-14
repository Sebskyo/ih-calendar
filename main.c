/*
 * Calendar - Simple CLI calendar program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calendar.h"

int print_month(int argc, char **argv)
{
	if (argc < 2) return 1;
	
	// argument parsing
	int year = atoi(argv[0]);
	int month = atoi(argv[1]);
	
	// setup
	int day = first_day(year, month);
	if (day == 7) return 1;
	int monthlen;
	if ((monthlen = get_monthlen(month, check_leap(year))) == 0) return 1;
	
	// printing
	printf("\nMo Tu We Th Fr Sa Su\n");
	int i;
	for (i = 0; i < day; i++) {
		printf("   ");
	}
	for (i = 1; i <= monthlen; i++) {
		printf("%2d%c", i, (i+day)%7!=0?' ':'\n');
	}
	printf("\n\n");
	return 0;
}

int add_entry(int argc, char **argv)
{
	if (argc < 4) return 1;
	
	int time_included = argc >= 6;
	
	// TODO: make sanity checks
	unsigned int year, month, day, hour, minute;
	year = atoi(argv[0]);
	month = atoi(argv[1]);
	day = atoi(argv[2]);
	
	if (time_included) {
		hour = atoi(argv[3]);
		minute = atoi(argv[4]);
	}
	
	char *info = argv[time_included ? 5 : 3];
	
	struct date *date = mkdate(year, month, day);
	struct clock *clock = NULL;
	if (time_included)
		clock = mkclock(hour, minute);
	struct entry *entry = mkentry(date, clock, info);
	
	return 0;
}

int main(int argc, char **argv)
{
	if (argc < 2) return 1;
	
	load_conf();
	
	// TODO: move returns around and do some closing and stuff
	if (strcmp(argv[1], "print") == 0) {
		return print_month(argc-2, argv+2);
	}
	if (strcmp(argv[1], "add") == 0) {
		initialize_file("testdata", "a");
		return add_entry(argc-2, argv+2);
	}
	return -1;
}
