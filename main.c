#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "padre.h"



int main() {
    int p[2];
    pid_t pid, pid2; // Crea la pipe, fornendo i file descriptors in "pipe_fds"
    if(pipe(p) == -1) {
        // Scrive su stderr, ma include la descrizione dell'ultimo errore che si è presentato
        perror("Pipe call");
        exit(1);
    }

    initscr();
    noecho();
    curs_set(0);
    cbreak();
    nodelay(stdscr, true);
    keypad(stdscr, true);

    pid=fork();
    if(pid < 0) {
        perror("fork call"); _exit(2);
    }else if (pid == 0) { // Processo figlio
        close(p[0]); // Chiusura lettura, il figlio scrive
        contadinoFun(p);
    }

    pid2=fork();
    if(pid2 < 0) {
        perror("fork call"); _exit(3);
    }else if (pid2 == 0) { // Processo figlio
        close(p[0]); // Chiusura lettura, il figlio scrive
        vespaFun(p);
    }else { // Processo padre
        close(p[1]);
    }

    padreFun(p);
    kill(pid, SIGKILL);
    kill(pid2, SIGKILL);

    return 0;
}

