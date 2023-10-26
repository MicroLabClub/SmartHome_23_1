#include "mq2_task.h"


void MQ2_Task( void *pvParameters )  // This is a Task.
{
  MQ2_setup();

  for (;;)
  {
    
    MQ2_loop();

    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}


int MQ2_ReadSensor(void);

unsigned int MQ2_outputValue ;


void MQ2_setup()
{
    pinMode(MQ_SENSOR_PIN, INPUT);
}


void MQ2_loop()
{
    MQ2_outputValue = MQ2_ReadSensor();
    vTaskDelay(500 / portTICK_PERIOD_MS); 
}



//  This function returns the analog data to calling function
int MQ2_ReadSensor()
{
    unsigned int sensorValue = analogRead(MQ_SENSOR_PIN); // Read the analog value from sensor
    int outputValue = map(sensorValue, 0, 1023, 0, 100); // map the 10-bit data to 8-bit data
    return outputValue; // Return analog moisture value
}

int MQ2_GetGasLevel(){
    return MQ2_outputValue;
}