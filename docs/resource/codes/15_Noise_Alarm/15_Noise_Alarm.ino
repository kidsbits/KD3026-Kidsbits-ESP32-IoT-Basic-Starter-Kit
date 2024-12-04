/*  
  Project name: 15_Noise_Alarm
  Function: The sound in the environment is monitored, and the red LED on the threshold is exceeded
  Author: keyestudio
  Hardware connection:
    - Connect sound sensor to port 7
    - Connect traffic light module to port 9
  Library:  
    - none (no need to import additional library)  
  Cautions:  
    - Make sure you are connected to the correct interface   
    - Before uploading test code, please correctly connect to the development board and port
*/
#define sound_Pin 35      //set sound sensor pin to IO35
#define RED_LED_PIN 17    //Connect the red LED to port IO17
#define GREEN_LED_PIN 19  //Connect the green LED to port IO19

void setup() {
  //Set the baud rate
  Serial.begin(9600);
  //set IO35 to intput
  pinMode(sound_Pin, INPUT);
  // Initialize the digital port to output
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

void loop() {
  //Read the sound analog value
  int sound_value = analogRead(sound_Pin);
  //Determine whether the sound analog value is greater than 200, if yes, red LED on, otherwise green LED on
  if (sound_value > 200) {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    delay(2000);
  } else {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
}
