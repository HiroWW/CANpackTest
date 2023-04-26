#include <Arduino.h>
#include "global.hpp"
#include "CANpack.hpp"
void setup() {
  // put your setup code here, to run once:
  CANpack0.CANsetup();
}

int i = 0;
void loop() {
  // put your main code here, to run repeatedly:
  //受信をためす。
  for (int j = 0; j < 4; j++) {
    mp.gyro[j] = (j + 1) * 10;
  }
  mp.apflag = i;
  i++;
  int ID;
  ID = 0;
  CANpack0.send(ID,&mp);
}