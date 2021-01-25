#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"
#include "ebentoak.h"
#include "soinua.h"
#include "imagen.h"
#include "OurTypes.h"

#include "Funtzioak.h"

#define PI 3.1415926

#define MENUPRINTZIPALA 0
#define JOKOA 1
#define AUKERAK 2
#define KREDITUAK 3
#define LORE 4
#define BUKATU 5
#define WINNER 6
#define LOOSER 7

typedef struct angelua {
    float erdikoa;
    float hasierakoa;
    float bukaerakoa;
}angelua;

typedef struct mugimendua {
    float AurrekoX;
    float AurrekoY;
    float OraingoX;
    float OraingoY;
    int AurrekoDirekzioa;
    int OraingoDirekzioa;
    int HasierakoPosizioa;
    int AmaierakoPosizioa;
    float Animazioa;
}mugimendua;

typedef struct Mobs {
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

typedef struct Pertsonaia {
    float x;
    float y;
    double angelua;
    int IkusBertikala;
    float health;
    int arma;
    int Hilketak;

}PERTSONAIA;

 PERTSONAIA Pertsonaia;
 MOBS mobs[20];

 int backButton;
 int Kalitatea = 8;
 int Hizkuntza = 0;
 int tutoriala = 0;
 int sensibilitateMoldatzaile = 50;

int main(int argc, char * str[]) {

    /*-----------MENU PRINTZIPALA-------*/
    int irten = 0, menuHasi = 0, egoera = 0, RandNum, musika = 0;
    int idDictador = -1, idSombra = -1, idTitulo = -1, idEslogan = -1, idFondo = -1, idFranjas = -1, idBotones = -1, idHumo = -1, idLore = -1, idAukerak = -1;
    
    /*-------------INGAME-----------------*/
    int idSpriteSheet = -1, ebentu = 0, Pos = 0, idBarra = -1, idBihotza = -1, idVida = -1, idInterfaz = -1, idReticula = -1;

    /*--------------AMAIERAKO MENUA-----*/
    int idWinner = -1, idAmaiera = -1, idLooser = -1, idLooserStats = -1, idHil = -1;

    /*------------TUTORIALA--------------*/
    int idTutoriala, idTutorialaE = -1, idTutorialaC = -1, idTutorialaI = -1;
    
    /*-----------PAUSA MENUA-------------*/
    int idPausa = -1, idPausaE, idPausaC, idPausaI;

    /*----------ARMA SELEKZIOA-----------*/
    int idArmaSelekzioa = -1, idArmaSelekzioaE, idArmaSelekzioaC, idArmaSelekzioaI;
   
    /*--------------RONDA*---------------*/
    int Ronda[3] = {0, 0, 1}, idRonda = -1;
    int idAlerta = -1;

    /*--------------ARMAK----------------*/
    float Armak[19], bai = 0, armaZkia = -1, idArma = -1;
    
    /*---------------MAPA---------------*/
    int mapaX = 21, mapaY = 15, mapaS = 50, idMapa = -1;
    int Mapa[512] = {
        1,1,1,1,1,1,1,1,1,1,4,4,1,1,1,1,1,1,1,1,1,
        1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
        1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
        4,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,4,
        1,0,0,0,0,0,0,2,2,2,0,2,2,2,0,0,0,1,0,0,1,
        1,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,2,0,0,3,0,0,2,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,2,0,2,2,2,0,2,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
        1,1,1,1,1,1,1,4,4,1,1,1,1,1,1,1,1,1,1,1,1,
    };

    const Uint8* state = SDL_GetKeyboardState(NULL);

    Armak[8] = 0;
    Armak[9] = 0;
    Armak[10] = 0;
    Armak[11] = 0;
    Armak[12] = 0;
    Armak[13] = 0;

    hasieratu();
    
    while (irten == 0) {

        /*--------------------------------MENU PRINTZIPALA-------------------------------*/

        if (egoera == MENUPRINTZIPALA) {

            if (musika == 0) {
                audioTerminate();
                audioInit();
                loadTheMusic(".\\sound\\ost1.wav");
                playMusic();
                musika = 1;
            }
            SDL_ShowCursor(SDL_ENABLE);
            if (idDictador == -1) {
                idDictador = irudiaKargatu(".\\img\\Dictador.bmp");
                idSombra = irudiaKargatu(".\\img\\FondoSombra.bmp");
                idTitulo = irudiaKargatu(".\\img\\Titulo.bmp");
                idEslogan = irudiaKargatu(".\\img\\eslogan.bmp");
                idFondo = irudiaKargatu(".\\img\\Fondo.bmp");
                idFranjas = irudiaKargatu(".\\img\\Franjas.bmp");
                idBotones = irudiaKargatu(".\\img\\Botones.bmp");
                idHumo = irudiaKargatu(".\\img\\Humo.bmp");
                idMapa = irudiaKargatu(".\\img\\Minimapa.bmp");
                mobs[0].id = irudiaKargatu(".\\img\\etsaiak\\Etsaiak.bmp");
                mobs[10].id = irudiaKargatu(".\\img\\Dictadores\\Ronda1.bmp");
                mobs[11].id = irudiaKargatu(".\\img\\Dictadores\\Ronda2.bmp");
                mobs[12].id = irudiaKargatu(".\\img\\Dictadores\\Ronda3.bmp");
                mobs[13].id = irudiaKargatu(".\\img\\Dictadores\\Ronda4.bmp");
                mobs[14].id = irudiaKargatu(".\\img\\Dictadores\\Ronda5.bmp");
                mobs[15].id = irudiaKargatu(".\\img\\Dictadores\\Ronda6.bmp");
                mobs[16].id = irudiaKargatu(".\\img\\Dictadores\\Ronda7.bmp");
                mobs[17].id = irudiaKargatu(".\\img\\Dictadores\\Ronda8.bmp");
                mobs[18].id = irudiaKargatu(".\\img\\Dictadores\\Ronda9.bmp");
                mobs[19].id = irudiaKargatu(".\\img\\Dictadores\\Ronda10.bmp");
            }
          
            srand(time(NULL));
            RandNum = rand() % 10;

            pantailaGarbitu();

            while (!irten) {

                egoera = menua(idFondo, idSombra, idDictador, idTitulo, idEslogan, idBotones, idFranjas, idHumo, RandNum);
                ebentu = ebentuaJasoGertatuBada();
                pantailaBerriztu();

                if (ebentu == TECLA_ESCAPE || egoera)
                    irten = 1;
            }
            irten = 0;
        }

        /*--------------------------------------JOKOA------------------------------------*/

        if (egoera == JOKOA) {
            tutoriala = 0;
            if (idSpriteSheet == -1) {
                idSpriteSheet = irudiaKargatu(".\\img\\SpriteSheet.bmp");
                idInterfaz = irudiaKargatu(".\\img\\interfaz.bmp");
                idArma = irudiaKargatu(".\\img\\ArmaSpriteSheet.bmp");
                idBarra = irudiaKargatu(".\\img\\barra.bmp");
                idBihotza = irudiaKargatu(".\\img\\corazon.bmp");
                idReticula = irudiaKargatu(".\\img\\reticula.bmp");
                idRonda = irudiaKargatu(".\\img\\RondaBukatu\\Ronda.bmp");
                idRonda = irudiaKargatu(".\\img\\RondaBukatu\\Ronda.bmp");
                idArmaSelekzioaE = irudiaKargatu(".\\img\\menus\\seleccion_armas\\MenuArmasSpriteSheetEus.bmp");
                idArmaSelekzioaC = irudiaKargatu(".\\img\\menus\\seleccion_armas\\MenuArmasSpriteSheetCas.bmp");
                idArmaSelekzioaI = irudiaKargatu(".\\img\\menus\\seleccion_armas\\MenuArmasSpriteSheetIng.bmp");
                idPausaE = irudiaKargatu(".\\img\\menus\\pause\\pausa_E.bmp");
                idPausaC = irudiaKargatu(".\\img\\menus\\pause\\pausa_C.bmp");
                idPausaI = irudiaKargatu(".\\img\\menus\\pause\\pausa_I.bmp");
                idTutorialaE = irudiaKargatu(".\\img\\menus\\tutoriala\\TUTORIAL_E.bmp");
                idTutorialaC = irudiaKargatu(".\\img\\menus\\tutoriala\\TUTORIAL_C.bmp");
                idTutorialaI = irudiaKargatu(".\\img\\menus\\tutoriala\\TUTORIAL_I.bmp");
            }

            Pertsonaia.x = 600;
            Pertsonaia.y = 600;
            Pertsonaia.angelua = 3 * PI / 2;
            Pertsonaia.IkusBertikala = 0;
            Pertsonaia.health = 100;

            if (Hizkuntza == 0) {
                idPausa = idPausaE;
                idArmaSelekzioa = idArmaSelekzioaE;
                idTutoriala = idTutorialaE;
            }
            if (Hizkuntza == 1) {
                idPausa = idPausaC;
                idArmaSelekzioa = idArmaSelekzioaC;
                idTutoriala = idTutorialaC;
            }
            if (Hizkuntza == 2) {
                idPausa = idPausaI;
                idArmaSelekzioa = idArmaSelekzioaI;
                idTutoriala = idTutorialaI;
            }

            bai = 0;
            Ronda[0] = 0;
            Ronda[1] = 0;
            Ronda[2] = 1;

            SDL_ShowCursor(SDL_DISABLE);

            while (!irten) {

                pantailaGarbitu();
                lurra();

                ebentu = ebentuaJasoGertatuBada();
                Pos = PosizioZehastu(Pertsonaia.x, Pertsonaia.y, mapaX, mapaY, mapaS, Mapa);

                if (Ronda[2] && (Ronda[0] == 0 || Ronda[0] == 3 || Ronda[0] == 7)) {
                    Pertsonaia.arma = armaSelekzioa(Ronda[0], idArmaSelekzioa);//menu de selección de arma
                    Armak[5] = Armak[14];
                    armaEzaugarriak(Pertsonaia.arma, Armak);
                    SDL_ShowCursor(SDL_DISABLE);
                }
                
                PertsonaiaMarraztu(mapaX, mapaY, mapaS, Mapa, ebentu, Pos);
                kamaraMugitu();
                Mobs(Mapa, mapaX, mapaY, mapaS, Ronda);
                MobsEzaugarriak(Ronda);
                RayCasting(Mapa, mapaX, mapaY, mapaS, Pos, idSpriteSheet, Ronda[1]);
                MapaMarraztu(mapaX, mapaY, 25, Mapa, Ronda, idMapa);

                //-----------INTERFAZ-----------//
                interfaz(idInterfaz);
                bai = ArmaMarraztu(Armak, ebentu, bai, Ronda[1], Ronda);
                ArmaMunizioa(Armak, bai);
                LaVida(idBarra, idBihotza);

                if(idAlerta == -1)
                    idAlerta = loadSound(".\\sound\\CambioDeRonda.wav");
                Rondak(Ronda, idRonda, idAlerta);

                IrudiarenDimentzioakDst(idReticula, ((PantailaLuzeera() / 2) - 18), ((PantailaAltuera() / 2) - 18), 36, 36);
                IrudiarenDimentzioakSrc(idReticula, 0, 0, 36, 36);

                if (state[SDL_SCANCODE_P]) {//PAUSA MENUA
                    egoera = pausaMenua(idPausa);
                    if (egoera == 5)
                        irten = 1;
                    if (egoera == 0)
                        irten = 1;
                }
                
                if (Ronda[0] == 11) {//IRABAZI DUZU
                    irten = 1;
                    egoera = 6;
                }

                if (Pertsonaia.health <= 0) {//HIL ZARA
                    irten = 1;
                    egoera = 7;
                    idHil = loadSound(".\\sound\\ownDead.wav");
                    playSound(1, idHil);
                }
                
                pantailaBerriztu(); 

                if (tutoriala == 0) {
                    IrudiarenDimentzioakDst(idTutoriala, 0, 0, PantailaLuzeera(), PantailaAltuera());
                    IrudiarenDimentzioakSrc(idTutoriala, 0, 0, 1920, 1080);
                    pantailaBerriztu();
                    delay(5);
                    tutoriala = 1;
                }
            }
            irten = 0;
        }

        /*-------------------------------------AUKERAK-----------------------------------*/

        if (egoera == AUKERAK) {

            if (Hizkuntza == 0)
                idAukerak = irudiaKargatu(".\\img\\menus\\ajustes\\ajustes_E.bmp");
            if (Hizkuntza == 1)
                idAukerak = irudiaKargatu(".\\img\\menus\\ajustes\\ajustes_C.bmp");
            if (Hizkuntza == 2)
                idAukerak = irudiaKargatu(".\\img\\menus\\ajustes\\ajustes_I.bmp");

            egoera = aukerakMenu(idAukerak);
        }

        /*------------------------------------KREDITUAK----------------------------------*/

        if(egoera==KREDITUAK){
            egoera = kreditoakMenu();
        }

        /*---------------------------------------LORE------------------------------------*/

        if (egoera == LORE) {

            if (Hizkuntza == 0)
                idLore = irudiaKargatu(".\\img\\menus\\lore\\LoreSpriteSheetEus.bmp");
            if (Hizkuntza == 1)
                idLore = irudiaKargatu(".\\img\\menus\\lore\\LoreSpriteSheetCas.bmp");
            if (Hizkuntza == 2)
                idLore = irudiaKargatu(".\\img\\menus\\lore\\LoreSpriteSheetIng.bmp");

            egoera = loreaErakutsi(idLore);
        }

        /*-----------------------------------WINNER MENUA--------------------------------*/

        if (egoera == WINNER) {
            if (idWinner == -1)
                idWinner = irudiaKargatu(".\\img\\menus\\Bukaera\\Winner.bmp");
            if(idAmaiera == -1)
                idAmaiera = irudiaKargatu(".\\img\\menus\\Bukaera\\BOTONLOSEIZKIERDOS.bmp");
            
            egoera = BukaeraIrabazle(idWinner, Ronda[0] - 1, idAmaiera);
            musika = 0;
        }

        /*-----------------------------------LOOSER MENU---------------------------------*/

        if (egoera == LOOSER) {
            if(idAmaiera == -1)
                idAmaiera = irudiaKargatu(".\\img\\menus\\Bukaera\\BOTONLOSEIZKIERDOS.bmp");
            if (idLooser == -1) {
                idLooser = irudiaKargatu(".\\img\\menus\\Bukaera\\LooserMenu.bmp");
                idLooserStats = irudiaKargatu(".\\img\\menus\\Bukaera\\LooserStats.bmp");
            }

            egoera = BukaeraLooser(idAmaiera, idLooser, idLooserStats, Ronda[0]);
            musika = 0;
        }

        /*----------------------------------PROGRMAMA ITXI-------------------------------*/

        if (egoera == BUKATU) {

            sgItxi();
            irten = 1;
        }
    }

    return 0;
}