/*  
  Project name: 8_light
  Function: Read the analog value of the photoresistor
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
#define light_Pin 35  //set photoresistor to IO35

void setup() {
  //Set the baud rate
  Serial.begin(9600);
  //set IO35 to input
  pinMode(light_Pin, INPUT);
}

void loop() {
  //Read the analog value of photoresistor
  int light_value = analogRead(light_Pin);
  //Print the analog value of photoresistor
  Serial.print("Analog value:");
  Serial.println(light_value);
  //Delay 300ms to observe the printed analog value
  delay(300);
}
