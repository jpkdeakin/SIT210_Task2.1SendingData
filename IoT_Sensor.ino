/* 
  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  float temperature;
*/

#include "thingProperties.h"
#include "DHT.h"

#define read_delay 30000     // delay between readings
#define led_flash_time 300    // how long the led flashes when taking a reading

// Setup DHT
#define DHTPIN 14 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Setup timers
unsigned long last_read = 0; // store last time readings taken

void setup() {
  
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(LED_BUILTIN, OUTPUT);       // Setup LED
  dht.begin();
}

void loop() {
  
  ArduinoCloud.update();

  if (millis() >= (last_read + read_delay))
    {
      last_read = millis();
      temperature = dht.readTemperature(); // Read temperature from DHT
      digitalWrite(LED_BUILTIN, HIGH);
      delay(led_flash_time); 
      digitalWrite(LED_BUILTIN, LOW);
    }
}


/*
  Since Temperature is READ_WRITE variable, onTemperatureChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTemperatureChange()  {
  // Add your code here to act upon Temperature change
}
