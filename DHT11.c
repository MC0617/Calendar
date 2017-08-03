//��Դ���ż��100nf��������ȥ���˲�
//DHT11��Դ�͵����ӵ�Ƭ����Դ�͵�
//DHT11����λ��MCU֮�������߳���С��20mʱ����5K����,����20m����ʵ�����ѡ��
//�������ϵ��Ҫ�ȴ�1s��Խ�����ȶ�״̬,�ڴ��ڼ䲻Ҫ�����κ�ָ��
//DHT11 3pinΪ��
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
		//��ʱ������forѭ��
		if(DHT11_FLAG==1)break;
		//�ж�����λ��0����1

		// ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1

		ReadValue<<=1;
		ReadValue|=DHT11_TEMP;        //0
	}//rof
	return ReadValue;
}
unsigned int GetDHT11Data(void)
{
	unsigned char  DHT11_T_H,DHT11_T_L,DHT11_RH_H,DHT11_RH_L,DHT11_CHECK;
	unsigned int ReturnValue;
	//��������18ms
	DHT11_DATA=0;
	delay10ms();delay10ms();
	DHT11_DATA=1;
	//������������������ ������ʱ20us
	delay10us();
	delay10us();
	delay10us();
	//������Ϊ���� �жϴӻ���Ӧ�ź�
	DHT11_DATA=1;
	//�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������
	if(!DHT11_DATA)		 //T !
	{
		DHT11_FLAG=2;
		//�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����
		while((!DHT11_DATA)&&DHT11_FLAG++);
		DHT11_FLAG=2;
		//�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
		while((DHT11_DATA)&&DHT11_FLAG++);
		//���ݽ���״̬

		DHT11_RH_H=DHT11ReadByte();
		DHT11_RH_L=DHT11ReadByte();
		DHT11_T_H=DHT11ReadByte();
		DHT11_T_L=DHT11ReadByte();
		DHT11_CHECK=DHT11ReadByte();
		DHT11_DATA=1;
		//����У��

		if((DHT11_T_H+DHT11_T_L+DHT11_RH_H+DHT11_RH_L)==DHT11_CHECK)
		{
			ReturnValue=DHT11_RH_H;
			ReturnValue<<=8;
			ReturnValue|=DHT11_T_H;
		}//fi
	}//fi
	return ReturnValue;
}
