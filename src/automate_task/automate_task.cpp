#include "automate_task.h"
#include "mq2_task/mq2_task.h"
#include "win_task/win_task.h"

void AUTOMATE_Task(void *pvParameters) // This is a Task.
{

    AUTOMATE_setup();

    for (;;)
    {

        AUTOMATE_loop();

        vTaskDelay(1); // one tick delay (15ms) in between reads for stability
    }
}

volatile int automate_state = LOW;

void AUTOMATE_setup()
{

    automate_state = AUTOMATE_STATE_OFF;
}

int GAS_CriticalLevel = 50;
int GAS_SafeLevel = 20;

#define ALARM_ON 1
#define ALARM_OFF 0
int GAS_Alarm = ALARM_OFF;

void AUTOMATE_loop()
{
    // GAS EMERGANCY System
    // Deschidem fereatra la detectarea unui nivel critic de gaz
    int gas_level = MQ2_GetGasLevel();

    if (gas_level > GAS_CriticalLevel)
    {
        GAS_Alarm = ALARM_ON;
    }
    else if (gas_level < GAS_SafeLevel)
    {
        GAS_Alarm = ALARM_OFF;
    }else{
        GAS_Alarm = GAS_Alarm;
    }

    if (GAS_Alarm == ALARM_ON)
    {

        WIN_TurnOpen();

        tone(BUZZER_PIN, 5000, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        noTone(BUZZER_PIN);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        tone(BUZZER_PIN, 4000, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        noTone(BUZZER_PIN);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }


    
}

int AUTOMATE_GetState()
{
    return automate_state;
}

void AUTOMATE_Toggle(void)
{
    if (AUTOMATE_IsOff())
        AUTOMATE_TurnOn();
    else
        AUTOMATE_TurnOff();
}

void AUTOMATE_TurnOn()
{
    automate_state = AUTOMATE_STATE_ON;
}

void AUTOMATE_TurnOff()
{
    automate_state = AUTOMATE_STATE_OFF;
}

int AUTOMATE_IsOn()
{
    return (automate_state == AUTOMATE_STATE_ON);
}
int AUTOMATE_IsOff()
{
    return (automate_state == AUTOMATE_STATE_OFF);
}

void AUTOMATE_Set(int state)
{
    automate_state = state;
}
