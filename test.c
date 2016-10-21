/*
 * test.c - ONLY FOR TESTING PURPOSES
 */

#include <stdio.h>
#include <stdlib.h>

#include "calendar.h"

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

int main(void)
{
	struct entry *entry = mkentry(2016, 10, 19, 9, 30, "haha lol");
	
	printf("%d\n\n", print_entry(entry));
	
	int conf_status = load_conf();
	printf("load_conf() return value: %d\n", conf_status);
	if (conf_status == 0)
		printf("init status: %d\n", initialize_file(NULL, "ab"));
		
	printf("dadd status: %d\n", dadd(entry));
	finalize_file();
	
	struct entry *loaded = malloc(sizeof(struct entry));
	if (conf_status == 0)
		printf("init status: %d\n", initialize_file(NULL, "rb"));
	
	printf("dload status: %d\n", dload(loaded));
	printf("loaded: %p\n", loaded);
	print_entry(loaded);
	finalize_file();
	
	return 0;
}
