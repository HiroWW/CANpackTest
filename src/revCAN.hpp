#pragma once
#include <FlexCAN_T4.h>
#include "TeensyCAN2.h"

FlexCAN_T4FD<CAN3, RX_SIZE_1024, TX_SIZE_1024> can0;
TeensyCAN node36 = TeensyCAN(36);

class CANpack{
  public:
  void CANsetup();
  template <typename S>
  void CANsend(uint8_t ID_send, S *send_data) ;
};

void CANread(const uint8_t* buffer, uint16_t length, AsyncTC info);

void CANpack::CANsetup(){
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
}

template <typename S>
void CANpack::CANsend(uint8_t ID_send, S *send_data) {
  // struct=>uint8_t c[256]変換用union
  union send_data_union {
    S raw_data;
    uint8_t encoded_data[256] = {};
  };
  send_data_union sendDataUnion; //* unionのインスタンスを宣言
  sendDataUnion.raw_data = *send_data; //* 引数に取ったstructをunionへコピー

  //* 全Nodeに向けて送信
  uint32_t t = 0;
  uint32_t timeout = micros();
  while(1){
    t = micros();
    if (t - timeout > 500){
      if(Node.sendMsg(sendDataUnion.encoded_data, 256, ID_send)){
      }else{
        if(Serial.availableForWrite()){
          Serial.println("[ERROR] CANsend Failed !");
        }
      }
      break;
    }
  }
}

void CANread(const uint8_t* buffer, uint16_t length, AsyncTC info) {
  int ID_read;
  ID_read = info.packetid;
  memcpy(canPackList[ID_read], buffer, canPackLen[ID_read]);
}