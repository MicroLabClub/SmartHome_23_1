#ifndef LCD_TASK_H_
#define LCD_TASK_H_

#include <Arduino_FreeRTOS.h>

void LCD_Task( void *pvParameters );

void LCD_setup();
void LCD_loop();

void LCD_SetScreeNr(int screenNr);

enum LCD_screen_t
{
  LCD_SCREEN_DEFAULT,
  LCD_SCREEN_LIGHT,
  LCD_SCREEN_WIN,
  LCD_SCREEN_1,
  LCD_SCREEN_2,
  LCD_SCREEN_3,
  LCD_SCREEN_4,
  LCD_SCREEN_NR_OF

} ;


// va fi chemata din un task responsabil de LCD
void LCD_LIGHT_Task_Report();
void LCD_WIN_Task_Report();
void LCD_DHT_Temperature_Report();
void LCD_DHT_Fahrenheit_Report();
void LCD_DHT_Humidity_Report();
void LCD_DHT_TempIndC_Report();
void LCD_DHT_TempIndH_Report();
void LCD_MQ2_Task_GasLevel_Report();
#endif