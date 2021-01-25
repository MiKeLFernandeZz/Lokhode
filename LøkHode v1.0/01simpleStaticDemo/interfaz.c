#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

//Ertzeko metala erakusteko:
void interfaz(int idInterfaz) {

    IrudiarenDimentzioakDst(idInterfaz, 0, 0, PantailaLuzeera(), PantailaAltuera());
    IrudiarenDimentzioakSrc(idInterfaz, 0, 0, 1920, 1080);
}

//Bizitza barra pantailaratzeko:
void LaVida(int barra, int bihotza) {
    float Proportzioa, width;
    float pantailaLuzeera;

    pantailaLuzeera = PantailaLuzeera();

    //Bizitzaren arabera barra tamaina gehiago edo gutxiago pantailaratzea:
    width = (Pertsonaia.health * 354) / 100;
    Proportzioa = pantailaLuzeera / 1920;

    IrudiarenDimentzioakDst(barra, 30 * Proportzioa, 10 * Proportzioa, (width + 5) * Proportzioa, 48 * Proportzioa);
    IrudiarenDimentzioakSrc(barra, 0, 0, width, 48);

    IrudiarenDimentzioakDst(bihotza, 0, 0, 80 * Proportzioa, 70 * Proportzioa);
    IrudiarenDimentzioakSrc(bihotza, 0, 0, 83, 76);
}