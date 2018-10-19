#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

#include "helper.h"

// Escalonador de processos
typedef struct scheduler {
    queue * jobs; // Fila de jobs
    queue * ready; // Fila de pronto
    queue * blocked; // Fila de dispositivos
    queue * finished; // Fila de encerrados
    proc * exec; // Processo em execução
    int ready_limit;
} schd;

schd * createScheduler(int ready_limit);

void addProcess(schd * s, proc * p);
void fillReady(schd * s);
void blockProcess(schd * s);
void finishProcess(schd * s);
void returnToReady(schd * s);

int executeNext(schd * s, int quantum);

// 'Construtor' do escalonador
schd * createScheduler(int ready_limit) {
    schd * newer = (schd *) malloc (sizeof(schd));
    // Cria as filas
    newer->jobs = createQueue();
    newer->ready = createQueue();
    newer->blocked = createQueue();
    newer->finished = createQueue();
    // Nenhum processo em execução
    newer->exec = NULL;
    newer->ready_limit = ready_limit;
    return newer;
}

// Enche a fila de pronto
void fillReady(schd * s) {
    while (s->ready->size != s->ready_limit) {
        queueTranferProcess(s->jobs, s->ready);
        s->ready->last->state = PROC_STATE_READY;
    }
}

// Bloqueia o processo em execução
void blockProcess(schd * s) {
    s->exec->state = PROC_STATE_BLOCKED;
    queuePushProcess(s->blocked, s->exec);
    s->exec = NULL;
}

// Finaliza o processo em execução
void finishProcess(schd * s) {
    s->exec->state = PROC_STATE_FINISHED;
    queuePushProcess(s->finished, s->exec);
    s->exec = NULL;
}

// Recoloca o processo em execução na fila de pronto
void returnToReady(schd * s) {
    s->exec->state = PROC_STATE_READY;
    queuePushProcess(s->ready, s->exec);
    s->exec = NULL;
}

// Executa o próximo processo da fila de pronto
int executeNext(schd * s, int quantum) {
    if (!isEmpty(s->blocked)) {
        int uninterrupt = yes_or_not();
        if (uninterrupt) {
            queueTranferProcess(s->blocked, s->ready);
            s->ready->last->state = PROC_STATE_READY;
        }
    }
    if (s->exec == NULL && !isEmpty(s->ready)) {
        // Coloca o próximo processo da fila de pronto em execução
        s->exec = queuePopProcess(s->ready);
        s->exec->state = PROC_STATE_EXECUTING;
        s->exec->counter += 1;

        printf("%d passou pela CPU\n", s->exec->id);


        // Essa execução será interrompido?
        int interrupt = yes_or_not();
        if (interrupt) {
            // Em quanto tempo o processo será interrompido?
            int time_interrupt = rand() % min(quantum, s->exec->proctime);
            // executa o processo até a interrupção
            s->exec->proctime -= time_interrupt;
            // Coloca na fila de dispositivos
            blockProcess(s);
        } else {
            // O PROCESSO NÃO FOI INTERROMPIDO
            // executa o processo com base no quantum
            s->exec->proctime -= min(quantum, s->exec->proctime);
            // O processo terminou de executar?
            if (s->exec->proctime == 0) {
                // Finaliza o processo
                finishProcess(s);
                // Coloca mais um processo na fila de pronto
                if (!isEmpty(s->jobs)) {
                    queueTranferProcess(s->jobs, s->ready);
                    s->ready->last->state = PROC_STATE_READY;
                }
            } else {
                // Recoloca o processo na fila de pronto
                // quando ele não terminou e nem foi interrompido
                returnToReady(s);
            }
        }
        // Retorna 1 se foi executado corretamente
        return 1;
    }
    // Retorna 0 se não conseguiu ser executado porque a CPU estava ocupada
    return 0;
}

// Adiciona processo na fila de jobs
void addProcess(schd * s, proc * p) {
    queuePushProcess(s->jobs, p);
}