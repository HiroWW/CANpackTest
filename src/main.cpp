#include <Arduino.h>
#include "global.hpp"
#include "CANpack.hpp"
void setup() {
  // put your setup code here, to run once:
  delay(3000);
  Serial.println("Waiting for setup...");
  CANpack0.CANsetup();
  Serial.println("CAN setup : COMPLETE");
}

int i = 0;
int loopCount = 0;
float beforeStrain = 1.0f;
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
  if (Serial.availableForWrite() > 0){
    Serial.println("Master To IF sending content");
    Serial.print("attituded_dt = "); Serial.println(mip.attitude_dt);
    Serial.print("main_dt = "); Serial.println(mip.main_dt);
    Serial.print("control_dt = "); Serial.println(mip.control_dt);
    Serial.println("IF To Master sending content");
    Serial.print("strain[0] = "); Serial.println(imp.strain[0]);
    Serial.print("strain[1] = "); Serial.println(imp.strain[1]);
    Serial.print("strain[2] = "); Serial.println(imp.strain[2]);
    Serial.print("strain[3] = "); Serial.println(imp.strain[3]);
    Serial.print("strain[4] = "); Serial.println(imp.strain[4]);
    // Serial.println("Master to Tail content");
    // Serial.println(mtp.updateTime);
    // Serial.println(mtp.drCommand);
    // Serial.println(mtp.deCommand);
    // Serial.println(mtp.err_state[1]);
    // Serial.println(mtp.gravity[2]);
    // Serial.println(mtp.mode);
  }

  // Check when receiving the data fails
  // Serial.println(loopCount);
  // if (loopCount > 50000){
  //   if (imp.strain[0] == 0.0f && beforeStrain == 0.0f){
  //     delay(10000);
  //   }   
  // }
  // beforeStrain = imp.strain[0];

  //Reset If to Master pack content
  // for (int i = 0; i < 5; i++){
  //   imp.strain[i] = 0.0f;
  // }
  loopCount++ ;

}