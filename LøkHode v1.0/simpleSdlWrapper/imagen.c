#include <stdio.h>
#include "SDL.h"

#include "graphics.h"
#include "imagen.h"

int irudiarenPosizioaAurkitu(int id);

typedef struct Img
{
	int id;
  SDL_Surface* imagen;
  SDL_Texture* texture;
	SDL_Rect dest;
	SDL_Rect src;
}IMG;

IMG irudiak[MAX_IMG];
int irudiKop=0;
int id=0;

int irudiaKargatu(char *fileName)
{
	int colorkey;
  SDL_Surface* surface;
  SDL_Renderer* gRenderer = getRenderer();

	if (irudiKop< MAX_IMG)
	{
		surface = SDL_LoadBMP(fileName);
		if (surface == NULL ) //Surface no tiene valor
    {
			fprintf(stderr, "Couldn't load %s: %s\n", fileName, SDL_GetError());
			return -1;
		}
		else
		{
    	colorkey = SDL_MapRGB(surface->format, 255, 0, 255);
			SDL_SetColorKey(surface, SDL_TRUE, colorkey);//Cosas de RGB
      irudiak[irudiKop].texture=SDL_CreateTextureFromSurface(gRenderer, surface);
      irudiak[irudiKop].dest.x = irudiak[irudiKop].dest.y = 0;//Punto de origen
      irudiak[irudiKop].dest.w = surface->w;//Ancho de el BMP
      irudiak[irudiKop].dest.h = surface->h;//Alto del BMP
      SDL_FreeSurface(surface);//No c xd
			irudiak[irudiKop].id = id;
			irudiKop++;
			id++;
		}
	}
	else
	{
		printf("Has superado el maixmo de Imagens por aplicación.Para aumentar imagen.h\n");
		return -1;
	}
	
	return id-1;
}

void  irudiaMugitu( int numImg , int x, int y)
{

	int id=0;
	
	id =irudiarenPosizioaAurkitu(numImg);

	irudiak[id].dest.x = x;
    irudiak[id].dest.y = y;
}

void irudiakMarraztu(void)
{
  int i = 0;

  for (i = 0; i < irudiKop; i++)
  {
    irudiaMarraztu(irudiak[i].texture, &irudiak[i].src, &irudiak[i].dest);//La textua y Las dimensiones
  }
}

void irudiaKendu(int id)
{
	int i=0,pos=0;

	pos=irudiarenPosizioaAurkitu(id);
  SDL_DestroyTexture(irudiak[pos].texture);
	for ( i= pos ; i < irudiKop ; i++)
	{

		irudiak[i] = irudiak[i+1];
	}
	irudiKop--;
}

int irudiarenPosizioaAurkitu(int id)
{
  int i=0;

  for (i = 0; i < irudiKop; i++)
  {
    if (id == irudiak[i].id) return i;
  }
	return -1;
}

void IrudiarenDimentzioakDst(int id, int x0, int y0, int x, int y) {
	irudiak[id].dest.x = x0;
	irudiak[id].dest.y = y0;
	irudiak[id].dest.w = x;
	irudiak[id].dest.h = y;
	
}

void IrudiarenDimentzioakSrc(int id, int x0, int y0, int x, int y) {
	irudiak[id].src.x = x0;
	irudiak[id].src.y = y0;
	irudiak[id].src.w = x;
	irudiak[id].src.h = y;
	irudiaMarraztu(irudiak[id].texture, &irudiak[id].src, &irudiak[id].dest);
}