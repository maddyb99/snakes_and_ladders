#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
void board()
{
	int i,x=158,y=40,xi=4,yi=2;
	for(i=0;i<11;i++)
	{	line(x+(32*i),y,x+(32*i),y+(32*10));
		line(x,y+(32*i),x+(32*10),y+(32*i));
	}
	x=22;y=22;
	for(i=1;i<101;i++)
	{
		if(i>99)
			gotoxy(x-1,y);
		else
			gotoxy(x,y);
		cout<<i;
		if(i%10==0)
		{       x+=xi;
			xi=xi*-1;
			y=y-yi;
		}
		x+=xi;
		delay(50);
	}

}
void main()
{
	int gdriver=VGA,gmode=VGAHI;
	initgraph(&gdriver,&gmode,"");
	setbkcolor(1);
	board();
	getch();
}
