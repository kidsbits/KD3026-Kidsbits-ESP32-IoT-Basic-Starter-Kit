/*  
  Project name: 14_Environment_Detection
  Function: The OLED displays the value of temperature and humidity
  Author: keyestudio    
  Hardware connection:  
    - none
  Library:  
    - Adafruit_SSD1306
    - Adafruit_GFX
  Cautions:  
    - Before uploading test code, please correctly connect to the development board and port
    - Before uploading test code, the library must be imported
*/
#include <DHT.h>
#include <Adafruit_GFX.h>      // Core graphics library
#include <Adafruit_SSD1306.h>  // Hardware-specific library for SSD1306

//Define the XHT11 read data pin as IO27
#define xht11_Pin 27
// Creating SSD1306 display objects (using I2C interface)
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

DHT dht(xht11_Pin, DHT11);

// Declare an SSD1306 display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char str_T[10];
char str_F[10];
char str_H[10];


void setup() {
  // Initialize serial communication (optional, for debugging)
  Serial.begin(9600);
    //Initialize the XHT11 sensor
  dht.begin();

  // Initialize the display, 0x3C is the I2C address
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // quit
  }
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
  //Convert the humidity value to a string and stores it in the str_H array
  dtostrf(h, 6, 2, str_H);
  //Convert the value of temperature Celsius to a string and stores it in the array str_T
  dtostrf(t, 6, 2, str_T);
  //Converts the temperature Fahrenheit to a string and stores it in the array str_F
  dtostrf(f, 6, 2, str_F);

  // Clear display buffer
  display.clearDisplay();
  // Set the text color to white
  display.setTextColor(SSD1306_WHITE);
  // Set the text size, 2 for larger
  display.setTextSize(2);
  // Set the start position of the text
  display.setCursor(0, 0);
  // The first line shows the value of humidity
  display.print("H:");
  display.print(str_H);
  display.println(" %");
  // The second line shows the value of temperature Celsius
  display.print("T:");
  display.print(str_T);
  display.println(" C");
  // The third line shows the value of temperature Fahrenheit
  display.print("F:");
  display.print(str_F);
  display.println(" F");
  // Update display content
  display.display();
  delay(2000);
}