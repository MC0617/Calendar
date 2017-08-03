#include <reg52.h>		   //头文件
#include "TM1640.h"

sbit TM1640_DIN=P2^2;
sbit TM1640_CLK=P2^3;

unsigned char code CODE[12]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x40,0x08}; //共阴数码管0~9字型码

/********************Start函数*************************/
void TM1640Start()
{
	TM1640_DIN=1;
	TM1640_CLK=1;

	delay5us();
	TM1640_DIN=1;

	delay5us();
	TM1640_DIN=0;

	delay10us();
	TM1640_CLK=0;

	delay5us();
}
/********************Stop函数*************************/
void TM1640Stop()
{
	TM1640_CLK=1;
	delay5us();
	TM1640_DIN=0;
	delay5us();
	TM1640_DIN=1;
	delay5us();
	TM1640_CLK=0;
	TM1640_DIN=0;

}

/***************发送8bit数据，从低位开始**************/
void TM1640Writebyte(unsigned char oneByte)
{
	unsigned char i;
	for(i=0; i<8; i++)
	{
		TM1640_CLK=0;
		if(oneByte&0x01)
			TM1640_DIN=1;
		else
			TM1640_DIN=0;
		delay10us();
		TM1640_CLK=1;
		oneByte=oneByte>>1;
	}
	TM1640_CLK=0;
	delay10us();
	TM1640_DIN=0;
	delay5us();
}

/************显示函数，数码管1~16位显示0~F************/
void TM1640Display(unsigned char temp[16])
{
	unsigned char i;

	TM1640Start();
	TM1640Writebyte(0x40);	//数据命令设置：普通模式，地址自动加一
	TM1640Stop();

	TM1640Start();
	TM1640Writebyte(0xc0);	//地址命令设置：初始地址00H
	for(i=0; i<16; i++)	//发送16位显示数据
	{
		TM1640Writebyte(CODE[temp[i]]);
	}
	TM1640Stop();

	TM1640Start();
	TM1640Writebyte(0x8a);	//显示控制：显示开，脉冲宽度设为4/16
	TM1640Stop();
}

void TM1640DisplayActual(unsigned char temp[8])
{
	unsigned char Dis[16],i,j;
	for(i=0; i<8; i++)
	{
		if(3>=i) j=2*i;
		else j=2*i-1;
		if(3!=i)
		{
			if(0xff==temp[i])
			{
				Dis[j]=10;
				Dis[j+1]=10;
			}
			else if(0xee==temp[i])
			{
				Dis[j]=11;
				Dis[j+1]=11;
			}
			else
			{
				Dis[j]=temp[i]/10;
				Dis[j+1]=temp[i]%10;
			}
		}
		else
		{
			if(0xff==temp[i])
			{
				Dis[j]=10;
			}
			else if(0xee==temp[i])
			{
				Dis[j]=11;
			}
			else
			{
				if(7!=temp[i])
					Dis[j]=temp[i];
				else
					Dis[j]=8;
			}

		}
	}
	TM1640Display(Dis);
}

/***************发送8bit数据，从低位开始**************/
void TM1640WritebyteInterrupt(unsigned char oneByte)
{
	unsigned char i;
	for(i=0; i<8; i++)
	{
		TM1640_CLK=0;
		if(oneByte&0x01)
			TM1640_DIN=1;
		else
			TM1640_DIN=0;
		delay10us();
		TM1640_CLK=1;
		oneByte=oneByte>>1;
	}
	TM1640_CLK=0;
	delay10us();
	TM1640_DIN=0;
	delay5us();
}

/************显示函数，数码管1~16位显示0~F************/
void TM1640DisplayInterrupt(unsigned char temp[16])
{
	unsigned char i;

	TM1640Start();
	TM1640WritebyteInterrupt(0x40);	//数据命令设置：普通模式，地址自动加一
	TM1640Stop();

	TM1640Start();
	TM1640WritebyteInterrupt(0xc0);	//地址命令设置：初始地址00H
	for(i=0; i<16; i++)	//发送16位显示数据
	{
		TM1640WritebyteInterrupt(CODE[temp[i]]);
	}
	TM1640Stop();

	TM1640Start();
	TM1640WritebyteInterrupt(0x8a);	//显示控制：显示开，脉冲宽度设为8/16
	TM1640Stop();
}


void TM1640DisplayActualInterrupt(unsigned char temp[6])
{
	unsigned char Dis[16],i,j;
	for(i=11; i<15; i++)
	{
		Dis[i]=10;
	}
	for(i=0; i<6; i++)
	{
		if(3>=i) j=2*i;
		else j=2*i-1;
		if(3!=i)
		{
			if(0xee==temp[i])
			{
				Dis[j]=11;
				Dis[j+1]=11;
			}
			else
			{
				Dis[j]=temp[i]/10;
				Dis[j+1]=temp[i]%10;
			}
		}
		else
		{
			if(0xee==temp[i])
			{
				Dis[j]=11;
			}
			else
			{
				if(7!=temp[i])
					Dis[j]=temp[i];
				else
					Dis[j]=8;
			}

		}
	}
	TM1640DisplayInterrupt(Dis);
}