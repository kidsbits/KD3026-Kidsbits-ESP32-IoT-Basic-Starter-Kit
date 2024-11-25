/*  
  Project name: LED_BLINK 
  Function: LED BLINK
  Author: keyestudio    
  Hardware connection:  
    - Connect RED LED to digital port 17  
  Library:  
    - none (no need to import additional library)  
  Cautions:  
    - Ensure the LED is connected to digital port IO17  
    - Before uploading test code, please correctly connect to the development board and port  
*/    
#define RED_LED_PIN 17   //Connect the red LED to port IO17
  
void setup() {  
  // Initialize the digital port to output  
  pinMode(RED_LED_PIN, OUTPUT);  
}  
  
void loop() {  
  // LED on
  digitalWrite(RED_LED_PIN, HIGH);  
  // delay 500ms  
  delay(500);  
  // LED off
  digitalWrite(RED_LED_PIN, LOW);  
  // delay 500ms  
  delay(500);  
}
