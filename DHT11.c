//电源引脚间接100nf电容用以去耦滤波
//DHT11电源和地连接单片机电源和地
//DHT11数据位与MCU之间连接线长度小于20m时上拉5K电阻,大于20m根据实际情况选择
//传感器上电后要等待1s以越过不稳定状态,在此期间不要发送任何指令
//DHT11 3pin为空
#include <reg52.h>
#include "DHT11.h"
#include "delay.h"

sbit  DHT11_DATA  = P2^4 ;

unsigned char  DHT11_FLAG;
unsigned char  DHT11_TEMP;

unsigned char DHT11ReadByte(void)
{
	unsigned char ReadValue=0;
	unsigned char i;

	for(i=0; i<8; i++)
	{

		DHT11_FLAG=2;
		while((!DHT11_DATA)&&DHT11_FLAG++);
		delay10us();
		delay10us();
		delay10us();
		DHT11_TEMP=0;
		if(DHT11_DATA)
			DHT11_TEMP=1;
		DHT11_FLAG=2;
		while((DHT11_DATA)&&DHT11_FLAG++);
		//超时则跳出for循环
		if(DHT11_FLAG==1)break;
		//判断数据位是0还是1

		// 如果高电平高过预定0高电平值则数据位为 1

		ReadValue<<=1;
		ReadValue|=DHT11_TEMP;        //0
	}//rof
	return ReadValue;
}
unsigned int GetDHT11Data(void)
{
	unsigned char  DHT11_T_H,DHT11_T_L,DHT11_RH_H,DHT11_RH_L,DHT11_CHECK;
	unsigned int ReturnValue;
	//主机拉低18ms
	DHT11_DATA=0;
	delay10ms();delay10ms();
	DHT11_DATA=1;
	//总线由上拉电阻拉高 主机延时20us
	delay10us();
	delay10us();
	delay10us();
	//主机设为输入 判断从机响应信号
	DHT11_DATA=1;
	//判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行
	if(!DHT11_DATA)		 //T !
	{
		DHT11_FLAG=2;
		//判断从机是否发出 80us 的低电平响应信号是否结束
		while((!DHT11_DATA)&&DHT11_FLAG++);
		DHT11_FLAG=2;
		//判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
		while((DHT11_DATA)&&DHT11_FLAG++);
		//数据接收状态

		DHT11_RH_H=DHT11ReadByte();
		DHT11_RH_L=DHT11ReadByte();
		DHT11_T_H=DHT11ReadByte();
		DHT11_T_L=DHT11ReadByte();
		DHT11_CHECK=DHT11ReadByte();
		DHT11_DATA=1;
		//数据校验

		if((DHT11_T_H+DHT11_T_L+DHT11_RH_H+DHT11_RH_L)==DHT11_CHECK)
		{
			ReturnValue=DHT11_RH_H;
			ReturnValue<<=8;
			ReturnValue|=DHT11_T_H;
		}//fi
	}//fi
	return ReturnValue;
}
