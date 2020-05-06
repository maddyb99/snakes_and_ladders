#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
class player
{
	int position, lastroll;
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
			lastroll=roll;
			return(1);
		}
	}
	int getpos(){return(position);}
	void disp(int x, int y)
	{
		gotoxy(x,y);
		cout<<"You got a "<<lastroll<<".";
		gotoxy(x,y+1);
		cout<<"You are now at "<<position<<".";
	}

};
player p[2];
void gamedisp()
{
	clrscr();
	cleardevice();
	cout<<"PLAYER 1";
	line(320,0,320,600);
	gotoxy(42,wherey());
	cout<<"PLAYER 2";
}
void endgame(int mode=0)
{
	clrscr();
	cleardevice();
	switch(mode)
	{
		case 0: cout<<"Player ENDED the Game.";
			break;
		default: cout<<"GAME ENDED\nPlayer "<<mode<<" WON.";
			break;
	}
	cout<<"\n\nPress any key to exit.";
}
void gameplay()
{
	char ans,ans2='y';
	int x[2],check,y,i,pos[2]={0,0},pn;
	x[0]=1;x[1]=42;
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
			gotoxy(50,1);
			cout<<"  ";
			gotoxy(9,1);
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
			gotoxy(9,1);
			cout<<"  ";
			gotoxy(50,1);
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
		gotoxy(x[pn],wherey());
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
	int gmode,gdriver=DETECT;
	initgraph(&gdriver,&gmode,"");
	setbkcolor(1);
	randomize();
	gamedisp();
	gameplay();
	getch();
	exit(0);
}