#ifndef tclass_h

#include <graphics.h>
#include <time.h>
#include <dos.h>
#include <alloc.h>
#include <fstream.h>
#include <stdlib.h>
#include "tconst.h"
#include "tscreen.h"

void fbox(int upleftx, int uplefty, int brightx, int brighty, int color);

class tankclass
{
	public:
   tankclass();
   tankclass(int xpos, int ypos, int color,int num);
   tankclass(tankclass &tk);

   int xpos();
   int ypos();
   int angle();
   int turnedrightlast();
   int turnedleftlast();
   int timeshit();


   int leftside();
   int upside();
   int downside();
   int rightside();

   void movedown();
   void moveleft();
   void moveright();
   void moveup();

   void turnright();
   void turnleft();
   void movefoward();
   void moveback();

   void init(int color);
   void uninit();
   void checkhit();
   void draw();
   void erase();
   void PrintScore();

   private:
   int myx, myy, ang, px, py, lastrt, lastlt, hitcount, tnum;
   int washit;
	void *dpic[4];
   void *epic[3];

   void spawn();
   void hit();
   void eraseall();

};

#define tclass_h
#endif
