#include "CANpack.hpp"
#include "global.hpp"
#include <FlexCAN_T4.h>
#include <TeensyCAN.h>

// FlexCAN_T4FD<CAN3, RX_SIZE_256, TX_SIZE_16> can0;
// TeensyCAN node36 = TeensyCAN(36);

// void CANread(const uint8_t* buffer, uint16_t length, AsyncTC info) {
//   int ID_read;
//   ID_read = info.packetid;
//   memcpy(p[ID_read], buffer, len[ID_read]);
// }