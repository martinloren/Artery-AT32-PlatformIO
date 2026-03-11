/**
  **************************************************************************
  * File   : delay.h
  */

#ifndef __DELAY_H
#define __DELAY_H	 
#include "at32f435_437.h"

/*Delay function*/
void delay_init(void);
void delay_us(u32 nus);
void delay_ms(u16 nms);
void delay_sec(u16 sec);

#endif