/*  
  Project name: 16_Tilt_Alarm
  Function: Monitor whether the plane is tilted, if yes, red LED on and the buzzer alarms, if not, the green LED on and the buzzer does not sound
  Author: keyestudio    
  Hardware connection:  
    - Connect tilt senser to port 2
    - Connect traffic light module to port 9
    - Connect buzzer to port 3
  Library:  
    - none (no need to import additional library)  
  Cautions:  
    - Make sure you are connected to the correct interface   
    - Before uploading test code, please correctly connect to the development board and port
*/
#define tilt_Pin 2        //set button pin to IO2
#define beeppin 26        //Set pin to IO26
#define RED_LED_PIN 17    //Connect the red LED to port IO17
#define GREEN_LED_PIN 19  //Connect the green LED to port IO19

void setup() {
  //Set pin modes
  pinMode(tilt_Pin, INPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(beeppin, OUTPUT);  
  Serial.begin(9600);
}

void loop() {
  //Read TTL level of pin IO2 (high level '1', low level '0')
  int tilt_state = digitalRead(tilt_Pin);
  Serial.println(tilt_state);
  //Determine whether to tilt
  if (tilt_state == 1) {
    //If it tilts, the red LED on, the buzzer alerts
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    tone(beeppin,384);
    delay(500);

  } else {
    //If there is no tilt, the green LED on, the buzzer does not sound
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    noTone(beeppin);
  }
}
