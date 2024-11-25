/*  
  Project name: 2_PWM_LED 
  Function: Control LED brightness, from dark to light and then from light to dark. 
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
   // initialize PWM
  pinMode(RED_LED_PIN,OUTPUT);
}  
  
void loop() {  
	
  for(int i = 0;i <= 255;i++){
    analogWrite(RED_LED_PIN,i);
    delay(10);
  }
  for(int i = 255;i >= 0;i--){
    analogWrite(RED_LED_PIN,i);
    delay(10);
  }
}
