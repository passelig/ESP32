// hei

#include "thingProperties.h"
#include <DHT.h>

#define DHTPIN 13       // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22  // Change to DHT11 if you're using that model

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1000); 
  dht.begin();
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  delay(1500); 
  
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
 
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  temperature = dht.readTemperature(); // Read temperature in Celsius
  humidity = dht.readHumidity();       // Read humidity
  
  delay(1000);
}

