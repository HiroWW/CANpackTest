#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <TeensyCAN.h>
#include "print.hpp"
#include "CommunicationPacks.hpp"

//--------------------------------------
//   change here to switch read/send
//--------------------------------------
bool IFREAD = true;
//--------------------------------------

FlexCAN_T4FD<CAN3, RX_SIZE_256, TX_SIZE_16> can0;
TeensyCAN node36 = TeensyCAN(36);

CAN::MasterToIF mip;
CAN::IFToMaster imp;
CAN::MasterToTail mtp;
CAN::TailToMaster tmp;
CAN::TailToIF tip;

CAN::pack* p[5] = {&mip,&imp,&mtp,&tmp,&tip};
int len[5] = {sizeof(mip), sizeof(imp),sizeof(mtp), sizeof(tmp), sizeof(tip)};

void CANread(const uint8_t* buffer, uint16_t length, AsyncTC info) {
  int ID_read;
  ID_read = info.packetid;
  memcpy(p[ID_read], buffer, len[ID_read]);
}

template <typename S>
void send(uint8_t ID_send, S *send_data) {
  // struct=>uint8_t c[256]変換用union
  union send_data_union {
    S raw_data;
    uint8_t encoded_data[256];
  };
  send_data_union sendDataUnion; //* unionのインスタンスを宣言
  sendDataUnion.raw_data = *send_data; //* 引数に取ったstructをunionへコピー

  //* 全Nodeに向けて送信
  static uint32_t t = millis();
  if (millis() - t > 1000) {
    Node.sendMsg(sendDataUnion.encoded_data, 256, ID_send);
    t = millis();
  }
}

void setup() {
  delay(3000);
  Serial.println("Waiting for setup...");

  can0.begin();

  Node.setBus(_CAN3);
  Node.setID(36);
  Node.onReceive(CANread);

  CANFD_timings_t config;
  config.clock = CLK_24MHz;
  config.baudrate = 1000000;
  config.baudrateFD = 2000000;
  config.propdelay = 190;
  config.bus_length = 1;
  config.sample = 87.5;
  can0.setRegions(64);
  can0.setBaudRate(config);
  can0.enableMBInterrupts();
  can0.mailboxStatus();

  Serial.println("CAN setup : COMPLETE");
}

int loopCount = 0;
float beforeStrain = 1.0f;
void loop() {
  can0.events();
  Node.events();
  if (IFREAD){
    // case read
    // for (int i = 0; i < 5; i++) {
    //   CANpack0.packPointer[i] = p[i];
    //   // p[i] = CANpack0.packPointer[i];
    // }
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
    // setup Master to Interface pack
    mip.attitude_dt = 11.1f * (loopCount % 5 + 1);
    mip.main_dt = 22.2f * (loopCount % 5 + 1);
    mip.control_dt = 33.3f * (loopCount % 5 + 1);
    send(0,&mip);
    Serial.println("Master to IF sending success");
  } else {


    
    // setup Interface to Master pack
    for (int i = 0; i < 5 ; i++ ){
      imp.strain[i] = (i + 1) * 11.1f * (loopCount % 5 + 1);
    }
    send(1,&imp);
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
    send(2,&mtp);
    Serial.println("Master to Tail : send SUCCESS");
    UTHAPS::println("Master To IF sending content");
    UTHAPS::println("attituded_dt = ",mip.attitude_dt);
    UTHAPS::println("main_dt = ", mip.main_dt);
    UTHAPS::println("control_dt = ", mip.control_dt);
  }
  loopCount++ ;
}