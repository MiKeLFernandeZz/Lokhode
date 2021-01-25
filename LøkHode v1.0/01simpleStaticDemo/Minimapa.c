#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "graphics.h"
#include "ebentoak.h"
#include "soinua.h"
#include "text.h"
#include "imagen.h"
#include "SDL.h"

#include "OurTypes.h"
#include "Funtzioak.h"

extern struct angelua {
    float erdikoa;
    float hasierakoa;
    float bukaerakoa;
};

extern struct mugimendua {
    float AurrekoX;
    float AurrekoY;
    float OraingoX;
    float OraingoY;
    int AurrekoDirekzioa;
    int OraingoDirekzioa;
    int HasierakoPosizioa;
    int AmaierakoPosizioa;
    float Animazioa;
};

extern struct Mobs
{
    float x;
    float y;
    float d;
    struct angelua angelua;
    struct mugimendua mugimendua;
    int id;
    float abiadura;
    int width;
    int height;
    int health;
    int Pos;

}MOBS;

extern struct Pertsonaia
{
    float x;
    float y;
    double angelua;
    int IkusBertikala;
    float health;
    int arma;
    int Hilketak;

}PERTSONAIA;

extern struct Mobs mobs[20];
extern struct Pertsonaia Pertsonaia;

//--------------------------------GENERAR MAPA-------------------------------------------//

void MapaMarraztu(int mapaX, int mapaY, int mapaS, int Mapa[], int Ronda[], int idMapa) {
    int x, y, dx, dy, i;
    float x0, y0, PosizioTemp[4];

    x0 = PantailaLuzeera() - 125 - Pertsonaia.x / 2;//Maparen hasierako puntua x ardatzean
    y0 = 125 - Pertsonaia.y / 2;//Maparen hasierako puntua y ardatzean

    LaukiaMarraztu(PantailaLuzeera() - 225, 25, 200, 200, 0, 0, 0);//Minimapa atzealdean dagoen lauki beltza

    arkatzKoloreaEzarri(0, 0xFF, 0xFF);
    for (y = 0; y < mapaY; y++) {
        for (x = 0; x < mapaX; x++) {
            if (Mapa[y * mapaX + x] == 0) {
                if (x0 <= PantailaLuzeera() - 25 && x0 + mapaS > PantailaLuzeera() - 225 && y0 <= 225 && y0 + mapaS > 25) {

                    //Para delimitar en el eje X
                    if (x0 + mapaS > PantailaLuzeera() - 25)
                        PosizioTemp[1] = PantailaLuzeera() - 24 - x0;
                    else
                        PosizioTemp[1] = mapaS;
                    if (x0 < PantailaLuzeera() - 225) {
                        PosizioTemp[0] = PantailaLuzeera() - 225;
                        PosizioTemp[1] = mapaS - (PantailaLuzeera() - 225 - x0);
                    }
                    else
                        PosizioTemp[0] = x0;

                    //Para delimiter en el eje Y
                    if (y0 + mapaS > 225)
                        PosizioTemp[3] = 226 - y0;
                    else
                        PosizioTemp[3] = mapaS;
                    if (y0 < 25) {
                        PosizioTemp[2] = 25;
                        PosizioTemp[3] = mapaS - (25 - y0);
                    }
                    else
                        PosizioTemp[2] = y0;

                    LaukiaMarraztu(PosizioTemp[0], PosizioTemp[2], PosizioTemp[1], PosizioTemp[3], 255, 255, 255);//Matrizean 0 balioa daukaten gelaxka

                    //Lauki txuriak testura izateko horma batekin kontaktua badute
                    if (Mapa[(y * mapaX + x) - mapaX] != 0) {
                        IrudiarenDimentzioakDst(idMapa, PosizioTemp[0], PosizioTemp[2], PosizioTemp[1], PosizioTemp[3]);
                        if (y0 + mapaS >= 225)
                            IrudiarenDimentzioakSrc(idMapa, 0, 0, 25, PosizioTemp[3]);
                        if(y0 < 25)
                            IrudiarenDimentzioakSrc(idMapa, 0, 25 - PosizioTemp[3], 25, PosizioTemp[3]);
                        if (y0 + mapaS < 225 && y0 > 25)
                            IrudiarenDimentzioakSrc(idMapa, 0, 0, 25, 25);
                    }

                    if (Mapa[(y * mapaX + x) + mapaX] != 0) {
                        IrudiarenDimentzioakDst(idMapa, PosizioTemp[0], PosizioTemp[2], PosizioTemp[1], PosizioTemp[3]);
                        if (y0 + mapaS >= 225)
                            IrudiarenDimentzioakSrc(idMapa, 0, 25, 25, PosizioTemp[3]);
                        if (y0 < 25)
                            IrudiarenDimentzioakSrc(idMapa, 0, 50 - PosizioTemp[3], 25, PosizioTemp[3]);
                        if (y0 + mapaS < 225 && y0 > 25)
                            IrudiarenDimentzioakSrc(idMapa, 0,25, 25, 25);
                    }

                    if (Mapa[(y * mapaX + x) - 1] != 0) {
                        IrudiarenDimentzioakDst(idMapa, PosizioTemp[0], PosizioTemp[2], PosizioTemp[1], PosizioTemp[3]);
                        if (y0 + mapaS >= 225)
                            IrudiarenDimentzioakSrc(idMapa, 25, 0, PosizioTemp[1], 25);
                        if (y0 < 25)
                            IrudiarenDimentzioakSrc(idMapa, 50 - PosizioTemp[1], 0, PosizioTemp[1], 25);
                        if (y0 + mapaS < 225 && y0 > 25)
                            IrudiarenDimentzioakSrc(idMapa, 25, 0, 25, 25);
                    }

                    if (Mapa[(y * mapaX + x) + 1] != 0) {
                        IrudiarenDimentzioakDst(idMapa, PosizioTemp[0], PosizioTemp[2], PosizioTemp[1], PosizioTemp[3]);
                        if (y0 + mapaS >= 225)
                            IrudiarenDimentzioakSrc(idMapa, 25, 25, PosizioTemp[1], 25);
                        if (y0 < 25)
                            IrudiarenDimentzioakSrc(idMapa, 50 - PosizioTemp[1], 25, PosizioTemp[1], 25);
                        if (y0 + mapaS < 225 && y0 > 25)
                            IrudiarenDimentzioakSrc(idMapa, 25, 25, 25, 25);
                    }
                }
            }
            x0 = x0 + mapaS;
        }
        y0 = y0 + mapaS;
        x0 = PantailaLuzeera() - 125 - Pertsonaia.x / 2;
    }
    arkatzKoloreaEzarri(0, 0, 255);
    zirkuluaMarraztu(PantailaLuzeera() - 125, 125, 5);//Pertsonaia
    
    //Etsaiak irudikatu
    for (i = 0; i < Ronda[1]; i++) {
        dx = (Pertsonaia.x - mobs[i].x) / 2;
        dy = (Pertsonaia.y - mobs[i].y) / 2;
        if (125 - dx > 25 && 125 - dy > 25 && 125 - dx < 225 && 125 - dy < 225 && mobs[i].health > 0) {
            arkatzKoloreaEzarri(255, 0, 0);
            zirkuluaMarraztu(PantailaLuzeera() - 125 - dx, 125 - dy, 2.5);
        }
    }

    //Diktadorea irudikatu
    dx = (Pertsonaia.x - mobs[Ronda[0] + 9].x) / 2;
    dy = (Pertsonaia.y - mobs[Ronda[0] + 9].y) / 2;
    if (125 - dx > 25 && 125 - dy > 25 && 125 - dx < 225 && 125 - dy < 225 && mobs[Ronda[0] + 9].health > 0) {
        arkatzKoloreaEzarri(255, 0, 0);
        zirkuluaMarraztu(PantailaLuzeera() - 125 - dx, 125 - dy, 2.5);
    }
}

void Marraztu(int px, int py) {

    arkatzKoloreaEzarri(0, 0, 0xFF);
    zirkuluaMarraztu(px, py, 5);
}