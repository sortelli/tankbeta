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

int getcolor(void) {
  // TODO: Implement
  return 0;
}

void setcolor(int color) {
  // TODO: Implement
}
