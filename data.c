/*
 * data.c
 * Functions related to data structures
 */

#include <stdlib.h>
#include <string.h>

#include "calendar.h"

struct entry *mkentry(int year, int month, int day, int hour, int minute, char *info)
{
	if(!info) return NULL;
	struct entry *entry = malloc(sizeof(struct entry));
	entry->year = year;
	entry->month = month;
	entry->day = day;
	entry->hour = hour;
	entry->minute = minute;
	strncpy(entry->info, info, MAXINFO);
	return entry;
}

struct node *mknode(struct entry entry)
{
	struct node *node = malloc(sizeof(struct node));
	node->entry = entry;
	node->next = NULL;
	return node;
}

int *listadd(struct node *node, struct entry entry)
{
	while (node->next != NULL)
		node = node->next;
	
	struct node *new = mknode(entry);
	node->next = new;
	
	return 0;
}
