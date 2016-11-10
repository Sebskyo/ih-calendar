/*
 * calendar.h
 * Contains struct and definitions for the entire program.
 */

#ifndef IH_CALENDAR_CALENDAR_H
#define IH_CALENDAR_CALENDAR_H

#define MAXINFO 1000

// data structures
struct entry {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	char info[MAXINFO];
};
struct node {
	struct entry entry;
	struct node *next;
};

// data processing
struct entry *mkentry(int, int, int, int, int, char *);
struct entry entrycmp(struct entry *, struct entry *);
struct node *mknode(struct entry);
int listadd(struct node *, struct entry);
int fbym(struct node **, int, int);

// calendar functions
int first_day(int, int);
int check_leap(int);
int count_leaps(int, int);
int get_monthlen(int, int);

// file interaction
int load_conf();
int initialize_file(char *, char*);
int finalize_file();
int dadd(struct entry *);
int dload(struct entry *);
int dloada(struct node **root);

#endif // IH_CALENDAR_CALENDAR_H
