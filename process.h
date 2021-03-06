#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tabela de estado de processo
#define PROC_STATE_NEW 0
#define PROC_STATE_READY 1
#define PROC_STATE_BLOCKED 2
#define PROC_STATE_EXECUTING 3
#define PROC_STATE_FINISHED 4

#define PROC_MIN_TIME 5
#define PROC_MAX_TIME 100
#define PROC_MIN_PRIOR 1
#define PROC_MAX_PRIOR 5

// Último ID global
int last_id = -1;

// definição de processo
typedef struct process_t {
    // ID do processo
    int id;
    // conta quantas vezes o processo passou pela CPU
    int counter;
    // tempo restante para o processo ser concluído
    int proctime;
    // prioridade do processo
    int prior;
    // guarda o estado do processo
    int state;

    // estrutura da fila
    struct process_t * next;
} proc;

// cria um processo
proc * createProcess(int proctime, int prior) {
    proc * p = (proc*) malloc (sizeof(proc));
    p->id = (++last_id);
    p->proctime = proctime;
    p->prior = prior;
    p->counter = 0;
    p->state = PROC_STATE_NEW;
    p->next = NULL;
    return p;
}

proc * createRandomProcess() {
    int period = rand() % (PROC_MAX_TIME - PROC_MIN_TIME) + PROC_MIN_TIME;
    int prior = rand() % (PROC_MAX_PRIOR - PROC_MIN_PRIOR) + PROC_MIN_PRIOR;
    return createProcess(period, prior);
}

void printProcess(proc * p) {
    printf("| id: %d | counter: %d | time: %d | prior: %d | state: %d |\n", p->id, p->counter, p->proctime, p->prior, p->state);
}