/*  
  Project name: 13_Automatic_lighting
  Function: The brightness of the led is automatically adjusted by the analog value of the photoresistor
  Author: keyestudio    
  Hardware connection:  
    - Connect photoresistor to port 7
    - Connect traffic light module to port 9
  Library:  
    - none
  Cautions:  
    - Make sure you are connected to the correct port   
    - Before uploading test code, please correctly connect to the development board and port
*/
#define light_Pin 35    //connect the photoresisotr to pin IO35
#define RED_LED_PIN 17  //Connect the red LED to pin IO17

#define redLED_PWM_Channel 1  // Red led light using PWM channel 1
#define pwmFreq 5000          // PWM frequency
#define pwmResolution 8       //Set the PWM resolution to 8 so the value range is 0-255

void setup() {
  //Set IO35 to input
  pinMode(light_Pin, INPUT);
  // initialize PWM
  ledcSetup(redLED_PWM_Channel, pwmFreq, pwmResolution);
  ledcAttachPin(RED_LED_PIN, redLED_PWM_Channel);
}

void loop() {
  //read photoresisotr analog value
  int light_value = analogRead(light_Pin);
  //map photoresisotr analog value to 0-255, so value 4095 = 0; 0 = 255;
  int brightness = 255 - ((light_value * 255) / 4095);
  //Light the led according to the brightness value of the photoresistor
  ledcWrite(redLED_PWM_Channel,brightness);
  //delay 300ms
  delay(300);
}
