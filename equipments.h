#include <wiringPi.h>
#include <stdio.h>
#include <syslog.h>

#define EQUIPMENT_TABLE_LIGHT			8
#define EQUIPMENT_STAIR_LIGHT			9
#define EQUIPMENT_BED_FAN				10
#define EQUIPMENT_BED_LIGHT				11

#define TRIG_TABLE_LIGHT					1
#define TRIG_STAIR_LIGHT					1
#define TRIG_BED_FAN						1
#define TRIG_BED_LIGHT					1
#define OPEN_EQUIPMENT					1

#define UNTRIG_TABLE_LIGHT				0
#define UNTRIG_STAIR_LIGHT				0
#define UNTRIG_BED_FAN					0
#define UNTRIG_BED_LIGHT					0
#define CLOSE_EQUIPMENT					0

//自动控制模式下触发工作后绝对持续工作时间，以秒为单位，在此期间不检测传感器状态
int KEEP_TABLE_LIGHT;
int KEEP_STAIR_LIGHT;
int KEEP_BED_LIGHT;
int KEEP_BED_FAN;
int KEEP_CAMERA;

#define EQUIPMENT_STR					"table-light(tl), bed-light(bl), stair-light(sl), bed-fan(bf), all(a)"

int init_equipments();
int handle_equipment(int handle, char *equipment_str);
int toggle_equipment(char *equipment_str);
int convert_str_to_equipment(char * str);