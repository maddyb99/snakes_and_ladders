#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<graphics.h>
#include<stdio.h>
#include<string.h>
class player
{
	int position, lastroll,lad;
	char plname[8],temp[3];
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
			lad=0;
			for(int i=0;i<3;i++)
			{
				if(position==ladder[i][0])
				{	lad=i+1;
					position=ladder[i][1];
					break;
				}
			}
			lastroll=roll;
			return(1);
		}
	}
	int getpos(){return(position);}
	void disp(int x,int y)
	{
		if (position!=0)
		{if(lad==0)
		{
			temp[2]=NULL;
			temp[0]=position/10+48;
			temp[1]=position%10+48;
			if(x!=640)
			{
				if(position<100)
				{
					outtextxy(x,y+12,"You are now at ");
					outtextxy(x+textwidth("You are now at "),y+12,temp);
				}
				else
					outtextxy(x,y+12,"You are now at 100!");
				outtextxy(x,y,"You got a ");
				temp[0]=lastroll+48;
				temp[1]=NULL;
				outtextxy(x+textwidth("You got a "),y,temp);
			}
			else
			{
				if(position<100)
				{
					outtextxy(x-textwidth("You are now at ")-16,y+12,"You are now at ");
					outtextxy(x-textwidth(temp),y+12,temp);
				}
				else
					outtextxy(x-textwidth("You are now at 100!"),y+12,"You are now at 100!");
				outtextxy(x-textwidth("You got a")-16,y,"You got a ");
				temp[0]=lastroll+48;
				temp[1]=NULL;
				outtextxy(x-textwidth(temp),y,temp);
			}
		}
		else
		{
			temp[2]=NULL;
			temp[0]=position/10+48;
			temp[1]=position%10+48;
			if(x!=640)
			{
				if(position<100)
				{
					outtextxy(x,y+12,"You are now at ");
					outtextxy(x+textwidth("You are now at "),y+12,temp);
				}
				else
					outtextxy(x,y+12,"You are now at 100!");
				outtextxy(x,y,"You got a ");
				temp[0]=lastroll+48;
				temp[1]=NULL;
				outtextxy(x+textwidth("You got a "),y,temp);
				outtextxy(x+textwidth("You got a   "),y,"and Ladder");
				temp[0]=lad+48;
				outtextxy(x+textwidth("You got a   and Laadder "),y,temp);
			}
			else
			{
				if(position<100)
				{
					outtextxy(x-textwidth("You are now at ")-16,y+12,"You are now at ");
					outtextxy(x-textwidth(temp),y+12,temp);
				}
				else
					outtextxy(x-textwidth("You are now at 100!")+12,y+24,"You are now at 100!");
				outtextxy(x-textwidth("You got a   and Ladder  "),y+12,"You got a ");
				temp[0]=lastroll+48;
				temp[1]=NULL;
				outtextxy(x-textwidth(temp)-textwidth(" and Ladder  "),y,temp);
				outtextxy(x-textwidth("and Ladder  "),y,"and Ladder");
				temp[0]=lad+48;
				outtextxy(x-textwidth(temp),y,temp);
			}

		}}
	}
	void indetails()
	{    gets(plname);
		if(strlen(plname)>8)
			exit(0);
	       if(!strcmpi(plname,"exit"))
	       {
			closegraph();
			exit(0);
	       }
	}
	char* getname()
	{	return(plname);
	}

};
player p[2];
int ladder[3][2];
void snakeladder()
{
	int i,x=2,y=7;
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
		}while(ladder[i][1]<=ladder[i][0]+(10-ladder[i][0]%10));
	}while(ladder[i][0]<=ladder[i-1][0]||ladder[i][1]==ladder[i-1][1]);
	}}

	for(i=0;i<3;i++,y++)
	{
		gotoxy(x,y);
		cout<<i+1<<") "<<ladder[i][0]<<"-"<<ladder[i][1];
	}
}
void gamedisp()
{
	clrscr();
	cleardevice();
	int x=160,y=40,xi=32,yi=32,*poly,i;
	char ch[3];
	line(0,20,640,20);
	line(130,20,130,390);
	line(510,20,510,390);
	line(130,390,510,390);
	line(0,340,130,340);
	line(510,340,640,340);
	line(320,390,320,480);
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
	setfillstyle(SOLID_FILL,6);
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
	setfillstyle(SOLID_FILL,11);
	setcolor(5);
	fillpoly(5,poly);
	delete poly;
	for(i=1;i<10;i++)
	{	line(x+(32*i),y,x+(32*i),y+(32*10));
		line(x,y+(32*i),x+(32*10),y+(32*i));
	}
	ch[2]=NULL;
	x=170;y=340;
	setcolor(getbkcolor());
	for(i=1;i<101;i++)
	{
		if(i==100)
		outtextxy(x-4,y,"100");
		else
		{	ch[0]=i/10+48;
			ch[1]=i%10+48;
			outtextxy(x,y,ch);
		}
		if(i%10==0)
		{       x+=xi;
			xi=xi*-1;
			y=y-yi;
		}
		x+=xi;
		delay(50);
	}
	setcolor(YELLOW);
       //	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);
	outtextxy(5,8,"Currently Winning: ");
	outtextxy(3,75,"Ladders are at:");
	outtextxy(3,175,"Snakes are at:");
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	outtextxy(5,350,p[0].getname());
	outtextxy(640-textwidth(p[1].getname()),350,p[1].getname());
	snakeladder();
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
}
void endgame(int mode,int pl)
{
	clrscr();
	cleardevice();
	switch(mode)
	{
		case 1: cout<<p[pl].getname()<<" ended the game.";
			break;
		case 0: cout<<"GAME ENDED\n"<<p[pl].getname()<<" WON.";
			break;
	}
	cout<<"\n\nPress any key to exit.";
}
void gameplay()
{
	char ans[2],ans2='y',*diecheck="Shall we roll the dice? ",*exitcheck="DO YOU REALLY WANT TO EXIT? ";
	ans[1]=NULL;
	int i,pn,y=400,*poly,x[2]={5,640};
	setfillstyle(SOLID_FILL,0);
	poly=new int[10];
	for(i=0;i>=0;i++)
	{
		pn=i%2;
		setcolor(getbkcolor());
		poly[0]=319;
		poly[1]=391;
		poly[2]=poly[0];
		poly[3]=480;
		poly[4]=x[pn];
		poly[5]=poly[3];
		poly[6]=poly[4];
		poly[7]=poly[1];
		poly[8]=poly[0];
		poly[9]=poly[1];
		fillpoly(5,poly);
		poly[0]=321;
		poly[1]=391;
		poly[2]=poly[0];
		poly[3]=480;
		poly[4]=x[pn];
		poly[5]=poly[3];
		poly[6]=poly[4];
		poly[7]=poly[1];
		poly[8]=poly[0];
		poly[9]=poly[1];
		fillpoly(5,poly);
		setcolor(15);
		p[!pn].disp(x[!pn],y);
		p[pn].disp(x[pn],y);
		if(pn)
		{
			outtextxy(x[pn]-textwidth(diecheck)-textwidth("Y"),y+24,diecheck);
			ans[0]=getch();
			outtextxy(x[pn]-textwidth(ans),y+24,ans);
		}
		else
		{	outtextxy(x[pn],y+24,diecheck);
			ans[0]=getch();
			outtextxy(x[pn]+1+textwidth(diecheck),y+24,ans);
		}
		if(ans[0]=='y'||ans[0]=='Y')
		{
			while(p[pn].update(random(7))==0) ;
		       //	p[pn].disp(x[pn],y);
		}
		else
		{
			if(pn)
				outtextxy(x[pn]-textwidth(exitcheck)-textwidth("Y"),y+36,exitcheck);
			else
				outtextxy(x[pn],y+36,exitcheck);
			ans2=getch();
			if(ans2=='y'||ans2=='Y')
			{	endgame(1,pn);
				break;
			}
			else
				i--;
		}
		setcolor(getbkcolor());
		poly[0]=5+textwidth("Currently winning: ");
		poly[1]=0;
		poly[2]=poly[0];
		poly[3]=19;
		poly[4]=poly[0]+textwidth("ABCDEFGH");
		poly[5]=poly[3];
		poly[6]=poly[4];
		poly[7]=poly[1];
		poly[8]=poly[0];
		poly[9]=poly[1];
		fillpoly(5,poly);
		setcolor(15);
		if(p[0].getpos()>p[1].getpos())
		{	if(p[0].getpos()>=100)
			{	endgame(0,0);
				break;
			}
			else
				outtextxy(5+textwidth("Currently Winning: "),8,p[0].getname());
		}
		else if (p[0].getpos()<p[1].getpos())
		{	if(p[1].getpos()>=100)
			{	endgame(0,1);
				break;
			}
			else
				outtextxy(5+textwidth("Currently Winning: "),8,p[1].getname());
		}
		else
			outtextxy(5+textwidth("Currently Winning: "),8,"Its a TIE!");
		delay(200);
	}
	delete poly;
	delete diecheck;
	delete exitcheck;
}


void main()
{
	clrscr();
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"");
	randomize();
	cout<<"Enter name of Player 1: ";
	p[0].indetails();
	cout<<"Enter Name of Player 2: ";
	p[1].indetails();
	//setbkcolor(15);
	gamedisp();
	gameplay();
	getch();
	closegraph();
	exit(0);
}