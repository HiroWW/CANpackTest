#include <Arduino.h>
#include "global.hpp"
#include "CANpack.hpp"
void setup() {
  // put your setup code here, to run once:
  CANpack0.CANsetup();
  delay(7000);
}
int loopCount = 0;
void loop() {
  // 送信か受信のどちらかをコメントアウトする

  // 二つのpackの中身を定義してCANバスに送信する
  // setup Master to Interface pack
  mip.attitude_dt = 11.1f * (loopCount % 5 + 1);
  mip.main_dt = 22.2f * (loopCount % 5 + 1);
  mip.control_dt = 33.3f * (loopCount % 5 + 1);
  // send to can bus
  CANpack0.send(0,&mip);
  Serial.println("Master to IF sending success");
  
  // setup Interface to Master pack
  
  for (int i = 0; i < 5 ; i++ ){
    imp.strain[i] = (i + 1) * 11.1f * (loopCount % 5 + 1);
  }
  uint32_t ID = 1;
  CANpack0.send(ID,&imp);
  Serial.println("IF to Master : send SUCCESS");

  // imp.strain[0] = 11.1f;
  // imp.strain[1] = 22.2f;
  // imp.strain[2] = 33.3f;
  // imp.strain[3] = 44.4f;
  // imp.strain[4] = 55.5f;
  // send to can bus

  // setup Master to Tail pack and send it to CAN bus
  mtp.updateTime = 11.1f * (loopCount % 5 + 1);
  mtp.drCommand = 22.2f * (loopCount % 5 + 1);
  mtp.deCommand = 1.0f * (loopCount % 5 + 1);
  for (int i = 0; i < 15; i++){
    mtp.err_state[i] = 1.0f * i;
  }
  mtp.gravity[0] = 33.4f;
  mtp.gravity[1] = 66.8f;
  mtp.gravity[2] = 99.4f;
  mtp.mode = 2.0f * (loopCount % 5 + 1);
  CANpack0.send(2,&mtp);
  Serial.println("Master to Tail : send SUCCESS");

  // 割り込みで受信して内容をシリアルモニタに表示

  // can0.events();
  // if (loopCount % 10000 == 0){
  //   Serial.println("Master To IF ");
  //   Serial.print("attituded_dt = "); Serial.println(mip.attitude_dt);
  //   Serial.print("main_dt = "); Serial.println(mip.main_dt);
  //   Serial.print("control_dt = "); Serial.println(mip.control_dt);
  //   Serial.println("IF To Master ");
  //   Serial.print("strain[0] = "); Serial.println(imp.strain[0]);
  //   Serial.print("strain[1] = "); Serial.println(imp.strain[1]);
  //   Serial.print("strain[2] = "); Serial.println(imp.strain[2]);
  //   Serial.print("strain[3] = "); Serial.println(imp.strain[3]);
  // }
  loopCount++ ;

}