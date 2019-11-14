#include <Pixy2.h>
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>





const int red = 3;
const int green = 5;
const int blue= 6;

int sendymabob[2];


Pixy2 pixy;

Servo panServo;
Servo tiltServo;

int p;




void setup() {

  Wire.begin(1);
  Wire.onReceive(gotRate);
  Wire.onRequest(requestEvent);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);


  pixy.init();



  Serial.begin(19200);

}

void loop() {


  int x;

  float angleDif;



//digitalWrite(led, HIGH);


  int xMove = pixy.ccc.blocks[x].m_x;

  int blocks = pixy.ccc.getBlocks();



  int gain = abs(158 - xMove);
  int autoGain = map(gain, 0, 158, 0, 30);



  
    int value = Wire.read();
    
Serial.println(value);

    if (value == 0) {
      digitalWrite(red, HIGH);
    }
    if (value == 1) {
      digitalWrite(red, LOW);
    }

       if (value == 2) {
      digitalWrite(green, HIGH);
    }
    if (value == 3) {
      digitalWrite(green, LOW);
    }

    if (value == 4) {
      digitalWrite(blue, HIGH);
    }
    if (value == 5) {
      digitalWrite(blue, LOW);
    }

    if (value == 6) {
      for (int i = 0; i < 256; i++) {
        analogWrite(red, 255 - i);
        analogWrite(green, i);
        delay(25);
      }
      for (int i = 0; i < 256; i++) {
        analogWrite(green, 255 - i);
        analogWrite(blue, i);
        delay(25);
      }
      for (int i = 0; i < 256; i++) {
        analogWrite(blue, 255 - i);
        analogWrite(red, i);
        delay(25);
      }
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      digitalWrite(blue, LOW);
    }
  
  if (blocks == 1) {
    angleDif = map(xMove, 0, 316, -autoGain, autoGain);

sendymabob[0] = angleDif;
sendymabob[1] = 1;

    

  }

  else {

    sendymabob[1] = 0;
    
//Serial.println("no ball");
  }
}
void gotRate() {
  if (Wire.available()) {

   int value = Wire.read();

     delay(2);


  }
}

  void requestEvent() {
  Wire.write(sendymabob[0]);
  Wire.write(sendymabob[1]);// respond with message of 6 bytes
  // as expected by master
  }
