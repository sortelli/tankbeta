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

	//MakeLevel();
   closegraph();
   return 0;
}

void PlayTank()
{
	apstring lev;
   int cr1,cr2,winner;

   GameOptions(lev,cr1,cr2);	//asks user for team colors and level

   int sc[XRES][YRES],flag=true;  //sc array is for placing informtion on wall
	InitScr(sc);                    		//and floor placement
   point t1,t2;                    //t1 and t2 are used for getting starting
   LoadLevel(sc,lev,t1,t2);            //points of tanks

   bulletclass b1,b2;
   tankclass tank1(t1.x,t1.y,cr1,1),tank2(t2.x,t2.y,cr2,2);

   DrawAllScreen(sc);

   b1.draw();
   b2.draw();

   tank1.draw();
   tank2.draw();

   while (!GetKeyState(KEY_ESC) && flag)
   {
      //movetanks
      //the key parameters is so the same function can be used to handle
      //different players
   	MoveTank(tank1,b1,KEY_E,KEY_C,KEY_S,KEY_F,KEY_D);
   	MoveTank(tank2,b2,KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT,KEY_ENTER);

      //draw
      b1.draw();
      b2.draw();

      tank1.draw();
      tank2.draw();

      //spead delay
   	delay(7);

      //check win
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
   //deletes pointers to tank pics
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









