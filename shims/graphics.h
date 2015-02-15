#ifndef _graphics__h__
#define _graphics__h__

/* Macros defined in original graphics.h */
#define BLACK    0
#define WHITE    0xFFFFFFFF
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

int getpixel(int x, int y);
void putpixel(int x, int y, int color);

int getcolor(void);
void setcolor(int color);

void getimage(int x, int y, int width, int height, void *pic);
void putimage(int x, int y, void *pic, int mode);
size_t imagesize(int x, int y, int width, int height);

#define KEY_C     0  /* TODO: Implement */
#define KEY_D     0  /* TODO: Implement */
#define KEY_DOWN  0  /* TODO: Implement */
#define KEY_E     0  /* TODO: Implement */
#define KEY_ENTER 0  /* TODO: Implement */
#define KEY_ESC   0  /* TODO: Implement */
#define KEY_F     0  /* TODO: Implement */
#define KEY_LEFT  0  /* TODO: Implement */
#define KEY_RIGHT 0  /* TODO: Implement */
#define KEY_S     0  /* TODO: Implement */
#define KEY_UP    0  /* TODO: Implement */

int GetKeyState(int key);
void SetNormalKeysMode(void);
void SetButtonKeysMode(void);

void itoa(int num, char *str, int base);

#endif
