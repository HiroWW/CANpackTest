#include "CANpack.hpp"
#include <Arduino.h>
#include "print.hpp"
#include "global.hpp"


//--------------------------------------
//   change here to switch read/send
//--------------------------------------
bool IFREAD = true;

//--------------------------------------

CANpack canpack;

void setup() {
  delay(3000);
  Serial.println("Waiting for setup...");
  canpack.CANsetup();
  Serial.println("CAN setup : COMPLETE");
}

int loopCount = 0;
void loop() {
  Node.events();
  
  if (IFREAD){
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
  } else {

    // setup Master to Interface pack
    mip.attitude_dt = 11.1f * (loopCount % 5 + 1);
    mip.main_dt = 22.2f * (loopCount % 5 + 1);
    mip.control_dt = 33.3f * (loopCount % 5 + 1);
    canpack.CANsend(0,&mip);
    UTHAPS::println("Master to IF sending success");
    
    // setup Interface to Master pack
    for (int i = 0; i < 5 ; i++ ){
      imp.strain[i] = (i + 1) * 11.1f * (loopCount % 5 + 1);
    }
    canpack.CANsend(1,&imp);
    UTHAPS::println("IF to Master : send SUCCESS");

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
    canpack.CANsend(2,&mtp);
    UTHAPS::println("Master to Tail : send SUCCESS");
  }
  loopCount++ ;
}