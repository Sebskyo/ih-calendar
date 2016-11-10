/*
 * Calendar - Simple CLI calendar program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calendar.h"

// taken from test.c TODO: delet this
int print_entry(struct entry *e)
{
	if (e == NULL) return -1;
	
	printf(
		"%2d/%2d/%4d %02d:%02d\n%s\n",
		e->day,
		e->month,
		e->year,
		e->hour,
		e->minute,
		e->info
	);
	
	return 0;
}

int print_month(int argc, char **argv)
{
	if (argc < 2) return 1;
	if (initialize_file(NULL, "rb") != 0) return -1;
	
	// argument parsing
	int year = atoi(argv[0]);
	int month = atoi(argv[1]);
	
	// setup
	int day = first_day(year, month);
	if (day == 7) return 2;
	int monthlen;
	if ((monthlen = get_monthlen(month, check_leap(year))) == 0) return 3;
	struct node *root = NULL;
	
	// finding days with entries in month
	fbym(&root, year, month);
	int dwe[32] = {0}; // days with entries
	struct node *node;
	for (node = root; node != NULL; node = node->next) {
		dwe[node->entry.day] = 1;
	}
	
	// printing
	printf("\nMo Tu We Th Fr Sa Su\n");
	int i;
	for (i = 0; i < day; i++) {
		printf("   ");
	}
	for (i = 1; i <= monthlen; i++) {
		if (dwe[i]) printf("\x1B[7m");
		printf("%2d\x1B[0m%c", i, (i+day)%7!=0?' ':'\n');
	}
	printf("\n\n");
	return 0;
}

int add_entry(int argc, char **argv)
{
	if (argc < 4) return 1;
	
	if (initialize_file(NULL, "ab") != 0) return -1;
	
	int time_included = argc >= 6;
	
	// TODO: make sanity checks
	int year, month, day, hour, minute;
	year = atoi(argv[0]);
	month = atoi(argv[1]);
	day = atoi(argv[2]);
	
	hour	=	time_included ? atoi(argv[3]) : -1;
	minute	=	time_included ? atoi(argv[4]) : -1;
	
	char *info = argv[time_included ? 5 : 3];
	
	struct entry *entry = mkentry(year, month, day, hour, minute, info);
	print_entry(entry);
	return dadd(entry);
}

int read_all(int argc, char **argv)
{
	if (initialize_file(NULL, "rb") != 0) return -1;
	
	struct node *root = NULL;
	struct node *node;
	struct entry e;
	if (dloada(&root) != 0) return 1;
	
	for (node = root; node != NULL; node = node->next) {
		e = node->entry;
		printf("== \"%s\" ==\n", e.info);
		printf("%d/%d/%d\n", e.year, e.month, e.day);
		printf("%d:%d\n", e.hour, e.minute);
		printf("\n");
	}
	
	return 0;
}

int main(int argc, char **argv)
{
	if (argc < 2) return 1;
	
	int conf_status = load_conf();
	if (conf_status != 0) return 2;
	
	int status = 0;
	// TODO: move returns around and do some closing and stuff
	if (strcmp(argv[1], "print") == 0) {
		status = print_month(argc-2, argv+2);
	}
	if (strcmp(argv[1], "add") == 0) {
		status = add_entry(argc-2, argv+2);
	}
	if (strcmp(argv[1], "list") == 0) {
		status = read_all(argc-2, argv+2);
	}
	finalize_file();
	return status;
}
