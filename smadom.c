#include "smadom.h"

int main(int argc, char * argv[]) {
//   digitalWrite(1, EQUIPMENT_STAIR_LIGHT);
//   printf("dddd\n");
  if (argc ==1) {
    show_help_info();
  }
  int opt;
  while ((opt = getopt(argc, argv, ":hvldSt:o:c:s:k:x")) != -1) {
    switch (opt) {
      case ':':
	show_help_info();
	break;
      case 'h':
	show_help_info();
	break;
      case 'v':
	printf("Smadom On Console\nVersion 0.0.1-beta\n");
	break;
      case 'l':
	//在当前终端显示所有接口状态
	show_interface_info();
	break;
      case 'd':
	load_config("/etc/smadom/smadom-config");
	run_server();
	break;
      case 'S':
	run_server_daemon();
	break;
      case 't':
	toggle_equipment(optarg);
	break;
      case 'o':
	printf("openning %s\n", optarg);
	if (handle_equipment(OPEN_EQUIPMENT, optarg) < 0) {
	  printf("open %s failed\n", optarg);
	} else {
	  printf("open %s successed\n", optarg);
	}
	break;
      case 'c':
	printf("closing %s\n", optarg);
	if (handle_equipment(CLOSE_EQUIPMENT, optarg) < 0) {
	  printf("close %s failed\n", optarg);
	} else {
	  printf("close %s successed\n", optarg);
	}
	break;
      case 's':
	printf("starting auto_control_process: %s\n", optarg);
	start_auto_process(optarg);
	break;
      case 'k':
	printf("exitting auto_control_process: %s\n", optarg);
	exit_auto_process(optarg);
	break;
      case 'x':
	exit_smadom();
	break;
      case '?':
	printf("Unknow option\n");
	show_help_info();
	break;
    }
  }
  return 0;
}

int init_server_sock() {
	int server_sock;
	struct sockaddr_in my_addr;

	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = INADDR_ANY;
	SERVER_PORT = 8081;
	my_addr.sin_port = htons(SERVER_PORT);
	
	if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return 1;
	}

	if (bind(server_sock, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) < 0) {
		perror("bind");
		return 1;
	}
	return server_sock;
}

void * control_handler(void *arg) {
  int client_sock = *((int *)arg);
  
}

int run_server_daemon() {
  openlog("smadom", LOG_PID | LOG_CONS, LOG_USER);
  syslog(LOG_INFO, "smadom server starting");
  printf("starting smadom....\n");
  init_sensors();
  printf("Initialed sensor's interfaces\n");
  init_equipments() ;
  printf("Initialed equipmen's interfaces\n");
  
  run_in_daemon();

  int server_sock, client_sock, len = 0;
  server_sock = init_server_sock();
  
  int sin_size, res;
  struct sockaddr_in remote_addr;
  pthread_t a_thread;
  
  IDENTIFY_IP[0] = malloc(16);
  strcpy(IDENTIFY_IP[0], "192.168.10.49");
  
  while( 1 ) {
//     syslog(LOG_INFO, "starting server main loop\n");
    identify_ip(IDENTIFY_IP[0]);
    listen(server_sock, 3);
//     syslog(LOG_INFO, "listening for client....\n");
    
    sin_size = sizeof(struct sockaddr_in);
    if ((client_sock = accept(server_sock, (struct sockaddr *)&remote_addr, &sin_size)) < 0) {
      syslog(LOG_INFO, "accept error %m\n");
      return 1;
      
    }
    syslog(LOG_INFO, "accepted client: %s\n", inet_ntoa(remote_addr.sin_addr));
    len = send(client_sock, "Welcom to raspi server\n", 23, 0);
//     syslog(LOG_INFO, "The new client sock is: %d\n", client_sock);
    res = pthread_create(&a_thread, NULL, control_handler, (void *)&client_sock);
    if (res != 0) {
      syslog(LOG_INFO, "%s which sock is %d connect error: %m\n", inet_ntoa(remote_addr.sin_addr), client_sock);
    } else {
      syslog(LOG_INFO, "%s which sock is %d connect successed\n", inet_ntoa(remote_addr.sin_addr), client_sock);
    }
  }
  
  syslog(LOG_USER, "Smadom exit\n");
  closelog();
}

int run_server() {
    openlog("smadom", LOG_PID | LOG_CONS, LOG_USER);
  syslog(LOG_INFO, "smadom server starting");
  printf("starting smadom....\n");
  init_sensors();
  printf("Initialed sensor's interfaces\n");
  init_equipments() ;
  printf("Initialed equipmen's interfaces\n");
  
  int server_sock, client_sock, len = 0;
  server_sock = init_server_sock();
  
  int sin_size, res;
  struct sockaddr_in remote_addr;
  pthread_t a_thread;
 
  
  while(1) {
//     syslog(LOG_INFO, "starting server main loop\n");
//     identify_ip(IDENTIFY_IP[0]);
    listen(server_sock, 3);
//     syslog(LOG_INFO, "listening for client....\n");
    printf("listening for client....\n");
    sin_size = sizeof(struct sockaddr_in);
    if ((client_sock = accept(server_sock, (struct sockaddr *)&remote_addr, &sin_size)) < 0) {
      syslog(LOG_INFO, "accept error %m\n");
      return 1;
      
    }
    syslog(LOG_INFO, "accepted client: %s\n", inet_ntoa(remote_addr.sin_addr));
    len = send(client_sock, "Welcom to raspi server\n", 23, 0);
//     syslog(LOG_INFO, "The new client sock is: %d\n", client_sock);
    res = pthread_create(&a_thread, NULL, control_handler, (void *)&client_sock);
    if (res != 0) {
      syslog(LOG_INFO, "%s which sock is %d connect error: %m\n", inet_ntoa(remote_addr.sin_addr), client_sock);
    } else {
      syslog(LOG_INFO, "%s which sock is %d connect successed\n", inet_ntoa(remote_addr.sin_addr), client_sock);
    }
  }
  
  syslog(LOG_USER, "Smadom exit\n");
  closelog();
}

void show_help_info() {
  printf("Smadom On Console\nVersion 0.0.1-beta\n");
  printf("Usage:\nsmadom [OPTIONS]... [EQUIPMENT]....\n");
  printf("-v\t\tprint program version and exit.\n");
  printf("-h\t\tprint usage and exit\n");
  printf("-d\t\trun smadom server by debug mode\n");
  printf("-S\t\trun smadom server-daemon\n");
  printf("-t <equipment>\ttoggle an equipment status(%s)\n\n", EQUIPMENT_STR);
  printf("-o <equipment>\topen an equipment(%s)\n\n", EQUIPMENT_STR);
  printf("-c <equipment>\tclose an equipment(%s)\n\n" , EQUIPMENT_STR);
  printf("-l\t\tprint current status of sensors and equipments\n");
  printf("-s <process>\tstart control an equipment automaticlly, auto_process: %s\n\n", SERVER_STR);
  printf("-k <process>\tstop control an equipment automaticlly, auto_process: %s\n\n", SERVER_STR);
  printf("-x\t\texit smadom-server-daemon process\n");
}

void show_interface_info(char *arg) {
  init_sensors();
  init_equipments();
  printf("----------------sensors----------------\n");
  if (digitalRead(SENSOR_SEAT_PERSON) == TRIG_SEAT_PERSON) {
    printf("SENSOR_SEAT_PERSON\t\tTRUE\n");
  } else {
    printf("SENSOR_SEAT_PERSON\t\tFALSE\n");
  }
  
  if (digitalRead(SENSOR_LIGHT) == TRIG_LIGHT) {
    printf("SENSOR_LIGHT\t\t\tTRUE\n");
  } else {
    printf("SENSOR_LIGHT\t\t\tFALSE\n");
  }
  
  if (digitalRead(SENSOR_BED_FAN_PERSON) == TRIG_BED_FAN_PERSON) {
    printf("SENSOR_BED_FAN_PERSON\t\tTRUE\n");
  } else {
    printf("SENSOR_BED_FAN_PERSON\t\tFALSE\n");
  }
  
  if (digitalRead(SENSOR_BED_LIGHT_PERSON) == TRIG_BED_LIGHT_PERSON) {
    printf("SENSOR_BED_LIGHT_PERSON\t\tTRUE\n");
  } else {
    printf("SENSOR_BED_LIGHT_PERSON\t\tFALSE\n");
  }
  
  if (digitalRead(SENSOR_STAIR_PERSON) == TRIG_STAIR_PERSON) {
    printf("SENSOR_STAIR_PERSON\t\tTRUE\n");
  } else {
    printf("SENSOR_STAIR_PERSON\t\tFALSE\n");
  }
  
  if (digitalRead(SENSOR_DOOR_PERSON) == TRIG_DOOR_PERSON) {
    printf("SENSOR_DOOR_PERSON\t\tTRUE\n");
  } else {
    printf("SENSOR_DOOR_PERSON\t\tFALSE\n");
  }
  
  if (digitalRead(SENSOR_TEMPERATURE) == TRIG_TEMPERATURE) {
    printf("SENSOR_TEMPERATURE\t\tTRUE\n");
  } else {
    printf("SENSOR_TEMPERATURE\t\tFALSE\n");
  }
  
  printf("---------------equipments---------------\n");
  if (digitalRead(EQUIPMENT_TABLE_LIGHT) == TRIG_TABLE_LIGHT){
    printf("EQUIPMENT_TABLE_LIGHT\t\tTRUE\n");
  } else {
    printf("EQUIPMENT_TABLE_LIGHT\t\tFALSE\n");
  }
  
  if (digitalRead(EQUIPMENT_STAIR_LIGHT) == TRIG_STAIR_LIGHT) {
    printf("EQUIPMENT_STAIR_LIGHT\t\tTRUE\n");
  } else {
    printf("EQUIPMENT_STAIR_LIGHT\t\tFALSE\n");
  }
  
    if (digitalRead(EQUIPMENT_BED_FAN) == TRIG_BED_FAN) {
    printf("EQUIPMENT_BED_FAN\t\tTRUE\n");
  } else {
    printf("EQUIPMENT_BED_FAN\t\tFALSE\n");
  }
  
    if (digitalRead(EQUIPMENT_BED_LIGHT) == TRIG_BED_LIGHT) {
    printf("EQUIPMENT_BED_LIGHT\t\tTRUE\n");
  } else {
    printf("EQUIPMENT_BED_LIGHT\t\tFALSE\n");
  }
  
  printf("---------------auto control---------------\n");
  FILE *f;
  char buf[100];
  f = popen("pgrep auto_table_ligh", "r");
  memset(buf, '\0', 100);
  fread(buf, 100, 1, f);
  if (strlen(buf) < 1) {
    printf("TABLE_LIGHT_AUTO\t\tSTOP\n");
  } else {
    printf("TABLE_LIGHT_AUTO\t\t%s", buf);
  }
  fclose(f);
  
  f = popen("pgrep auto_stair_ligh", "r");
  memset(buf, '\0', 100);
  fread(buf, 100, 1, f);
  if (strlen(buf) < 1) {
    printf("STAIR_LIGHT_AUTO\t\tSTOP\n");
  } else {
    printf("STAIR_LIGHT_AUTO\t\t%s", buf);
  }
  fclose(f);
  
  f = popen("pgrep auto_bed_ligh", "r");
  memset(buf, '\0', 100);
  fread(buf, 100, 1, f);
  if (strlen(buf) < 1) {
    printf("BED_LIGHT_AUTO\t\t\tSTOP\n");
  } else {
    printf("BED_LIGHT_AUTO\t\t\t%s", buf);
  }
  fclose(f);
  
  f = popen("pgrep auto_bed_fan", "r");
  memset(buf, '\0', 100);
  fread(buf, 100, 1, f);
  if (strlen(buf) < 1) {
    printf("BED_FAN_AUTO\t\t\tSTOP\n");
  } else {
    printf("BED_FAN_AUTO\t\t\t%s", buf);
  }
  fclose(f);
}

void exit_smadom() {
  FILE *pipe_file;
  pipe_file = popen ("sudo pkill -9 smadom", "r");
  pclose (pipe_file);
}


int tmp_solve() {
  for (; ; ) {
    //黑暗时灯光控制
    if (digitalRead(SENSOR_LIGHT) == TRIG_LIGHT) {
      //台灯控制
      if (digitalRead(SENSOR_SEAT_PERSON) == TRIG_SEAT_PERSON) {
	if (digitalRead(EQUIPMENT_TABLE_LIGHT) == UNTRIG_TABLE_LIGHT) {
	    printf("open table light\n");
	    digitalWrite(EQUIPMENT_TABLE_LIGHT, TRIG_TABLE_LIGHT);
	}
      } else {
	if (digitalRead(EQUIPMENT_TABLE_LIGHT) == TRIG_TABLE_LIGHT) {
	  printf("close table light\n");
	  digitalWrite(EQUIPMENT_TABLE_LIGHT, UNTRIG_TABLE_LIGHT);
	}
      }
      
      //床头灯控制
      if (digitalRead(SENSOR_BED_LIGHT_PERSON) == TRIG_BED_LIGHT_PERSON) {
	if (digitalRead(EQUIPMENT_BED_LIGHT) == UNTRIG_BED_LIGHT) {
	    printf("open bed light\n");
	    digitalWrite(EQUIPMENT_BED_LIGHT, TRIG_BED_LIGHT);
	}
      }else{
	 if (digitalRead(EQUIPMENT_BED_LIGHT) == TRIG_BED_LIGHT) {
	    printf("close bed light\n");
	    digitalWrite(EQUIPMENT_BED_LIGHT, UNTRIG_BED_LIGHT);
	}
      }
      
      //扶梯灯控制
      if (digitalRead (SENSOR_STAIR_PERSON) == TRIG_STAIR_PERSON) {
	//感应到人时开灯
	if (digitalRead (SENSOR_BED_FAN_PERSON) == UNTRIG_BED_FAN) {
	    printf("open stair light\n");
	    digitalWrite (EQUIPMENT_STAIR_LIGHT, TRIG_STAIR_LIGHT);
	}
      } else {
	//没有人时关灯
	 if (digitalRead(EQUIPMENT_STAIR_LIGHT) == TRIG_STAIR_LIGHT) {
	  printf("close stair light\n");
	  digitalWrite (EQUIPMENT_STAIR_LIGHT, UNTRIG_STAIR_LIGHT);
	}
      }
      //室内明亮时关闭可能打开的灯光
    } else {
      //若台灯处于打开状态则关闭
      if (digitalRead(EQUIPMENT_TABLE_LIGHT) == TRIG_TABLE_LIGHT) {
	  printf("close table light\n");
	  digitalWrite(EQUIPMENT_TABLE_LIGHT, UNTRIG_TABLE_LIGHT);
      }
      //若床头灯处于打开状态则关闭
      if (digitalRead(EQUIPMENT_BED_LIGHT) == TRIG_BED_LIGHT) {
	printf("close bed light\n");
        digitalWrite(EQUIPMENT_BED_LIGHT, UNTRIG_BED_LIGHT);
      }
      //若扶梯灯处于打开状态则关闭
      if (digitalRead(EQUIPMENT_STAIR_LIGHT) == TRIG_STAIR_LIGHT) {
	printf("close stair light\n");
	digitalWrite (EQUIPMENT_STAIR_LIGHT, UNTRIG_STAIR_LIGHT);
      }
    }
    
    //风扇控制，感应到有人时打开风扇，无人时关闭风扇
    if (digitalRead (SENSOR_BED_FAN_PERSON) == TRIG_BED_FAN_PERSON) {
      if (digitalRead (EQUIPMENT_BED_FAN != TRIG_BED_LIGHT)) {
	  printf("open bed fan\n");
	  digitalWrite (EQUIPMENT_BED_FAN, TRIG_BED_LIGHT);
      }
    } else {
      if (digitalRead (EQUIPMENT_BED_FAN) == TRIG_BED_LIGHT) {
	printf("close bed fan\n");
	digitalWrite (EQUIPMENT_BED_FAN, UNTRIG_BED_LIGHT);
      }
    }
    
    delay (500);
  }
  return 0;
}