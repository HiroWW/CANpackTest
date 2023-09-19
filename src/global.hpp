#pragma once
#include "CommunicationPacks.hpp"


extern CAN::MasterToIF mip;
extern CAN::IFToMaster imp;
extern CAN::MasterToTail mtp;
extern CAN::TailToMaster tmp;
extern CAN::TailToIF tip;
extern CAN::pack* canPackList[5];
extern int canPackLen[5];

