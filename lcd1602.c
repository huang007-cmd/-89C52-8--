#include "main.h"


//------------------------------------------------
// 引脚定义
//------------------------------------------------
sbit LCD_RS = P2^6;
sbit LCD_RW = P2^5;
sbit LCD_EN = P2^7;
sbit LCD_D4 = P2^1;
sbit LCD_D5 = P2^2;
sbit LCD_D6 = P2^3;
sbit LCD_D7 = P2^4;

//------------------------------------------------
// LCD 指令定义（提高可读性）
//------------------------------------------------
#define LCD_CLEAR           0x01  // 清屏
#define LCD_HOME            0x02  // 光标归位
#define LCD_ENTRY_MODE      0x06  // 光标右移，不移动显示
#define LCD_DISPLAY_ON      0x0C  // 显示开，光标关，不闪烁
#define LCD_DISPLAY_CURSOR  0x0E  // 显示开，光标开，不闪烁
#define LCD_DISPLAY_BLINK   0x0F  // 显示开，光标开，闪烁
#define LCD_4BIT_2LINE      0x28  // 4位模式，2行，5x7字体
#define LCD_LINE1           0x80  // 第一行起始地址
#define LCD_LINE2           0xC0  // 第二行起始地址


//------------------------------------------------
// 发送半字节（4bit）- 底层函数
//------------------------------------------------
void LCD_Send4Bit(unsigned char dat)
{
    LCD_D7 = (dat >> 3) & 0x01;
    LCD_D6 = (dat >> 2) & 0x01;
    LCD_D5 = (dat >> 1) & 0x01;
    LCD_D4 = dat & 0x01;
}

//------------------------------------------------
// 使能脉冲 - 独立函数提高复用性
//------------------------------------------------
void LCD_EnablePulse(void)
{
    LCD_EN = 1;
    Delay_us(1);  // 使能脉冲至少450ns
    LCD_EN = 0;
    Delay_us(50); // 命令执行时间
}

//------------------------------------------------
// 写字节（4位模式）- 统一底层接口
//------------------------------------------------
void LCD_WriteByte(unsigned char rs, unsigned char dat)
{
    LCD_RS = rs;  // 0=命令, 1=数据
    LCD_RW = 0;   // 写模式
    
    // 发送高4位
    LCD_Send4Bit(dat >> 4);
    LCD_EnablePulse();
    
    // 发送低4位
    LCD_Send4Bit(dat);
    LCD_EnablePulse();
    
    Delay_ms(2);  // 等待命令执行完成
}

//------------------------------------------------
// 发送命令
//------------------------------------------------
void LCD_WriteCommand(unsigned char cmd)
{
    LCD_WriteByte(0, cmd);
}

//------------------------------------------------
// 发送数据
//------------------------------------------------
void LCD_WriteData(unsigned char dat)
{
    LCD_WriteByte(1, dat);
}

//------------------------------------------------
// 清屏
//------------------------------------------------
void LCD_Clear(void)
{
    LCD_WriteCommand(LCD_CLEAR);
    Delay_ms(5);  // 清屏需要较长时间
}

//------------------------------------------------
// 设置光标位置 (x: 0-15, y: 0-1)
//------------------------------------------------
void LCD_SetCursor(unsigned char x, unsigned char y)
{
    unsigned char pos;
    
    // 限制范围
    if(x > 15) x = 0;
    if(y > 1) y = 0;
    
    pos = (y == 0) ? (LCD_LINE1 + x) : (LCD_LINE2 + x);
    LCD_WriteCommand(pos);
}

//------------------------------------------------
// 显示字符
//------------------------------------------------
void LCD_ShowChar(unsigned char x, unsigned char y, char ch)
{
    LCD_SetCursor(x, y);
    LCD_WriteData(ch);
}

//------------------------------------------------
// 显示字符串
//------------------------------------------------
void LCD_ShowString(unsigned char x, unsigned char y, char *str)
{
    LCD_SetCursor(x, y);
    while(*str)
    {
        LCD_WriteData(*str++);
    }
}

//------------------------------------------------
// 显示无符号整数（0-65535）
//------------------------------------------------
void LCD_ShowNum(unsigned char x, unsigned char y, unsigned int num, unsigned char len)
{
    unsigned char i;
    unsigned char buf[6];
    
    // 数字转字符串
    for(i = 0; i < len; i++)
    {
        buf[len - 1 - i] = (num % 10) + '0';
        num /= 10;
    }
    
    // 显示
    LCD_SetCursor(x, y);
    for(i = 0; i < len; i++)
    {
        LCD_WriteData(buf[i]);
    }
}

//------------------------------------------------
// 显示十六进制数
//------------------------------------------------
void LCD_ShowHex(unsigned char x, unsigned char y, unsigned char hex)
{
    unsigned char high, low;
    
    high = (hex >> 4) & 0x0F;
    low = hex & 0x0F;
    
    LCD_SetCursor(x, y);
    LCD_WriteData((high < 10) ? (high + '0') : (high - 10 + 'A'));
    LCD_WriteData((low < 10) ? (low + '0') : (low - 10 + 'A'));
}

//------------------------------------------------
// LCD 初始化（标准初始化流程）
//------------------------------------------------
void LCD_Init(void)
{
    Delay_ms(50);  // 等待LCD上电稳定
    
    LCD_RS = 0;
    LCD_RW = 0;
    
    // 初始化序列 - 确保进入4位模式
    LCD_Send4Bit(0x03);
    LCD_EnablePulse();
    Delay_ms(5);
    
    LCD_Send4Bit(0x03);
    LCD_EnablePulse();
    Delay_ms(5);
    
    LCD_Send4Bit(0x03);
    LCD_EnablePulse();
    Delay_ms(5);
    
    // 设置为4位模式
    LCD_Send4Bit(0x02);
    LCD_EnablePulse();
    Delay_ms(5);
    
    // 功能设置
    LCD_WriteCommand(LCD_4BIT_2LINE);  // 4位，2行，5x7
    LCD_WriteCommand(LCD_DISPLAY_ON);  // 显示开，光标关
    LCD_WriteCommand(LCD_CLEAR);       // 清屏
    Delay_ms(5);
    LCD_WriteCommand(LCD_ENTRY_MODE);  // 输入模式设置
}

//------------------------------------------------
// 主程序
//------------------------------------------------

/*
void main(void)
{
    unsigned int counter = 0;
    
    LCD_Init();
    
    LCD_ShowString(0, 0, "Hello LCD1602!");
    LCD_ShowString(0, 1, "Count: ");
    
    while(1)
    {
        LCD_ShowNum(7, 1, counter, 5);
        counter++;
        if(counter > 99999) counter = 0;
        Delay_ms(500);
    }
}
*/