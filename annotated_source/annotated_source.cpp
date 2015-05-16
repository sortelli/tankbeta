// ---------- Start of tankbeta.cpp ----------
/* ---------- Start of tankbeta.cpp ----------*/
#include <graphics.h>
#include <fstream.h>
#include <conio.h>
#include <dos.h>
#include <alloc.h>
#include "keyboard.h"
#include "tclass.h"
#include "tconst.h"
#include "bclass.h"
#include "tscreen.h"
#include <ctype.h>

const int true = 1;
const int false = 0;


void PlayTank();
void MoveTank(tankclass &tank,bulletclass &b, int upCode,
              int downCode, int leftCode, int rightCode, int fireCode);
void GameOptions(apstring &level,int &color1, int &color2);
int PickColor();



int main()
{
	int  gdriver=0, gmode;
	initgraph(&gdriver, &gmode, "");

   cleardevice();

   SetButtonKeysMode();
	PlayTank();
	SetNormalKeysMode();

	/*MakeLevel();*/
   closegraph();
   return 0;
}

void PlayTank()
{
	apstring lev;
   int cr1,cr2,winner;

   GameOptions(lev,cr1,cr2);	/*asks user for team colors and level*/

   int sc[XRES][YRES],flag=true;  /*sc array is for placing informtion on wall*/
	InitScr(sc);                    		/*and floor placement*/
   point t1,t2;                    /*t1 and t2 are used for getting starting*/
   LoadLevel(sc,lev,t1,t2);            /*points of tanks*/

   bulletclass b1,b2;
   tankclass tank1(t1.x,t1.y,cr1,1),tank2(t2.x,t2.y,cr2,2);

   DrawAllScreen(sc);

   b1.draw();
   b2.draw();

   tank1.draw();
   tank2.draw();

   while (!GetKeyState(KEY_ESC) && flag)
   {
      /*movetanks*/
      /*the key parameters is so the same function can be used to handle*/
      /*different players*/
   	MoveTank(tank1,b1,KEY_E,KEY_C,KEY_S,KEY_F,KEY_D);
   	MoveTank(tank2,b2,KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT,KEY_ENTER);

      /*draw*/
      b1.draw();
      b2.draw();

      tank1.draw();
      tank2.draw();

      /*spead delay*/
   	delay(7);

      /*check win*/
      if (tank1.timeshit()==GAMELNTH)
      {
      	flag=false;
         winner=2;
      }
      else if(tank2.timeshit()==GAMELNTH)
      {
      	flag=false;
         winner=1;
      }
   }
   /*deletes pointers to tank pics*/
   tank1.uninit();
   tank2.uninit();

   cleardevice();
   switch(winner)
   {
   	case 1:  cout<<"Player 1 Wins!"<<endl;
      			cout<<"Try Again Player 2";
               break;
      case 2:
      			cout<<"Player 2 is the Champ"<<endl;
      			cout<<"Try Again Player 1";
               break;
   }
   delay(5000);

}


void MoveTank(tankclass &tank,bulletclass &b, int upCode,
              int downCode, int leftCode, int rightCode, int fireCode)
{
   if (GetKeyState(upCode))
   	tank.movefoward();

   if (GetKeyState(downCode))
   	tank.moveback();

   if (GetKeyState(leftCode) || tank.turnedleftlast()==TRNSPD)
   	tank.turnleft();

   if (GetKeyState(rightCode)|| tank.turnedrightlast()==TRNSPD)
   	tank.turnright();

   if (GetKeyState(fireCode))
   {
      if (tank.angle()==N)
	   	b.shoot(tank.xpos(),tank.ypos()-(TLNGTH+2),tank.angle(),BRANGE);
      else if (tank.angle()==E)
         b.shoot(tank.xpos()+(TLNGTH+2),tank.ypos(),tank.angle(),BRANGE);
      else if (tank.angle()==S)
         b.shoot(tank.xpos(),tank.ypos()+(TLNGTH+2),tank.angle(),BRANGE);
      else
         b.shoot(tank.xpos()-(TLNGTH+2),tank.ypos(),tank.angle(),BRANGE);
   }

   if (b.lifeleft()>0)
   {
   	if (b.angle()==N) for (int x=0; x<BMOVE; x++) b.moveup();
      else if (b.angle()==E) for (int x=0; x<BMOVE; x++) b.moveright();
      else if (b.angle()==S) for (int x=0; x<BMOVE; x++) b.movedown();
      else  for (int x=0; x<BMOVE; x++) b.moveleft();
   }
}

int PickColor()
{
   apstring c;
   char choice;

   for (int x=1; x<8; x++)
   {
   	setcolor(x);
   	rectangle(310,(x-1)*40+20,410,(x-1)*40+40);

      c=x+48;
      outtextxy(415,(x-1)*40+30,"= ");
		outtextxy(425,(x-1)*40+30,c.c_str());

      setcolor(x+8);
      rectangle(510,(x-1)*40+20,610,(x-1)*40+40);

      if (x+56>'9')
      	c=x+63;
      else
      	c=x+56;

      outtextxy(615,(x-1)*40+30,"= ");
      outtextxy(625,(x-1)*40+30,c.c_str());

      setfillstyle(1,x);
      floodfill(340,(x-1)*40+30,x);

      setfillstyle(1,x+8);
      floodfill(540,(x-1)*40+30,x+8);
   }
   choice=toupper(getch());
	while(choice =='8' || choice <='0' ||
        (choice >'9' && choice <'A') || choice >'F')
   	choice=toupper(getch());

   setcolor(WHITE);

   if (choice >'9')
   	return choice-55;
   else
	   return choice-48;
}

void GameOptions(apstring &level,int &color1, int &color2)
{
  	SetNormalKeysMode();

   int lv;
   cout<<"Player 1, pick your color:"<<endl;
	color1=PickColor();
   cout<<"Player 2, pick your color:"<<endl;
   color2=PickColor();
   cleardevice();
	cout<<"What level would you like to play (1-5)"<<endl;
   cin>>lv;
   while (lv<=0 || lv>5)
   {
      cout<<"What level would you like to play (1-5)"<<endl;
   	cin>>lv;
   }
   level+="level";
	lv+=48;
   level+=lv;
   level+=".lv";
   cleardevice();

   SetButtonKeysMode();
}

// ---------- End of tankbeta.cpp ----------
/* ---------- End of tankbeta.cpp ----------*/
// ---------- Start of tclass.cpp ----------
/* ---------- Start of tclass.cpp ----------*/

#include "tclass.h"
#include <stdlib.h>
#include <graphics.h>

const int true = 1;
const int false = 0;

tankclass::tankclass()
:washit(false),myx(320),myy(240),px(0),py(0),ang(0),lastrt(0), lastlt(0),hitcount(0)
{
}

tankclass::tankclass(int xpos, int ypos, int color, int num)
:washit(false),myx(xpos),myy(ypos),px(0),py(0),ang(0),lastrt(0), lastlt(0),hitcount(0),tnum(num)
{
	init(color);
}
tankclass::tankclass(tankclass &tk)
{
	myx=tk.myx;
   myy=tk.myy;
   ang=tk.ang;
   lastrt=tk.lastrt;
   lastlt=tk.lastlt;
   px=tk.px;
   py=tk.py;
   washit=tk.washit;
   hitcount=tk.hitcount;
   tnum=tk.tnum;

   for (int x=0; x<4; x++)
   	dpic[x]=tk.dpic[x];
   epic[0]=tk.epic[0];
   epic[1]=tk.epic[1];
}

int tankclass::xpos()
{
	return myx;
}

int tankclass::ypos()
{
	return myy;
}
int tankclass::angle()
{
	return ang;
}
int tankclass::timeshit()
{
	return hitcount;
}
int tankclass::turnedleftlast()
{
	return lastlt;
}
int tankclass::turnedrightlast()
{
	return lastrt;
}

void tankclass::movedown()
{
   if (downside()==1)
   	myy++;
}

void tankclass::moveleft()
{
	if (leftside()==1)
   	myx--;
}

void tankclass::moveright()
{
	if (rightside()==1)
   	myx++;
}

void tankclass::moveup()
{
	if (upside()==1)
   	myy--;
}

void tankclass::turnright()
{
   if (lastrt > TRNSPD)  /*has a variable to slow down turning*/
   	lastrt=0;
	else if (lastrt == TRNSPD)
		if (ang==3)
			ang=0;
		else
			ang++;

   if (lastrt <= TRNSPD)
   	lastrt++;
}

void tankclass::turnleft()
{
   if (lastlt > TRNSPD)
   	lastlt=0;
	else if (lastlt == TRNSPD)
   	if (ang==0)
   		ang=3;
   	else
   		ang--;
	if (lastlt <= TRNSPD)
   	lastlt++;
}
void tankclass::movefoward()
{
	if (ang==0)
   	moveup();
   else if(ang==1)
   	moveright();
   else if (ang==2)
   	movedown();
   else
   	moveleft();
}

void tankclass::moveback()
{
	if (ang==0)
   	movedown();
   else if(ang==1)
   	moveleft();
   else if(ang==2)
   	moveup();
   else
   	moveright();
}

int tankclass::upside()
{
	int move=true;    /*function originally designed to check what if anything*/
   						/*a tank was moveing into and return values based on that.*/
                     /*Now they are only used to see if it hits a WALL and not a*/
                     /*bullet, but old code was left in, in case of*/
                     /*future revision.*/
   for (int x=myx-TLNGTH; x<=myx+TLNGTH; x++)
   	if (getpixel(x,myy-(TLNGTH+1))==BULLET)
      	move=2;
      else if (getpixel(x,myy-(TLNGTH+1))!=FLOOR)
      	move=false;

   return move;
}
int tankclass::rightside()
{
	int move=true;
   for (int y=myy-TLNGTH; y<=myy+TLNGTH; y++)
   	if (getpixel(myx+(TLNGTH+1),y)==BULLET)
      	move=2;
   	else if (getpixel(myx+(TLNGTH+1),y)!=FLOOR)
      	move=false;

   return move;
}

int tankclass::downside()
{
	int move=true;
	for (int x=myx-TLNGTH; x<=myx+TLNGTH; x++)
   	if (getpixel(x,myy+(TLNGTH+1))==BULLET)
      	move=2;
   	else if (getpixel(x,myy+(TLNGTH+1))!=FLOOR)
      	move=false;

   return move;
}

int tankclass::leftside()
{
	int move=true;
   for (int y=myy-TLNGTH; y<=myy+TLNGTH;y++)
   	if (getpixel(myx-(TLNGTH+1),y)==BULLET)
      	move=2;
    	else if (getpixel(myx-(TLNGTH+1),y)!=FLOOR)
      	move=false;

   return move;
}
void tankclass::erase()
{
	/*erases only outside edges of tank, as it only needs to move a pixel at a*/
   /*time.  New drawing will erase the rest.*/
	putimage(px-TLNGTH,py+TLNGTH,epic[0],COPY_PUT);
	putimage(px-TLNGTH,py-TLNGTH,epic[0],COPY_PUT);

	putimage(px-TLNGTH,py-TLNGTH,epic[1],COPY_PUT);
	putimage(px+TLNGTH,py-TLNGTH,epic[1],COPY_PUT);

}
void tankclass::draw()
{
	erase();
	putimage(myx-TLNGTH,myy-TLNGTH,dpic[ang],COPY_PUT);
	px=myx;
	py=myy;

   if (washit==false) /*stops draw function from checking hit if tank is already*/
   {                  /*being hit*/
   	if ((leftside()==2||upside()==2||downside()==2||rightside()==2))
   		hit();
   }
}
void tankclass::init(int color)
{
   int temp=getcolor();

   epic[0]=malloc(imagesize(10,50,10+TLNGTH*2,50));
   epic[1]=malloc(imagesize(50,10,50,10+TLNGTH*2));
   epic[2]=malloc(imagesize(0,0,2*TLNGTH,2*TLNGTH));
	setcolor(FLOOR);
	line(10,50,10+TLNGTH*2,50);
   getimage(10,50,10+TLNGTH*2,50,epic[0]);
	fbox(0,0,2*TLNGTH,2*TLNGTH,FLOOR);
   getimage(0,0,2*TLNGTH,2*TLNGTH,epic[2]);
   cleardevice();
   line(50,10,50,10+TLNGTH*2);
   getimage(50,10,50,10+TLNGTH*2,epic[1]);
	setcolor(temp);

   ifstream fin;
   int pix;
   fin.open("texture2.txt");

   for (int x=0; x<4; x++)
   {
      cleardevice();
   	dpic[x]=malloc(imagesize(0,0,2*TLNGTH,2*TLNGTH));
      for (int y=0; y<=2*TLNGTH; y++)
	   	for (int x=0; x<=2*TLNGTH; x++)
      	{
      		fin>>pix;
         	if (pix==0)
         		pix=FLOOR;
         	if (pix==6)
         		pix=color;
         	putpixel(x+1,y+1,pix);
   		}
   	getimage(1,1,21,21,dpic[x]);
   }

  	fin.close();
   cleardevice();
}
void tankclass::uninit()
{
	delete dpic[0];
	delete dpic[1];
	delete dpic[2];
	delete dpic[3];

	delete epic[0];
	delete epic[1];
}

void tankclass::hit()
{
	washit=true;
   for (int x=0; x<31; x++)
	{
   	if (ang==3)
      	ang=0;
      else
      	ang++;
      delay(10);
      draw();
   }
   washit=false;
   hitcount++;
   PrintScore();
   spawn();
}

void tankclass::PrintScore()
{
	char score[5];
	switch(tnum)
   {

   	case 1:
               setcolor(0);
					itoa(hitcount-1,score,10);
               outtextxy(615,15,score);
               setcolor(15);
					itoa(hitcount,score,10);
      			outtextxy(615,15,score);
      			break;
      case 2:
               setcolor(0);
					itoa(hitcount-1,score,10);
               outtextxy(15,15,score);
               setcolor(15);
					itoa(hitcount,score,10);
      			outtextxy(15,15,score);
      			break;
   }
}

void tankclass::spawn()
{


   int x, y;
   int redo=true;

	time_t sec;
   time(&sec);
   srand((unsigned int) sec);

	while(redo)
   {
      redo=false;
   	x=rand() % (XRES*10-TLNGTH)+TLNGTH;
   	y=rand() % (YRES*10-TLNGTH)+TLNGTH;

   	for (int i=x-TLNGTH-1; i<x+TLNGTH+1; i++)
      	for (int k=y-TLNGTH-1; k<y+TLNGTH+1; k++)
			{
         	if (getpixel(i,k)!=FLOOR)
            	redo=true;
         }
   }


   myx=x;
   myy=y;
   eraseall();
	draw();
}

void tankclass::eraseall()
{
	putimage(px-TLNGTH,py-TLNGTH,epic[2],COPY_PUT);
}



// ---------- End of tclass.cpp ----------
/* ---------- End of tclass.cpp ----------*/
// ---------- Start of bclass.cpp ----------
/* ---------- Start of bclass.cpp ----------*/
#include "bclass.h"

const int true = 1;
const int false = 0;



bulletclass::bulletclass()
:blife(-1),myx(0),myy(0),px(0),py(0),ang(0),lastshoot(time(NULL))
{
	init();
}

bulletclass::bulletclass(bulletclass &bc)
{
	blife=bc.blife;
   myx=bc.myx;
   myy=bc.myy;
   ang=bc.ang;
   px=bc.px;
   py=bc.py;
   lastshoot=bc.lastshoot;
	pic[0]=bc.pic[0];
   pic[1]=bc.pic[1];
}
int bulletclass::xpos()
{
	return myx;
}

int bulletclass::ypos()
{
	return myy;
}

int bulletclass::angle()
{
	return ang;
}

int bulletclass::lifeleft()
{
	return blife;
}

void bulletclass::moveup()
{
	if (blife!=0)
   {
   	int move=true;
      int cr;
		for (int x=myx-BLNGTH; x<=myx+BLNGTH; x++)
   	{
         cr=getpixel(x,myy-BLNGTH-1);
      	if (cr==WALL)
         {
         	blife=0;
      		move=false;
         }
   	}
   	if (move)
   		myy-=1;
   }
}

void bulletclass::movedown()
{
   if (blife !=0)
   {
   	int move=true;
      int cr;
		for (int x=myx-BLNGTH; x<=myx+BLNGTH; x++)
   	{
   		cr=getpixel(x,myy+BLNGTH+1);
      	if (cr==WALL)
         {
         	blife=0;
      		move=false;
         }
   	}
   	if (move)
   		myy+=1;
   }
}

void bulletclass::moveleft()
{
	if (blife !=0)
   {
   	int move=true;
      int cr;
		for (int y=myy-BLNGTH; y<=myy+BLNGTH; y++)
   	{
   		cr=getpixel(myx-BLNGTH-1,y);
      	if (cr==WALL)
         {
         	blife=0;
      		move=false;
         }
   	}
   	if (move)
   		myx-=1;
   }
}

void bulletclass::moveright()
{
	if (blife !=0)
   {
   	int move=true;
      int cr;
		for (int y=myy-BLNGTH; y<=myy+BLNGTH; y++)
   	{
   		cr=getpixel(myx+BLNGTH+1,y);
      	if (cr==WALL)
         {
         	blife=0;
      		move=false;
         }
   	}
   	if (move)
   		myx+=1;
   }
}

void bulletclass::erase()
{
   if (blife>=0)
   {
	   putimage(px-BLNGTH,py-BLNGTH,pic[0],COPY_PUT);
      blife--;
   }
}

void bulletclass::draw()
{
   erase();
   if (blife>0)
   {
		putimage(myx-BLNGTH,myy-BLNGTH,pic[1],COPY_PUT);
      px=myx;
      py=myy;
   }
}

void bulletclass::init()
{
	pic[0]=malloc(imagesize(0,0,BLNGTH*2,BLNGTH*2));
	pic[1]=malloc(imagesize(0,0,BLNGTH*2,BLNGTH*2));

	fbox(0,0,BLNGTH*2,BLNGTH*2,BULLET);
   getimage(0,0,BLNGTH*2,BLNGTH*2,pic[1]);

   cleardevice();

   fbox(0,0,BLNGTH*2,BLNGTH*2,FLOOR);
   getimage(0,0,BLNGTH*2,BLNGTH*2,pic[0]);

   cleardevice();
}

void bulletclass::uninit()
{
	delete pic[0];
   delete pic[1];
}

void bulletclass::shoot(int x, int y, int angle, int life)
{
   if (blife<=0 && difftime(time(NULL),lastshoot)>.5)
   {
		myx=x;
   	myy=y;
   	ang=angle;
   	blife=life;

   	for (int x=myx-BLNGTH; x<=myx+BLNGTH; x++)
      	for(int y=myy-BLNGTH; y<=myy+BLNGTH; y++)
      		if (getpixel(x,y)==0)
         		blife=-1;
   	lastshoot=time(NULL);
   }
}


// ---------- End of bclass.cpp ----------
/* ---------- End of bclass.cpp ----------*/
// ---------- Start of tscreen.cpp ----------
/* ---------- Start of tscreen.cpp ----------*/

#include "tscreen.h"

const int true = 1;
const int false = 0;

void InitScr(int sc[XRES][YRES])
{
	for(int y=0; y<YRES;y++)
	   for (int x=0; x<XRES;x++)
         sc[x][y]=false;
}


void LoadLevel(int sc[XRES][YRES],apstring name,point &t1, point &t2)
{
	char pix;

	ifstream fin;
   fin.open(name.c_str());

   for(int y=0; y<YRES;y++)
	   for (int x=0; x<XRES;x++)
      {
      	fin>>pix;

         if (pix=='0')
         	sc[x][y]=false;

         else if (pix=='W')
         	sc[x][y]=true;

         else if (pix=='A')
         {
         	t1.x=x*10;
            t1.y=y*10;
         }

         else if (pix=='B')
         {
         	t2.x=x*10;
            t2.y=y*10;
         }

      }

   fin.close();
}

void DrawAllScreen(int sc[XRES][YRES])
{
   int color;

   for(int y=0; y<YRES;y++)
	   for (int x=0; x<XRES;x++)
      {
      	if (sc[x][y]==true)
         	color=WALL;
         else
         	color=FLOOR;

         jbox(x,y,color);
      }
}

void DrawSec(int sc[XRES][YRES],int x,int y)
{
   int color;

   if (sc[x][y]==true)
   	color=WALL;
   else
   	color=FLOOR;

   jbox(x,y,color);
}
void MakeLevel()
{
	cleardevice();
	int temp[XRES][YRES],pen=false;
   InitScr(temp);
   DrawAllScreen(temp);
   int x=0, y=0;
   point t1,t2,o1,o2;
   t1.x=t2.x=-1;
   t1.y=t2.y=-1;

   jbox(x,y,5);

   char c=getch();

   while (c!=27 && c!='s')
   {
      if (t1.x==x && t1.y==y)
      {
         DrawSec(temp,o1.x,o1.y);
      	jbox(x,y,3);
      }
      else if (t2.x==x && t2.y==y)
      {
      	DrawSec(temp,o2.x,o2.y);
      	jbox(x,y,9);
      }
      else
	      DrawSec(temp,x,y);

      if (c=='a')
      {
      	o1.x=t1.x;
         o1.y=t1.y;
      	t1.x=x;
         t1.y=y;
   	}

      if (c=='b')
      {
      	o2.x=t2.x;
         o2.y=t2.y;
      	t2.x=x;
         t2.y=y;
      }

      if (c=='e')
      {
      	InitScr(temp);
         DrawAllScreen(temp);
      }

      if (c=='6')
      	if (x<XRES)
         	x++;

      if (c=='4')
      	if (x>0)
         	x--;

      if (c=='8')
      	if (y>0)
         	y--;

      if (c=='2')
      	if (y<YRES)
         	y++;

      if (c==' ')
      	if (pen==true)
         	pen=false;
         else
         	pen=true;

      if (pen==true)
      	if (temp[x][y]==false)
      		temp[x][y]=true;
         else
         	temp[x][y]=false;


      jbox(x,y,5);
      c=getch();
   }

   if (c=='s')
   {
      assert(t1.x!=-1&&t2.x!=-1);
   	cleardevice();
      apstring name;
   	cout<<"FileName: ";
   	cin>>name;
      ofstream fout;

      fout.open(name.c_str());

      for(int y=0; y<YRES;y++)
      {
	   	for (int x=0; x<XRES;x++)
      	{
            if (t1.x==x && t1.y==y)
            	fout<<"A";
            else if (t2.x==x && t2.y==y)
            	fout<<"B";
            else
            {
            	if (temp[x][y]==true)
            		fout<<"W";
            	else
            		fout<<"0";
            }
      	}
         fout<<endl;
      }
      fout.close();
      cout<<"done";
    }
}
void jbox(int x, int y, int color)
{
   int temp=getcolor();
   setcolor(color);
   setfillstyle(1,color);
	rectangle(x*10,y*10,x*10+9,y*10+9);
   floodfill(x*10+5,y*10+5,color);
   setcolor(temp);
}
void fbox (int x, int y, int x2, int y2, int color)
{
   int temp=getcolor();
   setcolor(color);
   setfillstyle(1,color);
	rectangle(x,y,x2,y2);
   floodfill((x+x2)/2,(y+y2)/2,color);
   setcolor(temp);
}

// ---------- End of tscreen.cpp ----------
/* ---------- End of tscreen.cpp ----------*/
