#ifndef tscreen.h

#include <graphics.h>
#include <fstream.h>
#include <conio.h>
#include <assert.h>
#include "tconst.h"
#include "apstring.h"
#include "keyboard.h"

void InitScr(int sc[XRES][YRES]);
void MakeLevel();
void LoadLevel(int sc[XRES][YRES],apstring name,point &t1, point &t2);
void DrawAllScreen(int sc[XRES][YRES]);
void DrawSec(int sc[XRES][YRES],int x,int y);
void jbox(int x, int y, int color);
void fbox (int x, int y, int x2, int y2, int color);

#define tscreen_h
#endif
