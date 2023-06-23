#include <Arduino.h>
#include "global.hpp"
#include "CANpack.hpp"
#include "print.hpp"

void setup() {
  // put your setup code here, to run once:
  delay(3000);
  Serial.println("Waiting for setup...");
  CANpack0.CANsetup();
  Serial.println("CAN setup : COMPLETE");
}

int i = 0;
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
  // for (int i = 0; i < 5; i++) {
  //   CANpack0.packPointer[i] = p[i];
  //   // p[i] = CANpack0.packPointer[i];
  // }

  UTHAPS::println("Master To IF sending content");
  UTHAPS::println("attituded_dt = ",mip.attitude_dt);
  UTHAPS::println("main_dt = ", mip.main_dt);
  UTHAPS::println("control_dt = ", mip.control_dt);
  UTHAPS::println("IF To Master sending content");
  UTHAPS::println("strain[0] = ", imp.strain[0]);
  UTHAPS::println("strain[1] = ", imp.strain[1]);
  UTHAPS::println("strain[2] = ", imp.strain[2]);
  UTHAPS::println("strain[3] = ", imp.strain[3]);
  UTHAPS::println("strain[4] = ", imp.strain[4]);
  UTHAPS::println("Master to Tail content");
  UTHAPS::println("updateTime = ", mtp.updateTime);
  UTHAPS::println("drCommand = ", mtp.drCommand);
  UTHAPS::println("deCommand = ", mtp.deCommand);
  UTHAPS::println("err state = ", mtp.err_state[1]);
  UTHAPS::println("gravity = ", mtp.gravity[2]);
  UTHAPS::println("mtp.mode = ", mtp.mode);

}