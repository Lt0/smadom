smadom: smadom.o daemon.o sensors.o equipments.o wifi_identify.o config.o common_string.o auto_control.o
	gcc -g -o smadom smadom.o daemon.o sensors.o equipments.o wifi_identify.o config.o common_string.o auto_control.o -lwiringPi
	
tl: auto_table_light.o daemon.o sensors.o equipments.o wifi_identify.o config.o common_string.o auto_control.o
	gcc -o auto_table_light auto_table_light.o daemon.o sensors.o equipments.o wifi_identify.o config.o common_string.o auto_control.o -lwiringPi
	
sl: auto_stair_light.o daemon.o sensors.o equipments.o wifi_identify.o config.o common_string.o auto_control.o
	gcc -o auto_stair_light auto_stair_light.o daemon.o sensors.o equipments.o wifi_identify.o config.o common_string.o auto_control.o -lwiringPi

bl: auto_bed_light.o daemon.o sensors.o equipments.o wifi_identify.o config.o common_string.o auto_control.o
	gcc -o auto_bed_light auto_bed_light.o daemon.o sensors.o equipments.o wifi_identify.o config.o common_string.o auto_control.o -lwiringPi

bf: auto_bed_fan.o daemon.o sensors.o equipments.o wifi_identify.o config.o common_string.o auto_control.o
	gcc -o auto_bed_fan auto_bed_fan.o daemon.o sensors.o equipments.o wifi_identify.o config.o common_string.o auto_control.o -lwiringPi
	
smadom.o: smadom.c
	gcc -g -c smadom.c
	
auto_table_light.o: auto_table_light.c
	gcc -g -c auto_table_light.c

auto_stair_light.o: auto_stair_light.c
	gcc -g -c auto_stair_light.c

auto_bed_light.o: auto_bed_light.c
	gcc -g -c auto_bed_light.c
	
auto_bed_fan.o: auto_bed_fan.c
	gcc -g -c auto_bed_fan.c
	
daemon.o: daemon.c
	gcc -g -c daemon.c
	
sensors.o: sensors.c
	gcc -g -c sensors.c
	
equipments.o: equipments.c
	gcc -g -c equipments.c

wifi_identify.o: wifi_identify.c
	gcc -g -c wifi_identify.c
	
config.o: config.c common_string.c
	gcc -g -c config.c common_string.c
	
auto_control.o: auto_control.c
	gcc -g -c auto_control.c


	
clean:
	rm -f ./*.o smadom auto_table_light auto_stair_light auto_bed_light auto_bed_fan
	
