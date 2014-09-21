#include "common_string.h"

int split_words(char *buf, char *words[]) {
// 	printf("buf: %s\n", buf);
	char *split_words_tmp_str;
	int i, j, k, changed;
	j = 0;
	k = 0;
	changed = 0;
	if ((split_words_tmp_str = malloc(BUFSIZ)) == NULL) {
		return -1;
	}
// 	for (i = 0; i<sizeof(split_words_buf) && *(buf + i) != '\0'; i++) {
	for (i = 0; i<strlen(buf) && *(buf + i) != '\0'; i++) {
// 		printf("i: %d\n", i);
// 		printf("split_words_buf[%d]: %c\n", i, *(buf + i));
		while (*(buf + i) != ' ' && *(buf + i) != '\n' && *(buf + i) != '\0') {
// 			printf("split_words_buf[%d]: %c\n", i, *(buf + i));
			*(split_words_tmp_str + j) = *(buf + i);
// 			printf("split_words_tmp_str[%d]: %c\n", j, split_words_tmp_str[j]);
			i++;
			j++;
			changed = 1;
		}
		if (changed != 0) {
// 			printf("changed: %d\n", changed);
			if ((words[k] = malloc(strlen(split_words_tmp_str) + 1)) == NULL) {
				perror(NULL);
				free(split_words_tmp_str);
				return k;
			}
// 			printf("malloc for words[%d]\n", k);
			*(split_words_tmp_str + j) = '\0';
			memset (words[k], '\0', (strlen(split_words_tmp_str) + 1));
// 			printf("split_words_tmp_str: %s\n", split_words_tmp_str);
			strcpy(words[k], split_words_tmp_str);
// 			printf("words[%d]: %s\n", k, words[k]);
			memset (split_words_tmp_str, '\0', BUFSIZ);
			j = 0;
			k++;
			changed = 0;
		}
	}
	free(split_words_tmp_str);
// 	printf("split_words finished\n");
	return k;
}

int split_lines(char *buf, char *lines[]) {
// 	printf("buf: %s\n", buf);
	char *split_lines_tmp_str;
	int i, j, k, changed;
	j = 0;
	k = 0;
	changed = 0;
	if ((split_lines_tmp_str = malloc(BUFSIZ)) == NULL) {
		return -1;
	}
// 	for (i = 0; i<sizeof(split_lines_buf) && *(buf + i) != '\0'; i++) {
	for (i = 0; i<strlen(buf) && *(buf + i) != '\0'; i++) {
// 		printf("i: %d\n", i);
// 		printf("split_lines_buf[%d]: %c\n", i, *(buf + i));
		while ( *(buf + i) != '\n' && *(buf + i) != '\0') {
// 			printf("split_lines_buf[%d]: %c\n", i, *(buf + i));
			*(split_lines_tmp_str + j) = *(buf + i);
// 			printf("split_lines_tmp_str[%d]: %c\n", j, split_lines_tmp_str[j]);
			i++;
			j++;
			changed = 1;
		}
		if (changed != 0) {
// 			printf("changed: %d\n", changed);
			if ((lines[k] = malloc(strlen(split_lines_tmp_str) + 1)) == NULL) {
				printf("error: malloc for lines[%d] failed\n", k);
				free(split_lines_tmp_str);
				return k;
			}
// 			printf("malloc for lines[%d]\n", k);
			*(split_lines_tmp_str + j) = '\0';
			memset (lines[k], '\0', (strlen(split_lines_tmp_str) + 1));
// 			printf("split_lines_tmp_str: %s\n", split_lines_tmp_str);
			strcpy(lines[k], split_lines_tmp_str);
// 			printf("lines[%d]: %s\n", k, lines[k]);
			memset (split_lines_tmp_str, '\0', BUFSIZ);
			j = 0;
			k++;
			changed = 0;
		}
	}
	free(split_lines_tmp_str);
// 	printf("split_lines finished\n");
	return k;
}

int config_split_words(char *buf, char *words[]) {
// 	printf("buf: %s\n", buf);
	char *split_words_tmp_str;
	int i, j, k, changed;
	j = 0;
	k = 0;
	changed = 0;
	if ((split_words_tmp_str = malloc(BUFSIZ)) == NULL) {
		return -1;
	}
// 	for (i = 0; i<sizeof(split_words_buf) && *(buf + i) != '\0'; i++) {
	for (i = 0; i<strlen(buf) && *(buf + i) != '\0'; i++) {
// 		printf("i: %d\n", i);
// 		printf("split_words_buf[%d]: %c\n", i, *(buf + i));
		while (*(buf + i) != ' ' && *(buf + i) != '\n' && *(buf + i) != '\0' && *(buf + i) != ':') {
// 			printf("split_words_buf[%d]: %c\n", i, *(buf + i));
			*(split_words_tmp_str + j) = *(buf + i);
// 			printf("split_words_tmp_str[%d]: %c\n", j, split_words_tmp_str[j]);
			i++;
			j++;
			changed = 1;
		}
		if (changed != 0) {
// 			printf("changed: %d\n", changed);
			if ((words[k] = malloc(strlen(split_words_tmp_str) + 1)) == NULL) {
				printf("error: malloc for words[%d] failed\n", k);
				free(split_words_tmp_str);
				return k;
			}
// 			printf("malloc for words[%d]\n", k);
			*(split_words_tmp_str + j) = '\0';
			memset (words[k], '\0', (strlen(split_words_tmp_str) + 1));
// 			printf("split_words_tmp_str: %s\n", split_words_tmp_str);
			strcpy(words[k], split_words_tmp_str);
// 			printf("words[%d]: %s\n", k, words[k]);
			memset (split_words_tmp_str, '\0', BUFSIZ);
			j = 0;
			k++;
			changed = 0;
		}
	}
	free(split_words_tmp_str);
// 	printf("split_words finished\n");
	return k;
}