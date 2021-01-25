#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "SDL.h"

#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT  1080

int sgHasieratu();
void sgItxi();//Sin opciones
void arkatzKoloreaEzarri(int red, int green, int blue);
void puntuaMarraztu(int x, int y);
void zuzenaMarraztu(int x1, int y1, int x2, int y2);
void zirkuluaMarraztu(int x, int y, int r);
void pantailaGarbitu();
void pantailaBerriztu();
int irudiaMarraztu(SDL_Texture* texture, SDL_Rect * pSrc, SDL_Rect *pDest);
void LaukiaMarraztu(int x0, int y0, int x, int y, int r, int g, int b);

SDL_Renderer* getRenderer(void);


//menua egiteko:
void lurra(void);
void fondoMenu(void);
#endif