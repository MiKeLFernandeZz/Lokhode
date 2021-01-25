#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#include "graphics.h"
#include "ebentoak.h"
#include "soinua.h"
#include "text.h"
#include "imagen.h"

#include "OurTypes.h"
#include "Funtzioak.h"

#define PI 3.1415926

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
extern int sensibilitateMoldatzaile;
extern float Proportzioa;

//--------------------------------------------------COLISIONES---------------------------------------------//

int EzkerrekoKolisioa(int Mapa[], int Pos, int mapaX, int mapaY, int mapaS) {
    int x, irten = 0;

    while (irten == 0) {
        if (Mapa[Pos - 1] != 0) {
            x = (Pos % mapaX) * mapaS;
            irten = 1;
        } else
            Pos--;
    }

    return x;//x posizioa bat bueltatu
}

int EskuinekoKolisioa(int Mapa[], int Pos, int mapaX, int mapaY, int mapaS) {
    int x, irten = 0;

    while (irten == 0) {
        if (Mapa[Pos + 1] != 0) {
            x = ((Pos + 1) % mapaX) * mapaS;
            irten = 1;
        } else
            Pos++;
    }
    
    return x;//x posizioa bat bueltatu
}

int GoikoKolisioa(int Mapa[], int Pos, int mapaX, int mapaY, int mapaS) {
    int y, irten = 0;

    while (irten == 0) {
        if (Mapa[Pos - mapaX] != 0) {
            y = (Pos / mapaX) * mapaS;
            irten = 1;
        } else
            Pos = Pos - mapaX;
    }
    
    return y;//y posizioa bat bueltatu
}

int BehekoKolisioa(int Mapa[], int Pos, int mapaX, int mapaY, int mapaS) {
    int y, irten = 0;

    while (irten == 0) {
        if (Mapa[Pos + mapaX] != 0) {
            y = ((Pos + mapaX) / mapaX) * mapaS;
            irten = 1;
        } else
            Pos = Pos + mapaX;
    }
    

    return y;//y posizioa bat bueltatu
}

/*----------------------------------------MOVIMIENTO DEL PERSONAJE---------------------------------*/

void PertsonaiaMarraztu(int mapaX, int mapaY, int mapaS, int Mapa[], int ebentu, int Pos) {
    int GoiKolisioa, BeheKolisioa, EzkerKolisioa, EskuinKolisioa;
    float espeed = 0.3;
    const Uint8* state = SDL_GetKeyboardState(NULL);

    GoiKolisioa = GoikoKolisioa(Mapa, Pos, mapaX, mapaY, mapaS);
    BeheKolisioa = BehekoKolisioa(Mapa, Pos, mapaX, mapaY, mapaS);
    EskuinKolisioa = EskuinekoKolisioa(Mapa, Pos, mapaX, mapaY, mapaS);
    EzkerKolisioa = EzkerrekoKolisioa(Mapa, Pos, mapaX, mapaY, mapaS);

    //Zein koadrantean begira dagoen kolisioak baldintzatzen

    //-------------------------------ABAJO DERECHA---------------------------//

    if (cos(Pertsonaia.angelua) >= 0 && sin(Pertsonaia.angelua) >= 0) {
        if (state[SDL_SCANCODE_W]  && Pertsonaia.x + 5 < EskuinKolisioa && Pertsonaia.y + 5 < BeheKolisioa) {
            Pertsonaia.x = Pertsonaia.x + espeed * cos(Pertsonaia.angelua);
            Pertsonaia.y = Pertsonaia.y + espeed * sin(Pertsonaia.angelua);
        }
            
        if (state[SDL_SCANCODE_S] && Pertsonaia.x - 5 > EzkerKolisioa && Pertsonaia.y - 5 > GoiKolisioa) {
            Pertsonaia.x = Pertsonaia.x + espeed * cos(Pertsonaia.angelua + PI);
            Pertsonaia.y = Pertsonaia.y + espeed * sin(Pertsonaia.angelua + PI);
        }
            
        if (state[SDL_SCANCODE_A] && Pertsonaia.x + 5 < EskuinKolisioa && Pertsonaia.y - 5 > GoiKolisioa) {
            Pertsonaia.x = Pertsonaia.x + (espeed / 2) * cos(Pertsonaia.angelua - PI / 2);
            Pertsonaia.y = Pertsonaia.y + (espeed / 2) * sin(Pertsonaia.angelua - PI / 2);
        }

        if (state[SDL_SCANCODE_D] && Pertsonaia.x - 5 > EzkerKolisioa && Pertsonaia.y + 5 < BeheKolisioa) {
            Pertsonaia.x = Pertsonaia.x + (espeed / 2) * cos(Pertsonaia.angelua + PI / 2);
            Pertsonaia.y = Pertsonaia.y + (espeed / 2) * sin(Pertsonaia.angelua + PI / 2);
        }
    }

    //------------------------------ABAJO IZQUIERDA--------------------------//

    if (cos(Pertsonaia.angelua) < 0 && sin(Pertsonaia.angelua) >= 0) {
        if (state[SDL_SCANCODE_W] && Pertsonaia.x - 5 > EzkerKolisioa && Pertsonaia.y + 5 < BeheKolisioa) {
            Pertsonaia.x = Pertsonaia.x + espeed * cos(Pertsonaia.angelua);
            Pertsonaia.y = Pertsonaia.y + espeed * sin(Pertsonaia.angelua);
        }
            
        if (state[SDL_SCANCODE_S] && Pertsonaia.x + 5 < EskuinKolisioa && Pertsonaia.y - 5 > GoiKolisioa) {
            Pertsonaia.x = Pertsonaia.x + espeed * cos(Pertsonaia.angelua + PI);
            Pertsonaia.y = Pertsonaia.y + espeed * sin(Pertsonaia.angelua + PI);
        }
            
        if (state[SDL_SCANCODE_A] && Pertsonaia.x + 5 < EskuinKolisioa && Pertsonaia.y + 5 < BeheKolisioa) {
            Pertsonaia.x = Pertsonaia.x + (espeed / 2) * cos(Pertsonaia.angelua - PI / 2);
            Pertsonaia.y = Pertsonaia.y + (espeed / 2) * sin(Pertsonaia.angelua - PI / 2);
        }
            
        if (state[SDL_SCANCODE_D] && Pertsonaia.x - 5 > EzkerKolisioa && Pertsonaia.y - 5 > GoiKolisioa) {
            Pertsonaia.x = Pertsonaia.x + (espeed / 2) * cos(Pertsonaia.angelua + PI / 2);
            Pertsonaia.y = Pertsonaia.y + (espeed / 2) * sin(Pertsonaia.angelua + PI / 2);
        }
    }

    //----------------------------ARRIBA IZQUIERDA--------------------------//

    if (cos(Pertsonaia.angelua) < 0 && sin(Pertsonaia.angelua) < 0) {
        if (state[SDL_SCANCODE_W] && Pertsonaia.x - 5 > EzkerKolisioa && Pertsonaia.y - 5 > GoiKolisioa) {
            Pertsonaia.x = Pertsonaia.x + espeed * cos(Pertsonaia.angelua);
            Pertsonaia.y = Pertsonaia.y + espeed * sin(Pertsonaia.angelua);
        }
            
        if (state[SDL_SCANCODE_S] && Pertsonaia.x + 5 < EskuinKolisioa && Pertsonaia.y + 5 < BeheKolisioa) {
            Pertsonaia.x = Pertsonaia.x + espeed * cos(Pertsonaia.angelua + PI);
            Pertsonaia.y = Pertsonaia.y + espeed * sin(Pertsonaia.angelua + PI);
        }
            
        if (state[SDL_SCANCODE_A] && Pertsonaia.x - 5 > EzkerKolisioa && Pertsonaia.y + 5 < BeheKolisioa) {
            Pertsonaia.x = Pertsonaia.x + (espeed / 2) * cos(Pertsonaia.angelua - PI / 2);
            Pertsonaia.y = Pertsonaia.y + (espeed / 2) * sin(Pertsonaia.angelua - PI / 2);
        }
            
        if (state[SDL_SCANCODE_D] && Pertsonaia.x + 5 < EskuinKolisioa && Pertsonaia.y - 5 > GoiKolisioa) {
            Pertsonaia.x = Pertsonaia.x + (espeed / 2) * cos(Pertsonaia.angelua + PI / 2);
            Pertsonaia.y = Pertsonaia.y + (espeed / 2) * sin(Pertsonaia.angelua + PI / 2);
        }
    }

    //------------------------ARRIBA DERECHA--------------------------//

    if (cos(Pertsonaia.angelua) >= 0 && sin(Pertsonaia.angelua) < 0) {
        if (state[SDL_SCANCODE_W] && Pertsonaia.x + 5 < EskuinKolisioa && Pertsonaia.y - 5 > GoiKolisioa) {
            Pertsonaia.x = Pertsonaia.x + espeed * cos(Pertsonaia.angelua);
            Pertsonaia.y = Pertsonaia.y + espeed * sin(Pertsonaia.angelua);
        }
            
        if (state[SDL_SCANCODE_S] && Pertsonaia.x - 5 > EzkerKolisioa && Pertsonaia.y + 5 < BeheKolisioa) {
            Pertsonaia.x = Pertsonaia.x + espeed * cos(Pertsonaia.angelua + PI);
            Pertsonaia.y = Pertsonaia.y + espeed * sin(Pertsonaia.angelua + PI);
        }
            
        if (state[SDL_SCANCODE_A] && Pertsonaia.x - 5 > EzkerKolisioa && Pertsonaia.y - 5 > GoiKolisioa) {
            Pertsonaia.x = Pertsonaia.x + (espeed / 2) * cos(Pertsonaia.angelua - PI / 2);
            Pertsonaia.y = Pertsonaia.y + (espeed / 2) * sin(Pertsonaia.angelua - PI / 2);
        }
            
        if (state[SDL_SCANCODE_D] && Pertsonaia.x + 5 < EskuinKolisioa && Pertsonaia.y + 5 < BeheKolisioa) {
            Pertsonaia.x = Pertsonaia.x + (espeed / 2) * cos(Pertsonaia.angelua + PI / 2);
            Pertsonaia.y = Pertsonaia.y + (espeed / 2) * sin(Pertsonaia.angelua + PI / 2);
        }  
    }
}

void kamaraMugitu(void) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    //Kamara mugimendua x ardatzean
    if (x < (PantailaLuzeera() / 2))
        Pertsonaia.angelua -= 0.0002 * sensibilitateMoldatzaile;

    if (x > (PantailaLuzeera() / 2))
        Pertsonaia.angelua += 0.0002 * sensibilitateMoldatzaile;

    //Kamara mugimendua y ardatzean
    if (y < (PantailaAltuera() / 2) && Pertsonaia.IkusBertikala < 600)
        Pertsonaia.IkusBertikala += 10;

    if (y > (PantailaAltuera() / 2) && Pertsonaia.IkusBertikala > -600)
        Pertsonaia.IkusBertikala -= 10;

    //Angelua zuzendu
    if (Pertsonaia.angelua > 2 * PI)
        Pertsonaia.angelua = 0;

    if (Pertsonaia.angelua < 0)
        Pertsonaia.angelua = 2 * PI;

    SetCursorPos(PantailaLuzeera() / 2, PantailaAltuera() / 2);
}
