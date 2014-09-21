#include "auto_table_light.h"

int main() {
  openlog("smadom_auto_tl", LOG_PID | LOG_CONS, LOG_USER);
  syslog(LOG_INFO, "smadom_auto_tl server starting");
  printf("smadom_auto_tl starting....\n");
  init_sensors();
  printf("Initialed sensor's interfaces\n");
  init_equipments() ;
  printf("Initialed equipmen's interfaces\n");
  run_in_daemon();
  
  TIMES_LIGHT = 15;
  DELAY_LIGHT = 20;
  
  TIMES_SEAT_PERSON = 15;
  DELAY_SEAT_PERSON = 20;
  KEEP_TABLE_LIGHT= 10;
  void *arg;
  thread_auto_table_light(arg);
//   auto_table_light();
//   while (tmp_running) {
//     sleep (1);
//     printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
//   }
}