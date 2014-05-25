#include <NewPing.h>
#include <SoftwareSerial.h>  //Include the Soft Serial Library
#include <Servo.h> 

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define DIST 30 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int dir = 12;
int brake = 9;
int pwm = 3;
Servo servo;

enum {
forward,
backwards
} curDir;

SoftwareSerial BTSerial(4,5);  // RX, TX

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int inPos;
bool goingBackwards = false;
bool change = false;

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  Serial.println("Starting Car!");
  
  
  pinMode(dir,OUTPUT);
  pinMode(brake,OUTPUT);
  
    //Init motor vals
  
  digitalWrite(dir,LOW); // Motor forward 
  digitalWrite(brake,LOW); // Disengage brakes
  
    
  // Setup servo
  servo.attach(10);
  
  
  // Setup BT

  BTSerial.begin(9600);  //Start Bluetooth Serial Connection
 
  //BTSerial.print("Connected");
  
}

void loop() {
 
     /*delay(30);                      // Wait 30ms between pings 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  unsigned int distanceCM =  uS / US_ROUNDTRIP_CM;
  
 Serial.print("Dist is:");
 Serial.println(distanceCM);
 
  if(distanceCM < DIST && distanceCM > 1){
  
  // stop and measure again!! 
  
  /* TODO:
  1) Stop DC
  2) Mesure and avg over 10 .
  *//*
  // Brake!!
 
 if(!goingBackwards){
   
     Serial.println("Fwd brake");
   // stop if we are going forward
  digitalWrite(brake,HIGH); 
 
 }
  
  unsigned int totalDist =0;
  int div =0;
    for(int i=0;i<10;i++){
                        
      unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
      unsigned int distanceCM =  uS / US_ROUNDTRIP_CM;
      if(distanceCM > 0){
            totalDist += distanceCM;
            div++;
      }

      delay(30);    // Wait 30ms between pings 29ms should be the shortest delay between pings.
    
    }
    unsigned int avgDist =0; 
    if(div != 0){// avoid div with zero
    
      avgDist  = totalDist/div;
   
    
    }

    
    if(avgDist < DIST && avgDist > 1){
      

    Serial.println("Backwards! ");
    if(!goingBackwards){
    analogWrite(pwm,0);
    }
       //
        goingBackwards = true;
      digitalWrite(dir,HIGH); // Motor backwards!! 
      change = true;
      
    }else{
    // Nothing here, just wait for next loop iteration.

    }

  
  }
  // Dist > 20
  else if(distanceCM > 1){
    
    if(change){
    
       analogWrite(pwm,0);
       change = false;
    }
    
    Serial.println("Forward");
     digitalWrite(brake,LOW); // no brake
    digitalWrite(dir,LOW); // Motor forward 
    goingBackwards = false;
    
  // Nothing in front of us. Everything is ok 
    
  }
  */
   
  /* TODO:
  1) Read BT
  2) Set DC 
  3) set servo
  */
  
  /* START BT*/
  
if( BTSerial.available() ) {  // if data is available to read
  
  char BTChar;
  
  BTChar = BTSerial.read();
 // Serial.write(BTChar);
  
  if(BTChar == 'h'){
  // Set motor high
    digitalWrite(brake,LOW); 
   analogWrite(pwm,140);
  
 // Serial.println("Go go ");
  }else if(BTChar == 's'){
  
    // Stop motor
    digitalWrite(dir,LOW); // Motor fwd 
  //  Serial.println("Stopping");
    digitalWrite(brake,HIGH); 
    analogWrite(pwm,0);
  }
  else if(BTChar == 'm'){
    Serial.println("MAX");
     // MAX IT
     digitalWrite(dir,LOW); // Motor fwd 
      digitalWrite(brake,LOW); 
    analogWrite(pwm,255);
  }
   else if(BTChar == 'b'){
    Serial.println("back");
     // MAX IT
      digitalWrite(brake,LOW); 
      digitalWrite(dir,HIGH); // Motor back 
    analogWrite(pwm,140);
  }
  
  
  else if(BTChar == 'p'){

    
  inPos = BTSerial.parseInt();
// Serial.println(inPos);
  inPos = map(inPos,1,100,40,120); // change when servo is mounted  

  servo.write(inPos);
    Serial.println(inPos);
  //delay(100);
 
 
 
 
  
  }
  
  
  }
  
  
  /* END BT */
  
  
 
 
}

