#include "Arduino.h"
#include "serial_task.h"
#include "dht_task/dht_task.h"
#include "mq2_task/mq2_task.h"
#include "win_task/win_task.h"
#include "light_task/light_task.h"
#include "fan_task/fan_task.h"
#include "rain_task/rain_task.h"

void SERIAL_Task(void *pvParameters) // This is a Task.
{

  SERIAL_setup();

  for (;;)
  {

    SERIAL_loop();

    vTaskDelay(1); // one tick delay (15ms) in between reads for stability
  }
}

void SERIAL_setup()
{
  Serial.begin(9600);
  Serial.println("================================");
  Serial.println("|  MicroLab Smart Home On-Line |");
  Serial.println("================================");

}

void SERIAL_loop()
{
  // command line interpreter
  if (Serial.available()) // verificam daca avem caractere in interfata seriala
  {
    char cmd = Serial.read(); // citim caracter din interd=fata seriala
    if (cmd == 'h')           // detectam coincidenta cu un caracter specific 'h'
    {
      Serial.println("Hello World");
    }
    else if (cmd == 'n') // detectam coincidenta cu un caracter specific 'h'
    {
      Serial.println(" NO Hello World");
    }
  }

  // Raportare stare module

  Serial.println("=== SMART HOME Status report ===");
  
  SERIAL_LIGHT_Task_Report();
  SERIAL_WIN_Task_Report();
  SERIAL_FAN_Task_Report();

  SERIAL_DHT_Temperature_Report();
  SERIAL_DHT_TempIndC_Report();
  SERIAL_DHT_Fahrenheit_Report();
  SERIAL_DHT_TempIndH_Report();
  SERIAL_DHT_Humidity_Report();
  SERIAL_MQ2_Task_GasLevel_Report();
  SERIAL_RAIN_Task_RainLevel_Report();

  vTaskDelay(2000 / portTICK_PERIOD_MS);
}

// va fi chemata din un task responsabil de Serial
void SERIAL_LIGHT_Task_Report()
{
  int light_state = LIGHT_GetState();

  Serial.print("[ BL Task ] - ");
  if (light_state == LOW)
    Serial.println("Light is OFF");
  else if (light_state == HIGH)
    Serial.println("Light is ON");
  else
    Serial.println("Undefined Light State");
}

void SERIAL_FAN_Task_Report()
{
  int fan_state = FAN_GetState();

  Serial.print("[ FAN Task ] - ");
  if (fan_state == HIGH)
    Serial.println("FAN is OFF");
  else if (fan_state == LOW)
    Serial.println("FAN is ON");
  else
    Serial.println("Undefined FAN State");
}

void SERIAL_WIN_Task_Report()
{
  int win_state = WIN_GetState();

  Serial.print("[ WIN Task ] - ");
  if (win_state == WIN_STATE_OPEN)
    Serial.println("Window is OPEN");
  else if (win_state == WIN_STATE_OPENING)
    Serial.println("Window is OPENING");
  else if (win_state == WIN_STATE_CLOSED)
    Serial.println("Window is CLOSED");
  else if (win_state == WIN_STATE_CLOSING)
    Serial.println("Window is CLOSING");
  else
    Serial.println("Undefined WINDOW State");
}

void SERIAL_DHT_Temperature_Report()
{
  float t = DHT_Task_GetTemperature();
  Serial.print("[ DHT Task ] - ");
  Serial.print(" Temperature: ");
  Serial.print(t);
  Serial.println(" 'C");
}

void SERIAL_DHT_Fahrenheit_Report()
{
  float f = DHT_Task_GetFahrenheit();
  Serial.print("[ DHT Task ] - ");
  Serial.print(" Fahrenheit: ");
  Serial.print(f);
  Serial.println(" F: ");
}

void SERIAL_DHT_Humidity_Report()
{
  float h = DHT_Task_GetHumidity();
  Serial.print("[ DHT Task ] - ");
  Serial.print(" Humidity: ");
  Serial.print(h);
  Serial.println(" %: ");
}

void SERIAL_DHT_TempIndC_Report()
{
  float h = DHT_Task_GetHeatIndex_C();
  Serial.print("[ DHT Task ] - ");
  Serial.print(" Temperature Index : ");
  Serial.print(h);
  Serial.println(" 'C");
}

void SERIAL_DHT_TempIndH_Report()
{
  float h = DHT_Task_GetHeatIndex_F();
  Serial.print("[ DHT Task ] - ");
  Serial.print(" Temperature Index: ");
  Serial.print(h);
  Serial.println(" F");
}

void SERIAL_MQ2_Task_GasLevel_Report()
{
  float h = MQ2_GetGasLevel();
  Serial.print("[ MQ2 Task ] - ");
  Serial.print(" Gas Level: ");
  Serial.print(h);
  Serial.println(" %");
}

void SERIAL_RAIN_Task_RainLevel_Report()
{
  float h = RAIN_GetRainLevel();
  Serial.print("[ RAIN Task ] - ");
  Serial.print(" Moisture Level: ");
  Serial.print(h);
  Serial.println(" %");
}
