#include "menu_task.h"
#include "pinmap.h"
#include "Arduino.h"
#include "lcd_task/lcd_task.h"
#include "light_task/light_task.h"
#include "win_task/win_task.h"

#ifndef MENU_PIN
#define MENU_PIN 25
#endif

#define BUTTON_NO_KEY 0
#define BUTTON_RIGHT_KEY 1
#define BUTTON_LEFT_KEY 2
#define BUTTON_BOTH_KEY 3

#ifndef BUTTON_1_PIN
#define BUTTON_1_PIN 17
#endif

void MENU_Task(void *pvParameters) // This is a Task.
{

    MENU_setup();

    for (;;)
    {

        MENU_loop();

        vTaskDelay(1); // one tick delay (15ms) in between reads for stability
    }
}

void MENU_setup()
{
    pinMode(BUTTON_1_PIN, INPUT_PULLUP);
}

int menu_item = LOW;

int BUTTON_GetKey(void)
{
    int button_1 = digitalRead(BUTTON_1_PIN);
    int button_2 = digitalRead(BUTTON_2_PIN);

    if (button_1 == LOW && button_2 == LOW)
        return BUTTON_BOTH_KEY;
    else if (button_1 == LOW)
        return BUTTON_LEFT_KEY;
    else if (button_2 == LOW)
        return BUTTON_RIGHT_KEY;
    else
        return BUTTON_NO_KEY;
}

void MENU_loop()
{
    int key;
    do
    {
        key = BUTTON_GetKey();
    } while (key == BUTTON_NO_KEY);

    tone(BUZZER_PIN, 3000, 0);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    noTone(BUZZER_PIN);
    vTaskDelay(100 / portTICK_PERIOD_MS);

    // tone(BUZZER_PIN, 3000, 0);
    // vTaskDelay(100 / portTICK_PERIOD_MS);
    // noTone(BUZZER_PIN);
    // vTaskDelay(100 / portTICK_PERIOD_MS);
    //     /* code */
    // }

    if (key == BUTTON_LEFT_KEY)
    {
        if (++menu_item >= MENU_ITEM_NR_OF)
            menu_item = MENU_ITEM_DEFAULT;

        LCD_SetScreeNr(menu_item);

        // for (int i = 0; i < menu_item; i++)
        // {
        //     tone(BUZZER_PIN, 5000, 0);
        //     vTaskDelay(100 / portTICK_PERIOD_MS);
        //     noTone(BUZZER_PIN);
        //     vTaskDelay(100 / portTICK_PERIOD_MS); /* code */
        // }
    }
    else if (key == BUTTON_RIGHT_KEY)
    {

        tone(BUZZER_PIN, 4000, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        noTone(BUZZER_PIN);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        switch (menu_item)
        {
        case MENU_ITEM_LIGHT:
            LIGHT_Toggle();

            break;
        case MENU_ITEM_WIN:
            WIN_Toggle();

            break;

        default:
            break;
        }
    }

    // tone(BUZZER_PIN, 5000, 0);
    // vTaskDelay(500 / portTICK_PERIOD_MS);
    // noTone(BUZZER_PIN);
    // vTaskDelay(100 / portTICK_PERIOD_MS);

    while (BUTTON_GetKey() != BUTTON_NO_KEY)
        ;

    // tone(BUZZER_PIN, 5000, 0);
    // vTaskDelay(500 / portTICK_PERIOD_MS);
    // noTone(BUZZER_PIN);
    // vTaskDelay(100 / portTICK_PERIOD_MS);
}

int MENU_GetState()
{
    return menu_item;
}