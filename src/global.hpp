#pragma once
#include "CommunicationPacks.hpp"

extern CAN::MasterToIF mip;
extern CAN::IFToMaster imp;
extern CAN::MasterToTail mtp;
extern CAN::TailToMaster tmp;
extern CAN::TailToIF tip;
extern CAN::pack* p[5];
extern int len[5];

