#include "config.h"

int save_config(char *path) {

// 	printf("SOCKET_PORT: %d\n", cur_config_raspi_server.socket_port);
// 	fprintf(file, "SOCKET_PORT: %d\n", cur_config_raspi_server.socket_port);
// 	printf("MUSIC_PATH: %s\n", cur_config_raspi_server.music_path);
// 	fprintf(file, "MUSIC_PATH: %s\n", cur_config_raspi_server.music_path);
// 	printf("PLAY_MODE: %d\n", cur_config_raspi_server.play_mode);
// 	fprintf(file, "PLAY_MODE: %d\n", cur_config_raspi_server.play_mode);
// 	printf("PLAY_ITER: %d\n", cur_config_raspi_server.play_iter);
// 	fprintf(file, "PLAY_ITER: %d\n", cur_config_raspi_server.play_iter);
// 	printf("config saved\n");

	return 0;
}

int load_config(char *path) {
	int lines_num;
	char *lines[1024];
	int i ;
	lines_num = split_lines_from_file(path, lines);
	for (i = 0; i < lines_num; i++) {
// 		printf("formatting: %s\n", config_lines[i]);
// 		config_format_line_and_save(lines[i]);
// 		free(config_lines[i]);
// 		printf("fred: %s\n", config_lines[i]);
		printf("line %d: %s\n", i, lines[i]);
	}
	return 0;
}
/*
int config_get_playmode_str(char *mode_str) {
	if ((mode_str = malloc(30)) == NULL) {
		return -1;
	}
	memset(mode_str, '\0', 30);
	switch (cur_config_raspi_server.play_mode) {
	  case shuffle:
	    mode_str = strdup("SHUFFLE");
	    break;
	   case loop_list:
	    mode_str = strdup("LOOP_LIST");
	    break;
	   case play_list:
	    mode_str = strdup("PLAY_LIST");
	    break;
	   case loop_one:
	    mode_str = strdup("LOOP_ONE");
	    break;
	   case play_one:
	    mode_str = strdup("PLAY_ONE");
	    break;
	   default:
	     mode_str = strdup("UNSET");
	     return -1;
	}
	printf("GETED PLAYMODE: %s\n", mode_str);
	return 0;
}

int analy_config_raspi_server() {
	int word_num;
	char *config_lines[50];
// 	syslog(LOG_USER, "analy config_raspi_server\n");
	word_num = split_lines_from_file(config_raspi_file_path, config_lines);
	
// 	printf("there are %d lines in config file\n", word_num);
// 	syslog(LOG_USER, "there are %d lines in config file\n", word_num);
	char *option_value[word_num];
	int option_iter;
	int i = 0;
	for (i = 0; i < word_num; i++) {
// 		printf("formatting: %s\n", config_lines[i]);
		config_format_line_and_save(config_lines[i]);
// 		free(config_lines[i]);
// 		printf("fred: %s\n", config_lines[i]);
	}
// 	printf("cur_config_raspi_server.playmode: %d\n", cur_config_raspi_server.play_mode);
// 	syslog(LOG_USER, "cur_config_raspi_server.playmode: %d\n", cur_config_raspi_server.play_mode);
// 	printf("cur_config_raspi_server.music_path: %s\n", cur_config_raspi_server.music_path);
// 	syslog(LOG_USER, "cur_config_raspi_server.music_path: %s\n", cur_config_raspi_server.music_path);
// 	printf("cur_config_raspi_server.socket_port: %d\n", cur_config_raspi_server.socket_port);
// 	syslog(LOG_USER, "cur_config_raspi_server.socket_port: %d\n", cur_config_raspi_server.socket_port);
// 	printf("cur_config_raspi_server.play_iter: %d\n", cur_config_raspi_server.play_iter);
// 	syslog(LOG_USER, "cur_config_raspi_server.play_iter: %d\n", cur_config_raspi_server.play_iter);
	return 0;
}*/

//检查该字符是否是选项字符
// int word_is_option(char *word, char *options[], int option_num) {
// 	int i;
// 	for (i = 0; i < option_num; i++) {
// 		if (!strcmp(options[i], word)) {
// 			return i;
// 		}
// 	}
// 	return -1;
// }

/*
int config_format_line_and_save(char *line) {
	char *options[] = {"SOCKET_PORT", "MUSIC_PATH", "PLAY_MODE", "PLAY_ITER"};
	int config_artr_num = 4;
	char *words_of_line[strlen(line)];
	int words_num;
	int option_iter;
	int met_option = 0;
	int i = 0;
	if ((words_num = config_split_words(line, words_of_line)) <= 0) {
		return -1;
	}
// 	printf("splited line: %s\n%d words", line, words_num);
	for (i = 0; i < words_num; i++) {
// 		printf("checking word: %s\n", words_of_line[i]);
		if ((option_iter = word_is_option(words_of_line[i], options, config_artr_num)) >= 0) {
			if (++i > words_num) {
				break;
			}
			if (option_iter == socket_port) {
// 			      printf("formatting play mode\n");
			      config_format_socket_port(words_of_line[i]);
			      met_option = 1;
// 			      printf("formated play mode\n");
			      break;
			} 
			if (option_iter == music_path) {
// 			      printf("formatting music_path\n");
			      config_format_music_path(words_of_line, words_num, i);
			      met_option = 1;
			      break;
			}
			if (option_iter == play_mode) {
// 				printf("formating socket_port: %s\n", words_of_line[i]);
				config_format_play_mode(words_of_line[i]);
				met_option = 1;
				break;
			}
			if (option_iter == play_iter) {
// 				printf("formating socket_port: %s\n", words_of_line[i]);
				config_format_play_iter(words_of_line[i]);
				met_option = 1;
				break;
			}
		}
	}
	for(i = 0; i < words_num; i++) {
		free(words_of_line[i]);
	}
	if (met_option == 1) {
		return 0;
	}
	return -1;
}

int config_format_play_mode(char *mode_str) {
	char *modes[] = {"SHUFFLE", "LOOP_LIST", "PLAY_LIST", "LOOP_ONE", "PLAY_ONE"};
	int i = 0;
	for (i = 0; i < 5; i++) {
		if (!strcmp(modes[i], mode_str)) {
			cur_config_raspi_server.play_mode = i;
			return i;
		}
	}
	return -1;
}*/
/*
int config_format_play_iter(char *iter_str) {
	cur_config_raspi_server.play_iter = atoi(iter_str);
	return 0;
}

int config_format_music_path(char *words[], int words_num, int start_iter) {
	char *tmp_str;
	int is_fist = 1;
	if ((tmp_str = malloc(BUFSIZ)) == NULL) {
		return -1;
	}
	memset(tmp_str, '\0', BUFSIZ);
	for (start_iter; start_iter < words_num; start_iter++) {
		if (is_fist == 1) {
			strcat(tmp_str, words[start_iter]);
			is_fist == 0;
			continue;
		}
		strcat(tmp_str, " ");
		strcat(tmp_str, words[start_iter]);
	}
	if ((cur_config_raspi_server.music_path = malloc(strlen(tmp_str))) == NULL) {
		free(tmp_str);
		return -1;
	}
	strcpy(cur_config_raspi_server.music_path, tmp_str);
	free(tmp_str);
	return 0;
}

int config_format_socket_port(char *port_str) {
	cur_config_raspi_server.socket_port = atoi(port_str);
	return 0;
}*/

int split_lines_from_file(char *path, char *lines[]) {
	FILE *file;
	char *buf;
	int num;
	//检查配置文件是否存在
  	if (access(path, F_OK) != 0) {
		syslog(LOG_USER, "load config from: %s failed.%m\n", path);
		perror("load config failed");
		return -1;
	} else {
		  syslog(LOG_USER, "hit the config file: %s\n", path);
		  printf("hit the config file\n");
	}
	file = fopen(path, "r");
	if ((buf = malloc(1024*4)) == NULL) {
		return -1;
	}
	memset(buf, '\0', 1024 * 4);
// 	syslog(LOG_USER, "open file : %d\n", file);
	fread(buf, 1024, 4, file);
// 	syslog(LOG_USER, "read file : %s\n", buf);
	fclose(file);
	num = split_lines(buf, lines);
	free(buf);
	return num;
}

