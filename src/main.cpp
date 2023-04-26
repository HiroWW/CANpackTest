#include <Arduino.h>
#include "global.hpp"
#include "CANpack.hpp"
void setup() {
  // put your setup code here, to run once:
  CANpack0.CANsetup();
}

int i = 0;
int loopCount = 0;
void loop() {
  // put your main code here, to run repeatedly:
  
  //受信
  // for (int j = 0; j < 4; j++) {
  //   mp.gyro[j] = (j + 1) * 10;
  // }
  // mp.apflag = i;

  // for (int j = 0; j < 3; j++) {
  //   lp.gyro[j] = (j + 1) * 10;
  // }
  // lp.acc = 321.0f;
  // lp.apflag = i;
  // i++;
  // int ID;
  // ID = 1;
  // CANpack0.send(ID,&lp);

  can0.events();
  if (loopCount % 10000 == 0){
    Serial.println("Tail to Master ");
    Serial.print("gyro[0] = "); Serial.println(mp.gyro[0]);
    Serial.print("gyro[1] = "); Serial.println(mp.gyro[1]);
    Serial.print("gyro[2] = "); Serial.println(mp.gyro[2]);
    Serial.print("gyro[3] = "); Serial.println(mp.gyro[3]);
    Serial.print("apflag = "); Serial.println(mp.apflag);
    Serial.println("Tail to log ");
    Serial.print("gyro[0] = "); Serial.println(lp.gyro[0]);
    Serial.print("gyro[1] = "); Serial.println(lp.gyro[1]);
    Serial.print("gyro[2] = "); Serial.println(lp.gyro[2]);
    Serial.print("acc = "); Serial.println(lp.acc);
    Serial.print("apflag = "); Serial.println(lp.apflag);
  }
  loopCount++ ;

}