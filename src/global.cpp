#include "global.hpp"
CAN::MasterToIF mip;
CAN::IFToMaster imp;
CAN::MasterToTail mtp;
CAN::TailToMaster tmp;
CAN::TailToIF tip;

CAN::pack* canPackList[5] = {&mip,&imp,&mtp,&tmp,&tip};
int canPackLen[5] = {sizeof(mip), sizeof(imp),sizeof(mtp), sizeof(tmp), sizeof(tip)};

