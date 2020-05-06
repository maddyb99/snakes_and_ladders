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
	int getpos()
	{	return(position);
	}
	int getlastroll()
	{return(lastroll);}
};
player p[2];
void gamedisp()
{
	char ans,ans2='y';
	int x[2],check;
	x[0]=1;x[1]=42;
	cout<<"PLAYER 1";
	line(320,0,320,300);
	gotoxy(x[1],wherey());
	cout<<"PLAYER 2\n";
	for(int i=0;i>=0;i++){
	if(i%2==0)
	{
		gotoxy(x[i%2],wherey()+1);
	}
	else if(i%2!=0)
	{
		gotoxy(x[i%2],wherey()-2);
	}

	cout<<"Shall we roll the die?";
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
			exit(0);
	}
	}
}


void main()
{
	clrscr();
	int gmode=IBM8514HI,gdriver=IBM8514;
	initgraph(&gdriver,&gmode,"");
	if(graphresult()!=grOk)
	{
		cout<<"Error!";
		delay(1000);
		exit(0);
	}
	setbkcolor(25);
	randomize();
	gamedisp();
	exit(0);
}