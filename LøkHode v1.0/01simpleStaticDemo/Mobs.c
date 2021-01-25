#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

void Mobs(int Mapa[], int mapaX, int mapaY, int mapaS, int Ronda[]) {
    int i, MobKopurua = Ronda[1];

    if (Ronda[2]) {//Ronda aldatzean Posizioa aleatoria emateko etsailei
        for (i = 0; i < MobKopurua; i++) {
            PosizioAleatorioa(Mapa, mapaX, mapaY, mapaS, i);
        }
        PosizioAleatorioa(Mapa, mapaX, mapaY, mapaS, Ronda[0] + 9);
        Ronda[2] = 0;
    }

    for (i = 0; i < MobKopurua; i++) {
        mobs[i].Pos = 900;//Pantailan ez agertzeko
        if (mobs[i].health > 0)//Bizirik badago marraztu
            MobMarraztu(Mapa, mapaX, mapaY, mapaS, i, Ronda);
    }

    mobs[Ronda[0] + 9].Pos = 900;//Pantailan ez agertzeko

    if (mobs[Ronda[0] + 9].health > 0)//Bizirik badago marraztu
        MobMarraztu(Mapa, mapaX, mapaY, mapaS, Ronda[0] + 9, Ronda);
}

void PosizioAleatorioa(int Mapa[], int mapaX, int mapaY, int mapaS, int Moba) {
    int x, y, d, dx, dy, Pos;

    do {
        x = 50 + rand() % (1001 - 50);
        y = 50 + rand() % (701 - 50);
        dx = x - Pertsonaia.x;
        dy = y - Pertsonaia.y;
        d = sqrt(pow(dx, 2) + pow(dy, 2));
        Pos = PosizioZehastu(x, y, mapaX, mapaY, mapaS, Mapa);
    } while (Mapa[Pos] == 1 || d < 50);
    mobs[Moba].x = x;
    mobs[Moba].y = y;
}

void MobMarraztu(int Mapa[], int mapaX, int mapaY, int mapaS, int Moba, int Ronda[]) {
    int HasieraPos, AmaieraPos, Mugimendua[512], dx, dy, d, tmp;

    HasieraPos = PosizioZehastu(mobs[Moba].x, mobs[Moba].y, mapaX, mapaY, mapaS, Mapa);
    AmaieraPos = PosizioZehastu(Pertsonaia.x, Pertsonaia.y, mapaX, mapaY, mapaS, Mapa);

    dx = mobs[Moba].x - Pertsonaia.x;
    dy = mobs[Moba].y - Pertsonaia.y;

    d = sqrt(pow(dx, 2) + pow(dy, 2));

    if (d > 25) {//Gerturatu dezake
        if (HasieraPos != mobs[Moba].mugimendua.HasierakoPosizioa || AmaieraPos != mobs[Moba].mugimendua.AmaierakoPosizioa) {//Matrizearen gelaxka berean daude

            mobs[Moba].mugimendua.HasierakoPosizioa = HasieraPos;//Pertsonaiaren Posizioa
            mobs[Moba].mugimendua.AmaierakoPosizioa = AmaieraPos;//Etsailaren Posizioa

            tmp = mobs[Moba].mugimendua.OraingoDirekzioa;
            mobs[Moba].mugimendua.OraingoDirekzioa = PathFinding(Mapa, mapaX, mapaY, mapaS, mobs[Moba].mugimendua.HasierakoPosizioa, mobs[Moba].mugimendua.AmaierakoPosizioa, Mugimendua, Moba);

            //Lehenengo aldian
            if (mobs[Moba].mugimendua.AurrekoDirekzioa == 0)
                mobs[Moba].mugimendua.AurrekoDirekzioa = mobs[Moba].mugimendua.OraingoDirekzioa;
            else
                mobs[Moba].mugimendua.AurrekoDirekzioa = tmp;

            mobs[Moba].mugimendua.AurrekoX = 0;
            mobs[Moba].mugimendua.AurrekoY = 0;
            mobs[Moba].mugimendua.OraingoX = 0;
            mobs[Moba].mugimendua.OraingoY = 0;

            //Direkzioa ezarri aurreko gelaxkan oinarrituta
            if (mobs[Moba].mugimendua.AurrekoDirekzioa == 1) {
                mobs[Moba].mugimendua.AurrekoY = mobs[Ronda[0] + 9].abiadura;
                mobs[Moba].y += mobs[Ronda[0] + 9].abiadura;
            }
            if (mobs[Moba].mugimendua.AurrekoDirekzioa == 2) {
                mobs[Moba].mugimendua.AurrekoX = mobs[Ronda[0] + 9].abiadura;
                mobs[Moba].x += mobs[Ronda[0] + 9].abiadura;
            }
            if (mobs[Moba].mugimendua.AurrekoDirekzioa == 3) {
                mobs[Moba].mugimendua.AurrekoY = -mobs[Ronda[0] + 9].abiadura;
                mobs[Moba].y += -mobs[Ronda[0] + 9].abiadura;
            }
            if (mobs[Moba].mugimendua.AurrekoDirekzioa == 4) {
                mobs[Moba].mugimendua.AurrekoX = -mobs[Ronda[0] + 9].abiadura;
                mobs[Moba].x += -mobs[Ronda[0] + 9].abiadura;
            }

            //Direkzioa ezarri oraingo gelaxkan oinarrituta
            if (mobs[Moba].mugimendua.OraingoDirekzioa == 1) {
                mobs[Moba].mugimendua.OraingoY = mobs[Ronda[0] + 9].abiadura;
                mobs[Moba].y += mobs[Ronda[0] + 9].abiadura;
            }
            if (mobs[Moba].mugimendua.OraingoDirekzioa == 2) {
                mobs[Moba].mugimendua.OraingoX = mobs[Ronda[0] + 9].abiadura;
                mobs[Moba].x += mobs[Ronda[0] + 9].abiadura;
            }
            if (mobs[Moba].mugimendua.OraingoDirekzioa == 3) {
                mobs[Moba].mugimendua.OraingoY = -mobs[Ronda[0] + 9].abiadura;
                mobs[Moba].y += -mobs[Ronda[0] + 9].abiadura;
            }
            if (mobs[Moba].mugimendua.OraingoDirekzioa == 4) {
                mobs[Moba].mugimendua.OraingoX = -mobs[Ronda[0] + 9].abiadura;
                mobs[Moba].x += -mobs[Ronda[0] + 9].abiadura;
            }
        }
        else {//Norabide berbera egin
            mobs[Moba].x += mobs[Moba].mugimendua.AurrekoX + mobs[Moba].mugimendua.OraingoX;
            mobs[Moba].y += mobs[Moba].mugimendua.AurrekoY + mobs[Moba].mugimendua.OraingoY;
        }
    }
    else {//Pertsonaiari kalte egin
        Pertsonaia.health -= 0.01 * Ronda[0];
    }
}

int PathFinding(int Mapa[], int mapaX, int mapaY, int mapaS, int HasieraPos, int AmaieraPos, int Mugimendua[], int Moba) {
    int MapaEsc[512], Pos, Kont = 1;

    Pos = AmaieraPos;
    ArrayGarbitu(MapaEsc);
    ArrayGarbitu(Mugimendua);
    MapaEsc[Pos] = Kont;

    while (Pos != HasieraPos) {//Algoritmoa helmugara heltzen ez bada
        if (!MapaEsc[Pos - mapaX] && Mapa[Pos - mapaX] == 0) {
            MapaEsc[Pos - mapaX] = Kont + 1;
            Mugimendua[Pos - mapaX] = 1;
            Kont++;
        }
        if (!MapaEsc[Pos - 1] && Mapa[Pos - 1] == 0) {
            MapaEsc[Pos - 1] = Kont + 1;
            Mugimendua[Pos - 1] = 2;
            Kont++;
        }
        if (!MapaEsc[Pos + mapaX] && Mapa[Pos + mapaX] == 0) {
            MapaEsc[Pos + mapaX] = Kont + 1;
            Mugimendua[Pos + mapaX] = 3;
            Kont++;
        }
        if (!MapaEsc[Pos + 1] && Mapa[Pos + 1] == 0) {
            MapaEsc[Pos + 1] = Kont + 1;
            Mugimendua[Pos + 1] = 4;
            Kont++;
        }
        Pos = PosizioaBilatu(MapaEsc, MapaEsc[Pos] + 1);
        if (Pos == 512) {
            PosizioAleatorioa(Mapa, mapaX, mapaY, mapaS, Moba);
            HasieraPos = PosizioZehastu(mobs[Moba].x, mobs[Moba].y, mapaX, mapaY, mapaS, Mapa);
            Pos = AmaieraPos;
        }
            
    }
    return Mugimendua[HasieraPos];//Etsaila mugitu behar den direkzioa
}

void ArrayGarbitu(int b[]) {
    int i;

    for (i = 0; i < 315; i++)
        b[i] = 0;
}

int PosizioaBilatu(int MapaEsc[], int Pos) {
    int i = 0;

    while (MapaEsc[i] != Pos && i < 512) {
        i++;
    }
    return i;
}