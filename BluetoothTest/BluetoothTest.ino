#include <SoftwareSerial.h>  //Include the Soft Serial Library
#include <Servo.h> 
int dir = 12;
int brake = 9;
int pwm = 3;
Servo servo;
SoftwareSerial BTSerial(4, 5);  // RX, TX


int currPos;
int inPos;
void setup() {
  
  
    Serial.begin(9600);  // start serial communication at 9600bps
    Serial.println("GO GO ");// Setup Motor
  pinMode(dir,OUTPUT);
  pinMode(brake,OUTPUT);
  
  //Init motor vals
  
  digitalWrite(dir,HIGH); // Motor forward 
  digitalWrite(brake,LOW); // Disengage brakes
  
  // Setup servo
  servo.attach(10);
  
  // Setup BT

  BTSerial.begin(9600);  //Start Bluetooth Serial Connection
 
   BTSerial.print("Connected");
    
    
   
    
    
}
 
void loop() {
//  static parse = 0;
  static int pos = 0;
  if( BTSerial.available() ) {  // if data is available to read
  
  char BTChar;
  
  BTChar = BTSerial.read();
 // Serial.write(BTChar);
  
  if(BTChar == 'h'){
  // Set motor high
  
   analogWrite(pwm,255);
  
 // Serial.println("Go go ");
  }else if(BTChar == 's'){
  
    // Stop motor
  //  Serial.println("Stopping");
    analogWrite(pwm,0);
  }
  else if(BTChar == 'p'){

  inPos = BTSerial.parseInt();
  if(inPos ==){
 }else{
  inPos = map(inPos,1,100,0,179); // change when servo is mounted
  
  /*if(inPos > pos && pos < 179){
   
    pos++;
  
  }else if(inPos < pos && pos > 1){
  pos--;
  
  }*/
  servo.write(inPos);
    Serial.println(inPos);
  delay(100);
 }
 
 
 
  
  }
  
  
  }


 
}
