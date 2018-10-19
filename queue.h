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
        q->size -= 1;
    }
    return byebye;
}

// Transfere o primeiro processo da fila 'q' para 'r'
void * queueTranferProcess(queue * q, queue * r) {
    proc * p = queuePopProcess(q);
    queuePushProcess(r, p);
}

// Verifica se a fila está vazia
int isEmpty(queue * q) {
    return !(q->size);
}

// for que percorre a lista de processos
#define foreach(p,q) for(proc * p = q->first; p != NULL; p = p->next)