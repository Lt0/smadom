#include "auto_control.h"

void start_auto_process(char *process_str) {
  FILE *pipe_file;
  printf("process_str: %s\n", process_str);

  if (!strcmp(process_str, "tl") || !strcmp(process_str, "auto_table_light")) {
    syslog(LOG_DEBUG, "start auto_table_light\n");
    printf("Start auto_table_light\n");
    pipe_file = popen ("sudo auto_table_light", "r");
  } else if (!strcmp(process_str, "sl") || !strcmp(process_str, "auto_stair_light")) {
    syslog(LOG_DEBUG, "start auto_stair_light\n");
    printf("Start auto_stair_light\n");
    pipe_file = popen ("sudo auto_stair_light", "r");
  } else if (!strcmp(process_str, "bl") || !strcmp(process_str, "auto_bed_light")) {
    syslog(LOG_DEBUG, "start auto_bed_light\n");
    printf("Start auto_bed_light\n");
    pipe_file = popen ("sudo auto_bed_light", "r");
  } else if (!strcmp(process_str, "bf") || !strcmp(process_str, "auto_bed_fan")) {
    syslog(LOG_DEBUG, "start auto_bed_fan\n");
    printf("Start auto_bed_fan\n");
    pipe_file = popen ("sudo auto_bed_fan", "r");
  } else if (!strcmp(process_str, "all") || !strcmp(process_str, "auto_*")) {
    syslog(LOG_DEBUG, "start auto_*\n");
    printf("starting auto_table_light\n");
    pipe_file = popen ("sudo auto_table_light", "r");
    printf("starting auto_stair_light\n");
    pipe_file = popen ("sudo auto_stair_light", "r");
    printf("starting auto_bed_light\n");
    pipe_file = popen ("sudo auto_bed_light", "r");
    printf("starting auto_bed_fan\n");
    pipe_file = popen ("sudo auto_bed_fan", "r");
  } else {
    printf("Unknown auto_process: %s\n", process_str);
  }
  pclose (pipe_file);
}

void exit_auto_process (char *process_str) {
  FILE *pipe_file;

  if (!strcmp(process_str, "tl") || !strcmp(process_str, "auto_table_light")) {
    syslog(LOG_DEBUG, "Exit auto_table_light\n");
    printf("Exit auto_table_light\n");
    pipe_file = popen ("sudo pkill -9 auto_table_ligh", "r");
  } else if (!strcmp(process_str, "sl") || !strcmp(process_str, "auto_stair_light")) {
    syslog(LOG_DEBUG, "Exit auto_stair_light\n");
    printf("Exit auto_stair_light\n");
    pipe_file = popen ("sudo pkill -9 auto_stair_ligh", "r");
  } else if (!strcmp(process_str, "bl") || !strcmp(process_str, "auto_bed_light")) {
    syslog(LOG_DEBUG, "Exit auto_bed_light\n");
    printf("Exit auto_bed_light\n");
    pipe_file = popen ("sudo pkill -9 auto_bed_light", "r");
  } else if (!strcmp(process_str, "bf") || !strcmp(process_str, "auto_bed_fan")) {
     syslog(LOG_DEBUG, "Exit auto_bed_fan\n");
     printf("Exit auto_bed_fan\n");
     pipe_file = popen ("sudo pkill -9 auto_bed_fan", "r");
  } else if (!strcmp(process_str, "all") || !strcmp(process_str, "auto_*")) {
     syslog(LOG_DEBUG, "Exit auto_*\n");
    pipe_file = popen ("sudo pkill -9 auto_table_ligh", "r");
    pipe_file = popen ("sudo pkill -9 auto_stair_ligh", "r");
    pipe_file = popen ("sudo pkill -9 auto_bed_light", "r");
    pipe_file = popen ("sudo pkill -9 auto_bed_fan", "r");
  } else {
    printf("Unknown server: %s\n", process_str);
  }
  pclose (pipe_file);
}

void *thread_auto_table_light(void *arg) {
  int res;
  res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  if (res != 0) {
    perror("auto_table_light_thread pthread_setcancelstate failed");
    syslog(LOG_DEBUG, "auto_table_light_thread pthread_setcancelstate failed.%m\n");
    exit (EXIT_FAILURE);
  }
  res = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  if (res != 0) {
    perror("auto_table_light_thread pthread_setcanceltype failed");
    syslog(LOG_DEBUG, "auto_table_light_thread pthread_setcanceltype failed.%m\n");
    exit (EXIT_FAILURE);
  }
  printf("thread_auto_table_light function is running\n");
  syslog(LOG_DEBUG, "thread_auto_table_light function is running\n");
  
  int status, last_status, i;
  int time_sum, start_add_time;
  start_add_time = 0;
  //close_for_light_up变量用来识别灯管是否因为亮度变量而自动关的，若是，则在下次灯亮时，不论避障传感器前后状态是否相同都进入开灯或准备工作
  int close_for_light_up;
  while (1) {
    //首先检测外界光线是否已暗，亮时检查灯管是否关闭并且无需准备开灯工作
//     if (digitalRead(SENSOR_LIGHT) != TRIG_LIGHT) {
//       if (digitalRead(EQUIPMENT_TABLE_LIGHT) == TRIG_TABLE_LIGHT) {
// 	syslog(LOG_DEBUG, "Auto close table light\n");
// 	digitalWrite(EQUIPMENT_TABLE_LIGHT, UNTRIG_TABLE_LIGHT);
// 	
// 	//确保下次读取到的status和上次的不同，否则会导致始终人本来坐在那里时，因外界变亮关灯之后，又因外界变暗需要开灯而不会自动开灯。
// 	close_for_light_up = 1;
//       }
//       printf("light_up\n");
//       delay (DELAY_LIGHT);
//       start_add_time = 0;
//       continue;
//     } 
    //将上次读取到的传感器信息保存到last_status中
    last_status = status;
    status = digitalRead(SENSOR_SEAT_PERSON);
//     printf("Last Status: %d\n", last_status);
//     printf("Read INFO: %d\n", status);
    //若新读取的传感器信息和上次的不同，则准备继续检测以确定是否需要开灯或关灯
    if (status != last_status  || close_for_light_up == 1) {
      //经过一次检查后即设置为不是因光线变暗而关灯，因为无论之前为何关灯，避障传感器的两次状态都得到正确的更新了。
      close_for_light_up = 0;
      printf("get a different status\n");
      //读取到有东西挡住传感器，可能需要开灯
      if (status == TRIG_SEAT_PERSON) {
	printf("prepare to change, status is TRIG_SEAT_PERSON\n");
	//连续循环检查设定的次数，若中间有一次不需要开灯则跳出循环
	for (i = 0; i < TIMES_SEAT_PERSON; i++) {
	  status = digitalRead(SENSOR_SEAT_PERSON);
// 	  printf("%d status: %d\n", i, status);
	  delay (DELAY_SEAT_PERSON);
	  
	  if (status != TRIG_SEAT_PERSON) {
// 	    printf("break by status: %d\n", status);
	    status = last_status;
	    break;
	  }
	}
	printf("i is: %d\nTIMES_SEAT_PERSON is: %d\n", i, TIMES_SEAT_PERSON);
	//比较检查的次数是否和规定的次数相同，相同则开灯，否则不做动作。
	if (i == TIMES_SEAT_PERSON) {
	  printf("open table light\n");
	  syslog(LOG_DEBUG, "Auto open table light\n");
	  digitalWrite(EQUIPMENT_TABLE_LIGHT, TRIG_TABLE_LIGHT);
	  start_add_time = 0;
	  time_sum = 0;
	}
      } else {
	//读取到挡住传感器的东西已离开，继续准备以确定是否需要关灯
	printf("prepare to change, status is 0\n");
	//连续循环检查设定的次数，若中间有一次不需要关灯则跳出循环
	for (i = 0; i < TIMES_SEAT_PERSON; i++) {
	  status = digitalRead(SENSOR_SEAT_PERSON);
// 	  printf("%d status: %d\n", i, status);
	  delay (DELAY_SEAT_PERSON);
	  if (status == TRIG_SEAT_PERSON) {
	    printf("break by status: %d\n", status);
	    status = last_status;
	    break;
	  }
	}	
	printf("i is: %d\nTIMES_SEAT_PERSON is: %d\n", i, TIMES_SEAT_PERSON);
	//比较检查的次数是否和规定的次数相同，相同则关灯，否则不做动作。
	if (i == TIMES_SEAT_PERSON) {
// 	  printf("close table light\n");
// 	  digitalWrite(EQUIPMENT_TABLE_LIGHT, UNTRIG_TABLE_LIGHT);
	  start_add_time = 1;
	}
      }
    }
    delay (DELAY_SEAT_PERSON) ;
    if (start_add_time == 1) {
	time_sum += DELAY_SEAT_PERSON;
	printf("time_sum = %d\n", time_sum);
	if (time_sum >= (KEEP_TABLE_LIGHT * 1000)) {
	  syslog(LOG_DEBUG, "Auto close table light\n");
	   digitalWrite(EQUIPMENT_TABLE_LIGHT, UNTRIG_TABLE_LIGHT);
	   start_add_time = 0;
	   time_sum = 0;
	 }
      }
  }
  
}

void *thread_auto_bed_light(void *arg) {
  int res;
  res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  if (res != 0) {
    perror("auto_bed_light_thread pthread_setcancelstate failed");
    syslog(LOG_DEBUG, "auto_bed_light_thread pthread_setcancelstate failed.%m\n");
    exit (EXIT_FAILURE);
  }
  res = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  if (res != 0) {
    perror("auto_bed_light_thread pthread_setcanceltype failed");
    syslog(LOG_DEBUG, "auto_bed_light_thread pthread_setcanceltype failed.%m\n");
    exit (EXIT_FAILURE);
  }
  printf("thread_auto_bed_light function is running\n");
  syslog(LOG_DEBUG, "thread_auto_bed_light function is running\n");
  
  int status, last_status, i;
  //close_for_light_up变量用来识别灯管是否因为亮度变量而自动关的，若是，则在下次灯亮时，不论避障传感器前后状态是否相同都进入开灯或准备工作
  int close_for_light_up;
  int time_sum, start_add_time;
  start_add_time = 0;
  while (1) {
    //首先检测外界光线是否已暗，量时检查灯管是否关闭并且无需准备开灯工作
    if (digitalRead(SENSOR_LIGHT) != TRIG_LIGHT) {
      if (digitalRead(EQUIPMENT_BED_LIGHT) == TRIG_BED_LIGHT) {
	syslog(LOG_DEBUG, "Auto close bed light\n");
	digitalWrite(EQUIPMENT_BED_LIGHT, UNTRIG_BED_LIGHT);
	//确保下次读取到的status和上次的不同，否则会导致始终人本来坐在那里时，因外界变亮关灯之后，又因外界变暗需要开灯而不会自动开灯。
	close_for_light_up = 1;
      }
      delay(DELAY_LIGHT);
      start_add_time = 0;
      continue;
    } 
    //将上次读取到的传感器信息保存到last_status中
    last_status = status;
    status = digitalRead(SENSOR_BED_LIGHT_PERSON);
//     printf("Last Status: %d\n", last_status);
//     printf("Read INFO: %d\n", status);
    //若新读取的传感器信息和上次的不同，则准备继续检测以确定是否需要开灯或关灯
    if (status != last_status  || close_for_light_up == 1) {
      //经过一次检查后即设置为不是因光线变暗而关灯，因为无论之前为何关灯，避障传感器的两次状态都得到正确的更新了。
      close_for_light_up = 0;
      printf("get a different status\n");
      //读取到有东西挡住传感器，可能需要开灯
      if (status == TRIG_BED_LIGHT_PERSON) {
	printf("prepare to change, status is TRIG_BED_LIGHT_PERSON\n");
	//连续循环检查设定的次数，若中间有一次不需要开灯则跳出循环
	for (i = 0; i < TIMES_BED_LIGHT_PERSON; i++) {
	  status = digitalRead(SENSOR_BED_LIGHT_PERSON);
	  printf("%d status: %d\n", i, status);
	  delay (DELAY_BED_LIGHT_PERSON);
	  if (status != TRIG_BED_LIGHT_PERSON) {
	    printf("break by status: %d\n", status);
	    status = last_status;
	    break;
	  }
	}
	printf("i is: %d\nTIMES_BED_LIGHT_PERSON is: %d\n", i, TIMES_BED_LIGHT_PERSON);
	//比较检查的次数是否和规定的次数相同，相同则开灯，否则不做动作。
	if (i == TIMES_BED_LIGHT_PERSON) {
	  printf("open bed light\n");
	  syslog(LOG_DEBUG, "Auto open bed light\n");
	  digitalWrite(EQUIPMENT_BED_LIGHT, TRIG_BED_LIGHT);
	  start_add_time = 0;
	  time_sum = 0;
	}
      } else {
	//读取到挡住传感器的东西已离开，继续准备以确定是否需要关灯
	printf("prepare to change, status is 0\n");
	//连续循环检查设定的次数，若中间有一次不需要关灯则跳出循环
	for (i = 0; i < TIMES_BED_LIGHT_PERSON; i++) {
	  status = digitalRead(SENSOR_BED_LIGHT_PERSON);
	  printf("%d status: %d\n", i, status);
	  delay (DELAY_BED_LIGHT_PERSON);
	  if (status == TRIG_BED_LIGHT_PERSON) {
	    printf("break by status: %d\n", status);
	    status = last_status;
	    break;
	  }
	}	
	printf("i is: %d\nTIMES_BED_LIGHT_PERSON is: %d\n", i, TIMES_BED_LIGHT_PERSON);
	//比较检查的次数是否和规定的次数相同，相同则关灯，否则不做动作。
	if (i == TIMES_BED_LIGHT_PERSON) {
// 	  printf("close bed light\n");
// 	  digitalWrite(EQUIPMENT_BED_LIGHT, UNTRIG_BED_LIGHT);
	  start_add_time = 1;
	}
      }
    }
    delay (DELAY_BED_LIGHT_PERSON) ;
    if (start_add_time == 1) {
	time_sum += DELAY_SEAT_PERSON;
	printf("time_sum = %d\n", time_sum);
	if (time_sum >= (KEEP_TABLE_LIGHT * 1000)) {
	  syslog(LOG_DEBUG, "Auto close bed light\n");
	   digitalWrite(EQUIPMENT_BED_LIGHT, UNTRIG_BED_LIGHT);
	   start_add_time = 0;
	   time_sum = 0;
	 }
      }
  }
  
}


void *thread_auto_bed_fan(void *arg) {
  int res;
  res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  if (res != 0) {
    perror("auto_bed_fan_thread pthread_setcancelstate failed");
    syslog(LOG_DEBUG, "auto_bed_fan_thread pthread_setcancelstate failed.%m\n");
    exit (EXIT_FAILURE);
  }
  res = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  if (res != 0) {
    perror("auto_bed_fan_thread pthread_setcanceltype failed");
    syslog(LOG_DEBUG, "auto_bed_fan_thread pthread_setcanceltype failed.%m\n");
    exit (EXIT_FAILURE);
  }
  printf("thread_auto_bed_fan function is running\n");
  syslog(LOG_DEBUG, "thread_auto_bed_fan function is running\n");
  
  int status, last_status, i;
  int time_sum, start_add_time;
  start_add_time = 0;
  //close_for_light_up变量用来识别灯管是否因为亮度变量而自动关的，若是，则在下次灯亮时，不论避障传感器前后状态是否相同都进入开灯或准备工作
  int close_for_light_up;
  while (1) {
    //首先检测外界光线是否已暗，量时检查灯管是否关闭并且无需准备开灯工作
    if (digitalRead(SENSOR_TEMPERATURE) != TRIG_TEMPERATURE) {
      if (digitalRead(EQUIPMENT_BED_FAN) == TRIG_BED_FAN) {
	syslog(LOG_DEBUG, "Auto close bed fun\n");
	digitalWrite(EQUIPMENT_BED_FAN, UNTRIG_BED_FAN);
	//确保下次读取到的status和上次的不同，否则会导致始终人本来坐在那里时，因外界变亮关灯之后，又因外界变暗需要开灯而不会自动开灯。
	close_for_light_up = 1;
      }
      printf("light_up\n");
      delay (DELAY_TEMPERATURE);
      start_add_time = 0;
      continue;
    } 
    //将上次读取到的传感器信息保存到last_status中
    last_status = status;
    status = digitalRead(SENSOR_BED_FAN_PERSON);
//     printf("Last Status: %d\n", last_status);
//     printf("Read INFO: %d\n", status);
    //若新读取的传感器信息和上次的不同，则准备继续检测以确定是否需要开灯或关灯
    if (status != last_status  || close_for_light_up == 1) {
      //经过一次检查后即设置为不是因光线变暗而关灯，因为无论之前为何关灯，避障传感器的两次状态都得到正确的更新了。
      close_for_light_up = 0;
      printf("get a different status\n");
      //读取到有东西挡住传感器，可能需要开风扇
      if (status == TRIG_BED_FAN_PERSON) {
	printf("prepare to open, status is TRIG_BED_FAN_PERSON\n");
	//连续循环检查设定的次数，若中间有一次不需要开风扇则跳出循环
	for (i = 0; i < TIMES_BED_FAN_PERSON; i++) {
	  status = digitalRead(SENSOR_BED_FAN_PERSON);
// 	  printf("%d status: %d\n", i, status);
	  delay (DELAY_BED_FAN_PERSON);
	  
	  if (status != TRIG_BED_FAN_PERSON) {
// 	    printf("break by status: %d\n", status);
	    status = last_status;
	    break;
	  }
	}
// 	printf("i is: %d\nTIMES_BED_FAN_PERSON is: %d\n", i, TIMES_BED_FAN_PERSON);
	//比较检查的次数是否和规定的次数相同，相同则开灯，否则不做动作。
	if (i == TIMES_BED_FAN_PERSON) {
	  printf("open bed fan\n");
	  syslog(LOG_DEBUG, "Auto open bed fun\n");
	  digitalWrite(EQUIPMENT_BED_FAN, TRIG_BED_FAN);
	  start_add_time = 0;
	  time_sum = 0;
	}
      } else {
	//读取到挡住传感器的东西已离开，继续准备以确定是否需要关灯
	printf("prepare to close, status is 0\n");
	//连续循环检查设定的次数，若中间有一次不需要关灯则跳出循环
	for (i = 0; i < TIMES_BED_FAN_PERSON; i++) {
	  status = digitalRead(SENSOR_BED_FAN_PERSON);
// 	  printf("%d status: %d\n", i, status);
	  delay (DELAY_BED_FAN_PERSON);
	  if (status == TRIG_BED_FAN_PERSON) {
	    printf("break by status: %d\n", status);
	    status = last_status;
	    break;
	  }
	}	
	printf("i is: %d\nTIMES_BED_FAN_PERSON is: %d\n", i, TIMES_BED_FAN_PERSON);
	//比较检查的次数是否和规定的次数相同，相同则关灯，否则不做动作。
	if (i == TIMES_BED_FAN_PERSON) {
// 	  printf("close bed fan\n");
// 	  digitalWrite(EQUIPMENT_BED_FAN, UNTRIG_BED_FAN);
	  start_add_time = 1;
	}
      }
    }
    delay (DELAY_BED_FAN_PERSON) ;
    if (start_add_time == 1) {
	time_sum += DELAY_BED_FAN_PERSON;
	printf("time_sum = %d\n", time_sum);
	if (time_sum >= (KEEP_BED_FAN * 1000)) {
	  syslog(LOG_DEBUG, "Auto close bed fun\n");
	   digitalWrite(EQUIPMENT_BED_FAN, UNTRIG_BED_FAN);
	   start_add_time = 0;
	   time_sum = 0;
	 }
      }
  }
  
}


void *thread_auto_stair_light(void *arg) {
  int res;
  res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  if (res != 0) {
    perror("auto_stair_light_thread pthread_setcancelstate failed");
    syslog(LOG_DEBUG, "auto_stair_light_thread pthread_setcancelstate failed.%m\n");
    exit (EXIT_FAILURE);
  }
  res = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  if (res != 0) {
    perror("auto_stair_light_thread pthread_setcanceltype failed");
    syslog(LOG_DEBUG, "auto_stair_light_thread pthread_setcanceltype failed.%m\n");
    exit (EXIT_FAILURE);
  }
  printf("thread_auto_stair_light function is running\n");
  syslog(LOG_DEBUG, "thread_auto_stair_light function is running\n");
  
  while (1) {
    //首先检测外界光线是否已暗，亮时检查灯管是否关闭并且无需准备开灯工作
    if (digitalRead(SENSOR_LIGHT) != TRIG_LIGHT) {
      if (digitalRead(EQUIPMENT_STAIR_LIGHT) == TRIG_STAIR_LIGHT) {
// 	syslog(LOG_DEBUG, "Auto close stair light\n");
	digitalWrite(EQUIPMENT_STAIR_LIGHT, UNTRIG_STAIR_LIGHT);
      }
      delay (DELAY_LIGHT);
      continue;
    } 

    if (digitalRead(SENSOR_STAIR_PERSON) == TRIG_STAIR_PERSON) {
	printf("open stair light\n");
// 	syslog(LOG_DEBUG, "Auto open stair light\n");
	digitalWrite(EQUIPMENT_STAIR_LIGHT, TRIG_STAIR_LIGHT);
	sleep (KEEP_STAIR_LIGHT);
      } else {
	printf("close stair light\n");
// 	syslog(LOG_DEBUG, "Auto close stair light\n");
	digitalWrite(EQUIPMENT_STAIR_LIGHT, UNTRIG_STAIR_LIGHT);
      }
    delay (DELAY_STAIR_PERSON) ;
  }
  
}

//此函数自动打开一个独立的新线程来自动控制台灯的开关，成功返回0,失败返回-1
int auto_table_light() {
  int res;

  //创建独立线程控制台灯
  res = pthread_create(&TABLE_LIGHT_THREAD, NULL, thread_auto_table_light, NULL);
  if (res != 0) {
    perror("create thread for thread_auto_table_light failed\n ");
    syslog(LOG_DEBUG, "create thread for thread_auto_table_light failed\n%m\n ");
    return -1;
  }
  return 0;
}

int auto_bed_light() {
  int res;

  //创建独立线程控制台灯
  res = pthread_create(&BED_LIGHT_THREAD, NULL, thread_auto_bed_light, NULL);
  if (res != 0) {
    perror("create thread for thread_auto_bed_light failed\n ");
    syslog(LOG_DEBUG, "create thread for thread_auto_bed_light failed\n%m\n ");
    return -1;
  }
  return 0;
}

int auto_bed_fan() {
  int res;

  //创建独立线程控制台灯
  res = pthread_create(&BED_FAN_THREAD, NULL, thread_auto_bed_fan, NULL);
  if (res != 0) {
    perror("create thread for thread_auto_bed_fan failed\n ");
    syslog(LOG_DEBUG, "create thread for thread_auto_bed_fan failed\n%m\n ");
    return -1;
  }
  return 0;
}

//此函数自动打开一个独立的新线程来自动控制台灯的开关，成功返回0,失败返回-1
int auto_stair_light() {
  int res;

  //创建独立线程控制台灯
  res = pthread_create(&STAIR_LIGHT_THREAD, NULL, thread_auto_stair_light, NULL);
  if (res != 0) {
    perror("create thread for thread_auto_stair_light failed\n ");
    syslog(LOG_DEBUG, "create thread for thread_auto_stair_light failed\n%m\n ");
    return -1;
  }
  return 0;
}

//通过字符串类型的名字启动该设备的自动控制线程
int auto_control_equipment(char *name) {
  int equipment;
  equipment = convert_str_to_equipment(name);
  switch (equipment) {
    case EQUIPMENT_TABLE_LIGHT:
      auto_table_light();
      break;
    case EQUIPMENT_STAIR_LIGHT:
      
      break;
    case EQUIPMENT_BED_FAN:
      
      break;
    case EQUIPMENT_BED_LIGHT:
      
      break;
    default:
      printf("unknow equipent\n");
      return -1;
  }
  return 0;
}


//通过字符串类型的名字退出该设备的自动控制线程
int cancel_auto_control_thread(char *name) {
  int equipment;
  equipment = convert_str_to_equipment(name);
  switch (equipment) {
    case EQUIPMENT_TABLE_LIGHT:
      cancel_thread(TABLE_LIGHT_THREAD);
      break;
    case EQUIPMENT_STAIR_LIGHT:
      
      break;
    case EQUIPMENT_BED_FAN:
      
      break;
    case EQUIPMENT_BED_LIGHT:
      
      break;
    default:
      printf("unknow equipent\n");
      return -1;
  }
  return 0;
}

//退出某个线程
int cancel_thread(pthread_t a_thread) {
  int res;
  res = pthread_cancel(a_thread);
  if (res != 0) {
    perror("cancel thread failed");
    syslog(LOG_DEBUG, "cancel thread failed\n%m\n");
    return -1;
  }
  return 0;
}

// void auto_table_light_process() {
//   int sensor_status, equipment_status, close_for_light_up;
//   while (1) {
//     if (digitalRead(SENSOR_LIGHT) != TRIG_LIGHT) {
//       if (digitalRead(EQUIPMENT_TABLE_LIGHT) == TRIG_TABLE_LIGHT) {
// 	digitalWrite(EQUIPMENT_TABLE_LIGHT, UNTRIG_TABLE_LIGHT);
// 	close_for_light_up = 1;
//       }
//       delay (DELAY_LIGHT);
//       continue;
//     }
//     sensor_status = digitalRead(SENSOR_SEAT_PERSON);
//     equipment_status = digitalRead(EQUIPMENT_TABLE_LIGHT)
//     if (sen)
//   }
// }