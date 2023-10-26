#ifndef AUTOMATE_TASK_H_
#define AUTOMATE_TASK_H_

#include "Arduino.h"
#include <Arduino_FreeRTOS.h>

#include "pinmap.h"


#define AUTOMATE_STATE_ON HIGH
#define AUTOMATE_STATE_OFF LOW

void AUTOMATE_Task(void *pvParameters);

void AUTOMATE_setup();
void AUTOMATE_loop();

void AUTOMATE_Set(int state);
int AUTOMATE_GetState();

void AUTOMATE_Toggle(void);

void AUTOMATE_TurnOn();
void AUTOMATE_TurnOff();

int AUTOMATE_IsOn();
int AUTOMATE_IsOff();

#endif