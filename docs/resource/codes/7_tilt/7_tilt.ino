/*  
  Project name: 7_tilt
  Function: Read button state
  Author: keyestudio    
  Hardware connection:  
    - Connect to port 2 
  Library:  
    - none (no need to import additional library)  
  Cautions:  
    - Connect to port 2   
    - Before uploading test code, please correctly connect to the development board and port
    - Set the baud rate to 9600 before using serial monitor printing
*/
#define tilt_Pin 2  //set pin to IO2

void setup() {
  //Set the baud rate
  Serial.begin(9600);
  //set pin to input
  pinMode(tilt_Pin, INPUT);
}

void loop() {
  //Read TTL level of pin IO2 (high level '1', low level '0')
  int tilt_state = digitalRead(tilt_Pin);
  //determine whether it tilt.
  if (tilt_state == 1) {
    //if yes, print "It's tilted!"
    Serial.println("It's tilted!");
  } else {
    //if not, print "No tilt！"
    Serial.println("No tilt!");
  }
  //Delay 300 to limit the printing speed
  delay(300);
}
