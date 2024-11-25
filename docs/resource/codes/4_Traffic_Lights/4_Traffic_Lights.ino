/*  
  Project name: 4_Traffic_Lights
  Function: Traffic light module simulates traffic light control
  Author: keyestudio    
  Hardware connection:  
    - Connect to port 9 
  Library:  
    - none (no need to import additional library)  
  Cautions:  
    - Ensure connect to port 9   
    - Before uploading test code, please correctly connect to the development board and port
*/

#define RED_LED_PIN 17     //Connect the red LED to port IO17
#define YELLOW_LED_PIN 18  //Connect the yellow LED to port IO18
#define GREEN_LED_PIN 19   //Connect the green LED to port IO19

void setup() {
  // Initialize the digital port to output
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

void loop() {
  // green LED on
  digitalWrite(GREEN_LED_PIN, HIGH);
  // Delay 5000ms
  delay(5000);
  // green LED off
  digitalWrite(GREEN_LED_PIN, LOW);
  // yellow LED blinks for three times
  for (int i = 0; i < 3; i++) {
    digitalWrite(YELLOW_LED_PIN, HIGH);
    delay(500);
    digitalWrite(YELLOW_LED_PIN, LOW);
    delay(500);
  }
  // red LED on
  digitalWrite(RED_LED_PIN, HIGH);
  // Delay 5000ms
  delay(5000);
  //red LED off
  digitalWrite(RED_LED_PIN, LOW);
}
