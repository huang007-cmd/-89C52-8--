#include "main.h"

typedef unsigned char uchar;

unsigned char keynum;
unsigned char keynum_show;
unsigned char time_SET = 10;
unsigned char time_number = 10;
unsigned char score[8] = {0};
uchar Flag_key = 0;
uchar MODE = 1;
uchar last_mode = 1;
char buffer[16]; // 缓冲区

// 定时器相关变量
unsigned int timer_count = 0; // 定时器计数器
uchar timer_1s_flag = 0;	  // 1秒标志位

void Timer0_Init();

void LCD_display()
{
	// 如果模式改变，才清屏
	if (last_mode != MODE)
	{
		LCD_Clear();
		last_mode = MODE;
	}
	// ---------------------- 主界面 ----------------------
	if (MODE == 1)
	{
		LCD_ShowString(0, 0, "Waiting to Start");
		sprintf(buffer, "Time: %2d s", (int)time_number);
		LCD_ShowString(0, 1, buffer);
	}
	// ---------------------- 倒计时 ----------------------
	else if (MODE == 2)
	{
		if (Flag_key == 0)
		{
			sprintf(buffer, "Start!Time:%2d s", (int)time_number);
			LCD_ShowString(0, 0, buffer);

			if (timer_1s_flag == 1)
			{
				timer_1s_flag = 0;
				time_number--;
				if (time_number == 0) // 倒计时结束
				{
					MODE = 5; // 进入倒计时结束界面
				}
			}
		}
	}
	// ---------------------- 锁定：玩家胜利 ----------------------
	else if (MODE == 3)
	{
		if (Flag_key != 0)
		{
			time_number = time_SET;
			sprintf(buffer, "Player %d Wins!", (int)keynum_show);
			LCD_ShowString(0, 0, buffer);
			score[keynum_show]++;
			sprintf(buffer, "Score: %d!", (int)score[keynum_show]);
			LCD_ShowString(0, 1, buffer);
			Flag_key = 0;
		}
	}
	// ---------------------- 设置模式 ----------------------
	else if (MODE == 4)
	{
		memset(score, 0, sizeof(score));
		sprintf(buffer, "SET! Time: %2d s", (int)time_SET);
		LCD_ShowString(0, 0, buffer);
	}

	// ---------------------- 倒计时结束 ----------------------
	else if (MODE == 5)
	{
		LCD_ShowString(0, 0, "Time Over");
		LCD_ShowString(0, 1, "Press RESET");
	}
}

void key_scan()
{
	keynum = GetKey();
	Flag_key = keynum ? 1 : 0;
	keynum_show = keynum;
}

void main()
{
	Timer0_Init();
	LCD_Init();

	while (1)
	{
		key_scan();
		LCD_display();
	}
}

/**
 * @brief 定时器0初始化（1ms中断）
 * @note  使用Timer0，工作方式1，产生1ms中断
 */
void Timer0_Init()
{
	TMOD &= 0xF0; // 清除Timer0的设置
	TMOD |= 0x01; // Timer0工作方式1（16位定时器）

	// 设置初值，产生1ms中断（假设晶振为11.0592MHz）
	TH0 = 0xFC; // 65536 - 1000 = 64536 = 0xFC18
	TL0 = 0x18;

	ET0 = 1; // 使能Timer0中断
	EA = 1;	 // 使能总中断
	TR0 = 1; // 启动Timer0
}

/**
 * @brief Timer0中断服务函数
 * @note  每1ms进入一次
 */
void Timer0_ISR() interrupt 1
{
	// 重装初值
	TH0 = 0xFC;
	TL0 = 0x18;

	timer_count++;

	// 1000ms = 1s
	if (timer_count >= 1000)
	{
		timer_count = 0;
		timer_1s_flag = 1; // 设置1秒标志
	}
}