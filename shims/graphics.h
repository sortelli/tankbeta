#ifndef _graphics__h__
#define _graphics__h__

#define main orig_main

/* Macros defined in original graphics.h */
#define BLACK         0
#define BLUE          1
#define GREEN         2
#define CYAN          3
#define RED           4
#define MAGENTA       5
#define BROWN         6
#define LIGHTGRAY     7
#define DARKGRAY      8
#define LIGHTBLUE     9
#define LIGHTGREEN   10
#define LIGHTCYAN    11
#define LIGHTRED     12
#define LIGHTMAGENTA 13
#define YELLOW       14
#define WHITE        15

#define COPY_PUT 0

/*
  All my original cpp files create constant ints named true and
  false. This worked with the Borland C++ compiler, but not gcc.
  I'll redefine them with a preprocessor macro to be a non-reserved
  name, but first I need to include all the system libraries because
  they may refer to the actual true/false variables.
*/
#include <alloc.h>
#include <assert.h>
#include <conio.h>
#include <ctype.h>
#include <dos.h>
#include <fstream.h>
#include <stdlib.h>
#include <time.h>

/* Now redefine true/false with non-reserved names */
#define true  local_true
#define false local_false


void initgraph(int *gdriver, int *gmode, const char *something);
void closegraph(void);

int getpixel(int x, int y);
void putpixel(int x, int y, int color);

int getcolor(void);
void setcolor(int color);

void getimage(int left, int top, int right, int bottom, void *pic);
void putimage(int left, int top, void *pic, int mode);
size_t imagesize(int left, int top, int right, int bottom);

void line(int a_x, int a_y, int b_x, int b_y);
void rectangle(int left, int top, int right, int bottom);

void setfillstyle(int mode, int color);
void floodfill(int x, int y, int color);

void outtextxy(int x, int y, const char *text);

#define KEY_ESC    0
#define KEY_E      1
#define KEY_F      2
#define KEY_C      3
#define KEY_D      4
#define KEY_S      5
#define KEY_UP     6
#define KEY_RIGHT  7
#define KEY_DOWN   8
#define KEY_LEFT   9
#define KEY_ENTER 10

#define KEY_LENGTH 11

int GetKeyState(int key);
void SetNormalKeysMode(void);
void SetButtonKeysMode(void);

void delay(int milliseconds);
void cleardevice(void);

void itoa(int num, char *str, int base);

#endif
