#include "equipments.h"

int init_equipments() {
  wiringPiSetup();
  pinMode(EQUIPMENT_TABLE_LIGHT, OUTPUT);
  pinMode(EQUIPMENT_STAIR_LIGHT, OUTPUT);
  pinMode(EQUIPMENT_BED_FAN, OUTPUT);
  pinMode(EQUIPMENT_BED_LIGHT, OUTPUT);
  return 0;
}

int handle_equipment(int handle, char *equipment_str) {
  int equipment;
  syslog(LOG_DEBUG, "Handle equipment: %d %s\n",handle, equipment_str);
  printf("Handle equipment: %d %s\n",handle, equipment_str);
  if (handle != 1 && handle != 0) {
    printf("unknow handle, it should be 0 or 1\n");
    return -1;
  }
  if ((equipment = convert_str_to_equipment(equipment_str)) == -1) {
    printf("unknow equipment: %s\n", equipment_str);
    printf("valid equipments:\n%s\n", EQUIPMENT_STR);
    return -1;
  } if ((equipment = convert_str_to_equipment(equipment_str)) == -2) {
    init_equipments();
    digitalWrite(EQUIPMENT_TABLE_LIGHT, handle);
    digitalWrite(EQUIPMENT_STAIR_LIGHT, handle);
    digitalWrite(EQUIPMENT_BED_LIGHT, handle);
    digitalWrite(EQUIPMENT_BED_FAN, handle);
    return 0;
  }
  
  init_equipments();
  if (handle == OPEN_EQUIPMENT ) {
    if (digitalRead(equipment) != OPEN_EQUIPMENT) {
      digitalWrite(equipment, handle);
    } else {
      printf("%s is already openned\n", equipment_str);
      return -1;
    }
  } else if (handle == CLOSE_EQUIPMENT ){
    if (digitalRead(equipment) != CLOSE_EQUIPMENT) {
      digitalWrite(equipment, handle);
    } else {
      printf("%s is already closed\n", equipment_str);
      return -1;
    }
  }
  return 0;
}

int toggle_equipment(char *equipment_str) {
  int equipment;
  if ((equipment = convert_str_to_equipment(equipment_str)) == -1) {
    printf("unknow equipment: %s\n", equipment_str);
    printf("valid equipments:\n%s\n", EQUIPMENT_STR);
    return -1;
  } if ((equipment = convert_str_to_equipment(equipment_str)) == -2) {
	init_equipments();
	equipment = EQUIPMENT_TABLE_LIGHT;
	if (digitalRead(equipment) == OPEN_EQUIPMENT) {
	    syslog(LOG_DEBUG, "Handle close tl\n");
	    printf("Handle close tl\n");
	    digitalWrite(equipment, CLOSE_EQUIPMENT);
	} else {
	    exit_auto_process("tl");
	    syslog(LOG_DEBUG, "Handle open tl\n");
	    printf("Handle open tl\n");
	    digitalWrite(equipment, OPEN_EQUIPMENT);
      }
	equipment = EQUIPMENT_STAIR_LIGHT;
	if (digitalRead(equipment) == OPEN_EQUIPMENT) {
	    syslog(LOG_DEBUG, "Handle close sl");
	    printf("Handle close sl\n");
	    digitalWrite(equipment, CLOSE_EQUIPMENT);
	} else {
	    exit_auto_process("sl");
	    syslog(LOG_DEBUG, "Handle open sl\n");
	    printf("Handle open sl\n");
	    digitalWrite(equipment, OPEN_EQUIPMENT);
      }
	equipment = EQUIPMENT_BED_LIGHT;
	if (digitalRead(equipment) == OPEN_EQUIPMENT) {
	    syslog(LOG_DEBUG, "Handle close bl\n");
	    printf("Handle close bl\n");
	    digitalWrite(equipment, CLOSE_EQUIPMENT);
	} else {
	    exit_auto_process("bl");
	    syslog(LOG_DEBUG, "Handle open bl\n");
	    printf("Handle open bl\n");
	    digitalWrite(equipment, OPEN_EQUIPMENT);
      }
	equipment = EQUIPMENT_BED_FAN;
	if (digitalRead(equipment) == OPEN_EQUIPMENT) {
	    syslog(LOG_DEBUG, "Handle close bf\n");
	    printf("Handle close bf\n");
	    digitalWrite(equipment, CLOSE_EQUIPMENT);
      } else {
	    exit_auto_process("bf");
	    syslog(LOG_DEBUG, "Handle open bf\n");
	    printf("Handle open  bf\n");
	    digitalWrite(equipment, OPEN_EQUIPMENT);
      }
      return 0;
  }
  init_equipments();
  if (digitalRead(equipment) == OPEN_EQUIPMENT) {
    syslog(LOG_DEBUG, "Handle close equipment: %s\n", equipment_str);
    printf("Handle close equipment: %s\n", equipment_str);
    digitalWrite(equipment, CLOSE_EQUIPMENT);
  } else {
    exit_auto_process(equipment_str);
    syslog(LOG_DEBUG, "Handle open equipment: %s\n", equipment_str);
    printf("Handle open equipment: %s\n", equipment_str);
    digitalWrite(equipment, OPEN_EQUIPMENT);
  }
  return 0;
}

int convert_str_to_equipment(char * str) {
//   printf("converting equipment string: %s\n", str);
  if(strcmp(str, "table-light") == 0 || !strcmp(str, "tl")) {
    return EQUIPMENT_TABLE_LIGHT;
  } else if (strcmp(str, "stair-light") == 0 || !strcmp(str, "sl")) {
    return EQUIPMENT_STAIR_LIGHT;
  } else if (!strcmp(str, "bed-light") || !strcmp(str, "bl")) {
    return EQUIPMENT_BED_LIGHT;
  } else if (!strcmp(str, "bed-fan") || !strcmp (str, "bf")) {
    return EQUIPMENT_BED_FAN;
  } else if (!strcmp(str, "a") || !strcmp(str, "all")) {
    return -2;
  }
  return -1;
}