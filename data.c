/*
 * data.c
 * Functions related to data structures
 */

#include <stdlib.h>

#include "calendar.h"

struct date *mkdate(unsigned int year, unsigned int month, unsigned int day)
{
	if (day > 31 || month > 12) return NULL;
	struct date *date = malloc(sizeof(struct date));
	date->year = year;
	date->month = month;
	date->day = day;
	return date;
}

struct clock *mkclock(unsigned int hour, unsigned int minute)
{
	if (hour > 23 || minute > 59) return NULL;
	struct clock *clock = malloc(sizeof(struct clock));
	clock->hour = hour;
	clock->minute = minute;
	return clock;
}

struct entry *mkentry(struct date *date, struct clock *clock, char *info)
{
	if(date == NULL || info == NULL) return NULL;
	struct entry *entry = malloc(sizeof(struct entry));
	entry->date = date;
	entry->clock = clock;
	entry->info = info;
	return entry;
}

struct node *mknode(struct entry *entry)
{
	struct node *node = malloc(sizeof(struct node));
	node->entry = entry;
	node->next = NULL;
	return node;
}

int *listadd(struct node *node, struct entry *entry)
{
	while (node->next != NULL)
		node = node->next;
	
	struct node *new = mknode(entry);
	node->next = new;
	
	return 0;
}
