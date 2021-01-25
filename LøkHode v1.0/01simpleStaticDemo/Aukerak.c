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
extern int sensibilitateMoldatzaile;
extern int Kalitatea;

int aukerakMenu(int idAukerak) {
    int loopa = 0, ebentu, idBala, idBanderas, idGraficos, Proportzioa, altBala = 55, graficType = 1, x, y, j, cortita ,backButton;

    backButton = irudiaKargatu(".\\img\\menus\\ESC.bmp");
    char sensibilitatea[4];
    float width, proportzioa = 1;

    idBala = irudiaKargatu(".\\img\\menus\\ajustes\\BALAS.bmp");
    idBanderas = irudiaKargatu(".\\img\\menus\\ajustes\\BANDERAS.bmp");
    idGraficos = irudiaKargatu(".\\img\\menus\\ajustes\\GRAFICOS.bmp");

    cortita = Hizkuntza;

    width = PantailaLuzeera();

    if (width < 1920)
        proportzioa = width / 1920;

    while (loopa == 0) {
        pantailaGarbitu();
        SDL_GetMouseState(&x, &y);

        Proportzioa = PantailaLuzeera() / 1920;
        ebentu = ebentuaJasoGertatuBada();

        //Menuaren atzeko argazkia hizkuntzaren arabera aldatzea:
        if (Hizkuntza != cortita) {
            if (Hizkuntza == 0) {
                idAukerak = irudiaKargatu(".\\img\\menus\\ajustes\\ajustes_E.bmp");
            }
            if (Hizkuntza == 1) {
                idAukerak = irudiaKargatu(".\\img\\menus\\ajustes\\ajustes_C.bmp");
            }
            if (Hizkuntza == 2) {
                idAukerak = irudiaKargatu(".\\img\\menus\\ajustes\\ajustes_I.bmp");
            }
            cortita = Hizkuntza;
        }

        IrudiarenDimentzioakDst(idAukerak, PantailaLuzeera() / 2 - 960 * proportzioa, 0, 1920 * proportzioa, PantailaAltuera());
        IrudiarenDimentzioakSrc(idAukerak, 0, 0, 1920, 993);

        IrudiarenDimentzioakDst(backButton, 30, 30, 333*0.75, 97*0.75);
        IrudiarenDimentzioakSrc(backButton, 0, 97*Hizkuntza, 333, 97);

        //Bala itxura duten botoien kolisioak
        for (j = 0; j < 3; j ++) {
            if (x >= PantailaLuzeera() / 2 - 326 * proportzioa && x <= PantailaLuzeera() / 2 - 180 * proportzioa && y >= PantailaAltuera() / 2 - 220 * proportzioa + j * 240 * proportzioa && y <= PantailaAltuera() / 2 - 155 * proportzioa + j * 240 * proportzioa) { //Bala izquierda
                IrudiarenDimentzioakDst(idBala, PantailaLuzeera() / 2 - 380 * proportzioa, PantailaAltuera() / 2 - 255 * proportzioa + j * 250 * proportzioa, 230 * proportzioa, 120 * proportzioa);
                IrudiarenDimentzioakSrc(idBala, 0, 0, 205, 105);
                if (ebentu == SAGU_BOTOIA_EZKERRA) {
                    if (j == 0) {//Lehen botoia (lehen aukerakoa, ezkerraldekoa), kalitatea aldatzeko:
                        if (Kalitatea == 16) {
                            Kalitatea = 4;
                        }
                        else
                            Kalitatea *= 2;
                    }
                    if (j == 1) {//Bigarren botoia (bigarren aukerakoa, ezkerraldekoa), saguaren sensibilitatea aldatzeko:
                        if (sensibilitateMoldatzaile > 0 && sensibilitateMoldatzaile <= 99)
                            sensibilitateMoldatzaile--;
                    }
                    if (j == 2) {//Hirugarren botoia (hirugarren aukerakoa, ezkerraldekoa), hizkuntza aldatzeko:
                        if (Hizkuntza == 0) {
                            Hizkuntza = 2;
                        }
                        else
                            Hizkuntza--;
                    }
                }
            }
            if (x >= PantailaLuzeera() / 2 + 120 * proportzioa && x <= PantailaLuzeera() / 2 + 276 * proportzioa && y >= PantailaAltuera() / 2 - 220 * proportzioa + j * 240 * proportzioa && y <= PantailaAltuera() / 2 - 155 * proportzioa + j * 240 * proportzioa) { //Bala derecha
                IrudiarenDimentzioakDst(idBala, PantailaLuzeera() / 2 + 120 * proportzioa, PantailaAltuera() / 2 - 255 * proportzioa + j * 250 * proportzioa, 230 * proportzioa, 120 * proportzioa);
                IrudiarenDimentzioakSrc(idBala, 205, 0, 400, 105);
                if (ebentu == SAGU_BOTOIA_EZKERRA) {
                    if (j == 0) {//Lehen botoia (lehen aukerakoa, eskuinaldekoa), kalitatea aldatzeko:
                        if (Kalitatea == 4) {
                            Kalitatea = 16;
                        }
                        else
                            Kalitatea /= 2;
                    }
                    if (j == 1) {//Bigarren botoia (bigarren aukerakoa, eskuinaldekoa), saguaren sensibilitatea aldatzeko:
                        if (sensibilitateMoldatzaile >= 0 && sensibilitateMoldatzaile < 99)
                            sensibilitateMoldatzaile++;
                    }
                    if (j == 2) {//Hirugarren botoia (hirugarren aukerakoa, eskuinaldekoa), hizkuntza aldatzeko:
                        if (Hizkuntza == 2) {
                            Hizkuntza = 0;
                        }
                        else
                            Hizkuntza++;
                    }
                }
            }
        }
        //Banderak pantailaratzeko:
        if (Hizkuntza == 0) {
            IrudiarenDimentzioakDst(idBanderas, PantailaLuzeera() / 2 - 65 * proportzioa, PantailaAltuera() / 2 + 262 * proportzioa, 125 * proportzioa, 81 * proportzioa);
            IrudiarenDimentzioakSrc(idBanderas, 0, 0, 130, 84);
        }
        if (Hizkuntza == 1) {
            IrudiarenDimentzioakDst(idBanderas, PantailaLuzeera() / 2 - 65 * proportzioa, PantailaAltuera() / 2 + 262 * proportzioa, 125 * proportzioa, 81 * proportzioa);
            IrudiarenDimentzioakSrc(idBanderas, 130, 0, 130, 84);
        }
        if (Hizkuntza == 2) {
            IrudiarenDimentzioakDst(idBanderas, PantailaLuzeera() / 2 - 65 * proportzioa, PantailaAltuera() / 2 + 262 * proportzioa, 125 * proportzioa, 81 * proportzioa);
            IrudiarenDimentzioakSrc(idBanderas, 260, 0, 130, 84);
        }
        //Kalitateko opzioak pantailaratzeko:
        if (Hizkuntza == 0) {//Euskara
            if (Kalitatea == 16) {
                IrudiarenDimentzioakDst(idGraficos, (PantailaLuzeera() / 2) - 170 * proportzioa, PantailaAltuera() / 2 - 230 * proportzioa, 285 * proportzioa, 90 * proportzioa);
                IrudiarenDimentzioakSrc(idGraficos, 0, 90, 285, 90);
            }
            if (Kalitatea == 8) {
                IrudiarenDimentzioakDst(idGraficos, (PantailaLuzeera() / 2) - 170 * proportzioa, PantailaAltuera() / 2 - 230 * proportzioa, 285 * proportzioa, 90 * proportzioa);
                IrudiarenDimentzioakSrc(idGraficos, 285, 90, 285, 90);
            }
            if (Kalitatea == 4) {
                IrudiarenDimentzioakDst(idGraficos, (PantailaLuzeera() / 2) - 170 * proportzioa, PantailaAltuera() / 2 - 230 * proportzioa, 285 * proportzioa, 90 * proportzioa);
                IrudiarenDimentzioakSrc(idGraficos, 610, 90, 285, 90);
            }
        }
        if (Hizkuntza == 1) {//Gaztelera
            if (Kalitatea == 16) {
                IrudiarenDimentzioakDst(idGraficos, (PantailaLuzeera() / 2) - 170 * proportzioa, PantailaAltuera() / 2 - 230 * proportzioa, 285 * proportzioa, 90 * proportzioa);
                IrudiarenDimentzioakSrc(idGraficos, 0, 170, 285, 90);
            }
            if (Kalitatea == 8) {
                IrudiarenDimentzioakDst(idGraficos, (PantailaLuzeera() / 2) - 170 * proportzioa, PantailaAltuera() / 2 - 230 * proportzioa, 285 * proportzioa, 90 * proportzioa);
                IrudiarenDimentzioakSrc(idGraficos, 285, 170, 295, 90);
            }
            if (Kalitatea == 4) {
                IrudiarenDimentzioakDst(idGraficos, (PantailaLuzeera() / 2) - 170 * proportzioa, PantailaAltuera() / 2 - 230 * proportzioa, 285 * proportzioa, 90 * proportzioa);
                IrudiarenDimentzioakSrc(idGraficos, 610, 170, 285, 90);
            }
        }
        if (Hizkuntza == 2) {//Ingelera
            if (Kalitatea == 16) {
                IrudiarenDimentzioakDst(idGraficos, (PantailaLuzeera() / 2) - 170 * proportzioa, PantailaAltuera() / 2 - 240 * proportzioa, 285 * proportzioa, 90 * proportzioa);
                IrudiarenDimentzioakSrc(idGraficos, 0, 0, 285, 90);
            }
            if (Kalitatea == 8) {
                IrudiarenDimentzioakDst(idGraficos, (PantailaLuzeera() / 2) - 170 * proportzioa, PantailaAltuera() / 2 - 240 * proportzioa, 285 * proportzioa, 90 * proportzioa);
                IrudiarenDimentzioakSrc(idGraficos, 285, 0, 285, 90);
            }
            if (Kalitatea == 4) {
                IrudiarenDimentzioakDst(idGraficos, (PantailaLuzeera() / 2) - 170 * proportzioa, PantailaAltuera() / 2 - 240 * proportzioa, 285 * proportzioa, 90 * proportzioa);
                IrudiarenDimentzioakSrc(idGraficos, 610, 0, 285, 90);
            }
        }
;
        //Sensibilitatea textu eran pantailaratzeko:
        sprintf(sensibilitatea, "%d", sensibilitateMoldatzaile);
        sensibilitatea[3] = '\0';

        textuaGaitu(60);
        textuaIdatzi(PantailaLuzeera()/2 - 50, PantailaAltuera()/2 + 25, sensibilitatea, 173, 0, 0);
        textuaDesgaitu();


        pantailaBerriztu();
        if (ebentu == TECLA_ESCAPE) {
            loopa = 1;
            return 0;
        }
    }
}