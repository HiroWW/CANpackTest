#include "global.hpp"
// Tail2Master mp;
// Tail2Log lp;
// p[0] = &mp;
// len[0] = sizeof(mp);
// p[1] = &lp;
// len[1] = sizeof(lp);
Tail2Master mp;
Tail2Log lp;
pack* p[2] = {&mp,&lp};
int len[2] = {sizeof(mp),sizeof(lp)};