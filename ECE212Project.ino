//www.elegoo.com
//2016.12.9

#include <SimpleDHT.h>
#include <Servo.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11; //temp/sensor object
Servo myservo;  // create servo object to control a servo

int servoPos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)==-1) {
    Serial.print("Read DHT11 failed");
    return;
  }
  if((int)humidity>30 || (int)temperature>21)
{  
   myservo.attach(9); 
   for (servoPos = 0; servoPos <= 360; servoPos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(servoPos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  Serial.print("Sample RAW Bits: ");
  for (int i = 0; i < 40; i++) {
    Serial.print((int)data[i]);
    if (i > 0 && ((i + 1) % 4) == 0) {
      Serial.print(' ');
    }
  }
  myservo.detach();
  Serial.println("");
  
  Serial.print("Sample OK: ");
}  Serial.print((int)temperature); Serial.print(" *C, ");
Serial.print((int)humidity); Serial.println(" %");
  
  // DHT11 sampling rate is 1HZ.
  delay(2000);
}
