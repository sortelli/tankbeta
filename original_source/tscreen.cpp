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
