//------------------------------------------------
// 延时函数（精确延时）
//------------------------------------------------
void Delay_us(unsigned int us)
{
    while(us--);
}

void Delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 120; j++);
}