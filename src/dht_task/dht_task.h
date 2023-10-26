#ifndef DHT_TASK_H_
#define DHT_TASK_H_

#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "pinmap.h"

#ifndef DHTPIN
#define DHTPIN 2 // Digital pin connected to the DHT sensor
#endif

void DHT_Task( void *pvParameters );

void DHT_setup();
void DHT_loop();

float DHT_Task_GetTemperature();
float DHT_Task_GetHumidity();
float DHT_Task_GetFahrenheit();
float DHT_Task_GetHeatIndex_C();
float DHT_Task_GetHeatIndex_F();

#endif