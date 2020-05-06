#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<graphics.h>
#include<stdio.h>
#include<string.h>
class player
{
	int position,lastroll,lad,start;

	public:
	char plname[9];
	void reset()
	{
		position=0;
		lastroll=0;
		lad=0;
		start=0;
		plname[0]=NULL;
	}
	int update(int roll)
	{
		if(roll==0)
			return(-1);
		else if((roll==1||roll==6)&&start==0)
			start=1;
		lastroll=roll;
		if(start==1)
		{
			position+=lastroll;
			lad=0;
			for(int i=0;i<3;i++)
			{
				if(position==ladder[i][0])
				{	lad=i+1;
					position=ladder[i][1];
					break;
				}
			}
			if(lastroll==6)
				return(0);
			else
				return(1);
		}
	}
	int getpos(){return(position);}
	void disp(int x,int y)
	{
		char *temp;
		temp=new char[3];
		if(lad==0)
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
					outtextxy(x-textwidth("You are now at 100!")+12,y+12,"You are now at 100!");
				outtextxy(x-textwidth("You got a   and Ladder  "),y,"You got a ");
				temp[0]=lastroll+48;
				temp[1]=NULL;
				outtextxy(x-textwidth(temp)-textwidth(" and Ladder  "),y,temp);
				outtextxy(x-textwidth("and Ladder  "),y,"and Ladder");
				temp[0]=lad+48;
				outtextxy(x-textwidth(temp),y,temp);
			}

		}
		delete temp;
	}

};
void gameend(int,int);
void gameplay();
void makeladder();
void gamedisp();
void help();
void gamestart();
int ladder[3][2];
player p[2];
int gameinput(int);

void main()
{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"");
	randomize();
	for(;;)
	{
		p[0].reset();
		p[1].reset();
		gamestart();
	}
}
void gamestart()
{
	clrscr();
	cleardevice();
	int *x,*y,*poly,option=0,end=0,check=0;
	char *arrow;
	arrow=new char[3];
	arrow[0]='-';
	arrow[1]='>';
	arrow[2]=NULL;
	setbkcolor(8);
	setcolor(14);
	settextstyle(4,HORIZ_DIR,6);
	x=new int[2];
	y=new int[3];
	x[0]=(getmaxx()/2)-(textwidth("Snakes & Ladders")/2);
	y[0]=textheight("S");
	outtextxy(x[0],y[0],"Snakes & Ladders");
	setcolor(3);
	settextstyle(0,HORIZ_DIR,2);
	x[0]=(getmaxx()/2)-(textwidth("Play")/2);
	x[1]=x[0]-textwidth(arrow);
	y[0]=(getmaxy()/2)-(textheight("P")*2);
	y[1]=(getmaxy()/2);
	y[2]=(getmaxy()/2)+(textheight("P")*2);
	outtextxy(x[0],y[0],"Play");
	outtextxy(x[0],y[1],"Help");
	outtextxy(x[0],y[2],"Exit");
	poly=new int[3];
	poly[0]=x[1];
	poly[2]=x[0]-1;
	//cout<<x<<" "<<y<<" "<<arrow<<" "<<poly;
	do
	{
		setcolor(3);
		outtextxy(x[1],y[option],arrow);
		end=getch();
		setcolor(getbkcolor());
		setfillstyle(SOLID_FILL,getbkcolor());
		poly[1]=y[option]+textheight(">");
		poly[3]=y[option];
		bar(poly[0],poly[1],poly[2],poly[3]);
		switch(end)
		{
			case 's':
			case 'S':
			case '2':option++;
				break;
			case 'w':
			case 'W':
			case '8':option--;
				break;
			case'd':
			case'D':
			case '6':
				if(!check)
				{
					arrow[0]='<';
					arrow[1]='-';
					arrow[3]=NULL;
					x[1]+=(textwidth("->Play")+1);
					x[0]+=textwidth("Play<-");
					poly[0]=x[1];
					poly[2]=x[0]+1;
					check++;
				}
				break;
			case'a':
			case'A':
			case '4':
				if(check)
				{
					arrow[0]='-';
					arrow[1]='>';
					x[1]-=textwidth("->Play");
					x[1]--;
					x[0]-=textwidth("Play<-");
					poly[0]=x[1];
					poly[2]=x[0]-1;
					check--;
				}
				break;
		}
		if(option>2)
			option=0;
		else if(option<0)
			option=2;
	}while(end!=13&&end!='5');
	delete poly;
	switch(option)
	{
		case 0: clrscr();
			cleardevice();
			if(!gameinput(0))
				break;
			if(!gameinput(1))
				break;
			gamedisp();
			break;
		case 1: help();
			break;
		case 2: closegraph();
			exit(0);
	}
	delete poly;
	delete arrow;
	delete x;
	delete y;
}

void help()
{
	clrscr();
	cleardevice();
	settextstyle(0,HORIZ_DIR,3);
	setcolor(14);
	outtextxy((getmaxx()-textwidth("You need help?"))/2,(getmaxy()/2)-textheight("A")*2,"You need help?");
	outtextxy((getmaxx()-textwidth("Ask some kid for that :P"))/2,(getmaxy()/2),"Ask some kid for that :P");
	getch();
}

int gameinput(int pnumber)
{
	int *poly,i=0;
	char ch;
	setcolor(YELLOW);
	poly=new int[3];
	setfillstyle(SOLID_FILL,2);
	settextstyle(0,HORIZ_DIR,3);
	if(!pnumber)
	{
		poly[0]=(getmaxx()-textwidth("ABCDEFGHI"))/2;
		poly[1]=(getmaxy()/2)+(textheight("A"));
		poly[2]=(getmaxx()+textwidth("ABCDEFGHI"))/2;
		poly[3]=(getmaxy()/2)+(textheight("A")*2.4);
		bar3d(poly[0],poly[1],poly[2],poly[3],0,0);
		poly[0]=(getmaxx()-textwidth("ABCDEFGHI"))/2;
		poly[1]=(getmaxy()/2)-(textheight("A")*2.4);
		poly[2]=(getmaxx()+textwidth("ABCDEFGHI"))/2;
		poly[3]=(getmaxy()/2)-(textheight("A"));
	}
	else
	{
		poly[0]=(getmaxx()-textwidth("ABCDEFGHI"))/2;
		poly[1]=(getmaxy()/2)+(textheight("A"));
		poly[2]=(getmaxx()+textwidth("ABCDEFGHI"))/2;
		poly[3]=(getmaxy()/2)+(textheight("A")*2.4);

	}
	do
	{
		setcolor(14);
		bar3d(poly[0],poly[1],poly[2],poly[3],0,0);
		if(p[pnumber].plname[0]==NULL)
		{
			setcolor(7);
			settextstyle(0,HORIZ_DIR,1);
			if(pnumber)
				outtextxy((getmaxx()-textwidth("Enter name of Player 1"))/2,poly[1]+(textheight("A")*1.5),"Enter name of Player 2");
			else
				outtextxy((getmaxx()-textwidth("Enter name of Player 1"))/2,poly[1]+(textheight("A")*1.5),"Enter name of Player 1");
		}
		else
		{
			setcolor(getbkcolor());
			settextstyle(0,HORIZ_DIR,3);
			outtextxy((getmaxx()-textwidth(p[pnumber].plname))/2,(poly[1]+(textheight("A")*0.2)),p[pnumber].plname);
		}
		ch=getch();
		switch(ch)
		{
			case 8: if(i>0)
				{
					i--;i--;
					p[pnumber].plname[i+1]=NULL;
				}
				break;
			case 13:if(i<8&&i>0)
				{
					p[pnumber].plname[i]=NULL;
					i=8;
				}
				break;
			default:if(i<8)
				{
					p[pnumber].plname[i]=ch;
					p[pnumber].plname[i+1]=NULL;
				}
				break;
		}
		if(i<8)
			i++;
	}while(ch!=13);
	delete poly;
	if(!strcmpi(p[pnumber].plname,"end"))
	{
		return(0);
	}
	       return(1);

}

void gamedisp()
{
	clrscr();
	cleardevice();
	int x=160,y=40,xi=32,yi=xi,*poly,i;
	char ch[3];
	setcolor(15);
	line(0,20,640,20);
	line(130,20,130,390);
	line(510,20,510,390);
	line(130,390,510,390);
	line(0,340,130,340);
	line(510,340,640,340);
	line(320,390,320,480);
	poly=new int[3];
	poly[0]=x-10;
	poly[1]=y-10;
	poly[2]=x+330;
	poly[3]=y+330;
	setcolor(2);
	setfillstyle(SOLID_FILL,10);
	bar3d(poly[0],poly[1],poly[2],poly[3],0,0);
	poly[0]=x;
	poly[1]=y;
	poly[2]=x+320;
	poly[3]=y+320;
	setfillstyle(SOLID_FILL,11);
	//setcolor(getbkcolor());
	bar3d(poly[0],poly[1],poly[2],poly[3],0,0);
	delete poly;
	for(i=1;i<10;i++)
	{	line(x+(32*i),y,x+(32*i),y+(32*10));
		line(x,y+(32*i),x+(32*10),y+(32*i));
	}
	ch[2]=NULL;
	x=170;y=340;
	setcolor(getbkcolor());
	settextstyle(0,HORIZ_DIR,1);
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
	outtextxy(2,textheight("C"),"Currently Winning: ");
	outtextxy(2,75,"Ladders are at:");
	outtextxy(2,175,"Snakes are at:");
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	outtextxy(2,350,p[0].plname);
	outtextxy(getmaxx()-textwidth(p[1].plname),350,p[1].plname);
	makeladder();
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	gameplay();
}

void makeladder()
{
	int i,y=7,x=2;
	for(i=0;i<3;i++)
	{
		if(i==0)
		{
			do{
				ladder[i][0]=random(60);
				ladder[i][1]=random(96);
			}while(ladder[i][0]<5||ladder[i][1]<=ladder[i][0]+(10-ladder[i][0]%10));
		}
		else
		{
			do{
			ladder[i][0]=random(60);
			ladder[i][1]=random(96);
			}while(ladder[i][1]<=ladder[i][0]+(10-ladder[i][0]%10)||ladder[i][0]<ladder[i-1][0]||ladder[i][1]==ladder[i-1][1]);
		}
	}
	for(i=0;i<3;i++,y++)
	{
		gotoxy(x,y);
		cout<<i+1<<") "<<ladder[i][0]<<"-"<<ladder[i][1];
	}
}

void gameplay()
{
	char ans[2],ans2='y',*diecheck="Shall we roll the dice? ",*exitcheck="DO YOU REALLY WANT TO EXIT? ";
	ans[1]=NULL;
	int i,pn,y=400,*poly,x[2]={3,640},no=1;
	setfillstyle(SOLID_FILL,0);
	poly=new int[3];
	for(i=0;i>=0;i++)
	{
		pn=i%2;
		setcolor(getbkcolor());
		if(no)
		{
			if(!pn)
			{
				poly[0]=321;
				poly[4]=x[!pn];
			}
			else
			{
				poly[0]=319;
				poly[4]=x[!pn];
			}
			poly[1]=391;
			poly[2]=poly[0];
			poly[3]=480;
			poly[5]=poly[3];
			poly[6]=poly[4];
			poly[7]=poly[1];
			poly[8]=poly[0];
			poly[9]=poly[1];
			fillpoly(5,poly);
		}
		else
		{
			no=1;
			if(pn)
			{
				poly[0]=321;
				poly[4]=x[pn];
			}
			else
			{
				poly[0]=319;
				poly[4]=x[pn];
			}
			poly[1]=391;
			poly[2]=poly[0];
			poly[3]=480;
			poly[5]=poly[3];
			poly[6]=poly[4];
			poly[7]=poly[1];
			poly[8]=poly[0];
			poly[9]=poly[1];
			fillpoly(5,poly);
		}
		setcolor(15);
		p[!pn].disp(x[!pn],y);
		p[pn].disp(x[pn],y);
		setcolor(getbkcolor());
		poly[0]=2+textwidth("Currently winning: ");
		poly[1]=0;
		poly[2]=poly[0];
		poly[3]=19;
		poly[4]=poly[0]+textwidth("ABCDEFGHIJ");
		poly[5]=poly[3];
		poly[6]=poly[4];
		poly[7]=poly[1];
		poly[8]=poly[0];
		poly[9]=poly[1];
		fillpoly(5,poly);
		setcolor(15);
		if(p[0].getpos()>p[1].getpos())
		{
			outtextxy(2+textwidth("Currently Winning: "),8,p[0].plname);
			if(p[0].getpos()>=100)
			{
				delay(1000);
				gameend(0,0);
				break;
			}
		}
		else if (p[0].getpos()<p[1].getpos())
		{
			outtextxy(5+textwidth("Currently Winning: "),8,p[1].plname);
			if(p[1].getpos()>=100)
			{
				delay(1000);
				gameend(0,1);
				break;
			}
		}
		else if(i!=0)
			outtextxy(5+textwidth("Currently Winning: "),8,"Its a TIE!");
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
			do
			{
				no=p[pn].update(random(7));
				if(no==0)
				{
					i--;
				}
			}while(no==-1);
		}
		else
		{
			if(pn)
				outtextxy(x[pn]-textwidth(exitcheck)-textwidth("Y"),y+36,exitcheck);
			else
				outtextxy(x[pn],y+36,exitcheck);
			ans2=getch();
			if(ans2=='y'||ans2=='Y')
			{	gameend(1,pn);
				break;
			}
			else
			{
				i--;
				no--;
			}
		}
		delay(200);
	}
	delete poly;
	delete diecheck;
	delete exitcheck;
}

void gameend(int mode,int pl)
{
	clrscr();
	cleardevice();
	switch(mode)
	{
		case 1: cout<<"'"<<p[pl].plname<<"' ended the game.";
			break;
		case 0: cout<<"GAME ENDED\n'"<<p[pl].plname<<"' WON.";
			break;
	}
	cout<<"\n\nPress any key to continue...";
	getch();
}