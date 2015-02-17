#include "graphics.h"
#undef main
#include <SDL.h>
#include <math.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define error(fmt, ...) _error(__LINE__, fmt, __VA_ARGS__)
#define sdl_error(name, ...) _sdl_error(__LINE__, name)

extern int orig_main();

extern "C" int main(int argc, char **argv) {
  orig_main();
}

static void _error(long  line, const char *fmt, ...);
static void _sdl_error(long  line, const char *name);
static void check_surface(void);
static void check_bpp(void);
static void check_color(int color);
static void render_surface(void);

static int const SURFACE_WIDTH  = 640;
static int const SURFACE_HEIGHT = 480;
static int const SURFACE_BPP    = 4;   //BytesPerPixel

static SDL_Surface *surface = NULL;
static uint32_t bgi_colors[16];
static int brush_color = BLACK;

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
    SURFACE_BPP * 8, //Bits Per Pixel
    SDL_HWSURFACE | SDL_DOUBLEBUF
  )) == NULL) {
    sdl_error("SDL_SetVideoMode");
  }

  bgi_colors[BLACK]        = SDL_MapRGB(surface->format, 0x00, 0x00, 0x00);
  bgi_colors[BLUE]         = SDL_MapRGB(surface->format, 0x00, 0x00, 0xFF);
  bgi_colors[GREEN]        = SDL_MapRGB(surface->format, 0x00, 0xFF, 0x00);
  bgi_colors[CYAN]         = SDL_MapRGB(surface->format, 0x00, 0xFF, 0xFF);
  bgi_colors[RED]          = SDL_MapRGB(surface->format, 0xFF, 0x00, 0x00);
  bgi_colors[MAGENTA]      = SDL_MapRGB(surface->format, 0xFF, 0x00, 0xFF);
  bgi_colors[BROWN]        = SDL_MapRGB(surface->format, 0xA5, 0x2A, 0x2A);
  bgi_colors[LIGHTGRAY]    = SDL_MapRGB(surface->format, 0xD3, 0xD3, 0xD3);
  bgi_colors[DARKGRAY]     = SDL_MapRGB(surface->format, 0xA9, 0xA9, 0xA9);
  bgi_colors[LIGHTBLUE]    = SDL_MapRGB(surface->format, 0xAD, 0xD8, 0xE6);
  bgi_colors[LIGHTGREEN]   = SDL_MapRGB(surface->format, 0x90, 0xEE, 0x90);
  bgi_colors[LIGHTCYAN]    = SDL_MapRGB(surface->format, 0xE0, 0xFF, 0xFF);
  bgi_colors[LIGHTRED]     = SDL_MapRGB(surface->format, 0xF0, 0x80, 0x80);
  bgi_colors[LIGHTMAGENTA] = SDL_MapRGB(surface->format, 0xDB, 0x70, 0x93);
  bgi_colors[YELLOW]       = SDL_MapRGB(surface->format, 0xFF, 0xFF, 0x00);
  bgi_colors[WHITE]        = SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF);
}

void closegraph(void) {
  if (surface) {
    SDL_Quit();
    surface = NULL;
  }
}

int getpixel(int x, int y) {
  uint8_t *pixel;
  int color, pixel_value;

  check_surface();
  check_bpp();

  if (SDL_LockSurface(surface) < 0) {
    sdl_error("SDL_LockSurface");
  }

  pixel = ((uint8_t *) surface->pixels) + y * surface->pitch + x * SURFACE_BPP;

  SDL_UnlockSurface(surface);

  pixel_value = *(uint32_t *) pixel;

  for (color = BLACK; color <= WHITE; ++color) {
    if (pixel_value == bgi_colors[color])
      return color;
  }

  error("Unknown pixel value: %d", pixel_value);
}

static void putpixel_raw(int x, int y, int color) {
  uint8_t *pixel;

  check_surface();
  check_bpp();
  check_color(color);

  if (SDL_LockSurface(surface) < 0) {
    sdl_error("SDL_LockSurface");
  }

  pixel = ((uint8_t *) surface->pixels) + y * surface->pitch + x * SURFACE_BPP;

  *(Uint32 *) pixel = bgi_colors[color];

  SDL_UnlockSurface(surface);
}

void putpixel(int x, int y, int color) {
  putpixel_raw(x, y, color);
  render_surface();
}

int getcolor(void) {
  return brush_color;
}

void setcolor(int color) {
  check_color(color);
  brush_color = color;
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
  double temp_x  = b_x - a_x;
  double temp_y  = b_y - a_y;
  double length  = sqrt(temp_x * temp_x + temp_y * temp_y);
  double delta_x = temp_x / length;
  double delta_y = temp_y / length;
  int steps;

  temp_x = a_x;
  temp_y = a_y;

  for (steps = 0; steps < length; ++steps) {
    putpixel_raw(temp_x, temp_y, brush_color);

    temp_x += delta_x;
    temp_y += delta_y;
  }

  render_surface();
}

void rectangle(int left, int top, int right, int bottom) {
  line(left,         top,    left + right, top);
  line(left + right, top,    left + right, bottom);
  line(left + right, bottom, left,         bottom);
  line(left,         bottom, left,         top);
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

static void check_surface(void) {
  if (surface == NULL) {
    error("surface is null", NULL);
  }
}

static void check_bpp(void) {
  if (surface->format->BytesPerPixel != SURFACE_BPP) {
    error("Expecting %d bytes per pxiel. Got %d",
          SURFACE_BPP,
          surface->format->BytesPerPixel);
  }
}

static void check_color(int color) {
  if (color < BLACK || color > WHITE) {
    error("Illegal color value: %d", color);
  }
}

static void render_surface(void) {
  SDL_Flip(surface);
}
