#ifndef COMMON_STRING_H
#define COMMON_STRING_H

#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int split_words(char *buf, char *words[]);
int split_lines(char *buf, char *lines[]);
int config_split_words(char *buf, char *words[]);

#endif