#include <reg52.h>
#include "delay.h"
#include "DS1302.h"
#include "TM1640.h"
#include "DHT11.h"

sbit KEY_SET=P1^0;
sbit KEY_UP=P1^1;
sbit KEY_DOWN=P1^2;
sbit KEY_ALARM=P1^3;

sbit BUZZ=P2^1;

void InitTimer0(void)	//定时器0  50ms
{
	TMOD = 0x01;
	TH0 = 0x3C;
	TL0 = 0x0B0;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}

unsigned char DisDis[6]= {0,0,0,0,0,0},DisNoDis[6]= {0,0,0,0,0,0};
unsigned char KeyTimesFlag=0,FlikerFlag=0;
unsigned char Timer0Count=0;

void main()
{
	unsigned char DisData[8],temp,DisData_temp[8];
	unsigned char Second,i;
	unsigned int TnRH_temp;
	unsigned char Max,Min;
	unsigned char MONTH_MAX[12]= {0,31,28,31,30,31,30,31,31,30,31,30};
	bit Count;
	P1=0xff;
	ClockInit();
	Second=GetSecond();
	for(temp=0; temp<8; temp++)
	{
		DisData[temp]=0xff;
	}
	
	TM1640DisplayActual(DisData);
	BUZZ=1;
	delay1s();
	BUZZ=0;	   					

	while(1)
	{
		while(KEY_SET&&KEY_ALARM&&!KeyTimesFlag)
		{
			temp=GetSecond();
			if(temp>=Second+2)
			{
				TnRH_temp=GetDHT11Data();
				Second=temp;
			}
			else if(temp==0)
			{
				Second=temp;
			}
			DisData[6]=(TnRH_temp&0xff);
			DisData[7]=((TnRH_temp>>8)&0xff);
			
			temp=0;
			temp=GetYear();
			DisData[0]=temp;
			temp=GetMonth();
			DisData[1]=temp;
			temp=GetDay();
			DisData[2]=temp;
			temp=GetWeek();
			DisData[3]=temp;
			temp=GetHour();
			DisData[4]=temp;
			temp=GetMinute();
			DisData[5]=temp;

			Count=0;
			for(temp=0; temp<8; temp++)
			{
				if(DisData_temp[temp]!=DisData[temp])
				{
					DisData_temp[temp]=DisData[temp];
					Count=1;
				}
			}

			if(Count)
			{
				TM1640DisplayActual(DisData);
				Count=0;
			}
		}
		if(!KEY_SET)
		{
			delay10ms();
			if(!KEY_SET)
			{
				while(!KEY_SET);
				for(i=0; i<6; i++)
				{
					DisDis[i]=DisData[i];
					DisNoDis[i]=DisData[i];
				}
				InitTimer0();
				DisNoDis[0]=0xee;
				KeyTimesFlag=1;
				Max=99;
				Min=00;
				FlikerFlag=0;
			}
		}
		while(0!=KeyTimesFlag)
		{
			if(!KEY_SET)
			{
				delay10ms();
				if(!KEY_SET)
				{
					while(!KEY_SET);		//等待释放
					switch (KeyTimesFlag+1)
					{
						case 1:break;
					case 2:
					{
						Max=12;
						Min=01;
						break;
					}
					case 3:
					{
						Max=MONTH_MAX[DisDis[1]];
						Min=01;
						break;
					}
					case 4:
					{
						Max=7;
						Min=1;
						break;
					}
					case 5:
					{
						Max=23;
						Min=00;
						break;
					}
					case 6:
					{
						Max=59;
						Min=00;
						break;
					}
					}
					DisNoDis[KeyTimesFlag-1]=DisDis[KeyTimesFlag-1];	//去前一位闪烁
					DisNoDis[KeyTimesFlag]=0xee;		//当前位闪烁
					KeyTimesFlag++;
					FlikerFlag=0;
				}
			}

			if(!KEY_UP)
			{
				delay10ms();
				if(!KEY_UP)
				{
					while(!KEY_UP);
					if(DisDis[KeyTimesFlag-1]==Max)
					{
						DisDis[KeyTimesFlag-1]=Min;
					}
					else
					{
						DisDis[KeyTimesFlag-1]++;
					}
					FlikerFlag=1;
				}
			}
			if(!KEY_DOWN)
			{
				delay10ms();
				if(!KEY_DOWN)
				{
					while(!KEY_DOWN);
					if(Min==DisDis[KeyTimesFlag-1])
					{
						DisDis[KeyTimesFlag-1]=Max;
					}
					else
					{
						DisDis[KeyTimesFlag-1]--;
					}
					FlikerFlag=1;
				}
			}
		}
	}
}

void Timer0Interrupt(void) interrupt 1
{
	TH0 = 0x3C;
	TL0 = 0x0B0;
	//add your code here!
	Timer0Count++;
	if(Timer0Count>=10)
	{
		FlikerFlag++;
		Timer0Count=0;
	}
	if(0!=KeyTimesFlag)
	{
		if(FlikerFlag%2==0)
		{
			TM1640DisplayActualInterrupt(DisNoDis);
		}
		else// if(FlikerFlag%2==1)
		{
			TM1640DisplayActualInterrupt(DisDis);
		}
	}
	//中断中闪烁操作位
	//闪烁结束传入DS1302
	if(KeyTimesFlag>=7||FlikerFlag>=7)	//闪烁结束传入DS1302,停止中断`定时器0
	{
		KeyTimesFlag=0;
		FlikerFlag=0;
		DS1302SetTime(DisDis);
		TR0=0;
		EA=0;
	}

}