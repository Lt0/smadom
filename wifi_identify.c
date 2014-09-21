#include "wifi_identify.h"

int identify_ip(char *ip) {
  if (ip == NULL) {
    return FALSE;
  }
  if (strlen(ip) > 16) {
    return FALSE;
  }
  char command_str[22];
  strcat(command_str, "ping ");
  strcat(command_str, ip);
  FILE *f_iden;
  char read_buf[BUFSIZ + 1];
  
  f_iden = popen(command_str, "r");
  if (f_iden == NULL) {
    return FALSE;
  }
  syslog(LOG_DEBUG, "running command: %s\n", command_str);
  while (1) {
//     syslog(LOG_DEBUG, "reading ping data\n");
    memset(read_buf, '\0', BUFSIZ);
//     fread( read_buf, strlen("64 bytes from 192.168.10.49: icmp_seq=4 ttl=64 time=18.7 ms") , 1, f_iden);
//     syslog(LOG_INFO, "read: ");
    syslog(LOG_DEBUG, read_buf);
    sleep (1);
  }
//   pthread_t a_thread;
//   int res;
//   res =pthread_create(&a_thread, NULL, )
}
/*
void *identify_check_thread(void *arg) {
  FILE *f_iden;
  f_iden = (FILE *)arg;
  fread()
}*/