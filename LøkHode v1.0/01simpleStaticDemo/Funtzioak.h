#ifndef FUNTZIOAK_H
#define FUNTZIOAK_H
#include "SDL.h"

/*----------------------------------------MENUA-----------------------------------------------*/

int menua(int idFondo, int idSombra, int idDictador, int idTitulo, int idEslogan, int idHasi, int idFranjas, int idHumo, int RandNum);

/*-------------------------------------BUKAERA MENUAK-----------------------------------------*/

int BukaeraIrabazle(int idWinner, int Ronda, int idAmaiera);
int BukaeraLooser(int idAmaiera, int idLooser, int idLooserStats, int Ronda);

/*----------------------------------------Rondak----------------------------------------------*/

void Rondak(int Ronda[], int idRonda, int idAlerta);
void delay(float number_of_seconds);

/*---------------------------------------MOBS----------------------------------------------*/

void Mobs(int Mapa[], int mapaX, int mapaY, int mapaS, int Ronda[]);

void PosizioAleatorioa(int Mapa[], int mapaX, int mapaY, int mapaS, int Moba);
void MobMarraztu(int Mapa[], int mapaX, int mapaY, int mapa, int Moba, int Ronda[]);

int PathFinding(int Mapa[], int mapaX, int mapaY, int mapaS, int HasieraPos, int AmaieraPos, int Mugimendua[], int Moba);
void ArrayGarbitu(int b[]);
int PosizioaBilatu(int MapaEsc[], int Pos);

/*-------------------------------------INTERFAZEA---------------------------------------------*/

void interfaz(int idInterfaz);
void LaVida(int barra, int bihotza);

/*-------------------------------------FUNTZIOAK---------------------------------------------*/

void Marraztu(int px, int py);
void MapaMarraztu(int mapaX, int mapaY, int mapaS, int Mapa[], int Ronda[], int idMapa);
int PosizioZehastu(float X, float Y, int mapaX, int mapaY, int mapaS, int Mapa[]);

void MobsEzaugarriak(int Ronda[]);
void ArrayBete(int Etsailak[], int EtsaiKop);
void KapenOrdenaZehastu(int EtsaiKop, int Etsaiak[]);
void RayCasting(int Mapa[], int mapaX, int mapaY, int mapaS, int Pos, int idSpriteSheet, int EtsaiKop);
void Irudikatu(int Kont, int EtsaiKop, float angelua, int luzeera, int idSpriteSheet, int n, float HasierakoAngelua);
int PantailaAltuera(void);
int PantailaLuzeera(void);

/*--------------------------------------PERTSONAIA----------------------------------------------*/

void PertsonaiaMarraztu(int mapaX, int mapaY, int mapaS, int Mapa[], int ebentu, int Pos);

int EzkerrekoKolisioa(int Mapa[], int Pos, int mapaX, int mapaY, int mapaS);
int EskuinekoKolisioa(int Mapa[], int Pos, int mapaX, int mapaY, int mapaS);
int GoikoKolisioa(int Mapa[], int Pos, int mapaX, int mapaY, int mapaS);
int BehekoKolisioa(int Mapa[], int Pos, int mapaX, int mapaY, int mapaS);

void kamaraMugitu(void);

/*---------------------------------------ARMAK------------------------------------------------*/

void armaEzaugarriak(int armaAukeratuta, float propietateak[]);

int ArmaMarraztu(float propietateak[], int tiroa, int bai, int MobKpurua, int Ronda[]);
void ArmaMunizioa(float propietateak[], int bai);

void Tiroa(int MobKopurua, int Ronda[]);

/*--------------------------------------ARMA MENUA----------------------------------------*/

int armaSelekzioa(int Ronda, int idArmaSelekzioa);

/*----------------------------------------LORE------------------------------------------------*/

int loreaErakutsi(int idLore);

/*--------------------------------------AUKERAK-----------------------------------------------*/

int aukerakMenu(int idAukerak);

/*--------------------------------------KREDITUAK---------------------------------------------*/

int kreditoakMenu(void);

/*------------------------------------------PAUSA---------------------------------------------*/

int pausaMenua(int id);

#endif