/*  
  Project name: 5_Buzzer_Music
  Function: buzzer plays Happy Birthday
  Author: keyestudio    
  Hardware connection:  
    - Connect to port 3 
  Library:  
    - none (no need to import additional library)  
  Cautions:  
    - Connect to port 3   
    - Before uploading test code, please correctly connect to the development board and port
*/
#define beeppin 26  //Set pin to IO26

// do、re、mi、fa、so、la、si
int doremi[] = {262, 294, 330, 370, 392, 440, 494,      //falt(low) 0-6
                523, 587, 659, 698, 784, 880, 988,      //natural(middle) 7-13
                1047,1175,1319,1397,1568,1760,1967};    //sharp(high) 14-20

// Locate the position number in the doremi[] array based on the low, middle and high frequencies of the simplified numbers                
int happybirthday[] = {5,5,6,5,8,7,5,5,6,5,9,8,5,5,12,10,8,7,6,11,11,10,8,9,8};   
// beats
int meter[] = {1,1,2,2,2,4, 1,1,2,2,2,4, 1,1,2,2,2,2,2, 1,1,2,2,2,4};    

void setup() {
  pinMode(beeppin, OUTPUT);  //set the pin to output
}

void loop() {
  for( int i = 0 ; i <= 24 ;i++){       //i<=24: here are only 24 keys in the score
    //Emit a waveform with frequency using the tone() function
   tone(beeppin, doremi[happybirthday[i] - 1]);
   delay(meter[i] * 300); //beats
   noTone(beeppin);//stop
  }
}
