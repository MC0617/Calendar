#include "delay.h"
#include <intrins.h>
//11.0592mHz
/*
void delay5us(void)   //Îó²î -0.659722222222us
{
}
void delay10us(void)   //Îó²î -0.234375us
{
	unsigned char a;
	for(a=2; a>0; a--);
}
void delay50us(void)   //Îó²î -0.086805555556us
{
	unsigned char a,b;
	for(b=1; b>0; b--)
		for(a=19; a>0; a--);
}
void delay100us(void)   //Îó²î -0.173611111111us
{
	unsigned char a,b;
	for(b=3; b>0; b--)
		for(a=13; a>0; a--);
}
void delay500us(void)   //Îó²î -0.868055555556us
{
	unsigned char a,b;
	for(b=91; b>0; b--)
		for(a=1; a>0; a--);
}
void delay1ms(void)   //Îó²î -0.651041666667us
{
	unsigned char a,b;
	for(b=4; b>0; b--)
		for(a=113; a>0; a--);
}
void delay5ms(void)   //Îó²î -0.000000000001us
{
	unsigned char a,b,c;
	for(c=1; c>0; c--)
		for(b=200; b>0; b--)
			for(a=10; a>0; a--);
}
void delay10ms(void)   //Îó²î -0.000000000002us
{
	unsigned char a,b;
	for(b=151; b>0; b--)
		for(a=29; a>0; a--);
}
void delay50ms(void)   //Îó²î -0.00000000001us
{
	unsigned char a,b;
	for(b=97; b>0; b--)
		for(a=236; a>0; a--);
}
void delay100ms(void)   //Îó²î -0.000000000021us
{
	unsigned char a,b,c;
	for(c=35; c>0; c--)
		for(b=10; b>0; b--)
			for(a=130; a>0; a--);
}
void delay500ms(void)   //Îó²î -0.000000000127us
{
	unsigned char a,b,c;
	for(c=122; c>0; c--)
		for(b=222; b>0; b--)
			for(a=7; a>0; a--);
	//_nop_();  //if Keil,require use intrins.h
}
void delay1s(void)   //Îó²î -0.00000000024us
{
	unsigned char a,b,c;
	for(c=95; c>0; c--)
		for(b=26; b>0; b--)
			for(a=185; a>0; a--);
}
*/

	
//12mHz
void delay5us(void)   //Îó²î 0us
{
    _nop_();  //if Keil,require use intrins.h
}
void delay10us(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=1;a>0;a--);
}

/* void delay50us(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=9;b>0;b--)
        for(a=1;a>0;a--);
}
void delay100us(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=19;b>0;b--)
        for(a=1;a>0;a--);
}
void delay500us(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=99;b>0;b--)
        for(a=1;a>0;a--);
}
void delay1ms(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=199;b>0;b--)
        for(a=1;a>0;a--);
}
void delay5ms(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=185;b>0;b--)
        for(a=12;a>0;a--);
}
 */
void delay10ms(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=5;c>0;c--)
        for(b=4;b>0;b--)
            for(a=248;a>0;a--);
}
/*
void delay50ms(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=165;b>0;b--)
        for(a=150;a>0;a--);
}
void delay100ms(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=7;c>0;c--)
        for(b=74;b>0;b--)
            for(a=95;a>0;a--);
}
void delay500ms(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=205;c>0;c--)
        for(b=116;b>0;b--)
            for(a=9;a>0;a--);
}
*/
void delay1s(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=46;c>0;c--)
        for(b=152;b>0;b--)
            for(a=70;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}
