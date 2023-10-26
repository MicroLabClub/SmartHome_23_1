#include "dht_task.h"
#include "DHT.h"

// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
// #define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

void DHT_Task( void *pvParameters )  // This is a Task.
{

  DHT_setup();

  for (;;)
  {
    
    DHT_loop();

    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}


void DHT_setup()
{
  dht.begin();
}


float h = 0;
// Temperature as Celsius (the default)
float t = 0;
// Temperature as Fahrenheit (isFahrenheit = true)
float f = 0;
// Heat index in Fahrenheit (the default)
float hif = 0;
// Heat index in Celsius (isFahreheit = false)
float hic = 0;

void DHT_loop()
{
  // Wait a few seconds between measurements.
  vTaskDelay(2000/ portTICK_PERIOD_MS);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
   h = dht.readHumidity();
  // Read temperature as Celsius (the default)
   t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
   f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f))
  {
    //Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
   hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
   hic = dht.computeHeatIndex(t, h, false);
}

float DHT_Task_GetTemperature()
{
  return t;
}

float DHT_Task_GetHeatIndex_C()
{
  return hic;
}

float DHT_Task_GetHeatIndex_F()
{
  return hif;
}

float DHT_Task_GetHumidity()
{
  return h;
}

float DHT_Task_GetFahrenheit()
{
  return f;
}