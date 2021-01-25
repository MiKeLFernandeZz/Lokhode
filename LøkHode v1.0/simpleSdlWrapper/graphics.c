//Esto con un incude de include
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define GRAPHICS

#include "SDL_ttf.h"

#include "imagen.h"
#include "graphics.h"

SDL_Window* window = NULL;
SDL_Renderer* gRenderer;
int colorR, colorG, colorB;

extern struct Pertsonaia
{
    float x;
    float y;
    double angelua;
    int IkusBertikala;
    int health;

}PERTSONAIA;

extern struct Pertsonaia Pertsonaia;
extern struct MOBS mobs[64];

SDL_Renderer* getRenderer(void) { return gRenderer; }

int sgHasieratu()
{
  int ret = 0;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "ezin SDL hasieratu: %s\n", SDL_GetError());
    return -1;
  }
  atexit(SDL_Quit);
  window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
  
  if (window == NULL)
  {
    fprintf(stderr, "Ezin lehioa sortu: %s\n", SDL_GetError());
    return -1;
  }
  gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  TTF_Init();
  atexit(TTF_Quit);
  return ret;
}

int PantailaLuzeera(void) {
    int width, height;

    SDL_GetRendererOutputSize(gRenderer, &width, &height);

    return width;
}

int PantailaAltuera(void) {
    int width, height;

    SDL_GetRendererOutputSize(gRenderer, &width, &height);

    return height;
}

void sgItxi()
{
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void arkatzKoloreaEzarri(int red, int green, int blue)
{
  colorR = red;
  colorG = green;
  colorB = blue;
}


void zuzenaMarraztu(int x1, int y1, int x2, int y2)
{
  SDL_SetRenderDrawColor(gRenderer, colorR, colorG, colorB, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
}

void puntuaMarraztu(int x, int y)
{
  SDL_SetRenderDrawColor(gRenderer, colorR, colorG, colorB, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawPoint(gRenderer, x, y);
}

void zirkuluaMarraztu(int x, int y, int r)
{

  int i, h;

  SDL_SetRenderDrawColor(gRenderer, colorR, colorG, colorB, SDL_ALPHA_OPAQUE);
  for (i = x - r; i <= x + r; i++)
  {
    h = (int)llround(sqrt((double)(r*r - (i - x)*(i - x))));
    SDL_RenderDrawLine(gRenderer, i, y + h, i, y - h);
  }
}

int irudiaMarraztu(SDL_Texture* texture, SDL_Rect * pSrc, SDL_Rect *pDest)
{
  SDL_RenderCopy(gRenderer, texture, pSrc, pDest);
  return 0;
}

void pantailaGarbitu()
{
  SDL_SetRenderDrawColor(gRenderer, 135, 206, 235, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(gRenderer);
}

void lurra() {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = PantailaAltuera() / 2 + Pertsonaia.IkusBertikala;
    rect.w = PantailaLuzeera;
    rect.h = PantailaAltuera;

    SDL_SetRenderDrawColor(gRenderer, 55, 55, 55, 255);
    SDL_RenderDrawRect(gRenderer, &rect);
    SDL_RenderFillRect(gRenderer, &rect);

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    LaukiaMarraztu(0, 0, PantailaLuzeera(), PantailaAltuera() / 2 + Pertsonaia.IkusBertikala, 18, 16, 43);
}

void LaukiaMarraztu(int x0, int y0, int x, int y, int r, int g, int b) {
    SDL_Rect rect;
    rect.x = x0;
    rect.y = y0;
    rect.w = x;
    rect.h = y;

    SDL_SetRenderDrawColor(gRenderer, r, g, b, 255);
    SDL_RenderDrawRect(gRenderer, &rect);
    SDL_RenderFillRect(gRenderer, &rect);
}

void pantailaBerriztu()
{
  SDL_RenderPresent(gRenderer);
}

//menua egiteko

void fondoMenu() {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = PantailaLuzeera;
    rect.h = PantailaAltuera;

    SDL_SetRenderDrawColor(gRenderer, 10, 110, 10, 255);
    SDL_RenderDrawRect(gRenderer, &rect);
    SDL_RenderFillRect(gRenderer, &rect);

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
}