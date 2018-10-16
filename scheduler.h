#include <stdlib.h>
#include <stdio.h>
#include "process.h"
#include "queue.h"

typedef struct scheduler {
    queue * jobs;
    queue * ready;
    queue * blocked;
    queue * finished;
    proc * exec;
} schd;



