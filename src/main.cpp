#include <Arduino.h>
#include "global.hpp"
#include "CANpack.hpp"

bool IFREAD = true;

void setup() {
  // put your setup code here, to run once:
  CANpack0.CANsetup();
  delay(7000);
}
int loopCount = 0;
void loop() {
  if (IFREAD){
    // read
  } else {
    // 二つのpackの中身を定義してCANバスに送信する

    // setup Master to Interface pack
    mip.attitude_dt = 11.1f * (loopCount % 5 + 1);
    mip.main_dt = 22.2f * (loopCount % 5 + 1);
    mip.control_dt = 33.3f * (loopCount % 5 + 1);
    CANpack0.send(0,&mip);
    Serial.println("Master to IF sending success");
    
    // setup Interface to Master pack
    for (int i = 0; i < 5 ; i++ ){
      imp.strain[i] = (i + 1) * 11.1f * (loopCount % 5 + 1);
    }
    CANpack0.send(1,&imp);
    Serial.println("IF to Master : send SUCCESS");

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
  }
  loopCount++ ;
}