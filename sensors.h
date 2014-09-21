#include <wiringPi.h>
#include <stdio.h>

//座位传感器
#define SENSOR_SEAT_PERSON				0
//光线传感器
#define SENSOR_LIGHT						1
//床上风扇控制传感器
#define SENSOR_BED_FAN_PERSON 			2
//床头灯控制传感器
#define SENSOR_BED_LIGHT_PERSON		3
//扶梯灯控制传感器
#define SENSOR_STAIR_PERSON				4
//门口监测控制传感器
#define SENSOR_DOOR_PERSON				5
//温度传感器
#define SENSOR_TEMPERATURE				6

//各传感器的触发值
//此时为座位上有人
#define TRIG_SEAT_PERSON					0
//此时为外界亮度低于阀值，各照明设备需要开始工作
#define TRIG_LIGHT							1
//此时为床上有人躺着，需要开风扇
#define TRIG_BED_FAN_PERSON 				1
//此时为床上有人坐着，需要开床头灯
#define TRIG_BED_LIGHT_PERSON			1
//此时为有人经过扶梯，需要打开扶梯灯
#define TRIG_STAIR_PERSON				0
//此时检测到门口有人经过，需要监控
#define TRIG_DOOR_PERSON				1
//此时表示温度高于阀值
#define TRIG_TEMPERATURE				0

//各传感器的非触发值
//此时为座位上无人
#define UNTRIG_SEAT_PERSON					1
//此时为外界亮度高于阀值，各照明设备不需要开始工作
#define UNTRIG_LIGHT							0
//此时为床上无人躺着，不需要开风扇
#define UNTRIG_BED_FAN_PERSON 				0
//此时为床上无人坐着，不需要开床头灯
#define UNTRIG_BED_LIGHT_PERSON			0
//此时为无人经过扶梯，不需要打开扶梯灯
#define UNTRIG_STAIR_PERSON				1
//此时检测到门口无人经过，不需要监控
#define UNTRIG_DOOR_PERSON				0
//此时表示温度低于阀值
#define UNTRIG_TEMPERATURE				1

//检查多少次传感器信息符合后才触发动作
int TIMES_SEAT_PERSON	;
int TIMES_LIGHT;
int TIMES_BED_FAN_PERSON;
int TIMES_BED_LIGHT_PERSON;
int TIMES_STAIR_PERSON;
int TIMES_DOOR_PERSON;
int TIMES_TEMPERATURE;

//每两次读取传感器的时间间隔
int DELAY_SEAT_PERSON;
int DELAY_LIGHT;
int DELAY_BED_FAN_PERSON;
int DELAY_BED_LIGHT_PERSON;
int DELAY_STAIR_PERSON;
int DELAY_DOOR_PERSON;
int DELAY_TEMPERATURE;


int check_sensor(int sensor) ;
