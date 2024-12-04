/*  
  Project name: 6_Button_Basic_2
  Function: read button state
  Author: keyestudio    
  Hardware connection:  
    - Connect to port 3 
  Library:  
    - none (no need to import additional library)  
  Cautions:  
    - Connect to port 3   
    - Before uploading test code, please correctly connect to the development board and port
    - Set the baud rate to 9600 before using serial monitor printing
*/
#define button_Pin 26  //set button pin to IO26

void setup() {
  //Set the baud rate
  Serial.begin(9600);
  //set the pin to input
  pinMode(button_Pin, INPUT);
}

void loop() {
  //Read TTL level of pin IO26 (high level '1', low level '0')
  int button_state = digitalRead(button_Pin);
  //determine whether the button is pressed
  if (button_state == 0) {
    //if ues, "Button Down!"
    Serial.println("Button Down!");
  } else {
    //if not, "Release the button!"
    Serial.println("Release the button!");
  }
  //Delay 300ms to limit the printing speed
  delay(300);
}
