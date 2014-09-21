#ifndef COMMON_CONFIG_H
#define COMMON_CONFIG_H

#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include "common_string.h"

typedef int bool;
#define TRUE 1
#define FALSE 0

bool TABLE_LIGHT;
bool STAIR_LIGHT;
bool BED_LIGHT;
bool BED_FAN;
bool CAMERA;

bool AUTO_ALL;
bool AUTO_NONE;
bool AUTO_TABLE_LIGHT;
bool AUTO_BED_LIGHT;
bool AUTO_STAIR_LIGHT;
bool AUTO_BED_FAN;
bool AUTO_CAMERA;
/*
int DELAY_ALL;
int DELAY_NONE;
int DELAY_TABLE_LIGHT;
int DELAY_STAIR_LIGHT;
int DELAY_BED_LIGHT;
int DELAY_BED_FAN;

int TIMES_ALL;
int TIMES_TABLE_LIGHT;
int TIMES_STAIR_LIGHT;
int TIMES_BED_LIGHT;
int TIME_BED_FAN;*/

bool WIFI_IDENTIFY;
#define max_mac 10
char *macs[max_mac];


int save_config(char *path);
int load_config(char *path);
int config_get_playmode_str(char *mode_str);
int analy_config_raspi_server();
int word_is_option(char *word);
int config_format_line_and_save(char *line);
int config_format_play_mode(char *mode_str);
int config_format_music_path(char *words[], int words_num, int start_iter);
int split_lines_from_file(char *path, char *lines[]);


#endif