/*
 * calendar.h
 * Contains struct and definitions for the entire program.
 */

#ifndef IH_CALENDAR_CALENDAR_H
#define IH_CALENDAR_CALENDAR_H

// filename TODO: change this
#define DATAFILE caldata.cld

// data structures
struct date {
	unsigned int year;
	unsigned int month;
	unsigned int day;
};
struct clock {
	unsigned int hour;
	unsigned int minute;
};
struct entry {
	struct date *date;
	struct clock *clock;
	char *info;
};
struct node {
	struct entry *entry;
	struct node *next;
};

// make structures
struct date *mkdate(unsigned int, unsigned int, unsigned int);
struct clock *mkclock(unsigned int, unsigned int);
struct entry *mkentry(struct date *, struct clock *, char *);
struct node *mknode(struct entry *);
int *listadd(struct node *, struct entry *);

// calendar functions
int first_day(int, int);
int check_leap(int);
int count_leaps(int, int);
int get_monthlen(int, int);

// file interaction
int load_conf();
int initialize_file(char *, char*);
int need_a_close_func();
int fadd(struct entry *);

#endif // IH_CALENDAR_CALENDAR_H
