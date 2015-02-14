#ifndef _graphics__h__
#define _graphics__h__

/* BLACK color, which I presume was defined in the original graphics.h */
#define BLACK 0

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

#endif
