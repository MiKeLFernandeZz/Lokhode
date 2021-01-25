#ifndef IMAGEN_H
#define IMAGEN_H

#define MAX_IMG 1000

int  irudiaKargatu(char *fileName);
void irudiaMugitu(int numImg, int x, int y);
void irudiakMarraztu(void);
void irudiaKendu(int id);
void IrudiarenDimentzioakDst(int id, int x0, int y0, int x, int y);
void IrudiarenDimentzioakSrc(int id, int x0, int y0, int x, int y);

#endif
