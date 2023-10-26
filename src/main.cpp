#include <Arduino.h>

#include <Arduino_FreeRTOS.h>

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/
#include "lcd_task/lcd_task.h"
#include "serial_task/serial_task.h"
#include "dht_task/dht_task.h"
#include "mq2_task/mq2_task.h"
#include "light_task/light_task.h"
#include "win_task/win_task.h"
#include "fan_task/fan_task.h"
#include "rain_task/rain_task.h"
#include "menu_task/menu_task.h"
#include "automate_task/automate_task.h"


// the setup function runs once when you press reset or power the board
void setup() {

  // Set up Tasks to run independently.

  xTaskCreate(
    LCD_Task
    ,  "LCD_Task"  // A name just for humans
    ,  512  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    SERIAL_Task
    ,  "SERIAL_Task"
    ,  512  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  xTaskCreate(
    DHT_Task
    ,  "DHT_Task"
    ,  512  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

 xTaskCreate(
    MQ2_Task
    ,  "MQ2_Task"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

 xTaskCreate(
    RAIN_Task
    ,  "RAIN_Task"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

 xTaskCreate( 
    LIGHT_Task
    ,  "LIGHT_Task"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

 xTaskCreate(
    WIN_Task
    ,  "WIN_Task"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

 xTaskCreate(
    FAN_Task
    ,  "FAN_Task"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

 xTaskCreate(
    MENU_Task
    ,  "MENU_Task"
    ,  256  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

 xTaskCreate(
    AUTOMATE_Task
    ,  "AUTOMATE_Task"
    ,  256  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}
