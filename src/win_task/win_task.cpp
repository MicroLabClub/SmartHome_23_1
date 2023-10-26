/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include "win_task.h"
#include "Arduino.h"
#include <Servo.h>

#ifndef BUTTON_2_PIN
#define BUTTON_2_PIN 16
#endif

#ifndef SERVO_PIN
#define SERVO_PIN 9
#endif

#ifndef BUZZER_PIN
#define BUZZER_PIN 10
#endif

Servo arm_servos; // create servo object to control a servo
// twelve servo objects can be created on most boards

#define SPEED_DELAY 5
#define ANGLE_OPEN 0
#define ANGLE_CLOSE 100

int current_pos = ANGLE_CLOSE; // variable to store the servo position
int target_pos = ANGLE_CLOSE;  // variable to store the servo position
int win_state = WIN_STATE_CLOSED;
int win_state_op = WIN_STATE_CLOSED;

void WIN_Task(void *pvParameters) // This is a Task.
{

    WIN_setup();

    for (;;)
    {
        WIN_loop();
        vTaskDelay(1); // one tick delay (15ms) in between reads for stability
    }
}

void WIN_setup()
{
    arm_servos.attach(SERVO_PIN); // attaches the servo on pin 9 to the servo object
    win_state = LOW;
    // Setarea Buzzer-ului in calitate de OUTPUT.
    pinMode(BUZZER_PIN, OUTPUT);
}

void WIN_loop()
{

    if (current_pos > target_pos)
        current_pos--;
    else if (current_pos < target_pos)
        current_pos++;

    arm_servos.write(current_pos);                   // tell servo to go to position in variable 'pos'
    vTaskDelay(SPEED_DELAY / portTICK_PERIOD_MS); // waits 15 ms for the servo to reach the position

    // tone(BUZZER_PIN, 5000, 0);
    // vTaskDelay(500 / portTICK_PERIOD_MS);
    // noTone(BUZZER_PIN);
    // vTaskDelay(100 / portTICK_PERIOD_MS);

    // Report completion
    if ((win_state == WIN_STATE_CLOSING && target_pos == current_pos) ||
        (win_state == WIN_STATE_OPENING && target_pos == current_pos))
    {

        tone(BUZZER_PIN, 5000, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        noTone(BUZZER_PIN);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        tone(BUZZER_PIN, 5000, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        noTone(BUZZER_PIN);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    // change the status
    if (target_pos == ANGLE_CLOSE && target_pos != current_pos)
        win_state = WIN_STATE_CLOSING;
    else if (target_pos == ANGLE_OPEN && target_pos != current_pos)
        win_state = WIN_STATE_OPENING;
    else if (target_pos == ANGLE_CLOSE && target_pos == current_pos)
        win_state = WIN_STATE_CLOSED;
    else if (target_pos == ANGLE_OPEN && target_pos == current_pos)
        win_state = WIN_STATE_OPEN;
}

void WIN_Toggle(void)
{
    if (WIN_IsOpen())
        WIN_TurnClose();
    else
        WIN_TurnOpen();
}

int WIN_GetState()
{
    return win_state;
}

void WIN_TurnOpen()
{
    target_pos = ANGLE_OPEN;
}

void WIN_TurnClose()
{
    target_pos = ANGLE_CLOSE;
}

int WIN_IsOpen()
{
    return (target_pos == ANGLE_OPEN);
}

int WIN_IsClosed()
{
    return (target_pos == ANGLE_CLOSE);
}

void WIN_Set(int state)
{
    target_pos = state;
}
