#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "scheduler.h"

#define N 500

int main() {
    srand(time(NULL));
    // Criou o escalonador
    schd * s = createScheduler(15);
    // coloca processo na fila de jobs
    for (int i = 0; i < 50; i++) {
        proc * p = createRandomProcess();
        addProcess(s, p);
    }
    printf("Todos os Jobs:\n");
    foreach (p, s->jobs) {
        printProcess(p);
    }
    getchar();
    printf("--------------------------------------------------------------------------\n");
    // Preenche a fila de pronto
    fillReady(s);
    while (!isEmpty(s->ready) || !isEmpty(s->jobs) || !isEmpty(s->blocked)) {
        if (! executeNext(s, 20)) {
            printf("Deu erro!\n");
        }

        // Printa PCB
        printf("Jobs:\n");
        foreach (p, s->jobs) {
            printProcess(p);
        }
        printf("Pronto:\n");
        foreach (p, s->ready) {
            printProcess(p);
        }
        printf("Dispositivos:\n");
        foreach (p, s->blocked) {
            printProcess(p);
        }
        printf("Encerrados:\n");
        foreach(p, s->finished) {
            printProcess(p);
        }
        getchar();
        printf("--------------------------------------------------------------------------\n");
    }

    return 0;
}