#include "auto_bed_fan.h"

int main() {
  openlog("smadom_auto_tl", LOG_PID | LOG_CONS, LOG_USER);
  syslog(LOG_INFO, "smadom_auto_bf server starting");
  printf("smadom_auto_bf starting....\n");
  init_sensors();
  printf("Initialed sensor's interfaces\n");
  init_equipments() ;
  printf("Initialed equipmen's interfaces\n");
  run_in_daemon();
  
  DELAY_TEMPERATURE = 20;
  DELAY_BED_FAN_PERSON = 20;
  TIMES_BED_FAN_PERSON = 15;
  KEEP_BED_FAN = 1 * 60 ;
  void *arg;
  thread_auto_bed_fan(arg);
}