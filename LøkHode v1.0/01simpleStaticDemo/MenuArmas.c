#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "graphics.h"
#include "ebentoak.h"
#include "soinua.h"
#include "text.h"
#include "imagen.h"
#include "OurTypes.h"

#include "Funtzioak.h"

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

extern struct Pertsonaia Pertsonaia;
extern int click;

int armaSelekzioa(int Ronda, int idArmaSelekzioa) {
    int loopa = 0, ebentu, xMenu = 3840, yMenu = 1080, x, y, n = -1, Kont = -1;
    
    if (Ronda == 0) {
        n = 0;
        Kont = 2;
    }
    if (Ronda == 3) {
        n = 2;
        Kont = 3;
    }
    if (Ronda == 7) {
        n = 5;
        Kont = 4;
    }

    SDL_ShowCursor(SDL_ENABLE);

    while (loopa == 0) {
        pantailaGarbitu();
        SDL_GetMouseState(&x, &y);

        xMenu = n % 3;
        yMenu = n / 3;

        ebentu = ebentuaJasoGertatuBada();
        if (((x < (PantailaLuzeera() / 2.400)) && (x > (PantailaLuzeera() / 9.600))) && ((y > (PantailaAltuera() / 2.920)) && (y < (PantailaAltuera() / 1.560)))) {
            xMenu = (n + Kont - 1) % 3;
            yMenu = (n + Kont - 1) / 3;
            if (ebentu == SAGU_BOTOIA_EZKERRA) {
                click = SDL_MOUSEBUTTONUP;
                return 1;
            }
        }
        if (Ronda > 2 &&((x < (PantailaLuzeera() / 1.096)) && (x > (PantailaLuzeera() / 1.662))) && ((y > (PantailaAltuera() / 3.000)) && (y < (PantailaAltuera() / 1.556)))) {
            xMenu = (n + Kont - 2) % 3;
            yMenu = (n + Kont - 2) / 3;
            if (ebentu == SAGU_BOTOIA_EZKERRA) {
                click = SDL_MOUSEBUTTONUP;
                return 2;
            }
        }
        if (Ronda > 6 &&((x < (PantailaLuzeera() / 1.570)) && (x > (PantailaLuzeera() / 3.160))) && ((y > (PantailaAltuera() / 1.530)) && (y < (PantailaAltuera() / 1.075)))) {
            xMenu = (n + Kont - 3) % 3;
            yMenu = (n + Kont - 3) / 3;
            if (ebentu == SAGU_BOTOIA_EZKERRA) {
                click = SDL_MOUSEBUTTONUP;
                return 3;
            }
        }

        IrudiarenDimentzioakDst(idArmaSelekzioa, 0, 0, PantailaLuzeera(), PantailaAltuera());
        IrudiarenDimentzioakSrc(idArmaSelekzioa, 1920 * xMenu, 1080 * yMenu, 1920, 1080);
        pantailaBerriztu();
    }
}