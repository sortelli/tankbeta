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
   if (lastrt > TRNSPD)  //has a variable to slow down turning
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
	int move=true;    //function originally designed to check what if anything
   						//a tank was moveing into and return values based on that.
                     //Now they are only used to see if it hits a WALL and not a
                     //bullet, but old code was left in, in case of
                     //future revision.
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
	//erases only outside edges of tank, as it only needs to move a pixel at a
   //time.  New drawing will erase the rest.
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

   if (washit==false) //stops draw function from checking hit if tank is already
   {                  //being hit
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



