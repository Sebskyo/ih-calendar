/*
 * test.c - ONLY FOR TESTING PURPOSES
 */

#include <stdio.h>

#include "calendar.h"

int print_entry(struct entry *e)
{
	if (e == NULL) return -1;
	
	printf(
		"%2d/%2d/%4d %02d:%02d\n%s\n",
		e->date->day,
		e->date->month,
		e->date->year,
		e->clock->hour,
		e->clock->minute,
		e->info
	);
	
	return 0;
}

int main(void)
{
	struct date *date = mkdate(2016, 10, 19);
	struct clock *clock = mkclock(9, 30);
	struct entry *entry = mkentry(date, clock, "haha lol");
	
	printf("%d,%d,%d\n", date == NULL, clock == NULL, entry == NULL);
	
	printf("%d\n", print_entry(entry));
	printf("test.c:main():%d\n", load_conf());
	initialize_file(NULL, "a");
	
	fadd(entry);
	
	return 0;
}
