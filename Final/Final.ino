#include <NewPing.h>
#include <SoftwareSerial.h>  //Include the Soft Serial Library
#include <Servo.h> 

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define DIST 35

int dir = 12;
int brake = 9;
int pwm = 3;
Servo servo;

enum direction {
forward,
reverse
};

bool inZone;

direction curDir;

SoftwareSerial BTSerial(4,5);  // RX, TX

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int inPos;



void brakeOff(){

  digitalWrite(brake,LOW); // Disengage brakes
}

void brakeOn(){
 digitalWrite(brake,HIGH); // On brakes
 digitalWrite(pwm,0); // Staph!
}


 
void dirForward(){
 digitalWrite(dir,LOW); // Motor forward 
curDir = forward;
}

void dirReverse(){
digitalWrite(dir,HIGH); // Motor backwards 
curDir = reverse;
}




void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  Serial.println("Starting Car!");
  
  
  pinMode(dir,OUTPUT);
  pinMode(brake,OUTPUT);
  
    //Init motor vals
  
 
  brakeOff();
  dirForward();
  
   
    
  // Setup servo
  servo.attach(10);
  
  
  // Setup BT

  BTSerial.begin(9600);  //Start Bluetooth Serial Connection
 
  //BTSerial.print("Connected");
inZone = false;
}



void loop() {
 
     delay(60);           // Wait 60ms between pings 29ms should be the shortest delay between pings.
     
  unsigned int distanceCM = sonar.ping_cm(); // Send ping, get ping distance in cm
  
 Serial.print("Dist is:");
 
 Serial.println(distanceCM);
 
  if(distanceCM < DIST && distanceCM > 10){
  
  // stop and measure again!! 
  
  /* TODO:
  1) Stop DC
  2) Mesure and avg over 3.
  
  */
  // Brake!!*/ 
  
 
 if(curDir == forward){
   
 
   Serial.println(distanceCM);
     Serial.println("Fwd brake");
   // stop if we are going forward
   
   dirReverse();
   delay(800);
    analogWrite(pwm,0);
   
  brakeOn();
 
 }
  
  unsigned int totalDist =0;
  
  int div =0;
    for(int i=0;i<3;i++){
                        
      unsigned int distanceCM = sonar.ping_cm(); // Send ping, get ping time in microseconds (uS).
      if(distanceCM > 0){
            totalDist += distanceCM;
            div++;
      }

      delay(60);    // Wait 30ms between pings 29ms should be the shortest delay between pings.
    
    }
    unsigned int avgDist =0; 
    if(div != 0){// avoid div with zero
    
      avgDist  = totalDist/div;
   
    
    }

    
    if(avgDist < DIST && avgDist > 1){
      // Vi er i zonen
      
      inZone = true; 
    
      
      
    }else{
    // Nothing here, just wait for next loop iteration.

    }

  // SLUT UNDER
  // SLUT UNDER
  // SLUT UNDER
  // SLUT UNDER
  
  
  }
  // Dist > DIST. OVER
  else if(distanceCM > 1){
    
    if(inZone){
    inZone = false;
    
    }
    
    
    Serial.println("Forward");
    
    
  // Nothing in front of us. Everything is ok 
    
  }
  
   
   
   
   
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
    brakeOff();
    dirForward();
   analogWrite(pwm,140);
  
  Serial.println("Go go ");
  }else if(BTChar == 's'){
  
    // Stop motor
   
    brakeOn();
  }
  else if(BTChar == 'm'){
    Serial.println("MAX");
     // MAX IT
     dirForward();
     brakeOff(); 
    analogWrite(pwm,255);
  }
   else if(BTChar == 'b'){
    Serial.println("back");
     // MAX IT
      brakeOff();
      dirReverse();
    analogWrite(pwm,140);
  }
  
  
  else if(BTChar == 'p'){

    
  inPos = BTSerial.parseInt();
// Serial.println(inPos);
  inPos = map(inPos,1,100,40,120); // change when servo is mounted  

  servo.write(inPos);
    //Serial.println(inPos);
  //delay(100);
 
 
 
 
  
  }
  
  
  }
  
  
  /* END BT */
  
  
 
 
}

