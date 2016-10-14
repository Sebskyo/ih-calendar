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
	
	printf("%d\n\n", print_entry(entry));
	
	int conf_status = load_conf();
	printf("load_conf() return value: %d\n", conf_status);
	if (conf_status == 0)
		printf("init status: %d\n", initialize_file(NULL, "a"));
		
	//fadd(entry);
	
	need_a_close_func();
	return 0;
}
