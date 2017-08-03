#ifndef _TM1640_H
#define _TM1640_H

#include "delay.h"

//void TM1640Display(unsigned char DisData[16]);
void TM1640DisplayActual(unsigned char temp[8]);
void TM1640DisplayActualInterrupt(unsigned char temp[6]);

#endif