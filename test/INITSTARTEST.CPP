#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<graphics.h>
#include<stdio.h>
#include<string.h>
void display()
{
	int x[2],y[3],*poly,option=0,end=0;
	setcolor(6);
	settextstyle(4,HORIZ_DIR,6);
	x[0]=(getmaxx()/2)-(textwidth("Snakes & Ladders")/2);
	y[0]=textheight("S");
	outtextxy(x[0],y[0],"Snakes & Ladders");
	setcolor(3);
	settextstyle(0,HORIZ_DIR,2);
	x[0]=(getmaxx()/2)-(textwidth("Play")/2);
	x[1]=x[0]-textwidth("->");
	y[0]=(getmaxy()/2)-(textheight("P")*2);
	y[1]=(getmaxy()/2);
	y[2]=(getmaxy()/2)+(textheight("P")*2);
	outtextxy(x[0],y[0],"Play");
	outtextxy(x[0],y[1],"Help");
	outtextxy(x[0],y[2],"Exit");
	poly=new int[10];
	poly[0]=x[1];
	poly[2]=x[0]-1;
	poly[4]=poly[2];
	poly[6]=poly[0];
	poly[8]=poly[0];
	do
	{
		setcolor(3);
		outtextxy(x[1],y[option],"->");
		end=getch();
		setcolor(getbkcolor());
		setfillstyle(SOLID_FILL,getbkcolor());
		poly[1]=y[option]+textheight(">");
		poly[3]=poly[1];
		poly[5]=y[option];
		poly[7]=poly[5];
		poly[9]=poly[1];
		fillpoly(5,poly);
		switch(end)
		{
			case '2':option++;
				break;
			case '8':option--;
				break;
		}
		if(option>2)
			option=0;
		else if(option<0)
			option=2;
	}while(end!=13);
	delete poly;
	if(option==0)
		displae();
	else if(option==1)
	else if
	{
		return();
	}
}

void main()
{
	clrscr();
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"");
	display();
}
