#include<reg51.h>
sbit sen1=P1^0;
sbit sen2=P1^1;
sbit rs=P1^2;
sbit rw=P1^3;
sbit en=P1^4;
sbit li=P1^5;
sbit re=P1^6;
void lcdcmd(unsigned char);
void lcddat(unsigned char);
void delay();
void lcddis(unsigned char *s,unsigned char r);
void lcdconv(unsigned char);
void main()
{
	unsigned char x;
	y:
	x=0;
	lcdcmd(0x38);
	delay();
	lcdcmd(0x01);
	delay();
	lcdcmd(0x10);
	delay();
	lcdcmd(0x0c);
	delay();
	lcddis(" WELCOME",8);
	lcdcmd(0xc0);
	delay();
	lcddis("VISITOR COUNTER",15);
	delay();
	lcdcmd(0x01);
	delay();
	while(1)
	{	
		if(re==0)
		{
			goto y;
		}
		if(sen1==0)
		{
			lcdcmd(0x80);
			delay();
			lcddis("COUNT:",6);
			lcdcmd(0x87);
			delay();
			x=x+1;
			lcdconv(x);
		}
		if(sen2==0)
		{
			if(x!=0)
			{
				lcdcmd(0xc6);
				delay();
				x=x-1;
				delay();
				lcdcmd(0x87);
				delay();
				lcdconv(x);
			}
		}
		if(x==0)
		{
			li=0;
		}
		else
		{
			li=1;
		}	
	}
}
void lcdcmd(unsigned char val)
{
	P2=val;
	rs=0;
	rw=0;
	en=1;
	delay();
	en=0;
}
void lcddat(unsigned char dat)
{
	P2=dat;
	rs=1;
	rw=0;
	en=1;
	delay();
	en=0;
}
void lcddis(unsigned char *s, unsigned char r)
{
	unsigned char w;
	for(w=0;w<r;w++)
	{
		lcddat(s[w]);
		delay();
	}
}
void lcdconv(unsigned char num)
{
	unsigned char p,n;
	p=num/10;
	n=num%10;
	p=p+0x30;
	n=n+0x30;
	lcddat(p);
	lcddat(n);
}
void delay()
{
	unsigned int k,l;
	for(k=0;k<5000;k++);
	for(l=0;l<1000;l++);
}
