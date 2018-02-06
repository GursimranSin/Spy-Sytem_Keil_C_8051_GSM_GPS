#include<reg51.h>
#include<stdio.h>
void gsm();
void key_scan();
unsigned int row,col,net,t;
 	char abhi[15];
sbit RS=P0^0;
sbit E=P0^1;
sbit R1=P2^0;
sbit R2=P2^1;
sbit R3=P2^2;
sbit R4=P2^3;
sbit C1=P2^4;
sbit C2=P2^5;
sbit C3=P2^6;
sbit C4=P2^7;

sbit g1 = P3^7;
sbit g2 = P3^2;

void delay(int x)
{
	int i;
	for(i=0;i<x;i++);
}
void lcd_cmd(char dat)
{
	P1=dat;
	RS=0;
	E=1;
	delay(1000);
	E=0;
}

void lcd_data(char dat)
{
	P1=dat;
	RS=1;
	E=1;
	delay(1000);
	E=0;
}
void lcd_installation()
{
	lcd_cmd(0X38);
	lcd_cmd(0X0E);
	lcd_cmd(0X06);
	lcd_cmd(0X01);
	lcd_cmd(0X80);
}

 void key_scan2()
{
	P2=0xf0;
	do
	{
		R1=R2=R3=R4=0;
	}
	while(C1==1&&C2==1&&C3==1&&C4==1);

	if(C1==0)	col=0x01;
	if(C2==0)   col=0x02;
	if(C3==0)	col=0x03;
	if(C4==0)	col=0X04;

	P2=0x0f;
	do
	{
		C1=C2=C3=C4=0;
	}
	while(R1==1&&R2==1&&R3==1&&R4==1);

	if(R1==0)	row=0x00;
	if(R2==0)	row=0x04;
	if(R3==0)	row=0x08;
	if(R4==0)	row=0x0c;

	net=row+col;

	if(net==0x0a)			net = 0x09;
	else if(net==0x0b)		net = 0x00;


}
void serial_init()
{
	SCON=0X50;
	TMOD=0X20;
	TH1=0XFD;
	TR1=1;
}
void serial_trans(unsigned char trans)
{
	SBUF=trans;
	while(TI==0);
	TI=0;
}

/*void serial_rec(unsigned char rec)
{
	while(RI==0);
	rec=SBUF;
	RI=0;
}*/ 

void gsm()
{ 
	int i;
	char arr1[]="";
	unsigned char arr2[]="ENTER NUMBER";
	g1=1;g2=0;
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	for(i=0;i<12;i++)
	{
		lcd_data(arr2[i]);
	}
	lcd_cmd(0xc0);
	for(i=0;i<10;i++)
	{
		key_scan2();	
		abhi[i]=arr1[i]=net+0x30;
		lcd_data(arr1[i]);
		delay(30000);		
	} 
	TI=0;
	serial_trans('A');
	serial_trans('T');
	serial_trans('D');

	for(i=0;i<10;i++)
	{
	 serial_trans(arr1[i]);
	} 
	delay(3000);
}

void call()
{ 
	int i;
	unsigned char arr3[]="CALLING....";
	g1=1;g2=0;
	t=1;
	SBUF=';';
	while(TI==0);
	TI=0;
	SBUF=0x0d;
	while(TI==0);
	delay(30000);delay(30000);delay(30000);delay(30000);
	lcd_cmd(0x01);
	delay(3000);
	lcd_cmd(0x80);
	delay(3000);
	for(i=0;i<11;i++)
	{
		lcd_data(arr3[i]);
		delay(300);	
	}


}
  
void key_scan()
{
	P2=0xf0;
	do
	{
		R1=R2=R3=R4=0;
	}
	while(C1==1&&C2==1&&C3==1&&C4==1);

	if(C1==0)	col=0x01;
	if(C2==0)   col=0x02;
	if(C3==0)	col=0x03;
	if(C4==0)	col=0X04;

	P2=0x0f;
	do
	{
		C1=C2=C3=C4=0;
	}
	while(R1==1&&R2==1&&R3==1&&R4==1);

	if(R1==0)	row=0x00;
	if(R2==0)	row=0x04;
	if(R3==0)	row=0x08;
	if(R4==0)	row=0x0c;

	net=row+col;

	if(net==0x0a)			net = 0x09;
	else if(net==0x0b)		net = 0x00;
}
 
void key_scan1()
{
unsigned int gh;
	P2=0xf0;
	
		R1=R2=R3=R4=0;
	while(C1==1&&C2==1&&C3==1&&C4==1)
	{
	gh=gh+1;
	if(gh>30000)
	{
	gh=0;
	goto end;
	}
	}

	if(C1==0)	col=0x00;
	if(C2==0)   col=0x01;
	if(C3==0)	col=0x02;
	if(C4==0)	col=0X03;

	P2=0x0f;
	do
	{
		C1=C2=C3=C4=0;
	}
	while(R1==1&&R2==1&&R3==1&&R4==1);

	if(R1==0)	row=0x00;
	if(R2==0)	row=0x04;
	if(R3==0)	row=0x08;
	if(R4==0)	row=0x0c;

	net=row+col;
	end:
	delay(300);
	if(net==0x0a)			net = 0x09;
	else if(net==0x0b)		net = 0x00;
}
void gps();	
void halt()
{
	int i;
	char arr5[]="CALL ENDED";
	g1=1;g2=0;
	TI=0;
	serial_trans('A');
	serial_trans('T');
	serial_trans('H');
	serial_trans(0x0d);
	TI=1;
	delay(30000);delay(30000);delay(30000);delay(30000);
 	lcd_cmd(0x01);
	delay(3000);
	lcd_cmd(0x80);
	delay(3000);
	for(i=0;i<10;i++)

	{
		lcd_data(arr5[i]);
		delay(300);	
	}
	if(t==1)
	{  t=0;
	   gps();
	   }
}

void rec()
{
	int i,i11,j;
	int hr,min,sec,a,b,c;
	char arr4[]="CALL RECIEVED";
	
	unsigned char arr6[9]="CALL FROM";
	g1=1;g2=0;
	t=1;
	P2 = 0xf0;
	lcd_cmd(0xc0);
					for(i=0;i<13;i++)
	{
		lcd_data(arr4[i]);
		delay(300);	
	}

   lcd_cmd(0x80);
	do
	{
		while(RI==0);
		RI=0;
	}while(SBUF != '+');

	
	do
	{
		while(RI==0);
		RI=0;
	}while(SBUF != '9');

	
	do
	{
		while(RI==0);
		RI=0;
	}while(SBUF != '1'); 


	i11=0;
	for(i=0;i<10;i++)
	{
		while(RI==0);
		RI=0;
		abhi[i11] = SBUF;
		i11++;
	}//while(abhi != '"');

	lcd_cmd(0x80);
	delay(3000);
	for(i=0;i<i11;i++)
	{
		lcd_data(abhi[i]);
		delay(300);	
	}

	TI=0;
	serial_trans('A');
	serial_trans('T');
	serial_trans('A');
	serial_trans(0x0d);
	TI=1;
	delay(30000);delay(30000);
	
	delay(3000);
	lcd_cmd(0x80);
	delay(3000);

	lcd_cmd(0xc0);	   
	for(hr=0;hr<12;hr++)
	{	  
		  
		for(min=0;min<60;min++)
		{
			
			for(sec=0;sec<60;sec++)
			{
		    	
				lcd_cmd(0Xc0);
				a=hr/10;
				lcd_data(0x30+a);
				a=hr%10;
				lcd_data(0x30+a);
				delay(3000);
				lcd_data(':');
				lcd_cmd(0Xc3);
				b=min/10;
				lcd_data(0x30+b);
			    b=min%10;
				lcd_data(0x30+b);
				delay(32000);
				lcd_data(':');
				lcd_cmd(0Xc6);
				c=sec/10;
				lcd_data(0x30+c);
				c=sec%10;
				lcd_data(0x30+c);
				lcd_data(' ');
				lcd_data(' ');
				lcd_data(' ');
				lcd_data(' ');
				 lcd_data(' ');

				
				while(P2 != 0xf0)
				{

				  key_scan2();

				if(net==0x0c)	
				{	
					halt();
		 	 		lcd_cmd(0Xc0);
					a=hr/10;
					lcd_data(0x30+a);
					a=hr%10;
					lcd_data(0x30+a);
					delay(3000);
					lcd_data(':');
					lcd_cmd(0Xc3);
					b=min/10;
					lcd_data(0x30+b);
				    b=min%10;
					lcd_data(0x30+b);
					delay(13250);
					lcd_data(':');
					lcd_cmd(0Xc6);
					c=sec/10;
					lcd_data(0x30+c);
					c=sec%10;
					lcd_data(0x30+c);
		 	 		goto zxc;}
				} 

							   
		 		
				}  
			}
		}  
		
	zxc:
	//gps();
	delay(1);
}
	
void msgread()
{
unsigned char gur[99];
	int i,x,j;
	
	char arr4[]="AT+CMGF=1";
	char ar4[]="AT+CMGR=";
	char ar1[]="msg number ";
	g1=1;g2=0;
	TI=0;
	for(i=0;i<9;i++)
	{
		serial_trans(arr4[i]);
	}
	TI=0;
	SBUF=0x0d;
	while(TI==0);
	TI=0;
	lcd_cmd(0x80);
	lcd_cmd(0x01);
	for(i=0;i<8;i++)
	{
		
		lcd_data(ar4[i]);
		serial_trans(ar4[i]);
		delay(300);
	}
		lcd_cmd(0xc0);
   for(i=0;i<11;i++)
	{
		lcd_data(ar1[i]);
		delay(300);
	}
	key_scan2();
	delay(30000);
	x=net+0x30;
	lcd_cmd(0x88);
	lcd_data(x);
	SBUF=x;
	while(TI==0);
	TI=0;
		SBUF=0x0d;
	while(TI==0);
	TI=0;
	i=0;
/*	
	do
	{
	while(RI==0);
    j=SBUF;
	RI=0;}while(i<40);*/
	for(i=0;i<99;i++)
	{		
	while(RI==0);
	gur[i]=SBUF;
	RI=0;
	}	 lcd_cmd(0x01);
		for(i=40;i<99;i++)
	{		
      lcd_data(gur[i]);
	  delay(3000);
	} 

	delay(30000);delay(30000);delay(30000);delay(30000);
}
void msgdel()
{
	int i,x;
	char ar1[]="msg number ";
	char arr5[]="AT+CMGD=";
	g1=1;g2=0;
	TI=0;
	for(i=0;i<8;i++)
	{
		lcd_data(arr5[i]);
		serial_trans(arr5[i]);
		delay(300);
	}
	TI=0;
	
	lcd_cmd(0xc0);
    for(i=0;i<11;i++)
	{
		lcd_data(ar1[i]);
		delay(300);
	}
	key_scan2();
	delay(30000);
	x=net+0x30;
	lcd_cmd(0x88);
	lcd_data(x);
	SBUF=x;
	while(TI==0);
	TI=0;
	SBUF=0x0d;
	while(TI==0);
	TI=0;
	delay(30000);delay(30000);delay(30000);delay(30000);
}  
 
void gps()
{	 
	int i,temp[60],abc;
    g1=0;g2=1;		                                                  
	do
	{
		while(RI==0);
		RI=0;
	}
	while(SBUF!='$');
	do
	{
	while(RI==0);
	RI=0;
	}	
	while(SBUF!='G');
	do
	{
		while(RI==0);
		RI=0;
	}
	while(SBUF!='P');
	do
	{
		while(RI==0);
		RI=0;
	}
	while(SBUF!='G');
	do
	{
		while(RI==0);
		RI=0;
	}
	while(SBUF!='G');
	do
	{
		while(RI==0);
		RI=0;
	}
	while(SBUF!='A');

	for(i=0;i<50;i++)
	{
		while(!RI);
		temp[i]=SBUF;
		RI=0;
	}
	//lcd_cmd(0x80);
	//for(i=12;i<44;i++)
	//{
//	lcd_data(temp[i]);
//	}
	
	g1=1;g2=0;
	
	TI = 1;
	printf("AT+CMGF+1\n");
	delay(30000);
	printf("AT+CMGS=\"9478050001\"\n");
	delay(30000);
	printf("Longitude:");

	for(abc=12;abc<24;abc++)
	{
	TI = 0;
	SBUF=temp[abc];
	while(TI==0);
	TI=0;
	}

	delay(30000);
	TI=1;
	printf("Lattitude:");

	for(abc=26;abc<40;abc++)
	{
	TI = 0;
	SBUF=temp[abc];
	while(TI==0);
	TI=0;
	}
	delay(30000);
			 SBUF=0x0d;
	while(TI==0);
	TI=0;
		for(abc=0;abc<10;abc++)
	{
	TI = 0;
	SBUF=abhi[abc];
	while(TI==0);
	TI=0;
	}

	
	TI = 0;
	SBUF=0x1a;
	while(TI==0);
	TI=0;  

}
 
	
void main()
{
	unsigned char a[]=" ";
	lcd_installation();
	serial_init();
	 //gps();
	
	while(1) 
	{
	 
		key_scan2();
		if(net==0x0a)		net = 0x09;
        else if(net==0x0b)	net = 0x00;

		else if(net==0x09)		call();
		else if(net==0x0c)		halt();
		else if(net==0x0d)		gsm(); 
		else if(net==0x0e)		rec();
		else if(net==0X0f)		msgread();
		else 				  	msgdel();
	}	
}			 