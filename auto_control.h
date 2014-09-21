#include <stdio.h>
#include <syslog.h>
#include <pthread.h>
#include <wiringPi.h>
#include <unistd.h>
#include <stdlib.h>
#include "sensors.h"
#include "equipments.h"

pthread_t TABLE_LIGHT_THREAD;
pthread_t STAIR_LIGHT_THREAD;
pthread_t BED_LIGHT_THREAD;
pthread_t BED_FAN_THREAD;
pthread_t CAMERA_THREAD;

void start_auto_process(char *process_str);
void exit_auto_process (char *process_str);
void *thread_auto_table_light(void *arg);
void *thread_auto_bed_light(void *arg);
void *thread_auto_bed_fan(void *arg);
void *thread_auto_stair_light(void *arg);
int auto_table_light();
int auto_bed_light();
int auto_bed_fan();
int auto_stair_light();
int auto_control_equipment(char *name);
int cancel_auto_control_thread(char *name);
int cancel_thread(pthread_t a_thread);