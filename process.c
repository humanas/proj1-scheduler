#include <string.h>

// Tabela de estado de processo
#define PROC_STATE_NEW 0
#define PROC_STATE_READY 1
#define PROC_STATE_BLOCKED 2
#define PROC_STATE_EXECUTING 3
#define PROC_STATE_FINISHED 4

// definição de processo
struct process_t {
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
};

typedef struct process_t proc;

// cria um processo
proc * createProc(int id, int proctime, int prior) {
    proc * p = (proc*) malloc (sizeof(proc));
    p->prior = 3;
    p->proctime = proctime;
    p->prior = prior;
    p->counter = 0;
    p->state = PROC_STATE_NEW;
}