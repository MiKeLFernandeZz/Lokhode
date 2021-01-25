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

extern int Hizkuntza;

int kreditoakMenu() {
    int loopa = 0, ebentu, idFondo, idPantalla1[3], idPantalla3, idTexto, idMU, idMujang, fase, fase1;
    const Uint8* state = SDL_GetKeyboardState(NULL);
    float segundos = 5;

    idFondo = irudiaKargatu(".\\img\\menus\\creditos\\CREDITOS2_FONDO.bmp");
    idPantalla1[0] = irudiaKargatu(".\\img\\menus\\creditos\\CREDITOS1_E.bmp");
    idPantalla1[1] = irudiaKargatu(".\\img\\menus\\creditos\\CREDITOS1_C.bmp");
    idPantalla1[2] = irudiaKargatu(".\\img\\menus\\creditos\\CREDITOS1_I.bmp");
    idPantalla3 = irudiaKargatu(".\\img\\menus\\creditos\\CREDITOS3.bmp");
    idTexto= irudiaKargatu(".\\img\\menus\\creditos\\CRETEXTOS.bmp");
    idMU = irudiaKargatu(".\\img\\menus\\creditos\\MUUUUU.bmp");
    idMujang = irudiaKargatu(".\\img\\menus\\creditos\\MUJANGOWON.bmp");

    ebentu = ebentuaJasoGertatuBada();
    for(fase=0; fase < 3; fase++){
        pantailaGarbitu();
        if (fase == 0) { //CREADORES
            IrudiarenDimentzioakDst(idPantalla1[Hizkuntza], 0, 0, PantailaLuzeera(), PantailaAltuera());
            IrudiarenDimentzioakSrc(idPantalla1[Hizkuntza], 0, 0, 2000, 1200);
        }
        if (fase == 1) { //ENPRESAS
            
            for(fase1=0;fase1<4;fase1++){
                    pantailaGarbitu();
                    IrudiarenDimentzioakDst(idFondo, 0, 0, PantailaLuzeera(), PantailaAltuera());
                    IrudiarenDimentzioakSrc(idFondo, 0, 0, 2000, 1200);
                    if (fase1 == 0) { //un juego de la mano de...
                         if(Hizkuntza==0){
                            IrudiarenDimentzioakDst(idTexto, PantailaLuzeera()/2 -1111/2, PantailaAltuera() - 200, 1111, 135);
                            IrudiarenDimentzioakSrc(idTexto, 0, 135, 1111, 135);
                            fase1++;
                         }
                         if(Hizkuntza==1){
                            IrudiarenDimentzioakDst(idTexto, PantailaLuzeera()/2 -1612/2, PantailaAltuera()/2 - 135/2, 1612, 135);
                            IrudiarenDimentzioakSrc(idTexto, 0, 0, 1612, 135);
                         }
                         if(Hizkuntza==2){
                            IrudiarenDimentzioakDst(idTexto, PantailaLuzeera()/2 -800/2, PantailaAltuera()/2 - 144/2, 800, 144);
                            IrudiarenDimentzioakSrc(idTexto, 0, 280, 800, 144);
                         }
                    }
                    if (fase1 == 1) { //MUJANG
                        IrudiarenDimentzioakDst(idMujang, PantailaLuzeera()/2 - 1574/2, PantailaAltuera()/2 -430/2, 1574, 430);
                        IrudiarenDimentzioakSrc(idMujang, 0, 0, 1574, 430);
                    }
                    if (fase1 == 2) { //y en colaboracion con...
                        if(Hizkuntza==0){
                            IrudiarenDimentzioakDst(idTexto, PantailaLuzeera() / 2 - 1888 / 2, 125, 1888, 175);
                            IrudiarenDimentzioakSrc(idTexto, 0, 715, 1888, 175);
                            fase1++;
                        }
                        if(Hizkuntza==1){
                           IrudiarenDimentzioakDst(idTexto, PantailaLuzeera() / 2 - 1330 / 2, PantailaAltuera() / 2 - 146 / 2, 1330, 146);
                           IrudiarenDimentzioakSrc(idTexto, 0, 424, 1330, 146);
                        }
                        if(Hizkuntza==2){
                           IrudiarenDimentzioakDst(idTexto, PantailaLuzeera() / 2 - 1570 / 2, PantailaAltuera() / 2 - 130 / 2, 1570, 130);
                           IrudiarenDimentzioakSrc(idTexto, 0, 580, 1570, 130);
                        }
                    }
                    if (fase1 == 3) { //MU
                        IrudiarenDimentzioakDst(idMU, PantailaLuzeera() / 2 - 902 / 2, PantailaAltuera() / 2 - 672 / 2 + 50, 902, 672);
                        IrudiarenDimentzioakSrc(idMU, 0, 0, 902, 672);
                        segundos = segundos / 2;
                    }

                    pantailaBerriztu();
                    delay(segundos);
            }
        }
        if (fase == 2 || state[SDL_SCANCODE_ESCAPE]) { //TITULO
            IrudiarenDimentzioakDst(idPantalla3, 0, 0, PantailaLuzeera(), PantailaAltuera());
            IrudiarenDimentzioakSrc(idPantalla3, 0, 0, 2000, 1200);
        }

        pantailaBerriztu();
        delay(segundos);
    }
    return 0;
}