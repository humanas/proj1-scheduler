#include <stdio.h>
#include <stdlib.h>
#include "process.h"

// Define a estrutura da fila de processo
typedef struct {
    struct process_t * first;
    struct process_t * last;
    int size;  
} queue;

// Cria a fila
queue * createQueue() {
    queue * newer = (queue *) malloc (sizeof(queue));
    newer->first = NULL;
    newer->last = NULL;
    newer->size = 0;
    return newer;
}

// Coloca um processo na fila
void queuePushProcess(queue * q, proc * p) {
    if (p != NULL) {
        if (q->first == NULL) {
            q->first = p;
            q->last = p;
            p->next = NULL;
            q->size = 1;
        } else {
            q->last->next = p;
            p->next = NULL;
            q->size += 1;
            q->last = p;
        }
    }
}

// Retira o primeiro processo da fila
proc * queuePopProcess(queue * q) {
    proc * byebye = q->first;
    if (byebye != NULL) {
        q->first = byebye->next;
    }
    return byebye;
}

// Transfere o primeiro processo da fila 'q' para 'r'
void * queueTranferProcess(queue * q, queue * r) {
    proc * p = queuePopProcess(q);
    queuePushProcess(r, p);
}