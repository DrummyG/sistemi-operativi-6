//
// Created by Davide Balestrino on 16/12/24.
//

#include "padre.h"

void padreFun(int p[2]){
    struct personaggio c, v, r, t[NBOMBS], tl[NBOMBS]; // Contadino, Vespa, Trappola, Ultime trappole
    int vite = 3, contatore = BOMB, immunity = IMMUNITY; // Vite, Contatore aggiornamento bombe, Immunità dopo colpo
    c.t = CONTADINO; v.t = VESPA;
    c.x = 0; c.y = 0;
    v.x = COLS - 2; v.y = LINES - 1;
    bool flag = true; // Flag per il controllo delle trappole
    srand(time(NULL));

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    for(int i = 0; i < NBOMBS; i++){
        t[i].x = rand() % max_x;
        t[i].y = rand() % max_y;
    }

    clock_t start = clock(); // Inizio del gioco

    while(true){
        read(p[0], &r, sizeof(struct personaggio));

        if(r.t == CONTADINO){
            mvaddch(c.y, c.x, ' '); // Contadino
            c = r;
            mvaddch(c.y, c.x, 'C'); // Contadino
        }else if(r.t == VESPA){
            mvaddch(v.y, v.x, ' '); // Vespa
            v = r;
            mvaddch(v.y, v.x, 'V'); // Vespa
        }

        if(c.x == v.x && c.y == v.y && immunity <= 0) { // Controlla se il contadino è stato colpito
            vite--; // Decrementa le vite
            immunity = IMMUNITY; // Imposta l'immunità
            if (vite == 0) { // Se le vite sono finite
                clock_t end = clock();
                double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
                clear();
                mvprintw(max_y / 2 - 20, max_x / 2 - 10, "Hai perso\nTempo trascorso: %.2f secondi\n", elapsed_time); // Stampa il tempo trascorso
                usleep(MESSAGE);
                break;
            }
        }

        for(int i = 0; i < NBOMBS; i++){ // Controlla se la vespa è su una trappola
            if(v.x == t[i].x && v.y == t[i].y){ // Se la vespa è su una trappola
                if (vite < NVITE){ // Se le vite sono minori di 6
                    vite++; // Incrementa le vite
                }
            }
        }

        if(contatore == 0){ // Se il contatore è arrivato a 0
            contatore = BOMB; // Resetta il contatore
            for(int i = 0; i < NBOMBS; i++){
                mvaddch(t[i].y, t[i].x, ' '); // Trappola
                tl[i] = t[i]; // Salva le ultime trappole
            }
            flag = true;
            while(flag){
                flag = false;
                for(int i = 0; i < NBOMBS; i++){
                    t[i].x = rand() % max_x;
                    t[i].y = rand() % max_y;
                    for(int j = 0; j < NBOMBS; j++){
                        if(t[i].x == tl[j].x && t[i].y == tl[j].y){ // Se la trappola è in una vecchia posizione
                            flag = true; //ripeto il ciclo
                        }
                    }
                }
            }
        }

        for(int i = 0; i < NBOMBS; i++){
            mvaddch(t[i].y, t[i].x, '#'); // Trappola
        }

        clock_t now = clock();
        double elapsed_time = (double)(now - start) / CLOCKS_PER_SEC * 100;
        mvprintw(max_y, max_x - 40, "Vite rimaste: %d || tempo: %.2f", vite, elapsed_time); // Stampa le vite rimaste e il tempo
        contatore--;
        immunity--;
        refresh();
    }

}