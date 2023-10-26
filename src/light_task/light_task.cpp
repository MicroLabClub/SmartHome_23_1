#include "light_task.h"
#include "pinmap.h"

#include "Arduino.h"

#ifndef LED_R_PIN
#define LED_R_PIN 4
#endif

#ifndef LED_G_PIN
#define LED_G_PIN 5
#endif

#ifndef LED_B_PIN
#define LED_B_PIN 6
#endif



void LIGHT_Task(void *pvParameters) // This is a Task.
{

    LIGHT_setup();

    for (;;)
    {

        LIGHT_loop();

        vTaskDelay(1); // one tick delay (15ms) in between reads for stability
    }
}

volatile int light_state = LOW;

void LIGHT_setup()
{

    pinMode(LED_R_PIN, OUTPUT);
    pinMode(LED_G_PIN, OUTPUT);
    pinMode(LED_B_PIN, OUTPUT);
    digitalWrite(LED_R_PIN, LOW);
    digitalWrite(LED_G_PIN, LOW);
    digitalWrite(LED_B_PIN, LOW);

    pinMode(BUTTON_2_PIN, INPUT_PULLUP);
    light_state = LIGHT_STATE_OFF;
}

void LIGHT_loop()
{

    digitalWrite(LED_R_PIN, light_state);
    digitalWrite(LED_G_PIN, light_state);
    digitalWrite(LED_B_PIN, light_state);

}


int LIGHT_GetState()
{
    return light_state;
}


void LIGHT_Toggle(void)
{
    if (LIGHT_IsOff())
        LIGHT_TurnOn();
    else
        LIGHT_TurnOff();
}

void LIGHT_TurnOn()
{
    light_state = LIGHT_STATE_ON;
}

void LIGHT_TurnOff()
{
    light_state = LIGHT_STATE_OFF;
}

int LIGHT_IsOn()
{
    return (light_state == LIGHT_STATE_ON);
}
int LIGHT_IsOff()
{
    return (light_state == LIGHT_STATE_OFF);
}

void LIGHT_Set(int state)
{
    light_state = state;
}
