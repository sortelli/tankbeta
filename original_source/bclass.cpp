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




