#include <Pixy2.h>
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>





const int red = 3;
const int green = 5;
const int blue = 6;

int sendymabob[2];


Pixy2 pixy;

Servo panServo;
Servo tiltServo;

int p;

int rainbowMode;


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
    rainbowMode = 1;
  }
  if (value == 3) {
    rainbowMode = 0;
  }

  if (value == 4) {
    digitalWrite(blue, HIGH);
  }
  if (value == 5) {
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

  int rValue = 255;
  int gValue = 0;
  int bValue = 0;

  int stage1 = 1;
  int stage2 = 0;
  int stage3 = 0;

  if (rainbowMode == 1) {
    if (stage1 == 1) {
      analogWrite(red, rValue);
      analogWrite(green, gValue);
                  rValue--;
                  gValue++;
      if (rValue <= 0 && gValue == 255) {
      stage1 = 0;
      stage2 = 1;
    }
  }
  else if (stage2 == 1) {
      analogWrite(green, gValue);
      analogWrite(blue, bValue);
                  gValue--;
                  bValue++;
      if (gValue <= 0 && bValue == 255) {
      stage2 = 0;
      stage3 = 1;
    }
  }
  else if (stage3 == 1) {
      analogWrite(blue, bValue);
      analogWrite(red, rValue);
                  bValue--;
                  rValue++;
      if (bValue <= 0 && rValue == 255) {
      stage3 = 0;
      stage1 = 1;
    }
  }
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
