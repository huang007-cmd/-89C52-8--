#ifndef __MAIN_H__
#define __MAIN_H__

#include <STC89C5xRC.H>
#include <intrins.h>
#include "key.h"
#include "Delay.h"
#include <string.h>
#include "lcd1602.h"
#include <stdio.h>

sbit LED_RED4 = P3 ^ 3;
sbit LED_RED5 = P3 ^ 4;
sbit LED_RED6 = P3 ^ 5;
sbit LED_RED7 = P3 ^ 6;
sbit LED_RED8 = P3 ^ 7;

extern unsigned char last_mode;
extern unsigned char MODE;
extern unsigned char time_number;
extern unsigned char time_SET;

#endif