/*
 * file.c
 * Functions for file interaction and parsing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calendar.h"

#define MAXLINELEN	1024
#define MAXKEYLEN	64
#define MAXVALLEN	(MAXLINELEN - MAXKEYLEN - 1)

FILE *fp = NULL;
char *data_filename;

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
	conf = fopen(conf_lctn, "r");
	if (conf == NULL) return 1;
	
	char *buffer = malloc(sizeof(char) * MAXLINELEN);
	memset(buffer, '\0', MAXLINELEN);
	while (1)
	{
		char *status = fgets(buffer, MAXLINELEN, conf);
		if (status == NULL)
			break;
		int i, c;
		char key[MAXKEYLEN] = {'\0'};
		char value[MAXVALLEN] = {'\0'};
		int kp, vp; // position in key/value arrays
		kp = 0;
		vp = 0;
		int is_key_got = 0;
		for (i = 0; i < MAXLINELEN-1 && (c = buffer[i]) != '\0' && c != '\n'; i++) {
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
			}
		}
		
		if (strcmp(key, "data_file_lctn") == 0) {
			data_filename = malloc(sizeof(char) * strlen(value)+1);
			strcpy(data_filename, value);
		}
	}
	return 0;
}

int initialize_file(char *filename, char *mode)
{
	int use_default = 0;
	if (filename == NULL) use_default = 1;
	fp = fopen(use_default ? data_filename : filename, mode);
	return fp == NULL ? -1 : 0;
}

int finalize_file()
{
	// TODO: do proper return values
	if (fp)
		fclose(fp);
	return 0;
}

int dadd(struct entry *entry)
{
	if (fp == NULL || entry == NULL) return 1;
	int status = fwrite(entry, sizeof(struct entry), 1, fp);
	return status < 1 ? 2 : 0;
}

int dload(struct entry *entry)
{
	if (fp == NULL) return 1;
	
	int status = fread(entry, sizeof(struct entry), 1, fp);
	return status == 1 ? 0 : -1; // TODO: proper error handling
}

int dloada(struct node **root)
{
	if (fp == NULL) return 1;
	
	struct entry *entry = malloc(sizeof(struct entry));
	
	int status = dload(entry);
	if (status != 0) return 2;
	*root = mknode(*entry);
	
	while ((status = dload(entry)) == 0) {
		listadd(*root, *entry);
	}
	
	return 0;
}
