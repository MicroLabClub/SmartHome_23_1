
#include "Arduino.h"
#include "lcd_task.h"
#include "dht_task/dht_task.h"
#include "mq2_task/mq2_task.h"
#include "win_task/win_task.h"
#include "light_task/light_task.h"

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

void LCD_Task(void *pvParameters) // This is a Task.
{

  LCD_setup();

  for (;;) // A Task shall never return or exit.
  {

    LCD_loop();

    vTaskDelay(1); // one tick delay (15ms) in between reads for stability
  }
}

void LCD_Screen_DEFAULT(void);
void LCD_Screen_LIGHT(void);
void LCD_Screen_WIN(void);
void LCD_Screen_LIGHT_WIN(void);
void LCD_Screen_2(void);
void LCD_Screen_3(void);
void LCD_Screen_4(void);

void LCD_setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

int LCD_screen_nr = LCD_SCREEN_DEFAULT;

void LCD_loop()
{

  switch (LCD_screen_nr)
  {
  case LCD_SCREEN_DEFAULT:
    LCD_Screen_DEFAULT();
    break;
  case LCD_SCREEN_LIGHT:
    LCD_Screen_LIGHT();
    break;
  case LCD_SCREEN_WIN:
    LCD_Screen_WIN();
    break;
  case LCD_SCREEN_1:
    LCD_Screen_LIGHT_WIN();
    break;
  case LCD_SCREEN_2:
    LCD_Screen_2();
    break;
  case LCD_SCREEN_3:
    LCD_Screen_3();
    break;
  case LCD_SCREEN_4:
    LCD_Screen_4();
    break;

  default:
    LCD_Screen_DEFAULT();

    break;
  }

  // Screen 1:
  // if (++LCD_screen_nr >= LCD_SCREEN_NR_OF)
  //   LCD_screen_nr = LCD_SCREEN_DEFAULT;
  vTaskDelay(2000 / portTICK_PERIOD_MS); // display the above for two seconds
}

void LCD_SetScreeNr(int screenNr)
{

  if (screenNr >= LCD_SCREEN_NR_OF)
    screenNr = LCD_SCREEN_DEFAULT;

  LCD_screen_nr = screenNr;
}

void LCD_Screen_DEFAULT(void)
{
  // Screen 1:
  // lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  lcd.print("Welcome to :");
  lcd.setCursor(0, 1); // move cursor to   (2, 1)
  lcd.print("Smart Home");
}

void LCD_Screen_LIGHT(void)
{
  // Screen 1:
  lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  lcd.print("B2 - Light setting");
  lcd.setCursor(0, 1); // move cursor to   (2, 1)
  LCD_LIGHT_Task_Report();
}

void LCD_Screen_WIN(void)
{
  // Screen 1:
  lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  lcd.print("B2 - Win setting");
  lcd.setCursor(0, 1); // move cursor to   (2, 1)
  LCD_WIN_Task_Report();
}

void LCD_Screen_LIGHT_WIN(void)
{
  // Screen 1:
  lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  LCD_LIGHT_Task_Report();
  lcd.setCursor(0, 1); // move cursor to   (2, 1)
  LCD_WIN_Task_Report();
}
void LCD_Screen_2(void)
{
  // Screen 2:
  lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  LCD_DHT_Temperature_Report();
  lcd.setCursor(0, 1); // move cursor to   (2, 1)
  LCD_DHT_TempIndC_Report();
}
void LCD_Screen_3(void)
{

  // Screen 3:
  lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  LCD_DHT_Fahrenheit_Report();
  lcd.setCursor(0, 1); // move cursor to   (2, 1)
  LCD_DHT_TempIndH_Report();
}
void LCD_Screen_4(void)
{

  // Screen 4:
  lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  LCD_DHT_Humidity_Report();
  lcd.setCursor(0, 1); // move cursor to   (2, 1)
  LCD_MQ2_Task_GasLevel_Report();
}

// va fi chemata din un task responsabil de Serial
void LCD_LIGHT_Task_Report()
{
  int light_state = LIGHT_GetState();

  if (light_state == LOW)
    lcd.print("Light is OFF");
  else if (light_state == HIGH)
    lcd.print("Light is ON");
  else
    lcd.print("Undefined Light State");
}

void LCD_WIN_Task_Report()
{
  int win_state = WIN_GetState();

  if (win_state == WIN_STATE_OPEN)
    lcd.print("Win: OPEN       ");
  else if (win_state == WIN_STATE_OPENING)
    lcd.print("Win: OPENING    ");
  else if (win_state == WIN_STATE_CLOSED)
    lcd.print("Win: CLOSED     ");
  else if (win_state == WIN_STATE_CLOSING)
    lcd.print("Win: CLOSING    ");
  else
    lcd.print("Win: Undefined  ");
}

void LCD_DHT_Temperature_Report()
{
  float t = DHT_Task_GetTemperature();
  lcd.print(" Temp: ");
  lcd.print(t);
  lcd.print(" 'C");
}

void LCD_DHT_Fahrenheit_Report()
{
  float f = DHT_Task_GetFahrenheit();
  lcd.print(" Temp: ");
  lcd.print(f);
  lcd.print(" F: ");
}

void LCD_DHT_Humidity_Report()
{
  float h = DHT_Task_GetHumidity();
  lcd.print(" Hum: ");
  lcd.print(h);
  lcd.print(" %: ");
}

void LCD_DHT_TempIndC_Report()
{
  float h = DHT_Task_GetHeatIndex_C();
  lcd.print(" Feel : ");
  lcd.print(h);
  lcd.print(" 'C");
}

void LCD_DHT_TempIndH_Report()
{
  float h = DHT_Task_GetHeatIndex_F();
  lcd.print(" Feel : ");
  lcd.print(h);
  lcd.print(" F");
}

void LCD_MQ2_Task_GasLevel_Report()
{
  float h = MQ2_GetGasLevel();
  lcd.print(" Gas : ");
  lcd.print(h);
  lcd.print(" %");
}
