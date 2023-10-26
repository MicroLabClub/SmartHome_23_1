#ifndef FAN_TASK_H_
#define FAN_TASK_H_

#include "Arduino.h"
#include <Arduino_FreeRTOS.h>

#include "pinmap.h"

#ifndef FAN_PIN
#define FAN_PIN 6
#endif

#define FAN_STATE_ON HIGH
#define FAN_STATE_OFF LOW

void FAN_Task(void *pvParameters);

void FAN_setup();
void FAN_loop();

void FAN_Set(int state);
int FAN_GetState();

void FAN_Toggle(void);

void FAN_TurnOn();
void FAN_TurnOff();

int FAN_IsOn();
int FAN_IsOff();

#endif