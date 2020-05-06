#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
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
	int getpos()
	{	return(position);
	}
	int getlastroll()
	{return(lastroll);}
};
player p[2];
void gamedisp()
{
	clrscr();
	cleardevice();
	gotoxy(14,1);
	cout<<"PLAYER 1";
	line(320,0,320,600);
	gotoxy(56,1);
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
	int x[2],check,y;
	x[0]=8;x[1]=53;
	for(int i=0;i>=0;i++){
	if(i%2==0)
	{
		if(wherey()+1>23)
		{	gamedisp();
			gotoxy(x[i%2],wherey()+2);
			cout<<"You got a "<<p[i%2].getlastroll();
			gotoxy(x[i%2],wherey()+1);
			cout<<"You are now at "<<p[i%2].getpos();
			gotoxy(x[1],wherey()-1);
			cout<<"You got a "<<p[1].getlastroll();
			gotoxy(x[1],wherey()+1);
			cout<<"You are now at "<<p[1].getpos();
		       //	gotoxy(x[i%2],wherey()+1);
		}
		y=wherey();
		if(p[0].getpos()>p[1].getpos())
		{
			gotoxy(50,1);
			cout<<"  ";
			gotoxy(9,1);
			cout<<"*";
		}
		else if(p[0].getpos()<p[1].getpos())
		{
			gotoxy(9,1);
			cout<<"  ";
			gotoxy(50,1);
			cout<<"*";
		}
		gotoxy(x[i%2],y+2);
	}
	else if(i%2!=0)
	{

		gotoxy(x[i%2],wherey()-2);
	}
	if(p[0].getpos()>=100)
	{
		endgame(1);
		break;
	}
	else if(p[1].getpos()>=100)
	{
		endgame(2);
		break;
	}
	cout<<"Shall we roll the dice?";
	cin>>ans;
	if(ans=='y'||ans=='Y')
	{
		//temp=new int;
		//temp=p2.getpos();
		do{
		check=p[i%2].update(random(7));
		}while(check==0);
		gotoxy(x[i%2],wherey());
		cout<<"You got a "<<p[i%2].getlastroll();
		gotoxy(x[i%2],wherey()+1);
		cout<<"You are now at "<<p[i%2].getpos();
		//delete temp
	}
	else
	{
		gotoxy(x[i%2],wherey());
		cout<<"Do you want to exit?";
		cin>>ans2;
		if(ans2=='y'||ans2=='Y')
		{
			endgame();
			break;
		}
	}
	}
}


void main()
{
	clrscr();
	int gmode,gdriver=DETECT;
	initgraph(&gdriver,&gmode,"");
	setbkcolor(1);
	randomize();
	gamedisp();
	gameplay();
	getch();
	exit(0);
}