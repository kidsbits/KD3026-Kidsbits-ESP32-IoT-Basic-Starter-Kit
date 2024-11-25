/*  
  Project name: 3_Flowing_light 
  Function: Control the red, yellow and green LED to show the effect of water flow
  Author: keyestudio    
  Hardware connection:  
    - Connect to port 9 
  Library:  
    - none (no need to import additional library)  
  Cautions:  
    - Ensure that connect to port 9   
    - Before uploading test code, please correctly connect to the development board and port   
*/    
#define RED_LED_PIN 17      //Connect the red LED to port IO17
#define YELLOW_LED_PIN 18   //Connect the yellow LED to port IO18
#define GREEN_LED_PIN 19    //Connect the green LED to port IO19
  
void setup() {  
  // Initialize the digital port to output  
  pinMode(RED_LED_PIN, OUTPUT);  
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}  
  
void loop() {  
  // red LED on, yellow and green LED off
  digitalWrite(RED_LED_PIN, HIGH);  
  digitalWrite(YELLOW_LED_PIN, LOW);  
  digitalWrite(GREEN_LED_PIN, LOW);  
  // Delay 300ms  
  delay(300);  
  // yellow LED on, red and green LED off
  digitalWrite(RED_LED_PIN, LOW);  
  digitalWrite(YELLOW_LED_PIN, HIGH);  
  digitalWrite(GREEN_LED_PIN, LOW);   
  // Delay 300ms  
  delay(300);  
  // green LED on, red and yellow LED off
  digitalWrite(RED_LED_PIN, LOW);  
  digitalWrite(YELLOW_LED_PIN, LOW);  
  digitalWrite(GREEN_LED_PIN, HIGH);   
  // Delay 300ms  
  delay(300);  
}
