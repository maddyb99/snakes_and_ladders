#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
class player
{
	int position, lastroll,lad;
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
			lastroll=roll;
			position+=lastroll;
			lad=checkladder(position);
			if(lad!=0)
			{
				position=ladder[lad-1][1];
			}

		return(1);
		}
	}
	int getpos(){return(position);}
	void disp(int x, int y)
	{
		if(lad==0)
		{	gotoxy(x+6,y);
			cout<<"You got a "<<lastroll<<".";
		}
		else
		{
			gotoxy(x,y);
			cout<<"You got a "<<lastroll<<" and ladder "<<lad;
		}
		gotoxy(x+3,y+1);
		cout<<"You are now at "<<position<<".";
	}

};
player p[2];
int ladder[3][2],snake[3][2];
int checkladder(int pos)
{
	int i,j=0;
	for(i=0;i<3;i++)
	{
		if(pos==ladder[i][0])
			j=i+1;
	}
	return(j);
}
int snakeladder(int mode)
{
	int i,y,x;
	if (mode==1)
	{
		for(i=0;i<3;i++){
		if(i==0){
		do{
			ladder[i][0]=random(80);
			ladder[i][1]=random(100);
		}while(ladder[i][0]<0||ladder[i][1]<=ladder[i][0]+(10-ladder[i][0]%10));
		}
		else{
		do{
			do{
			ladder[i][0]=random(80);
			ladder[i][1]=random(100);
			}while(ladder[i][0]<=ladder[i-1][0]||ladder[i][1]==ladder[i-1][1]);
		}while(ladder[i][1]<=ladder[i][0]+(10-ladder[i][0]%10));
		}}
	}
	else if(mode==2)
	{
		 do{
			snake[3][0]=random(100);
			snake[3][1]=random(80);
		}while(snake[3][1]==0||snake[3][1]>=snake[3][0]-(snake[3][0]%10));

	       /*	else{
		do{
			do{
			snake[i][0]=random(100);
			snake[i][1]=random(80);
			}while(snake[i][0]>=snake[i-1][0]||snake[i][1]==snake[i-1][1]);
		}while(snake[i][1]>=snake[i][0]+(snake[i][0]%10));
		}}*/
	}
	y=wherey();x=wherex();
	gotoxy(37,8);
	cout<<"Snakes:";
	for(i=0;i<3;i++)
	{
		gotoxy(37,wherey()+1);
		cout<<i+1<<")"<<snake[i][0]<<"-"<<snake[i][1];
	}
	gotoxy(37,wherey()+2);
	cout<<"Ladders:";
	for(i=0;i<3;i++)
	{
		gotoxy(37,wherey()+1);
		cout<<i+1<<")"<<ladder[i][0]<<"-"<<ladder[i][1];
	}
	gotoxy(x,y);
	return(0);
}

void gamedisp(int mode=0)
{
	clrscr();
	gotoxy(16,1);
	cout<<"PLAYER 1";
	gotoxy(57,1);
	cout<<"PLAYER 2";
	if (mode)
	{	snakeladder(1);
		snakeladder(2);
	}
	else
	snakeladder(0);
}
void endgame(int mode=0)
{
	clrscr();
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
	randomize();
	gamedisp(1);
	gameplay();
	getch();
	exit(0);
}