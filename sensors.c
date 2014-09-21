#include "sensors.h"


int init_sensors() {
  wiringPiSetup ();
  pinMode(SENSOR_SEAT_PERSON, INPUT);
  pinMode(SENSOR_LIGHT, INPUT);
  pinMode(SENSOR_BED_FAN_PERSON, INPUT);
  pinMode(SENSOR_BED_LIGHT_PERSON, INPUT);
  pinMode(SENSOR_STAIR_PERSON, INPUT);
  pinMode(SENSOR_DOOR_PERSON, INPUT);
  pinMode(SENSOR_TEMPERATURE, INPUT);
  return 0;
}

int check_sensor(int sensor) {
  int hit_times, trig, trig_times, delay_time, i;
  hit_times = 0;
  switch (sensor) {
    case SENSOR_SEAT_PERSON:
      trig = TRIG_SEAT_PERSON;
      trig_times = TIMES_SEAT_PERSON;
      delay_time = DELAY_SEAT_PERSON;
      break;
    case SENSOR_LIGHT:
      trig = TRIG_LIGHT;
      trig_times = TIMES_LIGHT;
      delay_time = DELAY_LIGHT;
      break;
    case SENSOR_BED_FAN_PERSON:
      trig = TRIG_BED_FAN_PERSON;
      trig_times = TIMES_BED_FAN_PERSON;
      delay_time = DELAY_BED_FAN_PERSON;
      break;
    case SENSOR_BED_LIGHT_PERSON:
      trig = TRIG_BED_LIGHT_PERSON;
      trig_times = TIMES_BED_LIGHT_PERSON;
      delay_time = DELAY_BED_LIGHT_PERSON;
      break;
    case SENSOR_STAIR_PERSON:
      trig = TRIG_STAIR_PERSON;
      trig_times = TIMES_STAIR_PERSON;
      delay_time = DELAY_STAIR_PERSON;
      break;
    case SENSOR_DOOR_PERSON:
      trig = TRIG_DOOR_PERSON;
      trig_times = TIMES_DOOR_PERSON;
      delay_time = DELAY_DOOR_PERSON;
      break;
    case SENSOR_TEMPERATURE:
      trig = TRIG_TEMPERATURE;
      trig_times = TIMES_TEMPERATURE;
      delay_time = DELAY_TEMPERATURE;
      break;
    default:
      return -1;
  }
  printf("trig: %d\ntrig_times: %d\ndelay_time: %d\n", trig, trig_times, delay_time);
  for (i = 0; i < trig_times; i++) {
    printf("read: %d\n", digitalRead(sensor));
    if (digitalRead(sensor) == trig) {
      
      hit_times++;
    }
    printf("hit_times: %d\n", hit_times);
    delay(delay_time);
  }
  if (hit_times >= (trig_times/2)) {
    printf("return trig\n");
    return trig;
  } else {
    printf("return untrig\n");
    if (trig == 0) {
      return 1;
    } else {
      return 0;
    }
  }
}

int update_light() {
  
}

int update_bed_fan_person() {
  
}

int update_bed_light_person() {
  
}

int update_stair_person() {
  
}

int update_door_person() {
  
}

int update_temperature() {
  
}