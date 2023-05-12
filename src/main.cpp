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
    Serial.println("Master To IF ");
    Serial.print("attituded_dt = "); Serial.println(mip.attitude_dt);
    Serial.print("main_dt = "); Serial.println(mip.main_dt);
    Serial.print("control_dt = "); Serial.println(mip.control_dt);
    Serial.println("IF To Master ");
    Serial.print("strain[0] = "); Serial.println(imp.strain[0]);
    Serial.print("strain[1] = "); Serial.println(imp.strain[1]);
    Serial.print("strain[2] = "); Serial.println(imp.strain[2]);
    Serial.print("strain[3] = "); Serial.println(imp.strain[3]);
  }
  loopCount++ ;

}