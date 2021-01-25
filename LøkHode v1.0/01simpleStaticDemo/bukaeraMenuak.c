#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"
#include "ebentoak.h"
#include "soinua.h"
#include "text.h"
#include "imagen.h"
#include "SDL.h"

#include "OurTypes.h"
#include "Funtzioak.h"

#define MENUPRINTZIPALA 0

extern struct Pertsonaia {
    float x;
    float y;
    double angelua;
    int IkusBertikala;
    float health;
    int arma;
    int Hilketak;

}PERTSONAIA;

extern struct Pertsonaia Pertsonaia;

extern int Hizkuntza;

int BukaeraIrabazle(int idWinner, int Ronda, int idAmaieraBotoiak) {
    int irten = 0, egoera, ebentu, x, y, n, musika = -1;
    float width, proportzioa = 1;
    char rondaKop[4], hildaKop[4];


    width = PantailaLuzeera();

    if (width < 1920)
        proportzioa = width / 1920;

    audioInit();
    loadTheMusic(".\\sound\\aplausos.wav");
    playMusic();

    pantailaGarbitu();
    LaukiaMarraztu(0, 0, PantailaLuzeera(), PantailaAltuera(), 0, 0, 0);
    IrudiarenDimentzioakDst(idWinner, PantailaLuzeera() / 2 - 960 * proportzioa, 0, 1920 * proportzioa, 1080 * proportzioa);

    if (Hizkuntza == 0) {}//Euskera
        IrudiarenDimentzioakSrc(idWinner, 1920, 0, 1920, 1080);
    if (Hizkuntza == 1)//Castellano
        IrudiarenDimentzioakSrc(idWinner, 0, 0, 1920, 1080);
    if (Hizkuntza == 2)//Ingles

    IrudiarenDimentzioakSrc(idWinner, 3840, 0, 1920, 1080);

    pantailaBerriztu();

    delay(2);

    SDL_ShowCursor(SDL_ENABLE);

    while (!irten) {

        SDL_GetMouseState(&x, &y);
        ebentu = ebentuaJasoGertatuBada();

        pantailaGarbitu();

        LaukiaMarraztu(0, 0, PantailaLuzeera(), PantailaAltuera(), 0, 0, 0);
        IrudiarenDimentzioakDst(idWinner, PantailaLuzeera() / 2 - 960 * proportzioa, 0, 1920 * proportzioa, 1080 * proportzioa);

        if (Hizkuntza == 0)
            IrudiarenDimentzioakSrc(idWinner, 1920, 1080, 1920, 1080);

        if (Hizkuntza == 1)
            IrudiarenDimentzioakSrc(idWinner, 0, 1080, 1920, 1080);

        if (Hizkuntza == 2)
            IrudiarenDimentzioakSrc(idWinner, 3840, 1080, 1920, 1080);

        sprintf(rondaKop, "%d", Ronda);
        rondaKop[3] = '\0';
        textuaGaitu(200);
        textuaIdatzi(PantailaLuzeera() * 0.75 - 50, PantailaAltuera() * 0.666 - 160, rondaKop, 0, 0, 0);
        textuaIdatzi(PantailaLuzeera()* 0.75 - 55, PantailaAltuera() * 0.666 -168, rondaKop, 255, 255, 255);
        textuaDesgaitu();


        sprintf(hildaKop, "%d", Pertsonaia.Hilketak);
        hildaKop[3] = '\0';
        textuaGaitu(200);
        textuaIdatzi(PantailaLuzeera() * 0.75 - 50, PantailaAltuera() / 3 - 75, hildaKop, 0, 0, 0);
        textuaIdatzi(PantailaLuzeera() * 0.75 - 55, PantailaAltuera() / 3 - 83, hildaKop, 255, 255, 255);
        textuaDesgaitu();

        if (x > PantailaLuzeera() / 2 - 281 * proportzioa && x < PantailaLuzeera() / 2 + 323 * proportzioa && y > PantailaAltuera() / 2 + 309 * proportzioa && y < PantailaAltuera() / 2 + 492 * proportzioa) {
            if (Hizkuntza == 0)//Euskera
                n = 1;
            if (Hizkuntza == 1)//Castellano
                n = 0;
            if (Hizkuntza == 2)//Ingles
                n = 2;

            IrudiarenDimentzioakDst(idAmaieraBotoiak, PantailaLuzeera() / 2 - 279 * proportzioa, PantailaAltuera() / 2 + 307 * proportzioa, 604 * proportzioa, 146 * proportzioa);
            IrudiarenDimentzioakSrc(idAmaieraBotoiak, 603 * n, 147, 605, 147);

            if (ebentu == SAGU_BOTOIA_EZKERRA) {
                irten = 1;
                egoera = 0;
            }
        }
        pantailaBerriztu();
    }

    return egoera;
}

int BukaeraLooser(int idAmaiera, int idLooser, int idLooserStats, int Ronda) {
    int irten = 0, egoera, ebentu, x, y, n, i = 1, musika = -1, idHil = -1;
    float width, proportzioa = 1;
    char rondaKop[4], hildaKop[4];

    width = PantailaLuzeera();
    idHil = loadSound(".\\sound\\gameover.wav");
    if (width < 1920)
        proportzioa = width / 1920;

    soundsUnload();
    playSound(0, idHil);
    loadTheMusic(".\\sound\\gameover.wav");
    playMusic();

    pantailaGarbitu();
    LaukiaMarraztu(0, 0, PantailaLuzeera(), PantailaAltuera(), 0, 0, 0);
    IrudiarenDimentzioakDst(idLooser, PantailaLuzeera() / 2 - 960 * proportzioa, 0, 1920 * proportzioa, 1080 * proportzioa);
    
    while (i != Ronda)
        i++;
    i--;
    x = i % 3;
    y = i / 3;

    IrudiarenDimentzioakSrc(idLooser, 1920 * x, 1080 * y, 1920, 1080);
    pantailaBerriztu();

    delay(2);

    SDL_ShowCursor(SDL_ENABLE);

    while (!irten) {

        SDL_GetMouseState(&x, &y);
        ebentu = ebentuaJasoGertatuBada();

        pantailaGarbitu();

        LaukiaMarraztu(0, 0, PantailaLuzeera(), PantailaAltuera(), 0, 0, 0);
        IrudiarenDimentzioakDst(idLooserStats, PantailaLuzeera() / 2 - 960 * proportzioa, 0, 1920 * proportzioa, 1080 * proportzioa);

        if (Hizkuntza == 0)
            IrudiarenDimentzioakSrc(idLooserStats, 0, 0, 1920, 1080);

        if (Hizkuntza == 1)
            IrudiarenDimentzioakSrc(idLooserStats, 1920, 0, 1920, 1080);

        if (Hizkuntza == 2)
            IrudiarenDimentzioakSrc(idLooserStats, 3840, 0, 1920, 1080);

        sprintf(rondaKop, "%d", Ronda);
        rondaKop[3] = '\0';
        textuaGaitu(200);
        textuaIdatzi(PantailaLuzeera() * 0.75 - 50, PantailaAltuera() * 0.666 - 160, rondaKop, 0, 0, 0);
        textuaIdatzi(PantailaLuzeera() * 0.75 - 55, PantailaAltuera() * 0.666 - 168, rondaKop, 255, 255, 255);
        textuaDesgaitu();


        sprintf(hildaKop, "%d", Pertsonaia.Hilketak);
        hildaKop[3] = '\0';
        textuaGaitu(200);
        textuaIdatzi(PantailaLuzeera() * 0.75 - 50, PantailaAltuera() / 3 - 75, hildaKop, 0, 0, 0);
        textuaIdatzi(PantailaLuzeera() * 0.75 - 55, PantailaAltuera() / 3 - 83, hildaKop, 255, 255, 255);
        textuaDesgaitu();

        if (Hizkuntza == 0)//Euskera
                n = 1;
        if (Hizkuntza == 1)//Castellano
                n = 0;
        if (Hizkuntza == 2)//Ingles
                n = 2;

        for (i = 0; i < 2; i++) {
            if (x > PantailaLuzeera() / 2 - 642 * proportzioa + 700 * i * proportzioa && x < PantailaLuzeera() / 2 - 38 * proportzioa + 700 * i * proportzioa && y > PantailaAltuera() / 2 + 309 * proportzioa && y < PantailaAltuera() / 2 + 492 * proportzioa) {


                IrudiarenDimentzioakDst(idAmaiera, PantailaLuzeera() / 2 - 642 * proportzioa + 699 * i * proportzioa, PantailaAltuera() / 2 + 328 * proportzioa, 604 * proportzioa, 146 * proportzioa);
                IrudiarenDimentzioakSrc(idAmaiera, 603 * n, 147 * i, 605, 147);

                if (ebentu == SAGU_BOTOIA_EZKERRA && i == 0) {
                    irten = 1;
                    egoera = 1;
                    egoera = 1;

                    audioInit();
                    loadTheMusic(".\\sound\\ost1.wav");
                    playMusic();
                }
                if (ebentu == SAGU_BOTOIA_EZKERRA && i == 1) {
                    irten = 1;
                    egoera = 0;
                }
            }
        }
        
        pantailaBerriztu();
    }

    return egoera;
}