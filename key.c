#include <STC89C5xRC.H>
#include "main.h"

sbit S1 = P1^0;
sbit S2 = P1^1;
sbit S3 = P1^2;
sbit S4 = P1^3;
sbit S5 = P1^4;
sbit S6 = P1^5;
sbit S7 = P1^6;
sbit S8 = P1^7;

sbit START = P0^0;
sbit RESET = P0^1;
sbit SET = P0^2;
sbit INC = P0^3;
sbit DEC = P0^4;
sbit SEL = P0^5;

unsigned char GetKey(void)
{
	unsigned char KeyNum = 0;
	
    // ### 1 主界面，等待开始
	if(MODE == 1){
		if(START == 0){Delay_ms(10);if(START == 0){MODE = 2;while(START == 0);}}
		if(SET == 0){Delay_ms(10);if(SET == 0){MODE = 4;while(SET == 0);}}
	}
    // ### 2 倒计时阶段：等待选手按键
	else if(MODE == 2){
		if(S1 == 0){Delay_ms(10);if(S1 == 0){KeyNum = 1;MODE = 3;while(S1 == 0);}}
		if(S2 == 0){Delay_ms(10);if(S2 == 0){KeyNum = 2;MODE = 3;while(S2 == 0);}}
		if(S3 == 0){Delay_ms(10);if(S3 == 0){KeyNum = 3;MODE = 3;while(S3 == 0);}}
		if(S4 == 0){Delay_ms(10);if(S4 == 0){KeyNum = 4;MODE = 3;while(S4 == 0);}}
		if(S5 == 0){Delay_ms(10);if(S5 == 0){KeyNum = 5;MODE = 3;while(S5 == 0);}}
		if(S6 == 0){Delay_ms(10);if(S6 == 0){KeyNum = 6;MODE = 3;while(S6 == 0);}}
		if(S7 == 0){Delay_ms(10);if(S7 == 0){KeyNum = 7;MODE = 3;while(S7 == 0);}}
		if(S8 == 0){Delay_ms(10);if(S8 == 0){KeyNum = 8;MODE = 3;while(S8 == 0);}}
	}
    // ### 3 锁定阶段 或 5 倒计时结束阶段
	else if(MODE == 3 || MODE == 5){
		if(RESET == 0){Delay_ms(10);if(RESET == 0){MODE = 1;while(RESET == 0);}}
	}
    // ### 4 设置阶段
	else if(MODE == 4){
		if(INC == 0){Delay_ms(10);if(INC == 0){time_SET++;while(INC == 0);}}
		if(DEC == 0){Delay_ms(10);if(DEC == 0){time_SET--;while(DEC == 0);}}
		if(SET == 0){Delay_ms(10);if(SET == 0){MODE = 1;time_number = time_SET;while(SET == 0);}}
	}

	return KeyNum;
}
