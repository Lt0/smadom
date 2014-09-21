#ifndef SMADOM_H
#define SMADOM_H
#include <stdio.h> 
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <syslog.h>
#include "sensors.h"
#include "equipments.h"
#include "wifi_identify.h"
#include "config.h"
#include "auto_control.h"
#include "daemon.h"

int SERVER_PORT;
#define SERVER_STR "atl(auto_table_light), asl(auto_stair_light), abl(auto_bed_light), abf(auto_bed_fan), all(auto_*)"

int init_server_sock();
void *control_handler(void *arg);
void show_help_info();
void show_interface_info();
int run_server_daemon();
int run_server();
void exit_smadom();
int tmp_solve();

#endif