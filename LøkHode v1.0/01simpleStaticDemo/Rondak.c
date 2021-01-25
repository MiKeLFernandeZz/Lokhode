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
extern int click;

void Rondak(int Ronda[], int idRonda, int idAlerta) {
    int i, MobKop = Ronda[1], egia = 1;
    float width, Proportzioa;

    width = PantailaLuzeera();
    Proportzioa = width / 1920;

    if (Pertsonaia.health > 0) {//Pertsonaia bizirik dago
        if (Ronda[0] == 0) {//Hasieran ezaugarriak ezarri, eta lehenengo ronda pantailaratu
            pantailaGarbitu();
            LaukiaMarraztu(0, 0, PantailaLuzeera(), PantailaAltuera(), 0, 0, 0);
            IrudiarenDimentzioakDst(idRonda, PantailaLuzeera() / 2 - 891.5 * Proportzioa, PantailaAltuera() / 2 - 418.75 * Proportzioa, 1783 * Proportzioa, 837.5 * Proportzioa);
            IrudiarenDimentzioakSrc(idRonda, 1783.3 * 0, 837.5 * 0, 1783.3, 837.5);
            audioInit();
            playSound(0, idAlerta);
            pantailaBerriztu();
            delay(3);
            
            Ronda[0] = 1;
            mobs[Ronda[0] + 9].abiadura = 0.02 + Ronda[0] * 0.008;
            mobs[Ronda[0] + 9].health = 200 + Ronda[0] * 15;
            Pertsonaia.Hilketak = 0;
            Pertsonaia.health = 100;
        }

        for (i = 0; i < MobKop; i++) {//Etsailak bizirik daudela konprobatu
            if (mobs[i].health > 0 || mobs[i].mugimendua.Animazioa < 8)
                egia = 0;
        }

        if (egia && Ronda[0] <= 10) {
            
            if (mobs[Ronda[0] + 9].health <= 0 && mobs[Ronda[0] + 9].mugimendua.Animazioa > 8) {//Ronda bukaera
                Ronda[0]++;
                Ronda[1]++;
                Ronda[2]++;//Etsaiei ausazko posizio emateko erabiltzen da
                for (i = 0; i < Ronda[1]; i++) {//Etsaien ezaugarriak ezartzeko, rondaren arabera zailagoa:
                    mobs[i].health = 100 + Ronda[0] * 5;
                    mobs[i].abiadura = 0.05 + Ronda[0] * 0.3;
                    mobs[i].mugimendua.Animazioa = 0.005 * i;
                }
                //Diktadoreei ezaugarriak ezartzeko, rondaren arabera zailagua:
                mobs[Ronda[0] + 9].abiadura = 0.02 + Ronda[0] * 0.008;
                mobs[Ronda[0] + 9].health = 200 + Ronda[0] * 15;
                mobs[Ronda[0] + 9].mugimendua.Animazioa = 0.009;

                click = SDL_MOUSEBUTTONUP;

                if (Ronda[0] == 2) {
                    IrudiarenDimentzioakDst(idRonda, PantailaLuzeera() / 2 - 891.5 * Proportzioa, PantailaAltuera() / 2 - 418.75 * Proportzioa, 1783 * Proportzioa, 837.5 * Proportzioa);
                    IrudiarenDimentzioakSrc(idRonda, 1783.3, 0, 1783.3, 837.5);
                    audioInit();
                    playSound(0, idAlerta);
                    pantailaBerriztu();
                    delay(3);
                }
                if (Ronda[0] == 3) {
                    IrudiarenDimentzioakDst(idRonda, PantailaLuzeera() / 2 - 891.5 * Proportzioa, PantailaAltuera() / 2 - 418.75 * Proportzioa, 1783 * Proportzioa, 837.5 * Proportzioa);
                    IrudiarenDimentzioakSrc(idRonda, 1783.3*2, 837.5*0, 1783.3, 837.5);
                    audioInit();
                    playSound(0, idAlerta);
                    pantailaBerriztu();
                    delay(3);
                }
                if (Ronda[0] == 4) {
                    IrudiarenDimentzioakDst(idRonda, PantailaLuzeera() / 2 - 891.5 * Proportzioa, PantailaAltuera() / 2 - 418.75 * Proportzioa, 1783 * Proportzioa, 837.5 * Proportzioa);
                    IrudiarenDimentzioakSrc(idRonda, 1783.3*0, 837.5*1, 1783.3, 837.5);
                    audioInit();
                    playSound(0, idAlerta);
                    pantailaBerriztu();
                    delay(3);
                }
                if (Ronda[0] == 5) {
                    IrudiarenDimentzioakDst(idRonda, PantailaLuzeera() / 2 - 891.5 * Proportzioa, PantailaAltuera() / 2 - 418.75 * Proportzioa, 1783 * Proportzioa, 837.5 * Proportzioa);
                    IrudiarenDimentzioakSrc(idRonda, 1783.3*1, 837.5*1, 1783.3, 837.5);
                    audioInit();
                    playSound(0, idAlerta);
                    pantailaBerriztu();
                    delay(3);
                }
                if (Ronda[0] == 6) {
                    IrudiarenDimentzioakDst(idRonda, PantailaLuzeera() / 2 - 891.5 * Proportzioa, PantailaAltuera() / 2 - 418.75 * Proportzioa, 1783 * Proportzioa, 837.5 * Proportzioa);
                    IrudiarenDimentzioakSrc(idRonda, 1783.3*2, 837.5*1, 1783.3, 837.5);
                    audioInit();
                    playSound(0, idAlerta);
                    pantailaBerriztu();
                    delay(3);
                }
                if (Ronda[0] == 7) {
                    IrudiarenDimentzioakDst(idRonda, PantailaLuzeera() / 2 - 891.5 * Proportzioa, PantailaAltuera() / 2 - 418.75 * Proportzioa, 1783 * Proportzioa, 837.5 * Proportzioa);
                    IrudiarenDimentzioakSrc(idRonda, 1783.3*0, 837.5*2, 1783.3, 837.5);
                    audioInit();
                    playSound(0, idAlerta);
                    pantailaBerriztu();
                    delay(3);
                }
                if (Ronda[0] == 8) {
                    IrudiarenDimentzioakDst(idRonda, PantailaLuzeera() / 2 - 891.5 * Proportzioa, PantailaAltuera() / 2 - 418.75 * Proportzioa, 1783 * Proportzioa, 837.5 * Proportzioa);
                    IrudiarenDimentzioakSrc(idRonda, 1783.3*1, 837.5*2, 1783.3, 837.5);
                    audioInit();
                    playSound(0, idAlerta);
                    pantailaBerriztu();
                    delay(3);
                }
                if (Ronda[0] == 9) {
                    IrudiarenDimentzioakDst(idRonda, PantailaLuzeera() / 2 - 891.5 * Proportzioa, PantailaAltuera() / 2 - 418.75 * Proportzioa, 1783 * Proportzioa, 837.5 * Proportzioa);
                    IrudiarenDimentzioakSrc(idRonda, 1783.3*2, 837.5*2, 1783.3, 837.5);
                    audioInit();
                    playSound(0, idAlerta);
                    pantailaBerriztu();
                    delay(3);
                }
                if (Ronda[0] == 10) {
                    IrudiarenDimentzioakDst(idRonda, PantailaLuzeera() / 2 - 891.5 * Proportzioa, PantailaAltuera() / 2 - 418.75 * Proportzioa, 1783 * Proportzioa, 837.5 * Proportzioa);
                    IrudiarenDimentzioakSrc(idRonda, 1783.3*0, 837.5*3, 1783.3, 837.5);
                    audioInit();
                    playSound(0, idAlerta);
                    pantailaBerriztu();
                    delay(3);
                }
            }//Si el ultimo vivo es el dictador aumenta sus estadísticas
            else if (mobs[Ronda[0] + 9].abiadura == 0.02 + Ronda[0] * 0.008) {//Diktadorea errondaren azken etsaia bada, indatzea:
                mobs[Ronda[0] + 9].abiadura = mobs[Ronda[0] + 9].abiadura * 3;
            }
        }
    }
    
}

void delay(float number_of_seconds) {
    float milli_seconds = 1000 * number_of_seconds;
    
    clock_t start_time = clock();

    while (clock() < start_time + milli_seconds);
}