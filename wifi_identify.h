#include <stdio.h>
#include <syslog.h>
#include <string.h>
#include <pthread.h>

#define FALSE 0
#define TRUE 1
#define MAX_IP_NUM 10

int IN_DOM;
int SET_IP_NUM;
int TIME_OUT;
char *IDENTIFY_IP[MAX_IP_NUM];
// struct timeval recv_timeout;
// struct fd_set fds;


int identify_ip(char *ip);
int load_identify_config();
int check_macs(char *config_macs[], char *active_macs[]);
int get_ip_by_macs(char *mac, char *ip) ;
