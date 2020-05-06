#include<iostream.h>
#include<fstream.h>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<process.h>
#include<dos.h>
#include<graphics.h>
int lad[3][2], snake[3][2];
int chcksnk(int);
int chcklad(int);
void gamedisp(int=0,int=0,int=0,int=1);
class PLAYER
{
	int start,sl,lastroll[3],pos,roll;
	void updatescreen(int=0);
	void last(int rol)
	{
		for(int i=2;i>0;i--)
		lastroll[i]=lastroll[i-1];
		lastroll[0]=rol;
	}
	int chcksix()
	{
	    int j=0;
	    while(lastroll[j]==6&&j<2)
		j++;
	    return j;
	}
public:
	int col,no;
	char name[10];
	PLAYER()
	{
		pos=0;
		start=0;
		no=-1;
		sl=0;
		name[0]=NULL;
		lastroll[0]=0;
		lastroll[1]=0;
		lastroll[2]=0;
		roll=lastroll[0];
	}
	void reset()
	{
		pos=0;
		start=0;
		sl=0;
		name[0]=NULL;
		lastroll[0]=0;
		lastroll[1]=0;
		lastroll[2]=0;
		no=-1;
		roll=lastroll[0];
	}
	int update(int rol)
	{
		int ret=0;
		sl=0;
		if(rol==0)
		{
		     updatescreen();
		     return 0;
		}
		roll=rol;
		if(start)
		{
		    if(roll==6)
		    {
			if(chcksix()==2)
			{
				last(0);
				ret=0;
			}
			else
			{
				ret=1;
				last(roll);
			}
			updatescreen(0);
			return ret;
		    }
		    else
		    {	if((pos+(roll+(chcksix()*6)))<=100)
				pos+=(roll+(chcksix()*6));
			//pos--;
		    }
		}
		else
		{
			if(roll==1||roll==6)
			{
				pos=pos+roll;
				start=1;
				if(roll==6)
				roll=-1;
			}
		}
		updatescreen();
		if(roll==-1)
			gamedisp(no,0,6,1);
		else
			gamedisp(no,pos-(roll+(chcksix()*6)),pos,1);
		last(roll);
		sl=chcklad(pos);
		if(sl>0)
		{
			pos=lad[sl-1][1];
			gamedisp(no,lad[sl-1][0],lad[sl-1][1],0);
		}
		else if(chcksnk(pos)<0)
		{
			sl=chcksnk(pos);
			sl*=-1     ;
			pos=snake[(sl)-1][1];
			gamedisp(no,snake[sl-1][0],snake[sl-1][1],0);
			sl*=-1;
		}
		updatescreen(sl);
		return 0;
	}
	int getpos()
	{return pos;}

};
void PLAYER::updatescreen(int sl)
{
	int x,y=400;
	char *temp;
	setcolor(getbkcolor());
	setfillstyle(SOLID_FILL,getbkcolor());
	temp=new char[4];
	if(pos<100)
	{
		temp[2]=NULL;
		temp[0]=pos/10+48;
		temp[1]=pos%10+48;
	}
	else
	{
		temp[3]=NULL;
		temp[0]='1';
		temp[1]='0';
		temp[2]='0';
	}
	if(no==1)
	{
		x=3;
		bar3d(x,y-5,x+textwidth("do you want to save before exit? cancel"),y+(10*textheight("A")),0,0);
		setcolor(WHITE);
		outtextxy(x,y+12,"You are now at ");
		outtextxy(x+textwidth("You are now at "),y+12,temp);
	}
	else
	{
		x=getmaxx();
		bar3d(x-textwidth("do you want to save before exit? cancel"),y-5,x,y+(6*textheight("A")),0,0);
		setcolor(WHITE);
		outtextxy(x-textwidth("You are now at ")-textwidth(temp),y+12,"You are now at ");
		outtextxy(x-textwidth(temp),y+12,temp);
	}
	if(roll==-1&&start==1)
		temp[0]='6';
	else
		temp[0]=lastroll[0]+48;
	temp[1]=NULL;
	if(sl==0)
	{
		if(no==1)
		{
			outtextxy(x,y,"You got a");
			outtextxy(x+textwidth("You got a "),y,temp);
		}
		else
		{
			outtextxy(x-textwidth("You got a ")-16,y,"You got a");
			outtextxy(x-textwidth(temp),y,temp);
		}
	}
	else if(sl>0)
	{
		if(no==1)
		{
			outtextxy(x,y,"You got a ");
			outtextxy(x+textwidth("You got a "),y,temp);
			outtextxy(x+textwidth("You got a   "),y,"and Ladder");
			temp[0]=sl+48;
			outtextxy(x+textwidth("You got a   and Ladder "),y,temp);
		}
		else
		{
			outtextxy(x-textwidth("You got a   and Ladder  "),y,"You got a ");
			outtextxy(x-textwidth(temp)-textwidth(" and Ladder  "),y,temp);
			outtextxy(x-textwidth("and Ladder  "),y,"and Ladder");
			temp[0]=sl+48;
			outtextxy(x-textwidth(temp),y,temp);
		}
	}
	else if(sl<0)
	{
		if(x!=640)
		{
			outtextxy(x,y,"You got a ");
			outtextxy(x+textwidth("You got a "),y,temp);
			outtextxy(x+textwidth("You got a   "),y,"and Snake");
			temp[0]=(sl*-1)+48;
			outtextxy(x+textwidth("You got a   and Snake "),y,temp);
		}
		else
		{
			outtextxy(x-textwidth("You got a   and Snake  "),y,"You got a ");
			outtextxy(x-textwidth(temp)-textwidth(" and Snake  "),y,temp);
			outtextxy(x-textwidth("and Snake  "),y,"and Snake");
			temp[0]=(sl*-1)+48;
			outtextxy(x-textwidth(temp),y,temp);
		}
	}
	delete temp;
}

struct GAME
{
    PLAYER p[2];
    int tomove,owr;
}G;

int circ(int,int,int=-1);
void button(int,int,int,int,int=0);
void rembutton(int,int,int,int,int=0);
void play();
void gameend(int);
int gameinput(int);
void credits();
void help();
int endg();
void save();
int load();
int check();

int main()
{
	int i,opt,x,*y,chck,gdriver=DETECT,gmode,end=0,mx,my,r,col;
	char ch;
	initgraph(&gdriver,&gmode,"");               //initialise graphics
	randomize();
    opt=0;
	lad[0][0]=18;
	lad[0][1]=67;
	lad[1][0]=35;
	lad[1][1]=69;
	lad[2][0]=65;
	lad[2][1]=99;
	snake[0][0]=58;
	snake[0][1]=29;
	snake[1][0]=73;
	snake[1][1]=12;
	snake[2][0]=97;
	snake[2][1]=2;
	if(check())
	{
		setbkcolor(7);
		circ(getmaxx()/2,y[opt]+(textheight("A")/2));
		play();
	}
	circ(getmaxx()/2,y[opt]+(textheight("A")/2));
	setbkcolor(7);
	col=-1;
    for(;;)
    {
		if(col!=-1)
		circ(getmaxx()/2,y[opt]+(textheight("A")/2),col);
		cleardevice();
		settextstyle(1,HORIZ_DIR,6);
		setcolor(15);
		setfillstyle(SOLID_FILL,1);
		button(-1,textheight("S")*0.7,getmaxx()+1,textheight("S")*2.3,8);
		setcolor(10);
		outtextxy((getmaxx()-textwidth("Snakes & Ladders"))/2,textheight("S")*0.8,"Snakes & Ladders");
		setcolor(2);
		settextstyle(0,HORIZ_DIR,2);
		x=(getmaxx()/2)-(textwidth("Load game")/2);
		y=new int[5];
		y[0]=(getmaxy()/2)-(textheight("P")*4);
		y[1]=(getmaxy()/2)-(textheight("P")*2);
		y[2]=(getmaxy()/2);
		y[3]=(getmaxy()/2)+(textheight("P")*2);
		y[4]=(getmaxy()/2)+(textheight("P")*4);
		outtextxy((getmaxx()-textwidth("New Game"))/2,y[0],"New Game");
		outtextxy((getmaxx()-textwidth("NeweeGame"))/2,y[1],"Load Game");
		outtextxy((getmaxx()-textwidth("NewGame"))/2,y[2],"Credits");
		outtextxy((getmaxx()-textwidth("Newe"))/2,y[3],"Help");
		outtextxy((getmaxx()-textwidth("Newe"))/2,y[4],"Exit");
		do{
			setfillstyle(EMPTY_FILL,8);
			button(x-4,y[opt]-(textheight("G")/2),x+textwidth("load game")+4,y[opt]+(textheight("A")*1.5),1);
			setcolor(14);
			switch(opt)
			{
				case 0:outtextxy((getmaxx()-textwidth("New Game"))/2,y[0],"New Game");
					break;
				case 1:outtextxy((getmaxx()-textwidth("LOAD GAME"))/2,y[1],"Load Game");
					break;
				case 2:outtextxy((getmaxx()-textwidth("credits"))/2,y[2],"Credits");
					break;
				case 3:outtextxy((getmaxx()-textwidth("Play"))/2,y[3],"Help");
					break;
				case 4:outtextxy((getmaxx()-textwidth("Play"))/2,y[4],"Exit");
					break;
			}
			end=getch(); //input from keyboard
			rembutton(x-4,y[opt]-(textheight("G")/2),x+textwidth("load game")+4,y[opt]+(textheight("A")*1.5),1);
			setcolor(2);
			switch(opt)
			{
				case 0:outtextxy((getmaxx()-textwidth("New Game"))/2,y[0],"New Game");
					break;
				case 1:outtextxy((getmaxx()-textwidth("LOAD GAME"))/2,y[1],"Load Game");
					break;
				case 2:outtextxy((getmaxx()-textwidth("credits"))/2,y[2],"Credits");
					break;
				case 3:outtextxy((getmaxx()-textwidth("Play"))/2,y[3],"Help");
					break;
				case 4:outtextxy((getmaxx()-textwidth("Play"))/2,y[4],"Exit");
					break;
			}
			switch(end)
			{
				case 'w':
				case 'W':
				case '8':opt--;
						if(opt<0)
							opt=4;
					break;
				case 's':
				case 'S':
				case '2':opt++;
						if(opt>4)
							opt=0;
						break;

			}
		}while(end!=13&&end!='5');
		col=circ(getmaxx()/2,y[opt]+(textheight("A")/2));
		delete y;
	    switch(opt)
	    {
			case 0:
				G.p[0].reset();
				G.p[1].reset();
				G.tomove=0;
				G.owr=-1;
				G.p[0].no=1;
				G.p[1].no=2;
				G.p[0].col=LIGHTBLUE;
				G.p[1].col=LIGHTRED;
				clrscr();
				cleardevice();
				chck=gameinput(0);
				if(chck==0)
					break;
				chck=gameinput(1);
				if(chck==0)
					break;
				delay(250);
				circ(getmaxx()/2,y[opt]+(textheight("A")/2),col);
				play();
				break;
			case 1:
				if(load())
				play();
				break;
			case 2: credits();
				break;
			case 3: help();
				break;
			case 4: return(0);
	    }
    }
}

int chcklad(int pos)
{
    int i,ret=0;
    for(i=0;i<3;i++)
	{
		if(lad[i][0]==pos)
		{
			ret=i+1;
			break;
		}
    }
    return ret;
}

int chcksnk(int pos)
{
    int i,ret=0;
    for(i=0;i<3;i++)
    {
		if(snake[i][0]==pos)
		{
			ret=-(i+1);
			break;
		}
    }
    return ret;
}

int circ(int x, int y,int col)
{
	int r,old=getcolor();
	if(col==-1)
	{       
		do{
			col=random(16);
		}while(col==getbkcolor()||col==G.p[0].col||col==G.p[1].col||col==WHITE||col==BLUE);
	}
	setfillstyle(SOLID_FILL,col);
	setcolor(col);
	for(r=1;r<560;r+=9)
	{
		if(kbhit()!=0)
		{
			getch();
			break;
		}
		fillellipse(x,y,r,r);
		delay(1);
	}
	setcolor(old);
	if(r>=560)
	delay(100);
	return (col);
}

void button(int x,int y,int x2,int y2,int dep)
{
	int col=getcolor();
	if(dep<0)
	{
		dep*=-1;
		setcolor(col);
		bar3d(x,y,x2,y2,0,0);
		setcolor(8);
		for(int i=1;i<=dep;i++)
		{
			bar3d(x+i,y+i,x2,y2,0,0);
		}
	}
	else if(dep>0)
	{
		setcolor(8);
		for(int i=dep;i>=1;i--)
			bar3d(x,y,x2+i,y2+i,0,0);
		setcolor(col);
		bar3d(x,y,x2,y2,0,0);
	}
	else
	{
		setcolor(col);
		bar(x,y,x2,y2);
	}
}

void rembutton(int x,int y,int x2,int y2,int dep)
{
	setfillstyle(EMPTY_FILL,0);
	setcolor(getbkcolor());
	bar3d(x,y,x2+dep,y2+dep,0,0);
}

int gameinput(int pnumber)
{
	int *poly,i=0;
	char ch;
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
		settextstyle(1,HORIZ_DIR,6);
	}
	else
	{
		poly[0]=(getmaxx()-textwidth("ABCDEFGHI"))/2;
		poly[1]=(getmaxy()/2)+(textheight("A"));
		poly[2]=(getmaxx()+textwidth("ABCDEFGHI"))/2;
		poly[3]=(getmaxy()/2)+(textheight("A")*2.4);

	}
	setfillstyle(SOLID_FILL,10);
	do
	{
		setcolor(14);
		bar3d(poly[0],poly[1],poly[2],poly[3],0,0);
		if(G.p[pnumber].name[0]==NULL)
		{
			setcolor(7);
			settextstyle(0,HORIZ_DIR,1);
			if(pnumber)
				outtextxy(poly[0]+(poly[2]-poly[0]-textwidth("Enter name of Player 1"))/2,poly[1]+((poly[3]-poly[1]-textheight("A"))/2),"Enter name of Player 2");
			else
				outtextxy(poly[0]+(poly[2]-poly[0]-textwidth("Enter name of Player 1"))/2,poly[1]+((poly[3]-poly[1]-textheight("A"))/2),"Enter name of Player 1");
		}
		else
		{
			setcolor(getbkcolor());
			settextstyle(0,HORIZ_DIR,3);
			outtextxy(poly[0]+(poly[2]-poly[0]-textwidth(G.p[pnumber].name))/2,(poly[1]+(textheight("A")*0.2)),G.p[pnumber].name);
		}
		ch=getch();
		switch(ch)
		{
			case 8: 
				if(i>0)
				{
					i-=2;
					G.p[pnumber].name[i+1]=NULL;
				}
				break;
			case 13:
				if(0<i&&i<8)
					G.p[pnumber].name[i]=NULL;
				else if(i==0)
				{
					if(pnumber)
						strcpy(G.p[pnumber].name,"Player 2");
					else
						strcpy(G.p[pnumber].name,"Player 1");
				}
				setcolor(14);
				setfillstyle(SOLID_FILL,2);
				bar3d(poly[0],poly[1],poly[2],poly[3],0,0);
				settextstyle(0,HORIZ_DIR,3);
				outtextxy(poly[0]+(poly[2]-poly[0]-textwidth(G.p[pnumber].name))/2,(poly[1]+(textheight("A")*0.2)),G.p[pnumber].name);
				break;
			default:if(i<8)
				{
					G.p[pnumber].name[i]=ch;
					G.p[pnumber].name[i+1]=NULL;
				}
				break;
		}
		if(i<8)
			i++;
	}while(ch!=13);
	delete poly;
	if(!strcmpi(G.p[pnumber].name,"end"))
		return(0);
	return(1);
}

void play()
{
    int flag=0,i,roll,j=0,ch,no,pn,x[2]={3,getmaxx()},y=424;
    fstream autosv("temp.dat",ios::binary|ios::out);
    autosv.write((char*)&j,sizeof(j));
    autosv.close();
    char ans,ans1;
    randomize();
    gamedisp();
    G.p[1].update(0);
    G.p[0].update(0);
    for(i=G.tomove;flag==0;i++)
    {
	pn=i%2;
		G.tomove=pn;
		setcolor(WHITE);
		if(pn==0)
			outtextxy(x[pn],y,"Do you want to roll die? ");
		else
			outtextxy(x[pn]-textwidth("do you want to roll die?vvvv"),y,"Do you want to roll die?");
		ans=getch();
		switch (ans)
		{
		    case 'y':
		    case 'Y':
				if (pn==1)
					outtextxy(x[pn]+textwidth("Do you want to roll die? "),y,"Yes");
				else
					outtextxy(x[pn]-textwidth("Doy"),y,"Yes");
				    do{
						roll=random(7);
				    }while(roll==0);
				if(G.p[pn].update(roll)==1)
					i--;
				if(G.p[pn].getpos()==100)
					flag=pn+1;
				autosv.open("temp.dat",ios::binary|ios::out);
				autosv.seekp(sizeof(j),ios::beg);
				autosv.write((char*)&G,sizeof(G));
				autosv.close();
				break;
		    case 'n':
		    case 'N':
				if (pn==0)
				{
					outtextxy(x[pn]+textwidth("Do you want to roll die? "),y,"No");
					setcolor(RED);
					outtextxy(x[pn],y+12,"Do you want to save before exit?");
				}
				else
				{
					outtextxy(x[pn]-textwidth("Doy"),y,"No");
					setcolor(RED);
					outtextxy(x[pn]-textwidth("Do you want to save before exit?vvvvvvv"),y+12,"Do you want to save before exit?");
				}
			    ans1=getch();
			    switch(ans1)
			    {
					case 'y':
					case 'Y':
						if(pn==0)
						outtextxy(x[pn]+textwidth("Do you want to save before exit?"),y+12,"Yes");
						else
						outtextxy(x[pn]-textwidth("Doyouw"),y+12,"Yes");
						save();
						flag=(-1*(pn+1));
						break;
					case 'n':
					case 'N':
						if(pn==0)
						outtextxy(x[pn]+textwidth("Do you want to save before exit?"),y+12,"No");
						else
						outtextxy(x[pn]-textwidth("Doyouw"),y+12,"No");
						flag=(-1*(pn+1));
						break;
					case 'C':
					case 'c':
						if(pn==0)
						outtextxy(x[pn]+textwidth("Do you want to save before exit?"),y+12,"Cancel");
						else
						outtextxy(x[pn]-textwidth("Doyouw"),y+12,"Cancel");
					default:G.p[pn].update(0);
						i--;
				}
			    setcolor(WHITE);
			    delay(750);
			    break;
		    default:G.p[pn].update(0);
			    i--;
		}
    }
    j=1;
    remove("temp.dat");
    autosv.open("temp.dat",ios::binary|ios::out);
    //autosv.seekp(0,ios::beg);
    autosv.write((char*)&j,sizeof(j));
    autosv.close();
    gameend(flag);
}

void gamedisp(int mode,int sval,int eval,int anm)
{
	int x=160,y=40,xi=32,yi=xi,sl,i;
	char ch[3];
	if(mode==0)
	{
		clrscr();
		cleardevice();
		settextstyle(0,HORIZ_DIR,1);
		setcolor(15);
		line(0,20,640,20);
		line(130,20,130,390);
		line(510,20,510,390);
		line(130,390,510,390);
		line(0,340,130,340);
		line(510,340,640,340);
		line(320,390,320,480);
		setcolor(GREEN);
		setfillstyle(SOLID_FILL,LIGHTBLUE);
		bar3d(x-10,y-10,x+330,y+330,0,0);
		ch[2]=NULL;
		x=170;y=340;
		settextstyle(0,HORIZ_DIR,1);
		for(i=1;i<101;i++)
		{
			setfillstyle(SOLID_FILL,15);
			setcolor(getbkcolor());
			bar3d(x-10,y+20,x+22,y-12,0,0);
			if(chcklad(i)>0)
				setcolor(2);
			else if(chcksnk(i)<0)
				setcolor(RED);
			else
				setcolor(0);
			if(i==100)
				outtextxy(x-4,y,"100");
			else
			{	
				ch[0]=i/10+48;
				ch[1]=i%10+48;
				outtextxy(x,y,ch);
			}
			if(i%10==0)
			{   
				x+=xi;
				xi=xi*-1;
				y=y-yi;
			}
			x+=xi;
			if(!kbhit())
				delay(50);
			else if(i==100)
				getch();
		}
		setcolor(YELLOW);
		outtextxy(2,textheight("C"),"Currently Winning: ");
		outtextxy(2,125,"Ladders are at:");
		outtextxy(517,125,"Snakes are at:");
		settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
		setcolor(G.p[0].col);
		outtextxy(2,350,G.p[0].name);
		setcolor(G.p[1].col);
		outtextxy(getmaxx()-textwidth(G.p[1].name),350,G.p[1].name);
		settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
		y=10;x=2;
		for(i=0;i<3;i++,y++)
		{
			gotoxy(x,y);
			cout<<i+1<<") "<<lad[i][0]<<"-"<<lad[i][1];
		}
		y=10;x=66;
		for(i=0;i<3;i++,y++)
		{
			gotoxy(x,y);
			cout<<i+1<<") "<<snake[i][0]<<"-"<<snake[i][1];
		}
	}
	else
	{
		if(anm==1)
		{
			x=170;y=340;
			ch[2]=NULL;
			setcolor(getbkcolor());
			settextstyle(0,HORIZ_DIR,1);
			for(i=1;i<101;i++)
			{
				if(i>=sval&&i<=eval)
				{
					setcolor(15);
					setfillstyle(SOLID_FILL,G.p[mode-1].col);
					bar(x-9,y+19,x+21,y-11);
					if(i==100)
						outtextxy(x-4,y,"100");
					else
					{
						ch[0]=i/10+48;
						ch[1]=i%10+48;
						outtextxy(x,y,ch);
					}
					if(!kbhit())
						delay(200);
					if(i!=eval)
					{
						setfillstyle(SOLID_FILL,15);
						if(chcklad(i)>0)
							setcolor(2);
						else if(chcksnk(i)<0)
							setcolor(RED);
						else if(G.p[!(mode-1)].getpos()==i)
							setfillstyle(SOLID_FILL,G.p[!(mode-1)].col);
						else
						       setcolor(getbkcolor());
						bar(x-9,y+19,x+21,y-11);
						if(i==100)
							outtextxy(x-4,y,"100");
						else
							outtextxy(x,y,ch);
					}
				}
				if(i%10==0)
				{
					x+=xi;
					xi=xi*-1;
					y=y-yi;
				}
				x+=xi;
			}
			if(kbhit())
				getch();
		}
		else
		{
			delay(250);
			x=170;y=340;
		    if((sval/10)%2==0)
				x+=(32*(sval%10-1));
		    else
				x+=(32*(10-(sval%10)));
		    y-=(32*(sval/10));
		    setfillstyle(SOLID_FILL,15);
		    if(chcklad(sval)>0)
				setcolor(2);
		    else if(chcksnk(sval)<0)
				setcolor(RED);
		    else if(G.p[!(mode-1)].getpos()==i)
				setfillstyle(SOLID_FILL,G.p[!(mode-1)].col);
		    else
				setcolor(getbkcolor());
		    bar(x-9,y+19,x+21,y-11);
		    if(sval==100)
				outtextxy(x-4,y,"100");
		    else
		    {
			ch[0]=sval/10+48;
				ch[1]=sval%10+48;
				outtextxy(x,y,ch);
		    }
			x=170;y=340;
		    if((eval/10)%2==0)
				x+=(32*(eval%10-1));
		    else
				x+=(32*(10-(eval%10)));
		    y-=(yi*(eval/10));
		    setcolor(15);
		    setfillstyle(SOLID_FILL,G.p[mode-1].col);
		    bar(x-9,y+19,x+21,y-11);
		    if(i==100)
				outtextxy(x-4,y,"100");
		    else
		    {
			ch[0]=eval/10+48;
				ch[1]=eval%10+48;
				outtextxy(x,y,ch);
		    }
		}
	}
}

void help()
{
	clrscr();
	cleardevice();
	settextstyle(0,HORIZ_DIR,3);
	setcolor(14);
	outtextxy((getmaxx()-textwidth("You need help?"))/2,(getmaxy()/2)-textheight("A")*2,"You need help?");
	outtextxy((getmaxx()-textwidth("Ask some kid for that "))/2,(getmaxy()/2),"Ask some kid for that!");
	getch();
}

void credits()
{
	clrscr();
	cleardevice();
	settextstyle(0,HORIZ_DIR,3);
	int x=(getmaxx()-textwidth("ishita jindal"))/2;
	setcolor(2);
	outtextxy(x,(getmaxy()/2)-(textheight("A")*1.5),"Made By:");
	setcolor(14);
	outtextxy(x,(getmaxy()/2)+textheight("A"),"Ishita Jindal");
	outtextxy(x,(getmaxy()/2),"Madhav Baveja");
	getch();
}

void save()
{
	fstream sv;
	if(G.owr==-1)
	{
		sv.open("games.dat",ios::binary|ios::app);
		sv.seekp(ios::end);
		G.owr=sv.tellp();
		sv.write((char*)&G,sizeof(G));
	}
	else
	{
		sv.open("games.dat",ios::binary|ios::out);
		sv.seekp(G.owr,ios::beg);
		sv.write((char*)&G,sizeof(G));
	}
	sv.close();
}

int load()
{
	fstream ld("games.dat",ios::binary|ios::in);
	int i=1,ans,y,x=20;
	char num[2];
	num[1]=NULL;
	GAME g;
	clrscr();
	cleardevice();
	settextstyle(1,HORIZ_DIR,6);
	setcolor(10);
	outtextxy((getmaxx()-textwidth("Choose Game:  "))/2,textheight("S")*0.8,"Choose Game:");
	y=textheight("S")*2.6;
	setcolor(YELLOW);
	settextstyle(0,HORIZ_DIR,2);
	while(!ld.eof())
	{
		num[0]=i+48;
		ld.read((char*)&g,sizeof(g));
		if(!ld.eof())
		{
			outtextxy(x,y+(i*textheight("A")),num);
			outtextxy(getmaxx()/2-textwidth("v ")-textwidth(g.p[0].name),y+(i*textheight("A")),g.p[0].name);
			outtextxy(getmaxx()/2-textwidth("v"),y+(i*textheight("A")),"vs");
			outtextxy(getmaxx()/2+textwidth("v "),y+(i*textheight("A")),g.p[1].name);
			cout<<endl;
			i++;
		}
	}
	ld.close();
	settextstyle(1,HORIZ_DIR,6);
	num[0]=NULL;
	ans=0;
	do{
		num[0]=getch();
		switch(num[0])
		{
			case 13:break;
			case 8: num[0]=NULL;
				ans=0;
				setfillstyle(SOLID_FILL,getbkcolor());
				setcolor(getbkcolor());
				bar((getmaxx()-textwidth("Choose Game:  "))/2+textwidth("Choose Game:"),textheight("S")*0.8,(getmaxx()-textwidth("Choose Game:  "))/2+textwidth("Choose Game:  "),textheight("S")*1.8);
				break;
			default:
				if(ans==0){
					setcolor(10);
					ans=(int)num[0]-48;
					outtextxy((getmaxx()-textwidth("Choose Game:  "))/2+textwidth("Choose Game: "),textheight("S")*0.8,num);
				}
		}
	}while(num[0]!=13);
	ld.open("games.dat",ios::binary|ios::in);
	ld.seekg((ans-1)*sizeof(G),ios::beg);
	ld.read((char*)&G,sizeof(G));
	ld.close();
	return (ans);
}

int check()
{
	fstream chck("temp.dat",ios::binary|ios::in);
	int i,opt=0,ret,x[2]={getmaxx()/2-textwidth("YESYE"),getmaxx()/2+textwidth("YE")};
	char end;
	chck.read((char*)&i,sizeof(i));
	if(i==0)
	{
		outtextxy((getmaxx()-textwidth("Unsaved Game Recovered!"))/2,getmaxy()/2-textheight("A"),"Unsaved Game Recovered!");
		outtextxy((getmaxx()-textwidth("Do you want to continue game?"))/2,getmaxy()/2,"Do you want to continue game?");
		outtextxy(x[0],getmaxy()/2+(textheight("A")*1.5),"Yes");
		setcolor(RED);
		outtextxy(x[1],getmaxy()/2+textheight("A")*1.5,"No");
		do{
			setfillstyle(SOLID_FILL,CYAN);
			setcolor(14);
			switch(opt)
			{
			case 0:setcolor(WHITE);
				button(x[opt]-4,getmaxy()/2+textheight("A")*1.4,x[opt]+4+((opt==0)?textwidth("YES"):textwidth("YE")),getmaxy()/2+(textheight("A")*2.6),0);
				outtextxy(x[0],getmaxy()/2+(textheight("A")*1.5),"Yes");
				break;
			case 1:setcolor(RED);
				button(x[opt]-4,getmaxy()/2+textheight("A")*1.4,x[opt]+4+((opt==0)?textwidth("YES"):textwidth("YE")),getmaxy()/2+(textheight("A")*2.6),0);
				outtextxy(x[1],getmaxy()/2+(textheight("A")*1.5),"No");
				break;
			}
			end=getch(); //input from keyboard
			rembutton(x[opt]-4,getmaxy()/2+textheight("A")*1.4,x[opt]+4+((opt==0)?textwidth("YES"):textwidth("YE")),getmaxy()/2+(textheight("A")*2.6),0);
			setcolor(2);
			switch(opt)
			{
			case 0:setcolor(WHITE);
				outtextxy(x[0],getmaxy()/2+(textheight("A")*1.5),"Yes");
				break;
			case 1:setcolor(RED);
				outtextxy(x[1],getmaxy()/2+(textheight("A")*1.5),"No");
				break;
			}
			switch(end)
			{
				case 'A':
				case 'a':
				case '4':(opt==0)?opt=1:opt=0;
					break;
				case 'd':
				case 'D':
				case '6':(opt==0)?opt=1:opt=0;
						break;
			}
		}while(end!=13&&end!='5');
		if(!opt)
		{
			chck.read((char*)&G,sizeof(G));
			ret=1;
		}
		else
			ret=0;
	}
	else
		ret=0;
	chck.close();
	remove("temp.dat");
	return (ret);
}

void gameend(int mode)
{
	if(mode>0)
	{
		settextstyle(1,HORIZ_DIR,6);
		setcolor(15);
		setfillstyle(SOLID_FILL,G.p[mode-1].col);
		button(-1,(getmaxy()-textheight("A"))/2,getmaxx()+1,(getmaxy()+(textheight("A")*1.8))/2,5);	setcolor(10);
		outtextxy((getmaxx()-textwidth("Winsss")-textwidth(G.p[mode-1].name))/2,(getmaxy()-textheight("A"))/2,G.p[mode-1].name);
		outtextxy((getmaxx()-textwidth("Winsss")-textwidth(G.p[mode-1].name))/2+textwidth(G.p[mode-1].name),(getmaxy()-textheight("A"))/2," wins!");
	}
	else
	{
		mode*=-1;
		settextstyle(1,HORIZ_DIR,5);
		setcolor(15);
		setfillstyle(SOLID_FILL,G.p[mode-1].col);
		button(-1,(getmaxy()-textheight("A"))/2,getmaxx()+1,(getmaxy()+(textheight("A")*1.8))/2,5);
		setcolor(15);
		outtextxy((getmaxx()-textwidth("  Ended the game")-textwidth(G.p[mode-1].name))/2,(getmaxy()-textheight("A"))/2,G.p[mode-1].name);
		outtextxy((getmaxx()-textwidth("  Ended the game")-textwidth(G.p[mode-1].name))/2+textwidth(G.p[mode-1].name),(getmaxy()-textheight("A"))/2," ended the game!");
	}
	getch();
}