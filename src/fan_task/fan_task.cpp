#include "fan_task.h"

void FAN_Task(void *pvParameters) // This is a Task.
{

    FAN_setup();

    for (;;)
    {

        FAN_loop();

        vTaskDelay(1); // one tick delay (15ms) in between reads for stability
    }
}

volatile int fan_state = LOW;

void FAN_setup()
{

    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(FAN_PIN, LOW);

    pinMode(BUTTON_2_PIN, INPUT_PULLUP);
    fan_state = FAN_STATE_OFF;
}

void FAN_loop()
{

    digitalWrite(FAN_PIN, fan_state);
}

int FAN_GetState()
{
    return fan_state;
}

void FAN_Toggle(void)
{
    if (FAN_IsOff())
        FAN_TurnOn();
    else
        FAN_TurnOff();
}

void FAN_TurnOn()
{
    fan_state = FAN_STATE_ON;
}

void FAN_TurnOff()
{
    fan_state = FAN_STATE_OFF;
}

int FAN_IsOn()
{
    return (fan_state == FAN_STATE_ON);
}
int FAN_IsOff()
{
    return (fan_state == FAN_STATE_OFF);
}

void FAN_Set(int state)
{
    fan_state = state;
}
