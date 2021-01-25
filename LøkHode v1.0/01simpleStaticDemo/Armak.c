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

extern Kalitatea;

int click = 0;

/*-----------------------------ARMA AUKERATUTA EZAUGARRIAK EZARRI-----------------------------*/
void armaEzaugarriak(int armaAukeratuta, float propietateak[]) {
    int idArma = -1, idArma_Irudi = -1;
    int balaKopuru = -1, kadentzia = -1, damage = -1, posizioaX = -1, posizioaY = -1, zarata = -1, rekargaSoinu = -1, rekargaDenbora = -1, rekargaSoinuAlt = -1, zuzenketa = -1;
    idArma = irudiaKargatu(".\\img\\ArmaSpriteSheet.bmp");
    soundsUnload();

    //PISTOLA:

    if (armaAukeratuta == 1) {
        posizioaX = 0;
        posizioaY = 0;
        idArma_Irudi = irudiaKargatu(".\\img\\Pistola_Icono.bmp");
        zarata = loadSound(".\\sound\\ARMAS\\pis_disparo.wav");
        rekargaSoinu = loadSound(".\\sound\\ARMAS\\rec_pis_fus.wav");
        rekargaSoinuAlt = -1;
        rekargaDenbora = 550;
        balaKopuru = 12;
        kadentzia = 70;
        damage = 30;
        zuzenketa = (PantailaLuzeera() / 30);
    }

    //METRAILETA:

    if (armaAukeratuta == 2) {
        posizioaX = 270;
        posizioaY = 0;
        idArma_Irudi = irudiaKargatu(".\\img\\Fusil_Icono.bmp");
        zarata = loadSound(".\\sound\\ARMAS\\balaSubfu.wav");
        rekargaSoinu = loadSound(".\\sound\\ARMAS\\rec_pis_fus.wav");
        rekargaSoinuAlt = -1;
        rekargaDenbora = 550;
        balaKopuru = 60;
        kadentzia = 10;
        damage = 15;
        zuzenketa = (PantailaLuzeera() / -165);
    }

    //ESKOPETA:

    if (armaAukeratuta == 3) {
        posizioaX = 540;
        posizioaY = 0;
        idArma_Irudi = irudiaKargatu(".\\img\\Escopeta_Icono.bmp");
        zarata = loadSound(".\\sound\\ARMAS\\esc_disparo.wav");
        rekargaSoinu = loadSound(".\\sound\\ARMAS\\rec_esc_2.wav");
        rekargaSoinuAlt = loadSound(".\\sound\\ARMAS\\rec_esc_1.wav");
        rekargaDenbora = 300;
        balaKopuru = 2;
        kadentzia = 300;
        damage = 200;
        zuzenketa = (PantailaLuzeera() / -30);
    }
    propietateak[0] = idArma;
    propietateak[1] = posizioaX;
    propietateak[2] = posizioaY;
    propietateak[3] = idArma_Irudi;
    propietateak[4] = zarata;
    propietateak[15] = rekargaSoinu;
    propietateak[17] = rekargaSoinuAlt;
    propietateak[16] = rekargaDenbora;
    propietateak[5] = balaKopuru;
    propietateak[14] = balaKopuru;
    propietateak[6] = kadentzia;
    propietateak[7] = damage;
    propietateak[18] = (PantailaLuzeera() / zuzenketa);
}

/*------------------------------ARMA MARRAZTU ETA FUNTZIONAMENDUA-----------------------------*/
int ArmaMarraztu(float propietateak[], int tiroa, int bai, int MobKopurua, int Ronda[]) {
    int cooldown;
    SDL_Event event;

    const Uint8* state = SDL_GetKeyboardState(NULL);

    //Munizio kopuruaren alboko armaren irudia:
    IrudiarenDimentzioakDst(propietateak[3], (PantailaLuzeera() - (PantailaLuzeera() / 4.8)), (PantailaAltuera() - (PantailaAltuera() / 18)), 162, 60);
    IrudiarenDimentzioakSrc(propietateak[3], 0, 0, 162, 60);

    //Tiroa posiblea den begiratzeko:
    if ((state[SDL_SCANCODE_SPACE]) && (bai == 0) && (propietateak[5] > 0) && (propietateak[10] >= propietateak[11])) {
        bai = 1;
        audioInit();
        playSound(1, propietateak[4]);
        Tiroa(MobKopurua, Ronda);
    }
    if (bai == 0) {
        propietateak[11]--;
    }

    //Tiroaren ezaugarri guztiak(cooldown, tiro-argazkia, tiro-animazioaren luzapena, munizioa gutxitu):
    if ((bai == 1)) {
        propietateak[2] = 296;
        propietateak[5]--;

        clock_t start_time = clock();
        propietateak[8] = start_time;
        cooldown = start_time + 30;
        propietateak[9] = cooldown;

        propietateak[10] = start_time;
        propietateak[11] = start_time + propietateak[6];

        propietateak[9]--;
        propietateak[11]--;

        bai = 2;
    }
    else {

        //Rekarga gauzatzeko(soinua, cooldown):
        if ((state[SDL_SCANCODE_R]) && (propietateak[5] < propietateak[14]) && (propietateak[12] >= propietateak[13])) {
            clock_t start_time = clock();
            propietateak[12] = start_time;

            cooldown = start_time + propietateak[16];
            audioInit();
            playSound(2, propietateak[15]);

            propietateak[13] = cooldown;
            bai = 4;
        }

        //Cooldownak behera egiteko:
        if (bai == 2 || bai == 4) {
            propietateak[9]--;
            propietateak[11]--;
            if(propietateak[12] != 0)
                propietateak[13]--;
        }

        //Bala berriztapena gauzatzeko:
        if ((propietateak[12] >= propietateak[13]) && (bai == 4)) {
            propietateak[5] = propietateak[14];
            bai = 0;
        }

        //Tiro animazioa bukatzeko:
        if (propietateak[8] >= propietateak[9] && bai != 4) {
            propietateak[2] = 0;
            bai = 0;
        }
    }
    //Arma marrazteko:
    IrudiarenDimentzioakDst(propietateak[0], ((PantailaLuzeera() / 2) - (PantailaLuzeera() / 3.84) + propietateak[18]), ((PantailaAltuera() / 2) + (PantailaAltuera() / 9.31)), PantailaLuzeera() / 2, PantailaAltuera() / 2);
    IrudiarenDimentzioakSrc(propietateak[0], propietateak[1], propietateak[2], 270, 296);

    return bai;
}

//Munizio kopurua erakusteko:
void ArmaMunizioa(float propietateak[], int bai) {
    int rekarga, ammo = propietateak[5];
    char balaKop[128];

    //munizio kopurua string batean bihurtzeko:
    sprintf(balaKop, "%d", ammo);
    balaKop[3] = '\0';

    //munizio testua sortzeko, tamaina batekin(60), posizioa eta kolorea:
    textuaGaitu(60);
    textuaIdatzi((PantailaLuzeera() - (PantailaLuzeera() / 14.222)), (PantailaAltuera() - (PantailaAltuera() / 16.615)), balaKop, 255, 255, 255);
    textuaDesgaitu();
}

/*------------------------------------ETSAIEI BIZITZA KENDU-----------------------------------*/
void Tiroa(int mobKopurua, int Ronda[]) {
    int i, erdikoPuntuaX, erdikoPuntuaY, A = 0, B = 0;

    erdikoPuntuaX = PantailaLuzeera() / 2;
    erdikoPuntuaY = PantailaAltuera() / 2;

    for (i = 0; i < mobKopurua; i++) {
        //Etsai normalak pantailaren erdian kokatuta baldin badaude:
        if (erdikoPuntuaX > mobs[i].Pos * Kalitatea - mobs[i].width / 2 && erdikoPuntuaX < mobs[i].Pos * Kalitatea + mobs[i].width / 2)
            A = 1;
        if (erdikoPuntuaY > PantailaAltuera() / 2 - mobs[i].height / 2 + Pertsonaia.IkusBertikala && erdikoPuntuaY < PantailaAltuera() / 2 + mobs[i].height / 2 + Pertsonaia.IkusBertikala)
            B = 1;

        //Etsai normalei bizitza kendu, arma motaren arabera:
        if (A && B) {
            if (Pertsonaia.arma == 1)
                mobs[i].health -= 25; //Pistola
            if (Pertsonaia.arma == 2)
                mobs[i].health -= 14; //Metraileta
            if (Pertsonaia.arma == 3)
                mobs[i].health -= 70; //Eskopeta
        }
        A = 0;
        B = 0;
    }

    //Diktadoreak pantailaren erdian kokatuta baldin badaude:
    if (erdikoPuntuaX > mobs[Ronda[0] + 9].Pos * Kalitatea - mobs[Ronda[0] + 9].width / 2 && erdikoPuntuaX < mobs[Ronda[0] + 9].Pos * Kalitatea + mobs[Ronda[0] + 9].width / 2)
        A = 1;
    if (erdikoPuntuaY > PantailaAltuera() / 2 - mobs[Ronda[0] + 9].height / 2 + Pertsonaia.IkusBertikala && erdikoPuntuaY < PantailaAltuera() / 2 + mobs[Ronda[0] + 9].height / 2 + Pertsonaia.IkusBertikala)
        B = 1;

    //Diktadoreei bizitza kendu, arma motaren arabera:
    if (A && B) {
        if (Pertsonaia.arma == 1)
            mobs[Ronda[0] + 9].health -= 25; //Pistola
        if (Pertsonaia.arma == 2)
            mobs[Ronda[0] + 9].health -= 14; //Metraileta
        if (Pertsonaia.arma == 3)
            mobs[Ronda[0] + 9].health -= 70; //Eskopeta
    }
    A = 0;
    B = 0;
};