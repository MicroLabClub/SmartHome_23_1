#ifndef MQ2_TASK_H_
#define MQ2_TASK_H_
#include "Arduino.h"
#include <Arduino_FreeRTOS.h>

// Sensor pins pin D6 LED output, pin A0 analog Input
#include "pinmap.h"

#ifndef MQ_SENSOR_PIN
#define MQ_SENSOR_PIN A0
#endif


void MQ2_Task( void *pvParameters );

void MQ2_setup();
void MQ2_loop();
int MQ2_GetGasLevel();


#endif