#ifndef bclass_h

#include "tclass.h"

class bulletclass
{
	public:
   bulletclass();
   bulletclass(bulletclass &bc);

   int xpos();
   int ypos();
   int angle();
   int lifeleft();

   void moveup();
   void movedown();
   void moveleft();
   void moveright();

   void shoot(int x, int y,int angle, int life);

   void erase();
   void draw();
   void init();
   void uninit();

   private:
   int blife,myx,myy,px,py,ang;
   time_t lastshoot;
   void *pic[2];
};
#define bclass_h
#endif