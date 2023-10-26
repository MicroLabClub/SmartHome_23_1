// https://circuitdigest.com/microcontroller-projects/interfacing-rain-sensor-with-arduino
// Sensor pins pin D6 LED output, pin A0 analog Input
#include "Arduino.h"
#include "rain_task.h"
#include "pinmap.h"

#ifndef RAIN_SENSOR_PIN
#define RAIN_SENSOR_PIN A1
#endif


void RAIN_Task(void *pvParameters) // This is a Task.
{

    RAIN_setup();

    for (;;)
    {
        RAIN_loop();

        vTaskDelay(1); // one tick delay (15ms) in between reads for stability
    }
}

int RAIN_ReadSensor(void);

void RAIN_setup()
{
    pinMode(RAIN_SENSOR_PIN, INPUT);
}

void RAIN_loop()
{
    RAIN_ReadSensor();
    vTaskDelay(500 / portTICK_PERIOD_MS);
}

unsigned int RAIN_outputValue;

//  This function returns the analog data to calling function
int RAIN_ReadSensor()
{
    int sensorValue = analogRead(RAIN_SENSOR_PIN);             // Read the analog value from sensor
    int RAIN_outputValue = map(sensorValue, 0, 1023, 255, 0); // map the 10-bit data to 8-bit data
    return RAIN_outputValue;                                  // Return analog moisture value
}

int RAIN_GetRainLevel()
{
    return RAIN_outputValue;
}