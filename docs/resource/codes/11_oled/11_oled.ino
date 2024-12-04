/*  
  Project name: 11_oled
  Function: OLED display characters
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

#include <Adafruit_GFX.h>    // Core graphics library  
#include <Adafruit_SSD1306.h> // Hardware-specific library for SSD1306  
  
// Creating SSD1306 display objects (using I2C interface) 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED displays height, in pixels
  
// Declares an SSD1306 display object  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);  
  
void setup() {  
  // Initialize serial communication (optional, for debugging)  
  Serial.begin(115200);  
    
  // Initialize the display, 0x3C is the I2C address
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));  
    while(1); // quit  
  }  
    
  // Clear display buffer  
  display.clearDisplay();  
    
  // Set the text color to white
  display.setTextColor(SSD1306_WHITE);  
    
  // Set text size (1 indicates normal size)  
  display.setTextSize(1);  
    
  // Sets the start position of the text 
  display.setCursor(0,0);  

  // Displays the first line of text  
  display.println("Hello, World!");  
    
  // Move to next line (Wrap)  
  // Or you can manually set the cursor position 
  // display.setCursor(0,10); // Starting position of the second line (y coordinate can be adjusted according to font height)
    
  // Displays the second line of text 
  display.println("Hello, Keyestudio!");  
    
  // Update display content 
  display.display();  
}  
  
void loop() {  
  // no need to do anything in the loop unless you want to dynamically update the display 
}