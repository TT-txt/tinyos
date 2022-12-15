#ifndef __PORTS__
#define __PORTS__
#include "../libs/utils.h"

u8 portByteIn(u16 port);
void portByteOut(u16 port, u8 data);
u16 portWordIn(u16 port);
void portWordOut(u16 port, u16 data);

#endif