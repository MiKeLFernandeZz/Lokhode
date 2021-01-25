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


SDL_Renderer* gRenderer;

extern int Hizkuntza;

int menua(int idFondo, int idSombra, int idDictador, int idTitulo, int idEslogan, int idBotones, int idFranjas, int idHumo, int RandNum) {
    int ebentu, i, j = 0, egia = 0, n = -1, xMenu, yMenu, x, y;
    float Proportzioa = 1, width, height;

    width = PantailaLuzeera();
    height = PantailaAltuera();

    if (Hizkuntza == 0)//Euskera
        n = 0;
    if (Hizkuntza == 1)//Castellano
        n = 1;
    if (Hizkuntza == 2)//Ingles
        n = 2;

    if(width <= 1920)//Irudiak eskalatzeko
        Proportzioa = width / 1920;

    xMenu = RandNum % 3;
    yMenu = RandNum / 3;

    IrudiarenDimentzioakDst(idFondo, width / 2 - 960 * Proportzioa, height / 2 - 540 * Proportzioa, 1920 * Proportzioa, 1080 * Proportzioa);
    IrudiarenDimentzioakSrc(idFondo, 0, 0, 1920, 1080);

    IrudiarenDimentzioakDst(idHumo, width / 2 - 960 * Proportzioa, height / 2 - 200 * Proportzioa, 1920 * Proportzioa, 857 * Proportzioa);
    IrudiarenDimentzioakSrc(idHumo, 0, 0, 1920, 1080);

    IrudiarenDimentzioakDst(idSombra, width / 2 - 960 * Proportzioa, height / 2 - 200 * Proportzioa, 1920 * Proportzioa, 857 * Proportzioa);
    IrudiarenDimentzioakSrc(idSombra, 0, 0, 1920, 857);

    IrudiarenDimentzioakDst(idDictador, width / 2 - 900 * Proportzioa, height / 2 - 370 * Proportzioa, 972 * Proportzioa, 783 * Proportzioa);
    IrudiarenDimentzioakSrc(idDictador, 972 * xMenu, 783 * yMenu, 972, 783);

    IrudiarenDimentzioakDst(idTitulo, width / 2 + 130 * Proportzioa, height / 2 - 365 * Proportzioa, 700 * Proportzioa, 131 * Proportzioa);
    IrudiarenDimentzioakSrc(idTitulo, 0, 0, 700, 131);

    IrudiarenDimentzioakDst(idEslogan, width / 2 + 195 * Proportzioa, height / 2 - 220 * Proportzioa, 626 * Proportzioa, 50 * Proportzioa);
    IrudiarenDimentzioakSrc(idEslogan, 0, 0, 626, 50);
    
    //Saguaren posizioa jasotzeko:
    SDL_GetMouseState(&x, &y);
    
    ebentu = ebentuaJasoGertatuBada();
    
    //Botoiak irudikatu
    for (i = 0; i < 5; i++) {
        if (x > width / 2 + 425 * Proportzioa && x < width / 2 + 813 * Proportzioa && y >  height / 2 - 75 + 75 * i * Proportzioa && y < height / 2 - 29 + 75 * Proportzioa* i ) {
            if (i == 0 && ebentu == SAGU_BOTOIA_EZKERRA) {
                return 1;
            }
            if (i == 1 && ebentu == SAGU_BOTOIA_EZKERRA) {
                return 2;
            }
            if (i == 2 && ebentu == SAGU_BOTOIA_EZKERRA) {
                return 3;
            }
            if (i == 3 && ebentu == SAGU_BOTOIA_EZKERRA) {
                return 4;
            }
            if (i == 4 && ebentu == SAGU_BOTOIA_EZKERRA) {
                return 5;
            }

            j++;
            egia = 1;
        }
        IrudiarenDimentzioakDst(idBotones, width / 2 + 425 * Proportzioa, height / 2 - 75 + 75 * i * Proportzioa, 388 * Proportzioa, 46 * Proportzioa);
        IrudiarenDimentzioakSrc(idBotones, j * 388, 46 * n, 388, 46);
        if (egia) {
            j++;
            egia = 0;
        }
        else
            j += 2;
    }

    IrudiarenDimentzioakDst(idFranjas, 0, 0, width, height);
    IrudiarenDimentzioakSrc(idFranjas, 0, 0, 1920, 1080);

    IrudiarenDimentzioakDst(idFranjas, 0, 0, 20, 20);
    LaukiaMarraztu(0, 0, width / 2 - 960, height, 0, 0 ,0);

    LaukiaMarraztu(width / 2 + 960, 0, width, height, 0, 0, 0); (ebentu == SAGU_BOTOIA_EZKERRA);

    return 0;
}