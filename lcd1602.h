#ifndef __LCD1602_H__
#define __LCD1602_H__

void LCD_Send4Bit(unsigned char dat);
void LCD_EnablePulse(void);
void LCD_WriteByte(unsigned char rs, unsigned char dat);
void LCD_WriteCommand(unsigned char cmd);
void LCD_WriteData(unsigned char dat);
void LCD_Clear(void);
void LCD_SetCursor(unsigned char x, unsigned char y);
void LCD_ShowChar(unsigned char x, unsigned char y, char ch);
void LCD_ShowString(unsigned char x, unsigned char y, char *str);
void LCD_ShowNum(unsigned char x, unsigned char y, unsigned int num, unsigned char len);
void LCD_ShowHex(unsigned char x, unsigned char y, unsigned char hex);
void LCD_Init(void);

#endif

