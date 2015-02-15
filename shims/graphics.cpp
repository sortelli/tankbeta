#include "graphics.h"
#include <SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

static int const SURFACE_WIDTH  = 640;
static int const SURFACE_HEIGHT = 480;
static int const SURFACE_BPP    = 32;

static SDL_Surface *surface = NULL;

void initgraph(int *gdriver, int *gmode, const char *something) {
  fprintf(stderr, "DEBUG: Called initgraph()\n");

  if (surface) {
    fprintf(stderr, "initgraph() can only be called once\n");
    exit(2);
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    exit(1);
  }

  if (SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL)) {
    fprintf(stderr, "SDL_EnableKeyRepeat failed: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  if ((surface = SDL_SetVideoMode(
    SURFACE_WIDTH,
    SURFACE_HEIGHT,
    SURFACE_BPP,
    SDL_HWSURFACE | SDL_DOUBLEBUF
  )) == NULL) {
    fprintf(stderr, "SDL_SetVideoMode failed: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
}

void closegraph(void) {
  // TODO: Implement
}

int getpixel(int x, int y) {
  // TODO: Implement
  return 0;
}

void putpixel(int x, int y, int color) {
  // TODO: Implement
}

int getcolor(void) {
  // TODO: Implement
  return 0;
}

void setcolor(int color) {
  // TODO: Implement
}

void getimage(int left, int top, int right, int bottom, void *pic) {
  // TODO: Implement
}

void putimage(int left, int top, void *pic, int mode) {
  // TODO: Implement
}

size_t imagesize(int left, int top, int right, int bottom) {
  // TODO: Implement
  return 0;
}

void line(int a_x, int a_y, int b_x, int b_y) {
  // TODO: Implement
}

void rectangle(int left, int top, int right, int bottom) {
  // TODO: Implement
}

void setfillstyle(int mode, int color) {
  // TODO: Implement
}

void floodfill(int x, int y, int color) {
  // TODO: Implement
}

int GetKeyState(int key) {
  // TODO: Implement
  return 0;
}

void SetNormalKeysMode(void) {
  // no implementation necessary
}

void SetButtonKeysMode(void) {
  // no implementation necessary
}

void delay(int milliseconds) {
  // TODO: Implement
}

void cleardevice(void) {
  // TODO: Implement
}

void itoa(int num, char *str, int base) {
  // Only writing impl for base 10 conversion
  if (base != 10) {
    fprintf(stderr, "iota() only supports base 10 conversion\n");
    exit(1);
  }

  // Stupid unsafe itoa has no buffer size parameter, so we have
  // to use sprintf instead of snprintf
  sprintf(str, "%d", num);
}
