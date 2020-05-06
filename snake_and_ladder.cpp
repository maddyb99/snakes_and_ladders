#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<graphics.h>
#include<stdio.h>
#include<string.h>
class player
{
	int position, lastroll,ladder;
	char plname[30];
/*	player()
	{	position=0;
	}*/
	public:
	player()
	{position=0;lastroll=0;}
	int update(int roll)
	{
		if(roll==0)
			return(0);
		else
		{
			position+=roll;
			ladder=checkladder(position);
			if(ladder!=0)
			{
				switch(ladder)
				{
					case 1:position=ladder1[1];
						break;
					case 2:position=ladder2[1];
						break;
					case 3:position=ladder3[1];
						break;
				}
			}
			lastroll=roll;
			return(1);
		}
	}
	int getpos(){return(position);}
	void disp(int x, int y)
	{
		if(ladder==0)
		{	gotoxy(x+6,y);
			cout<<"You got a "<<lastroll<<".";
		}
		else
		{
			gotoxy(x,y);
			cout<<"You got a "<<lastroll<<" and ladder "<<ladder;
		}
		gotoxy(x+3,y+1);
		cout<<"You are now at "<<position<<".";
	}
	void indetails()
	{    gets(plname);
	}
	char* getname()
	{	return(plname);
	}

};
player p[2];
int ladder1[2],ladder3[2],ladder2[2],snake1[2],snake2[2];
int checkladder(int pos)
{
	if(pos==ladder1[0])
		return(1);
	else if(pos==ladder2[0])
		return(2);
	else if(pos==ladder3[0])
		return(3);
	else
		return(0);
}
int snakeladder(int mode)
{
	int i,y,x;
	if (mode==1)
	{
		do{
			ladder1[0]=random(80);
			ladder1[1]=random(100);
		}while(ladder1[0]<0||ladder1[1]<=ladder1[0]);
		do{
			do{
			ladder2[0]=random(80);
			ladder2[1]=random(100);
			}while(ladder2[0]<ladder1[0]);
		}while(ladder2[0]<0||ladder2[1]<=ladder2[0]);
		do{
			do{
			ladder3[0]=random(80);
			ladder3[1]=random(100);
			}while(ladder3[0]<ladder2[0]);
		}while(ladder3[0]<0||ladder3[1]<=ladder3[0]);
	}
	if(mode==1||mode==0)
	{
		y=wherey();x=wherex();
		gotoxy(38,17);
		cout<<"Ladder:";
		gotoxy(38,wherey()+1);
		cout<<"1)"<<ladder1[0]<<"-"<<ladder1[1];
		gotoxy(38,wherey()+1);
		cout<<"2)"<<ladder2[0]<<"-"<<ladder2[1];
		gotoxy(38,wherey()+1);
		cout<<"3)"<<ladder3[0]<<"-"<<ladder3[1];
		gotoxy(x,y);
	}return(0);
}
void gamedisp()
{
	clrscr();
	cleardevice();
	int x=160,y=40,xi=32,yi=32,*poly,style=SOLID_FILL,i;
	char ch[3];
	outtextxy(8,8,"Currently Winning: ");
	outtextxy(3,45,"Ladders are at:");
	outtextxy(515,45,"Snakes are at:");
	outtextxy(5,350,p[0].getname());
	int temp=strlen(p[1].getname());
	outtextxy(640-(strlen(p[1].getname())*9),350,p[1].getname());
	line(0,20,640,20);
	line(130,20,130,390);
	line(510,20,510,390);
	line(130,390,510,390);
	line(0,340,130,340);
	line(510,340,640,340);
	poly=new int[10];
	poly[0]=x-10;
	poly[1]=y-10;
	poly[2]=x+330;
	poly[3]=poly[1];
	poly[4]=poly[2];
	poly[5]=y+330;
	poly[6]=poly[0];
	poly[7]=poly[5];
	poly[8]=poly[0];
	poly[9]=poly[1];
	setfillstyle(style,0);
	fillpoly(5,poly);
	poly[0]=x;
	poly[1]=y;
	poly[2]=x+320;
	poly[3]=poly[1];
	poly[4]=poly[2];
	poly[5]=y+320;
	poly[6]=poly[0];
	poly[7]=poly[5];
	poly[8]=poly[0];
	poly[9]=poly[1];
	setfillstyle(style,1);
	fillpoly(5,poly);
	delete poly;
	for(i=0;i<11;i++)
	{	line(x+(32*i),y,x+(32*i),y+(32*10));
		line(x,y+(32*i),x+(32*10),y+(32*i));
		delay(40);
	}
	ch[2]=NULL;
	x=170;y=340;
	for(i=1;i<101;i++)
	{
		if(i==100)
		outtextxy(x-4,y,"100");
		else
		{	ch[0]=i/10+48;
			ch[1]=i%10+48;
			outtextxy(x,y,ch);
		}
		//cout<<i;
		if(i%10==0)
		{       x+=xi;
			xi=xi*-1;
			y=y-yi;
		}
		x+=xi;
		delay(50);
	}

}
void endgame(int mode=0)
{
	clrscr();
	switch(mode)
	{
		case 0: cout<<"Player ENDED the Game.";
			break;
		default: cout<<"GAME ENDED\n"<<player[mode].getname()<<" WON.";
			break;
	}
	cout<<"\n\nPress any key to exit.";
}
void gameplay()
{
	char ans,ans2='y';
	int x[2],check,y,i,pos[2]={0,0},pn;
	x[0]=8;x[1]=49;
	for(i=0;i>=0;i++){
	pn=i%2;
	if(pn==0)
	{
		if(wherey()+1>23)
		{	gamedisp();
			p[pn].disp(x[pn],wherey()+2);
			p[1].disp(x[1],wherey()-1);
		}
		y=wherey();
		if(pos[0]>pos[1])
		{
			gotoxy(65,1);
			cout<<" ";
			gotoxy(24,1);
			cout<<"*";
		}
		else if(pos[0]<pos[1])
		{
			if(pos[1]>=100)
			{
				gotoxy(wherex()-4,wherey());
				cout<<"100!";
				delay(1000);
				endgame(2);
				break;
			}
			gotoxy(24,1);
			cout<<" ";
			gotoxy(65,1);
			cout<<"*";
		}
		gotoxy(x[pn],y+2);
	}
	else if(i%2!=0)
	{

		if(pos[0]>=100)
		{
			gotoxy(wherex()-4,wherey());
			cout<<"100!";
			delay(1000);
			endgame(1);
			break;
		}
		gotoxy(x[pn],wherey()-2);
	}
	cout<<"Shall we roll the dice?";
	ans=getch();
	cout<<ans<<"\n";
	if(ans=='y'||ans=='Y')
	{
		do{
		check=p[pn].update(random(7));
		}while(check==0);
		p[pn].disp(x[pn],wherey());
	}
	else
	{
		gotoxy(x[pn]+1,wherey());
		cout<<"Do you want to exit?";
		ans2=getch();
		cout<<ans2<<"\n";
		if(ans2=='y'||ans2=='Y')
		{
			endgame();
			break;
		}
	}
	pos[0]=p[0].getpos();
	pos[1]=p[1].getpos();     // delay(1000);
	}
}


void main()
{
	int gdriver=VGA,gmode=VGAHI;
	initgraph(&gdriver,&gmode,"");
	randomize();
	cout<<"Enter name of Player 1: ";
	p[0].indetails();
	cout<<"Enter Name of Player 2: ";
	p[1].indetails();
	gamedisp();
	getch();
	endgame(0);
	exit(0);
}