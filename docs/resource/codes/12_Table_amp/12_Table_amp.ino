/*  
  Project name: 12_Table_amp
  Function: Button control LED on and off
  Author: keyestudio    
  Hardware connection:  
    - Connect button module to port 3
    - Connect traffic light module to port 9
  Library:  
    - none (no need to import additional library)  
  Cautions:  
    - Connect ports correctly   
    - Before uploading test code, please correctly connect to the development board and port
    - Set the baud rate to 9600 before using serial monitor printing
*/
#define button_Pin 26   //set button pin to IO26
#define RED_LED_PIN 17  //Connect the red LED to port IO17

#define redLED_PWM_Channel 1  // Red led light using PWM channel 1
#define pwmFreq 5000          // PWM frequency
#define pwmResolution 8       //Set the PWM resolution to 8 so the value range is 0-255

int brightness = 2;     //Divide the PWM 0-255 into 5 parts, each of which is 51
bool led_state = false; //Use a bool type variable to control led on and off
int value = 0;  //Used to calculate long press


void setup() {
  //set button pin to input
  pinMode(button_Pin, INPUT);
  // initialize PWM
  ledcSetup(redLED_PWM_Channel, pwmFreq, pwmResolution);
  ledcAttachPin(RED_LED_PIN, redLED_PWM_Channel);
}

void loop() {
  //Read the button state
  int button_state = digitalRead(button_Pin);
  //Use while to determine whether the button is pressed, if yes, enter the loop
  while (button_state == 0) {
    //Start adding variables, each time the value of the loop value is added by one
    value++;
    //The while loop class continues to read the button state, which is used to exit the while loop
    button_state = digitalRead(button_Pin);
    //delay 100ms
    delay(100);
    //Check whether the value is greater than 5. If yes, enter the long-press mode
    //(value is greater than 5, so it is equal to 6. with 100ms delay, this is a 600ms long press)
    if (value > 5) {
      //Clear the value to 0 for the next long press
      value = 0;
      //The brightness value is increased by one, that is, every 600ms long press, the brightness rises by one level
      brightness++;
      //We only set 5 brightness levels, so when it is greater than the maximum brightness level, the brightness level should be adjusted to 1
      if(brightness > 5) brightness = 1;
      //Output the brightness of the current brightness level. brightness*51: Because we have divided the brightness level into 5 levels (255/5=51)
      ledcWrite(redLED_PWM_Channel, brightness * 51);
      //Exit the while loop, that is, after entering the long press mode, no longer enter the short press code
      break;
    }
    //Short press: Check whether the button is released. Release the button without triggering long press code, that is, within 500ms
    if (button_state == 1) {
      //Clear the value of value to 0 for the next count
      value = 0;
      //The current led_state is reversed and copied to the led_state
      led_state = !led_state;
      //After the led_state variable is reversed, the led lights up when it is true, and the led turns off when it is false
      if (led_state) {
        //led on
        ledcWrite(redLED_PWM_Channel, brightness * 51);
      } else {
        //led off
        ledcWrite(redLED_PWM_Channel, 0);
      }
    }
  }
}
