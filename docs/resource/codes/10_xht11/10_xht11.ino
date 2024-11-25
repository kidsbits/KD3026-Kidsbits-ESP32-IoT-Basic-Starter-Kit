/*  
  Project name: 10_xht11
  Function: Read the analog value of the sound sensor
  Author: keyestudio    
  Hardware connection:  
    - Connect to port 4 
  Library:  
    - DHT-sensor-library-master
  Cautions:  
    - Connect to port 4   
    - Before uploading test code, please correctly connect to the development board and port
    - Set the baud rate to 9600 before using serial monitor printing
    - Before uploading test code, the library must be imported
*/

#include <DHT.h>
//Define the XHT11 read data pin as IO27
#define xht11_Pin 27  
//Create an instance of the DHT class named dht. The DHT class is provided by the DHT.h library for communication with the DHT11(XHT11) sensor.
//XHT11 is fully compatible with DHT11's code
DHT dht(xht11_Pin,DHT11)

void setup() {
  //Set the baud rate
  Serial.begin(9600);
  //Initialize the XHT11 sensor
  dht.begin();
}

void loop() {
  // Reading  humidity
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);  

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("   Temperature: ");
  Serial.print(t);
  Serial.print("°C ");
  Serial.print(f);
  Serial.println("°F");
  // Wait a few seconds between measurements.
  delay(2000);
}
