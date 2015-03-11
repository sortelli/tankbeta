#include "graphics.h"
#undef main
#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define error(fmt, ...) _error(__LINE__, fmt, __VA_ARGS__)
#define sdl_error(name, ...) _sdl_error(__LINE__, name)
#define ttf_error(name, ...) _ttf_error(__LINE__, name)

extern int orig_main();

extern "C" int main(int argc, char **argv) {
  orig_main();
  return 0;
}

static SDL_Color sdl_colors[] = {
  {0x00, 0x00, 0x00, 0x00}, // BLACK
  {0x00, 0x00, 0xFF, 0x00}, // BLUE
  {0x00, 0xFF, 0x00, 0x00}, // GREEN
  {0x00, 0xFF, 0xFF, 0x00}, // CYAN
  {0xFF, 0x00, 0x00, 0x00}, // RED
  {0xFF, 0x00, 0xFF, 0x00}, // MAGENTA
  {0xA5, 0x2A, 0x2A, 0x00}, // BROWN
  {0xD3, 0xD3, 0xD3, 0x00}, // LIGHTGRAY
  {0xA9, 0xA9, 0xA9, 0x00}, // DARKGRAY
  {0xAD, 0xD8, 0xE6, 0x00}, // LIGHTBLUE
  {0x90, 0xEE, 0x90, 0x00}, // LIGHTGREEN
  {0xE0, 0xFF, 0xFF, 0x00}, // LIGHTCYAN
  {0xF0, 0x80, 0x80, 0x00}, // LIGHTRED
  {0xDB, 0x70, 0x93, 0x00}, // LIGHTMAGENTA
  {0xFF, 0xFF, 0x00, 0x00}, // YELLOW
  {0xFF, 0xFF, 0xFF, 0x00}  // WHITE
};

static void _error(long  line, const char *fmt, ...);
static void _sdl_error(long  line, const char *name);
static void _ttf_error(long  line, const char *name);
static void check_surface(void);
static void check_bpp(void);
static void check_color(int color);
static void check_font(void);
static void render_surface(void);

static int const SURFACE_WIDTH  = 640;
static int const SURFACE_HEIGHT = 480;
static int const SURFACE_BPP    = 1;   //BytesPerPixel

static SDL_Surface *surface = NULL;
static uint32_t bgi_colors[16];
static int brush_color = BLACK;
static int fill_color  = BLACK;
static TTF_Font *font = NULL;

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

  for (int i = BLACK; i <= WHITE; ++i) {
    SDL_Color *c = &sdl_colors[i];
    bgi_colors[i] = SDL_MapRGB(surface->format, c->r, c->g, c->b);
  }

  if (TTF_Init() < 0) {
    ttf_error("TTF_Init");
  }

  if ((font = TTF_OpenFont("fonts/CourierCode-Bold.ttf", 13)) == NULL) {
    ttf_error("TTF_OpenFont");
  }
}

void closegraph(void) {
  if (font) {
    TTF_CloseFont(font);
    TTF_Quit();
    font = NULL;
  }

  if (surface) {
    SDL_Quit();
    surface = NULL;
  }
}

int getpixel(int x, int y) {
  uint8_t *pixel;
  int color, pixel_value;

  if (x < 0 || x >= SURFACE_WIDTH || y < 0 || y >= SURFACE_HEIGHT) {
    fprintf(stderr, "DEBUG: pixel out of bounds %d, %d\n", x, y);
    return BLACK;
  }

  check_surface();
  check_bpp();

  if (SDL_LockSurface(surface) < 0) {
    sdl_error("SDL_LockSurface");
  }

  pixel = ((uint8_t *) surface->pixels) + y * surface->pitch + x * SURFACE_BPP;

  SDL_UnlockSurface(surface);

  pixel_value = *pixel;

  for (color = BLACK; color <= WHITE; ++color) {
    if (pixel_value == bgi_colors[color])
      return color;
  }

  error("Unknown pixel value at (%d, %d): %d", x, y, pixel_value);

  return -1;
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

  *pixel = bgi_colors[color];

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

typedef struct {
  int width;
  int height;
  SDL_Surface *surface;
} image;

void getimage(int left, int top, int right, int bottom, void *pic) {
  SDL_Rect src, dst;
  image *img = (image *) pic;

  check_surface();

  img->width  = right  - left;
  img->height = bottom - top;

  img->width  = img->width  == 0 ? 1 : img->width;
  img->height = img->height == 0 ? 1 : img->height;

  if ((img->surface = SDL_DisplayFormat(surface)) == NULL) {
    sdl_error("SDL_DisplayFormat");
  }

  src.x = left;
  src.y = top;
  src.w = img->width;
  src.h = img->height;

  dst.x = 0;
  dst.y = 0;
  dst.w = src.w;
  dst.h = src.h;

  if (SDL_BlitSurface(surface, &src, img->surface, &dst)) {
    sdl_error("SDL_BlitSurface");
  }
}

void putimage(int left, int top, void *pic, int mode) {
  SDL_Rect src, dst;
  image *img = (image *) pic;

  check_surface();

  src.x = 0;
  src.y = 0;
  src.w = img->width;
  src.h = img->height;

  dst.x = left;
  dst.y = top;
  dst.w = img->width;
  dst.h = img->height;

  if (SDL_BlitSurface(img->surface, &src, surface, &dst)) {
    sdl_error("SDL_BlitSurface");
  }

  SDL_UpdateRect(surface, dst.x, dst.y, dst.w, dst.h);
}

size_t imagesize(int left, int top, int right, int bottom) {
  return sizeof(image);
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
  /* A more accurate implementation of rectangle would only
     draw an empty box.  Example:

      line(left,         top,    left + right, top);
      line(left + right, top,    left + right, bottom);
      line(left + right, bottom, left,         bottom);
      line(left,         bottom, left,         top);

    Instead we will draw a filled rectangle, since all calls to
    rectangle in the original source are followed by floodfill
  */

  SDL_Rect rect;

  rect.x = left;
  rect.y = top;
  rect.w = right  - left + 1;
  rect.h = bottom - top  + 1;

  if (SDL_FillRect(surface, &rect, bgi_colors[brush_color])) {
    sdl_error("SDL_FillRect");
  }

  render_surface();
}

void setfillstyle(int mode, int color) {
  if (mode != 1) { // SOLID_FILL
    error("Only supported fill mode is 1 (SOLID_FILL). Illegal value = %d", mode);
  }

  check_color(color);
  fill_color = color;
}

void floodfill(int x, int y, int color) {
  // In the original source, the only calls to floodfill are used to
  // fill in rectangles. Instead of implementing this I'll just use
  // an implementation of rectangle that fills at the same time.
}

void outtextxy(int x, int y, const char *text) {
  SDL_Surface *text_surface;
  SDL_Color color;
  SDL_Rect rect;

  check_surface();
  check_font();

  color = sdl_colors[brush_color];

  rect.x = x;
  rect.y = y;
  rect.w = 10;
  rect.h = 10;

  if ((text_surface = TTF_RenderText_Solid(font, text, color)) == NULL) {
    ttf_error("TTF_RenderText_Solid");
  }

  if (SDL_BlitSurface(text_surface, NULL, surface, &rect)) {
    sdl_error("SDL_BlitSurface");
  }

  SDL_FreeSurface(text_surface);

  render_surface();
}

int GetKeyState(int key) {
  static int keys[KEY_LENGTH];
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      closegraph();
      exit(0);
    }

    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE: keys[KEY_ESC]   = 1; break;
        case SDLK_e:      keys[KEY_E]     = 1; break;
        case SDLK_f:      keys[KEY_F]     = 1; break;
        case SDLK_c:      keys[KEY_C]     = 1; break;
        case SDLK_d:      keys[KEY_D]     = 1; break;
        case SDLK_s:      keys[KEY_S]     = 1; break;
        case SDLK_UP:     keys[KEY_UP]    = 1; break;
        case SDLK_RIGHT:  keys[KEY_RIGHT] = 1; break;
        case SDLK_DOWN:   keys[KEY_DOWN]  = 1; break;
        case SDLK_LEFT:   keys[KEY_LEFT]  = 1; break;
        case SDLK_RETURN: keys[KEY_ENTER] = 1; break;
      }
    }
  }

  if (key >= 0 && key < KEY_LENGTH) {
    int k = keys[key];
    keys[key] = 0;

    return k;
  }

  return 0;
}

void SetNormalKeysMode(void) {
  // no implementation necessary
}

void SetButtonKeysMode(void) {
  // no implementation necessary
}

void delay(int milliseconds) {
  SDL_Delay(milliseconds);
}

void cleardevice(void) {
  if (SDL_FillRect(surface, NULL, bgi_colors[BLACK])) {
    sdl_error("SDL_FillRect");
  }

  render_surface();
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

static void _ttf_error(long  line, const char *name) {
  _error(line, "TTF function %s failed. Reason: %s", name, TTF_GetError());
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

static void check_font(void) {
  if (font == NULL) {
    error("font is null", NULL);
  }
}

static void render_surface(void) {
  SDL_Flip(surface);
}
