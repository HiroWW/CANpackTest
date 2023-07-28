#include "global.hpp"
CAN::MasterToIF mip;
CAN::IFToMaster imp;
CAN::MasterToTail mtp;
CAN::TailToMaster tmp;
CAN::TailToIF tip;

CAN::pack* p[5] = {&mip,&imp,&mtp,&tmp,&tip};
int len[5] = {sizeof(mip), sizeof(imp),sizeof(mtp), sizeof(tmp), sizeof(tip)};

