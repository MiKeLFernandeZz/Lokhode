#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "graphics.h"
#include "ebentoak.h"
#include "soinua.h"
#include "text.h"
#include "imagen.h"

#include "Funtzioak.h"

#define PI 3.1415926

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

extern int Kalitatea;
float Proportzioa = 0.00054541;

//Genera una ventana
void hasieratu(void) {
    double d = 7.3;

    if (sgHasieratu() == -1)
    {
        fprintf(stderr, "Unable to set fullscreen video: %s\n", SDL_GetError());
    }
    pantailaGarbitu();

    pantailaBerriztu();

}



//Determina la Posicion en la matriz
int PosizioZehastu(float X, float Y, int mapaX, int mapaY, int mapaS, int Mapa[]) {
    int Pos, y, x;

    y = Y / mapaS;
    x = X / mapaS;

    Pos = y * mapaX + x;

    return Pos;
}

//------------------ETSAILEEN EZAUGARRIAK--------------//

void MobsEzaugarriak(int Ronda[]) {
    int i, height, MobKop = Ronda[1];
    float dx, dy, proportzioa;

    proportzioa = 0.375;
    height = PantailaAltuera();

    /*-----------------Subditos------------------------------------*/
    for (i = 0; i < MobKop; i++) {
        dx = Pertsonaia.x - mobs[i].x;
        dy = Pertsonaia.y - mobs[i].y;
        mobs[i].d = sqrt(pow(dx, 2) + pow(dy, 2));
        mobs[i].height = (50 * height) / mobs[i].d;
        mobs[i].width = mobs[i].height * proportzioa;
        mobs[i].angelua.erdikoa = atan(dy / dx);
        if (dx > 0)
            mobs[i].angelua.erdikoa += PI;
        if (mobs[i].angelua.erdikoa < 0)
            mobs[i].angelua.erdikoa += 2 * PI;
    }

    /*------------------Para el boss------------------------------*/
    dx = Pertsonaia.x - mobs[Ronda[0] + 9].x;
    dy = Pertsonaia.y - mobs[Ronda[0] + 9].y;
    mobs[Ronda[0] + 9].d = sqrt(pow(dx, 2) + pow(dy, 2));
    mobs[Ronda[0] + 9].height = (50 * height) / mobs[Ronda[0] + 9].d;
    mobs[Ronda[0] + 9].width = mobs[Ronda[0] + 9].height * proportzioa;
    mobs[Ronda[0] + 9].angelua.erdikoa = atan(dy / dx);
    if (dx > 0)
        mobs[Ronda[0] + 9].angelua.erdikoa += PI;
    if (mobs[Ronda[0] + 9].angelua.erdikoa < 0)
        mobs[Ronda[0] + 9].angelua.erdikoa += 2 * PI;
}

//----------------------------------RAY CASTING----------------------------------------------//

void RayCasting(int Mapa[], int mapaX, int mapaY, int mapaS, int Pos, int idSpriteSheet, int EtsaiKop) {
    int width, height, irten = 0, x, y, x0, y0, luzeera, n = 0, Kont = 0, k = 0, Irudia = -1, Textura = 0, Kontadorea, tmp;
    float PAngelua = Pertsonaia.angelua, i, CosA = 0, SinA = 0, tmpX, tmpY, HasierakoAngelua, AmaierakoAngelua, dAngelua, j = 0;
    int Etsailak[20];

    Proportzioa = 0.00054541 * Kalitatea;

    width = PantailaLuzeera();
    height = PantailaAltuera();


    HasierakoAngelua = PAngelua - ((Proportzioa * width) / (Kalitatea * 2));
    AmaierakoAngelua = PAngelua + ((Proportzioa * width) / (Kalitatea * 2));

    ArrayBete(Etsailak, EtsaiKop);//Etsailen arabera array-a bete
    KapenOrdenaZehastu(EtsaiKop, Etsailak);//Etsailen ordena zehastu

    x0 = Pertsonaia.x;     y0 = Pertsonaia.y;

    i = HasierakoAngelua;
    dAngelua = AmaierakoAngelua - HasierakoAngelua;

    while (j < dAngelua) {

        CosA = cos(i);       tmpX = CosA / 1;       x = Pertsonaia.x + tmpX;
        SinA = sin(i);       tmpY = SinA / 1;       y = Pertsonaia.y + tmpY;

        while (irten == 0 && x < mapaX * mapaS && x > 0 && y < mapaY * mapaS && y > 0) {

            //Izpiaren kolisioak detektatu
            if (y % mapaS == 0 && tmpY < 0 && Mapa[((y / mapaS) - 1) * mapaX + (x / mapaS)] != 0) {
                irten = 1;
                n = x % mapaS + 50;
                for (Kontadorea = 0; Kontadorea < 4; Kontadorea++) {
                    if (Mapa[((y / mapaS) - 1) * mapaX + (x / mapaS)] == Kontadorea + 1)
                        Textura = 50 * Kontadorea;
                }
            }
            if ((y + 1) % mapaS == 0 && tmpY > 0 && Mapa[((y + 1) / mapaS) * mapaX + (x / mapaS)] != 0) {
                irten = 1;
                n = (x % mapaS) + 50;
                for (Kontadorea = 0; Kontadorea < 4; Kontadorea++) {
                    if (Mapa[((y + 1) / mapaS) * mapaX + (x / mapaS)] == Kontadorea + 1)
                        Textura = 50 * Kontadorea;
                }
            }
            if ((x + 1) % mapaS == 0 && tmpX < 0 && Mapa[(y / mapaS) * mapaX + ((x + 1) / mapaS) - 1] != 0) {
                irten = 1;
                n = y % mapaS;
                for (Kontadorea = 0; Kontadorea < 4; Kontadorea++) {
                    if (Mapa[(y / mapaS) * mapaX + ((x + 1) / mapaS) - 1] == Kontadorea + 1)
                        Textura = 50 * Kontadorea;
                }
            }
            if (x % mapaS == 0 && tmpX > 0 && Mapa[(y / mapaS) * mapaX + (x / mapaS)] != 0) {
                irten = 1;
                n = y % mapaS;
                for (Kontadorea = 0; Kontadorea < 4; Kontadorea++) {
                    if (Mapa[(y / mapaS) * mapaX + (x / mapaS)] == Kontadorea + 1)
                        Textura = 50 * Kontadorea;
                }
            }

            //Izpiak luzatu
            CosA = CosA + cos(i);       tmpX = CosA / 1;
            SinA = SinA + sin(i);       tmpY = SinA / 1;

            x = Pertsonaia.x + tmpX;
            y = Pertsonaia.y + tmpY;
        }
        irten = 0;

        //Izpiaren luzeera kalkulatu
        tmp = tmpX * tmpX + tmpY * tmpY;
        luzeera = sqrt(tmp);
        Irudikatu(Kont, EtsaiKop, i, luzeera, idSpriteSheet, n, HasierakoAngelua);//Etsailen Posizioa pantailan
        luzeera = ((100 * height) / 2) / luzeera;

        //Testura
        IrudiarenDimentzioakDst(idSpriteSheet, Kont * Kalitatea, (height / 2) - luzeera / 2 + Pertsonaia.IkusBertikala, Kalitatea, luzeera);
        IrudiarenDimentzioakSrc(idSpriteSheet, n, Textura, 1, 50);
        Kont++;

        i += Proportzioa;
        j += Proportzioa;
    }
    
    //Etsaiak irudikatu
    for (n = 0; n < EtsaiKop + 1; n++) {
        k = Etsailak[n];

        if (mobs[k].health <= 0 && mobs[k].mugimendua.Animazioa < 4) {
            mobs[k].mugimendua.Animazioa = 4;
            Pertsonaia.Hilketak++;
        }

        if (mobs[k].mugimendua.Animazioa >= 0 && mobs[k].mugimendua.Animazioa < 1)
            Irudia = 1;
        if (mobs[k].mugimendua.Animazioa >= 1 && mobs[k].mugimendua.Animazioa < 2)
            Irudia = 2;
        if (mobs[k].mugimendua.Animazioa >= 2 && mobs[k].mugimendua.Animazioa < 3)
            Irudia = 3;
        if (mobs[k].mugimendua.Animazioa >= 3 && mobs[k].mugimendua.Animazioa < 4)
            Irudia = 4;
        if (mobs[k].mugimendua.Animazioa >= 4 && mobs[k].mugimendua.Animazioa < 5)
            Irudia = 5;
        if (mobs[k].mugimendua.Animazioa >= 5 && mobs[k].mugimendua.Animazioa < 5.5)
            Irudia = 6;
        if (mobs[k].mugimendua.Animazioa >= 5.5 && mobs[k].mugimendua.Animazioa < 6.5)
            Irudia = 7;
        if (mobs[k].mugimendua.Animazioa >= 6.5 && mobs[k].mugimendua.Animazioa < 8)
            Irudia = 8;

        if(mobs[k].mugimendua.Animazioa < 8)
            mobs[k].mugimendua.Animazioa += 0.01;

        if (k < 10) {//Para los subditos
            if (mobs[k].health > 0) {
                IrudiarenDimentzioakDst(mobs[0].id, mobs[k].Pos * Kalitatea - mobs[k].width / 2, PantailaAltuera() / 2 - mobs[k].height / 2 + Pertsonaia.IkusBertikala, mobs[k].width, mobs[k].height);
                IrudiarenDimentzioakSrc(mobs[0].id, 26 * Irudia, 0, 26, 50);
            }
            else if (mobs[k].mugimendua.Animazioa <= 8) {
                IrudiarenDimentzioakDst(mobs[0].id, mobs[k].Pos * Kalitatea - mobs[k].width / 2, PantailaAltuera() / 2 - mobs[k].height / 2 + Pertsonaia.IkusBertikala, mobs[k].width, mobs[k].height);
                if (Irudia == 5)
                    IrudiarenDimentzioakSrc(mobs[0].id, 130, 0, 26, 50);
                if (Irudia == 6)
                    IrudiarenDimentzioakSrc(mobs[0].id, 156, 0, 26, 50);
                if (Irudia == 7) {
                    IrudiarenDimentzioakDst(mobs[0].id, mobs[k].Pos * Kalitatea - (mobs[k].width / 2) * 1.42, PantailaAltuera() / 2 - mobs[k].height / 2 + Pertsonaia.IkusBertikala + 15000 / mobs[k].d, mobs[k].width * 1.42, mobs[k].height);
                    IrudiarenDimentzioakSrc(mobs[0].id, 182, 0, 37, 50);
                }
                if (Irudia == 8) {
                    IrudiarenDimentzioakDst(mobs[0].id, mobs[k].Pos * Kalitatea - (mobs[k].width / 2) * 1.42, PantailaAltuera() / 2 - mobs[k].height / 2 + Pertsonaia.IkusBertikala + 15500 / mobs[k].d, mobs[k].width * 1.42, mobs[k].height);
                    IrudiarenDimentzioakSrc(mobs[0].id, 220, 0, 37, 50);
                }
            }
        }
        else {//Para el ditador
            if (mobs[k].health > 0) {
                IrudiarenDimentzioakDst(mobs[k].id, mobs[k].Pos * Kalitatea - mobs[k].width / 2, PantailaAltuera() / 2 - mobs[k].height / 2 + Pertsonaia.IkusBertikala, mobs[k].width, mobs[k].height);
                 IrudiarenDimentzioakSrc(mobs[k].id, 26 * Irudia, 0, 24, 64);
            }
            else if (mobs[k].mugimendua.Animazioa <= 8) {
                IrudiarenDimentzioakDst(mobs[k].id, mobs[k].Pos * Kalitatea - mobs[k].width / 2, PantailaAltuera() / 2 - mobs[k].height / 2 + Pertsonaia.IkusBertikala, mobs[k].width, mobs[k].height);
                if (Irudia == 5)
                    IrudiarenDimentzioakSrc(mobs[k].id, 130, 0, 26, 64);
                if (Irudia == 6)
                    IrudiarenDimentzioakSrc(mobs[k].id, 156, 0, 26, 64);
                if (Irudia == 7) {
                    IrudiarenDimentzioakDst(mobs[k].id, mobs[k].Pos * Kalitatea - (mobs[k].width / 2) * 1.42, PantailaAltuera() / 2 - mobs[k].height / 2 + Pertsonaia.IkusBertikala + 15000 / mobs[k].d, mobs[k].width * 1.42, mobs[k].height);
                    IrudiarenDimentzioakSrc(mobs[k].id, 182, 0, 37, 64);
                }
                if (Irudia == 8) {
                    IrudiarenDimentzioakDst(mobs[k].id, mobs[k].Pos * Kalitatea - (mobs[k].width / 2) * 1.42, PantailaAltuera() / 2 - mobs[k].height / 2 + Pertsonaia.IkusBertikala + 15500 / mobs[k].d, mobs[k].width * 1.42, mobs[k].height);
                    IrudiarenDimentzioakSrc(mobs[k].id, 220, 0, 37, 64);
                }
            }
        }

        if (mobs[k].mugimendua.Animazioa >= 4 && mobs[k].health > 0)
            mobs[k].mugimendua.Animazioa -= 4;
    }
}

void ArrayBete(int Etsailak[], int EtsaiKop) {
    int i;

    for (i = 0; i < EtsaiKop; i++) {
        Etsailak[i] = i;
    }
}

void Irudikatu(int Kont, int EtsaiKop, float angelua, int luzeera, int idSpriteSheet, int n, float HasierakoAngelua) {
    int i = 0;

    while (i < EtsaiKop) {
        if (mobs[i].angelua.erdikoa - HasierakoAngelua > 2 * PI)
            mobs[i].angelua.erdikoa -= 2 * PI;

        if (mobs[i].angelua.erdikoa > angelua && mobs[i].angelua.erdikoa < angelua + Proportzioa && mobs[i].d < luzeera) {
            mobs[i].Pos = Kont;
        }
        i++;
    }

    if ((mobs[EtsaiKop + 10].angelua.erdikoa - HasierakoAngelua) > 2 * PI)
        mobs[EtsaiKop + 10].angelua.erdikoa -= 2 * PI;

    if (mobs[EtsaiKop + 10].angelua.erdikoa > angelua && mobs[EtsaiKop + 10].angelua.erdikoa < angelua + Proportzioa && mobs[EtsaiKop + 10].d < luzeera) {
        mobs[EtsaiKop + 10].Pos = Kont;
    }
}

//ORDENA DE MAS LEJOS A MÁS CERCA LOS ENEMIGOS//

void KapenOrdenaZehastu(int EtsaiKop, int Etsaiak[]) {
    int i, j, tmp, handiena = 0;

    Etsaiak[EtsaiKop] = EtsaiKop + 10;

    for (i = 0; i < EtsaiKop + 1; i++) {
        for (j = i + 1; j < EtsaiKop + 1; j++) {
            if (mobs[Etsaiak[j]].d > mobs[Etsaiak[i]].d) {
                tmp = Etsaiak[j];
                Etsaiak[j] = Etsaiak[i];
                Etsaiak[i] = tmp;
            }
        }
    }
}