/*
 * file.c
 * Functions for file interaction and parsing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calendar.h"
#include "config.h"

#define MAXLINELEN	1024
#define MAXKEYLEN	64
#define MAXVALLEN	959
//#define MAXVALLEN	(MAXLINELEN - MAXKEYLEN - 1)

FILE *fp = NULL;
char *data_filename;

/*int getline(char *buffer, FILE *fp, int max) // does not include '\n'
{
	int c;
	int i = 0;
	while (--max && (c = fgetc(fp)) != EOF && c != '\n')
		buffer[i++] = c;
	buffer[i] = '\0';
	
	return c == EOF;
}*/

int load_conf()
{
	char *conf_lctn;
	FILE *conf;
	conf_lctn = getenv("ih_calendar_conf_lctn");
	if (conf_lctn == NULL) {
		char *home = getenv("HOME");
		const char *lcnt_const = "/.config/ih_calendar";
		int len;
		len = strlen(home) + strlen(lcnt_const) + 1; // includes space for '\0'
		conf_lctn = malloc(sizeof(char) * len);
		memset(conf_lctn, '\0', len);
		strcpy(conf_lctn, home);
		strcat(conf_lctn, lcnt_const);
	}
	printf("file.c:load_conf():%s\n", conf_lctn);
	conf = fopen(conf_lctn, "r");
	if (conf == NULL) return 1;
	
	char *buffer = malloc(sizeof(char) * MAXLINELEN);
	memset(buffer, '\0', MAXLINELEN);
	while(1)
	{
		//int status = getline(buffer, conf, MAXLINELEN);
		char *status = fgets(buffer, MAXLINELEN, conf);
		if (status == NULL)
			break;
		int i, c;
		/*char key[MAXKEYLEN], value[MAXVALLEN]; // TODO: change this
		memset(key, '\0', MAXKEYLEN);
		memset(value, '\0', MAXVALLEN);*/
		char key[MAXKEYLEN] = {'\0'};
		char value[MAXVALLEN] = {'\0'};
		int kp, vp; // position in key/value arrays
		kp = 0;
		vp = 0;
		int is_key_got = 0;
		for (i = 0; i < MAXLINELEN-1 && (c = buffer[i]) != '\0'; i++) {
			if (!is_key_got && c == '=') {
				is_key_got = 1;
			}
			else if (!is_key_got && kp < MAXKEYLEN-1) {
				key[kp++] = c;
			}
			else if (is_key_got && vp < MAXVALLEN-1) {
				value[vp++] = c;
			}
			else {
				break;
				//return 2; // couldn't parse config
			}
		}
		
		printf("k:\"%s\" | v:\"%s\"\n", key, value);
		
		if (strcmp(key, "data_file_lctn")) {
			data_filename = malloc(sizeof(char) * strlen(value)+1);
			strcpy(data_filename, value);
			printf("lcnt: \"%s\"\n", value);
		}
	}
	
	return 0;
}

int initialize_file(char *filename, char *mode)
{
	int use_default = 0;
	if (filename == NULL) use_default = 1;
	printf("%d\n", use_default);
	printf("%s\n", data_filename);
	fp = fopen(use_default ? data_filename : filename, mode);
	return fp == NULL ? -1 : 0;
}

int fadd(struct entry *entry)
{
	if (fp == NULL || entry == NULL) return 1;
	
	fprintf(
		fp,
		"%d,%d,%d,%d,%d,\"%s\";\n",
		entry->date->year,
		entry->date->month,
		entry->date->day,
		entry->clock == NULL ? -1 : entry->clock->hour,
		entry->clock == NULL ? -1 : entry->clock->minute,
		entry->info
	);
	
	return 0;
}
