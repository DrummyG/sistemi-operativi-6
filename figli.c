//
// Created by Davide Balestrino on 16/12/24.
//

#include "figli.h"

void controllo(struct personaggio *p, int dirx, int diry){
    // Controllo dei limiti
    p->x += dirx;
    p->y += diry;

    if (p->x < 0) p->x = 0;
    if (p->x >= COLS) p->x = COLS - 2;
    if (p->y < 0) p->y = 0;
    if (p->y >= LINES) p->y = LINES - 1;
}

void contadinoFun(int giocatore[2]){
    struct personaggio p; // Contadino
    p.x = 0; p.y = 0; p.t = CONTADINO;
    int dirx = 0, diry = 0;          // Direzioni iniziali
    int c;                           // Input da tastiera

    while (true) {
        // Leggi l'input da tastiera
        c = getch();
        switch (c) {
            case KEY_DOWN: diry = 1; dirx = 0; break; // Muovi giù
            case KEY_UP: diry = -1; dirx = 0; break; // Muovi su
            case KEY_LEFT: dirx = -2; diry = 0; break; // Muovi sinistra
            case KEY_RIGHT: dirx = 2; diry = 0; break; // Muovi destra
        }

        controllo(&p, dirx, diry); // Controlla i limiti

        // Scrivi le coordinate nella pipe
        write(giocatore[1], &p, sizeof(struct personaggio));
        dirx = 0; diry = 0; // Resetta le direzioni

        usleep(UDELAY); // Ritardo per il movimento fluido
    }
}

int movRandom() {
    int r = rand() % 4;
    return r;
}

void vespaFun(int vespa[2]){
    struct personaggio v; // Vespa
    v.x = COLS - 2; v.y = LINES - 1; v.t = VESPA;
    int dirx = 0, diry = -1, dir, c = 0;
    srand(time(NULL));
    while(true){
        if(c == NMOVES){
            c = 0; // Resetta il contatore
            dir = movRandom(); // Genera una direzione casuale
            switch (dir) { // Assegna la direzione
                case 0: diry = 1; dirx = 0; break; // Muovi giù
                case 1: diry = -1; dirx = 0; break; // Muovi su
                case 2: dirx = -2; diry = 0; break; // Muovi sinistra
                case 3: dirx = 2; diry = 0; break; // Muovi destra
            }
        }

        controllo(&v, dirx, diry); // Controlla i limiti

        write(vespa[1], &v, sizeof(struct personaggio));
        c++;

        usleep(UDELAY);
    }
}