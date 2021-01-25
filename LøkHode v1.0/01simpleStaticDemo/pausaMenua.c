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

int pausaMenua(int id) {
    int loop = -1, ebentu;
    const Uint8* state = SDL_GetKeyboardState(NULL);
 
    while (loop == -1) {

         ebentu = ebentuaJasoGertatuBada();
         IrudiarenDimentzioakDst(id, 0, 0, PantailaLuzeera(), PantailaAltuera());
         IrudiarenDimentzioakSrc(id, 0, 0, 1920, 993);

         pantailaBerriztu();

        if (state[SDL_SCANCODE_RETURN]) {//Jokora bueltatu
            loop = 1;
        }
        if (state[SDL_SCANCODE_BACKSPACE]) {//Menu printzipala
            loop = 0;
        }
        if (state[SDL_SCANCODE_ESCAPE]) {//Programatik irten
            loop = 5;
        }
    }
    return loop;
}