/**
  **************************************************************************
  * File   : delay.h
  */

#ifndef __DELAY_H
#define __DELAY_H	 
#include <at32f4xx.h>

/*Delay function*/
void Delay_init(void);
void Delay_us(u32 nus);
void Delay_ms(u16 nms);
void Delay_sec(u16 sec);

#endif