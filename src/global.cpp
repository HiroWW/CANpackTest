#include "global.hpp"

CAN::MasterToIF mip;
CAN::IFToMaster imp;
CAN::MasterToTail mtp;
CAN::TailToMaster tmp;
CAN::TailToIF tip;

CAN::pack* p[5] = {&imp,&mip,&mtp,&tmp,&tip};
int len[5] = {sizeof(imp), sizeof(mip), sizeof(mtp), sizeof(tmp), sizeof(tip)};

// Tail2Master mp;
// Tail2Log lp;
// pack* p[2] = {&mp,&lp};
// int len[2] = {sizeof(mp),sizeof(lp)};