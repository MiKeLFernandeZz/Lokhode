#ifndef SOINUA_H
#define SOINUA_H

#define MAX_SOUNDS 100

#include <SDL_mixer.h>

void audioInit();
int loadSound(char *fileName);
int loadTheMusic(char *fileName);
int playSound(int channel, int idSound);
int playMusic(void);
void toggleMusic(void);
void soundsUnload();
void audioTerminate();



#endif