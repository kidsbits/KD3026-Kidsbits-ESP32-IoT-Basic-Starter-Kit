/*  
  Project name: 6_Button_Basic
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
  //Serial port print character "Button State:", no wrap
  Serial.print("Button State:"); 
  //Serial port print the value of variable `button_state`, wrap
  Serial.println(button_state);
  //Delay 300ms to observe the printed values
  delay(300); 
}
