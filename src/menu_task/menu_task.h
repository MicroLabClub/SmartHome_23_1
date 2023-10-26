#ifndef MENU_TASK_H_
#define MENU_TASK_H_

#include <Arduino_FreeRTOS.h>

void MENU_Task( void *pvParameters );

void MENU_setup();
void MENU_loop();

int MENU_GetState();
int BUTTON_GetKey(void);

enum MENU_item_t
{
  MENU_ITEM_DEFAULT,
  MENU_ITEM_LIGHT,
  MENU_ITEM_WIN,
  MENU_ITEM_1,
  MENU_ITEM_2,
  MENU_ITEM_3,
  MENU_ITEM_4,
  MENU_ITEM_NR_OF

};



#endif