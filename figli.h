//
// Created by Davide Balestrino on 16/12/24.
//

#ifndef SO_7_FIGLI_H
#define SO_7_FIGLI_H

#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define NMOVES 10
#define NBOMBS 3
#define UDELAY 100000

typedef enum {CONTADINO, VESPA} tipo;

struct personaggio{
    int x;
    int y;
    tipo t;
};

void contadinoFun(int giocatore[2]);
void vespaFun(int vespa[2]);

void controllo(struct personaggio *p, int dirx, int diry);
int movRandom();

#endif //SO_7_FIGLI_H
