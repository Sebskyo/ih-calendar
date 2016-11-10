/*
 * data.c
 * Functions related to data structures
 */

#include <stdio.h>
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

struct entry entrycmp(struct entry *e1, struct entry *e2)
{
	struct entry r;
	r.year = e1->year - e2->year;
	r.month = e1->month - e2->month;
	r.day = e1->day - e2->day;
	r.hour =
		e1->hour == -1 || e2->hour == -1 ? 0 : e1->hour - e2->hour;
	r.minute =
		e1->minute == -1 || e2->minute == -1 ? 0 : e1->minute - e2->minute;
	sprintf(r.info, "%d", strcmp(e1->info, e2->info)); // TODO: this seems OTT
	
	return r;
}

struct node *mknode(struct entry entry)
{
	struct node *node = malloc(sizeof(struct node));
	node->entry = entry;
	node->next = NULL;
	return node;
}

int listadd(struct node *node, struct entry entry)
{
	while (node->next != NULL)
		node = node->next;
	
	struct node *new = mknode(entry);
	node->next = new;
	
	return 0;
}

int fbym(struct node **root, int year, int month)
{
	struct entry *base = mkentry(year, month, 0, 0, 0, "\0");
	struct entry *e = malloc(sizeof(struct entry));
	struct entry cmpr;
	
	int status = 0;
	while ((status = dload(e)) == 0) {
		if ((cmpr = entrycmp(base, e)).month == 0 && cmpr.year == 0) {
			if (*root == NULL) {
				*root = mknode(*e);
			}
			else {
				listadd(*root, *e);
			}
		}
	}
	return 0;
}
