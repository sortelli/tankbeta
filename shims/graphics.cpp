#include "graphics.h"
#include <SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define error(fmt, ...) _error(__LINE__, fmt, __VA_ARGS__)
#define sdl_error(name, ...) _sdl_error(__LINE__, name)

static void _error(long  line, const char *fmt, ...);
static void _sdl_error(long  line, const char *name);

static int const SURFACE_WIDTH  = 640;
static int const SURFACE_HEIGHT = 480;
static int const SURFACE_BPP    = 32;

static SDL_Surface *surface = NULL;

void initgraph(int *gdriver, int *gmode, const char *something) {
  if (surface) {
    error("initgraph() can only be called once", NULL);
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    sdl_error("SDL_Init");
  }

  if (SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL)) {
    sdl_error("SDL_EnableKeyRepeat");
  }

  if ((surface = SDL_SetVideoMode(
    SURFACE_WIDTH,
    SURFACE_HEIGHT,
    SURFACE_BPP,
    SDL_HWSURFACE | SDL_DOUBLEBUF
  )) == NULL) {
    sdl_error("SDL_SetVideoMode");
  }
}

void closegraph(void) {
  if (surface) {
    SDL_Quit();
    surface = NULL;
  }
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

void outtextxy(int x, int y, const char *text) {
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

static void _error(long  line, const char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  fprintf(stderr, "graphics.cpp error on line %ld: ", line);
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);

  closegraph();

  exit(1);
}

static void _sdl_error(long  line, const char *name) {
  _error(line, "SDL function %s failed. Reason: %s", name, SDL_GetError());
}
