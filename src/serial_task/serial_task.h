#ifndef SERIAL_TASK_H_
#define SERIAL_TASK_H_

#include <Arduino_FreeRTOS.h>

void SERIAL_Task( void *pvParameters );

void SERIAL_setup();
void SERIAL_loop();

void SERIAL_LIGHT_Task_Report();
void SERIAL_WIN_Task_Report();
void SERIAL_FAN_Task_Report();
void SERIAL_DHT_Temperature_Report();
void SERIAL_DHT_Fahrenheit_Report();
void SERIAL_DHT_Humidity_Report();
void SERIAL_DHT_TempIndC_Report();
void SERIAL_DHT_TempIndH_Report();
void SERIAL_MQ2_Task_GasLevel_Report();
void SERIAL_RAIN_Task_RainLevel_Report();


#endif