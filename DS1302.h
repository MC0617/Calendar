#ifndef _DS1302_H
#define _DS1302_H

//写时钟芯片的寄存器位置
#define DS1302_SECOND_WRITE 0x80
#define DS1302_MINUTE_WRITE 0x82
#define DS1302_HOUR_WRITE 0x84
#define DS1302_WEEK_WRITE 0x8A
#define DS1302_DAY_WRITE 0x86
#define DS1302_MONTH_WRITE 0x88
#define DS1302_YEAR_WRITE 0x8C
//读时钟芯片的寄存器位置
#define DS1302_SECOND_READ 0x81
#define DS1302_MINUTE_READ 0x83
#define DS1302_HOUR_READ 0x85
#define DS1302_WEEK_READ 0x8B
#define DS1302_DAY_READ 0x87
#define DS1302_MONTH_READ 0x89
#define DS1302_YEAR_READ 0x8D
//操作
#define DS1302_SCLK_H DS1302_SCLK=1
#define DS1302_SCLK_L DS1302_SCLK=0
#define DS1302_IO_H DS1302_IO=1
#define DS1302_IO_L DS1302_IO=0
#define DS1302_RST_H DS1302_RST=1
#define DS1302_RST_L DS1302_RST=0
#define DS1302_IO_READ DS1302_IO

//获取时间
unsigned char GetSecond();
unsigned char GetMinute();
unsigned char GetHour();
unsigned char GetDay();
unsigned char GetMonth();
unsigned char GetWeek();
unsigned char GetYear();


void TimeWriteAB(unsigned char Address,unsigned char Content);
void DS1302SetTime(unsigned char temp[]);
void ClockInit(void);

#endif