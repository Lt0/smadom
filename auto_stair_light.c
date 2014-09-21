#include "auto_stair_light.h"

int main() {
  openlog("smadom_auto_sl", LOG_PID | LOG_CONS, LOG_USER);
  syslog(LOG_INFO, "smadom_auto_sl server starting");
  printf("smadom_auto_sl starting....\n");
  init_sensors();
  printf("Initialed sensor's interfaces\n");
  init_equipments() ;
  printf("Initialed equipmen's interfaces\n");
  run_in_daemon();
  
  TIMES_LIGHT = 15;
  DELAY_LIGHT = 20;
  
  TIMES_STAIR_PERSON = 15;
  DELAY_STAIR_PERSON = 20;
  KEEP_STAIR_LIGHT= 15;
  void *arg;
  thread_auto_stair_light(arg);

}