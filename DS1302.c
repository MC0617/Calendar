#include "DS1302.h"
#include <reg52.h>
sbit DS1302_SCLK=P2^5;
sbit DS1302_IO=P2^6;
sbit DS1302_RST=P2^7;

//向DS1302当前设定地址写入1字节数据
void TimeWrite(unsigned char Content)
{
	unsigned char i;
	for(i=8; i>0; i--)
	{
		if(Content & 0x01)
		{
			DS1302_IO_H;
		}
		else
		{
			DS1302_IO_L;
		}
		Content >>= 1;

		DS1302_SCLK_H;
		DS1302_SCLK_L;
	}
}
//从DS1302当前设定地址读取1字节数据
unsigned char TimeRead(void)
{
	unsigned char i,ReadValue;
	DS1302_IO_H;
	for(i=8; i>0; i--)
	{
		ReadValue>>=1;
		if(DS1302_IO_READ)
		{
			ReadValue|=0x80;
		}
		else
		{
			ReadValue&=0x7f;
		}
		DS1302_SCLK_H;
		DS1302_SCLK_L;

	}
	//DS1302_IO_L;
	return ReadValue;
}
//向DS1302指定地址写入1字节数据
void TimeWriteAB(unsigned char Address,unsigned char Content)
{
	DS1302_RST_L;
	DS1302_SCLK_L;
	DS1302_RST_H;

	TimeWrite(Address);
	TimeWrite(Content);

	DS1302_RST_L;
	DS1302_SCLK_H;
}
//从DS1302指定地址读取1字节数据
unsigned char TimeReadAB(unsigned char Address)
{
	unsigned char ReadValue;

	DS1302_RST_L;
	DS1302_SCLK_L;
	DS1302_RST_H;

	TimeWrite(Address);
	ReadValue=TimeRead();


	DS1302_RST_L;
	DS1302_SCLK_H;

	//ReadValue=ReadValue/16*10+ReadValue%16;

	return ReadValue;
}
//初始化DS1302寄存器的值
void ClockInit(void)
{
	if(TimeReadAB(0xc1)!=0xf0)
	{
		TimeWriteAB(0x8e,0x00);//允许写操作
		TimeWriteAB(DS1302_YEAR_WRITE,0x16);//年
		TimeWriteAB(DS1302_WEEK_WRITE,0x04);//周
		TimeWriteAB(DS1302_MONTH_WRITE,0x06);//月
		TimeWriteAB(DS1302_DAY_WRITE,0x2);//日
		TimeWriteAB(DS1302_HOUR_WRITE,0x9);//时
		TimeWriteAB(DS1302_MINUTE_WRITE,0x00);//分
		TimeWriteAB(DS1302_SECOND_WRITE,0x00);//秒
		TimeWriteAB(0x90,0xa5);//充电
		TimeWriteAB(0xc0,0xf0);//判断是否初始化一次标识写入
		TimeWriteAB(0x8e,0x80);//禁止写操作
	}
}
//传入时间数据
void DS1302SetTime(unsigned char temp[6])
	{
		unsigned char i;
		for(i=0;i<6;i++)
	{
		temp[i]=temp[i]/10*16+temp[i]%10;
	}
	TimeWriteAB(0x8e,0x00);//允许写操作
	TimeWriteAB(DS1302_YEAR_WRITE,temp[0]);
	TimeWriteAB(DS1302_MONTH_WRITE,temp[1]);
	TimeWriteAB(DS1302_DAY_WRITE,temp[2]);
	TimeWriteAB(DS1302_WEEK_WRITE,temp[3]);
	TimeWriteAB(DS1302_HOUR_WRITE,temp[4]);
	TimeWriteAB(DS1302_MINUTE_WRITE,temp[5]);
	TimeWriteAB(DS1302_SECOND_WRITE,0x00);
	TimeWriteAB(0x8e,0x80);//禁止写操作
	}
//获取时间数据
unsigned char GetSecond()
{
	unsigned char temp;
	temp=TimeReadAB(DS1302_SECOND_READ);
	temp=temp/16*10+temp%16;
	return temp;
}
unsigned char GetMinute()
{
	unsigned char temp;
	temp=TimeReadAB(DS1302_MINUTE_READ);
	temp=temp/16*10+temp%16;
	return temp;
}
unsigned char GetHour()
{
	unsigned char temp;
	temp=TimeReadAB(DS1302_HOUR_READ);
	temp=temp/16*10+temp%16;
	return temp;
}
unsigned char GetDay()
{
	unsigned char temp;
	temp=TimeReadAB(DS1302_DAY_READ);
	temp=temp/16*10+temp%16;
	return temp;
}
unsigned char GetMonth()
{
	unsigned char temp;
	temp=TimeReadAB(DS1302_MONTH_READ);
	temp=temp/16*10+temp%16;
	return temp;
}
unsigned char GetWeek()
{
	unsigned char temp;
	temp=TimeReadAB(DS1302_WEEK_READ);
	temp=temp/16*10+temp%16;
	return temp;
}
unsigned char GetYear()
{
	unsigned char temp;
	temp=TimeReadAB(DS1302_YEAR_READ);
	temp=temp/16*10+temp%16;
	return temp;
}