#include <NewPing.h>
#include <SoftwareSerial.h>  //Include the Soft Serial Library
#include <Servo.h> 

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int dir = 12;
int brake = 9;
int pwm = 3;
Servo servo;

SoftwareSerial BTSerial(4,5);  // RX, TX

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int inPos;


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
  delay(30);                      // Wait 30ms between pings 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  unsigned int distanceCM =  uS / US_ROUNDTRIP_CM;
  
  
  if(distanceCM < 0){
  
  // stop and measure again!! 
  
  /* TODO:
  1) Stop DC
  2) Mesure and avg over 10 .
  */
  
 // digitalWrite(brake,HIGH); 
    
  }else{
  // Nothing in front of us. Everything is ok
   //digitalWrite(brake,LOW); 
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
  
   analogWrite(pwm,140);
  
 // Serial.println("Go go ");
  }else if(BTChar == 's'){
  
    // Stop motor
  //  Serial.println("Stopping");
    analogWrite(pwm,0);
  }
  else if(BTChar == 'p'){

    
  inPos = BTSerial.parseInt();
 
  inPos = map(inPos,1,100,40,120); // change when servo is mounted  

  servo.write(inPos);
    Serial.println(inPos);
  //delay(100);
 
 
 
 
  
  }
  
  
  }
  
  
  /* END BT */
  
  }
 
 
}

