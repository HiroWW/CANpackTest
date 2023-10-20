#include <Arduino.h>
#include "print.hpp"
#include "global.hpp"
#include "CANpack.hpp"
#include "testCAN.hpp"
//--------------------------------------
//   change here to switch read/send
//--------------------------------------
bool IFREAD = true;
bool IFDEBUG = false;
//--------------------------------------

CANpack canpack;

void setup() {
    delay(7000);
    Serial.println("Waiting for setup...");
    canpack.CANsetup();
    Serial.println("CAN setup : COMPLETE");
}

int loopCount = 0;
void loop() {
    // Node.events()
    if (IFREAD){
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
        mtp.receive_state = true;
        canpack.CANsend(loopCount%5,&mtp);
    } else if(!IFREAD){
        // setup Master to Interface pack
        mip.attitude_dt = 11.1f * (loopCount % 5 + 1);
        mip.main_dt = 22.2f * (loopCount % 5 + 1);
        mip.control_dt = 33.3f * (loopCount % 5 + 1);
        mip.receive_state = true;
        // canpack.CANsend(0,&mip);

        // setup Interface to Master pack
        for (int i = 0; i < 5 ; i++ ){
            imp.strain[i] = (i + 1) * 11.1f * (loopCount % 5 + 1);
        }
        imp.receive_state = true;
        // canpack.CANsend(1,&imp);
    }else{
    }

    if (IFDEBUG && (loopCount % 13 == 1)){
        UTHAPS::println("---------- 0 : Master To IF content----------");
        UTHAPS::println("attituded_dt = ",mip.attitude_dt);
        UTHAPS::println("main_dt = ", mip.main_dt);
        UTHAPS::println("control_dt = ", mip.control_dt);

        UTHAPS::println("---------- 1 :IF To Master content----------");
        UTHAPS::println("strain[0] = ", imp.strain[0]);
        UTHAPS::println("strain[1] = ", imp.strain[1]);
        UTHAPS::println("strain[2] = ", imp.strain[2]);
        UTHAPS::println("strain[3] = ", imp.strain[3]);
        UTHAPS::println("strain[4] = ", imp.strain[4]);

        UTHAPS::println("---------- 2 : Master to Tail content----------");
        UTHAPS::println("updateTime = ", mtp.updateTime);
        UTHAPS::println("drCommand = ", mtp.drCommand);
        UTHAPS::println("deCommand = ", mtp.deCommand);
        UTHAPS::println("err state = ", mtp.err_state[1]);
        UTHAPS::println("gravity = ", mtp.gravity[2]);
        UTHAPS::println("mtp.mode = ", mtp.mode);

        UTHAPS::println("---------- EX : loop CNT ----------");

        UTHAPS::println("loop count is ",loopCount);
    }
    if (IFREAD){
        CANMessage message;
        UTHAPS::print("receive data ");
        for (int i = 0; i < 12; i++){
            if (ACAN_T4::can2.receive(message)){
                UTHAPS::println("id", message.id);
                for (int i = 0; i < 8; i++){
                    // int dataCon = message.data[]
                    UTHAPS::print(message.data[i], " ");
                }
                UTHAPS::println("");
            }
        }
    }
    // while(ACAN_T4::can1.receive(message)){
        // canpack.CANread(message);
        // UTHAPS::println("receive state",mtp.receive_state,mip.receive_state,imp.receive_state);
        // if (mtp.receive_state,mip.receive_state,imp.receive_state){
        //     break;
        // }
    // }
    // UTHAPS::println("receive state",mtp.receive_state,mip.receive_state,imp.receive_state);
    loopCount++ ;
}