// // #include "CANpack.hpp"
// #include "global.hpp"
// #include <FlexCAN_T4.h>
// #include <TeensyCAN.h>

// FlexCAN_T4FD<CAN3, RX_SIZE_256, TX_SIZE_16> can0;
// TeensyCAN node36 = TeensyCAN(36);

// void CANread(const uint8_t* buffer, uint16_t length, AsyncTC info) {
//   int ID_read;
//   ID_read = info.packetid;
//   memcpy(p[ID_read], buffer, len[ID_read]);
// }

// template <typename S>
// void send(uint8_t ID_send, S *send_data) {
//   // struct=>uint8_t c[256]変換用union
//   union send_data_union {
//     S raw_data;
//     uint8_t encoded_data[256];
//   };
//   send_data_union sendDataUnion; //* unionのインスタンスを宣言
//   sendDataUnion.raw_data = *send_data; //* 引数に取ったstructをunionへコピー

//   //* 全Nodeに向けて送信
//   static uint32_t t = millis();
//   if (millis() - t > 1000) {
//     Node.sendMsg(sendDataUnion.encoded_data, 256, ID_send);
//     t = millis();
//   }
// }