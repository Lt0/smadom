#include "auto_bed_light.h"

int main() {
  openlog("smadom_auto_bl", LOG_PID | LOG_CONS, LOG_USER);
  syslog(LOG_INFO, "smadom_auto_bl server starting");
  printf("smadom_auto_bl starting....\n");
  init_sensors();
  printf("Initialed sensor's interfaces\n");
  init_equipments() ;
  printf("Initialed equipmen's interfaces\n");
  run_in_daemon();
  
  TIMES_LIGHT = 15;
  DELAY_LIGHT = 20;
  
  TIMES_BED_LIGHT_PERSON = 15;
  DELAY_BED_LIGHT_PERSON = 20;
  KEEP_BED_LIGHT = 3;
  void *arg;
  thread_auto_bed_light(arg);
}