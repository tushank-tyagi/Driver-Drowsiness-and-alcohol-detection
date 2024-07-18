#include <Wire.h>

//Alcohol Detector based on MQ3
#define in1 5 //Motor1  L293 Pin in1 
#define in2 6 //Motor1  L293 Pin in1 
#define in3 9 //Motor2  L293 Pin in1 
#define in4 10 //Motor2  L293 Pin in1 
#define alc 11
#define slp 3

 /* Here are the list of I/O pins*/
 
 
 #define MQ3 A0
 char sleep_status = 0;
 /***/
//
//Threshold value of MQ3 reading above which it should trigger//
 #define Thres_Val 460
 //
 // global int to store the analog reading from MQ3 (0 to 1023)
 int value;
 void setup() {
   // declaring the input and output pins
   pinMode(in1, OUTPUT); 
   pinMode(in2, OUTPUT); 
   pinMode(in3, OUTPUT); 
   pinMode(in4, OUTPUT); 
   pinMode(alc, OUTPUT); 
   pinMode(slp, OUTPUT); 

   pinMode(MQ3, INPUT);

    Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(loop); /* register request event */
 // Serial Output for debugging
   Serial.begin(9600);
 }
 void loop() {
   // reads the analog value from MQ3
   value = analogRead(MQ3);
 // sends the value to UART for debugging
   Serial.println(value);
 if ( value > 400 )   //if alcohol is detected
   {
    digitalWrite(in1, HIGH); //Right Motor forword Pin 
    digitalWrite(in2, HIGH); //Right Motor backword Pin 
    digitalWrite(in3, HIGH); //Left Motor backword Pin 
    digitalWrite(in4, HIGH); //Left Motor forword Pin
    digitalWrite(alc, HIGH);
    Wire.write("a");
 //digitalWrite(Buzzer,HIGH);    // turns on (uncomment if buzzer is used) 
 }
 if(value<400) 
 {
     digitalWrite(in1, LOW); //Right Motor forword Pin 
     digitalWrite(in2, HIGH);  //Right Motor backword Pin 
     digitalWrite(in3, HIGH);  //Left Motor backword Pin 
     digitalWrite(in4, LOW); //Left Motor forword Pin 
     digitalWrite(alc, LOW);
 //digitalWrite(Buzzer,LOW);   //  turns off (uncomment if buzzer is used) 
 }
 while (Serial.available()>0)
 {
   sleep_status= Serial.read();
   if(sleep_status=='a')
  {
     digitalWrite(in1, HIGH); //Right Motor forword Pin 
     digitalWrite(in2, HIGH); //Right Motor backword Pin 
     digitalWrite(in3, HIGH); //Left Motor backword Pin 
     digitalWrite(in4, HIGH); //Left Motor forword Pin
     digitalWrite(slp, HIGH);
     Wire.write("b");
  }
  else if(sleep_status=='b') 
  {
    digitalWrite(in1, LOW); //Right Motor forword Pin 
    digitalWrite(in2, HIGH);  //Right Motor backword Pin 
    digitalWrite(in3, HIGH);  //Left Motor backword Pin 
    digitalWrite(in4, LOW); //Left Motor forword Pin 
    digitalWrite(slp, LOW);
  }

 }
 delay (500);            //  a 500ms delay before reading is taken again
 }
 // function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    //Serial.print(c);           /* print the character */
  }
 //Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
 Wire.write("Hello NodeMCU");  /*send string on request */
}