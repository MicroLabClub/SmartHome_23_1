#ifndef LIGHT_TASK_H_
#define LIGHT_TASK_H_

#include <Arduino_FreeRTOS.h>

void LIGHT_Task(void *pvParameters);

void LIGHT_setup();
void LIGHT_loop();
int LIGHT_GetState();
void LIGHT_Toggle(void);
void LIGHT_TurnOn();
void LIGHT_TurnOff();
int LIGHT_IsOn();
int LIGHT_IsOff();
void LIGHT_Set(int state);

#define LIGHT_STATE_ON HIGH
#define LIGHT_STATE_OFF LOW

#endif