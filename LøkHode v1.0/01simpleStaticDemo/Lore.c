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

extern int Hizkuntza;

int loreaErakutsi(int idLore) {
    int irten = 0, ebentu, xMenu = 0, yMenu = 0, n = 0, zein = 1, a = 0, backButton;

    backButton = irudiaKargatu(".\\img\\menus\\ESC.bmp");

    while (!irten) {
        pantailaGarbitu();
        ebentu = ebentuaJasoGertatuBada();

        if (ebentu == TECLA_DOWN && n < 9)
            n++;
        if (ebentu == TECLA_UP && n > 0)
            n--;

        xMenu = n % 3;
        yMenu = n / 3;

        IrudiarenDimentzioakDst(idLore, 0, 0, PantailaLuzeera(), PantailaAltuera());
        IrudiarenDimentzioakSrc(idLore, 1920 * xMenu, 1080 * yMenu, 1920, 1080);

        IrudiarenDimentzioakDst(backButton, 30, 30, 333*0.75, 97*0.75);
        IrudiarenDimentzioakSrc(backButton, 0, 97 * Hizkuntza, 333, 97);

        pantailaBerriztu();
        if (ebentu == TECLA_ESCAPE) {
            irten = 1;
            return 0;
        }
    }
}