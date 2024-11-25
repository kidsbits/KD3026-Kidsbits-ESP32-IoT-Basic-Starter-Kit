/*  
  Project name: 3_Flowing_light_plus
  Function: Simplify the amount of code, control the red, yellow and green LED to show flowing water effect
  Author: keyestudio    
  Hardware connection:  
    - Connect to port 9 
  Library:  
    - none (no need to import additional library)  
  Cautions:  
    - Ensure connect to port 9   
    - Before uploading test code, please correctly connect to the development board and port
    - The bit number of the array value starts from 0   
*/    

//Put the pin numbers that control the LED into the array, then LED_PIN[0] is IO17 pin, LED_PIN[1] is IO18 pin, and LED_PIN[2] is IO19 pin
int LED_PIN[] = {17,18,19}; 
  
void setup() {  
  /*
    Initialize the digital port to output
    First loop: i = 0 meets the loop condition i < 3, enter loop, LED_PIN[i] is 17
    Second loop: i++ is executed first, so the value of i is 1; i < 3, enter loop, LED_PIN[i] is 18
    Third loop: loop: i++ is executed first, so the value of i is 2; i < 3, enter loop, LED_PIN[i] is 19
    Forth loop: i++ is executed first, so the value of i is 3, which does not meet the loop condition i < 3, exit the for loop.
  */
  for(int i = 0;i < 3;i++){
    pinMode(LED_PIN[i],OUTPUT);
  }
}  
  
void loop() {  
  //flowing water light, The loop pattern is the same as the initialization pin
  for(int i = 0;i < 3;i++){
    digitalWrite(LED_PIN[i],HIGH);
    delay(300);
    digitalWrite(LED_PIN[i],LOW);
  }
}
