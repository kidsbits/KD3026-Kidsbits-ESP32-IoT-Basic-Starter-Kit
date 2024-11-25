/*  
  Project name: 9_sound
  Function: Read the analog value of the sound sensor
  Author: keyestudio    
  Hardware connection:  
    - Connect to port 7
  Library:  
    - none (no need to import additional library)  
  Cautions:  
    - Connect to port 7   
    - Before uploading test code, please correctly connect to the development board and port
    - Set the baud rate to 9600 before using serial monitor printing
*/
#define sound_Pin 35  //set pin to IO35

void setup() {
  //Set the baud rate
  Serial.begin(9600);
  //set IO35 to input
  pinMode(sound_Pin, INPUT);
}

void loop() {
  //Read the sound analog value
  int sound_value = analogRead(sound_Pin);
  //Print the sound analog value
  Serial.print("Analog value:");
  Serial.println(sound_value);
}
