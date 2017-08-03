#include <reg52.h>		   //ͷ�ļ�
#include "TM1640.h"

sbit TM1640_DIN=P2^2;
sbit TM1640_CLK=P2^3;

unsigned char code CODE[12]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x40,0x08}; //���������0~9������

/********************Start����*************************/
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
/********************Stop����*************************/
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

/***************����8bit���ݣ��ӵ�λ��ʼ**************/
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

/************��ʾ�����������1~16λ��ʾ0~F************/
void TM1640Display(unsigned char temp[16])
{
	unsigned char i;

	TM1640Start();
	TM1640Writebyte(0x40);	//�����������ã���ͨģʽ����ַ�Զ���һ
	TM1640Stop();

	TM1640Start();
	TM1640Writebyte(0xc0);	//��ַ�������ã���ʼ��ַ00H
	for(i=0; i<16; i++)	//����16λ��ʾ����
	{
		TM1640Writebyte(CODE[temp[i]]);
	}
	TM1640Stop();

	TM1640Start();
	TM1640Writebyte(0x8a);	//��ʾ���ƣ���ʾ������������Ϊ4/16
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

/***************����8bit���ݣ��ӵ�λ��ʼ**************/
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

/************��ʾ�����������1~16λ��ʾ0~F************/
void TM1640DisplayInterrupt(unsigned char temp[16])
{
	unsigned char i;

	TM1640Start();
	TM1640WritebyteInterrupt(0x40);	//�����������ã���ͨģʽ����ַ�Զ���һ
	TM1640Stop();

	TM1640Start();
	TM1640WritebyteInterrupt(0xc0);	//��ַ�������ã���ʼ��ַ00H
	for(i=0; i<16; i++)	//����16λ��ʾ����
	{
		TM1640WritebyteInterrupt(CODE[temp[i]]);
	}
	TM1640Stop();

	TM1640Start();
	TM1640WritebyteInterrupt(0x8a);	//��ʾ���ƣ���ʾ������������Ϊ8/16
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