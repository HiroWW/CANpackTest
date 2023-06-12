#include <Arduino.h>
#include "global.hpp"
#include "CANpack.hpp"
void setup() {
  // put your setup code here, to run once:
  CANpack0.CANsetup();
}

void loop() {
  // 送信か受信のどちらかをコメントアウトする

  // 二つのpackの中身を定義してCANバスに送信する

  // setup Master to Interface pack
  mip.attitude_dt = 11.1f;
  mip.main_dt = 22.2f;
  mip.control_dt = 33.3f;
  // send to can bus
  CANpack0.send(0,&mip);
  
  //setup Interface to Master pack
  for (int i = 0; i < 4 ; i++ ){
    imp.strain[i] = (i + 1) * 100.0f;
  }
  // send to can bus
  CANpack0.send(1,&imp);

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
  // loopCount++ ;

}