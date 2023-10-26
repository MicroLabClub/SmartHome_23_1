#ifndef WIN_TASK_H_
#define WIN_LED_TASK_H_

#include <Arduino_FreeRTOS.h>

void WIN_Task(void *pvParameters);

void WIN_setup();
void WIN_loop();

#define WIN_STATE_OPEN 1
#define WIN_STATE_OPENING 2
#define WIN_STATE_CLOSED 0
#define WIN_STATE_CLOSING 3

int WIN_GetState();
void WIN_Toggle(void);
void WIN_TurnOpen();
void WIN_TurnClose();
int WIN_IsOpen();
int WIN_IsClosed();
void WIN_Set(int state);

#define WIN_STATE_ON HIGH
#define WIN_STATE_OFF LOW

#endif