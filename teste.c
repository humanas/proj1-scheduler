#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"

int main() {
    srand(time(NULL));
    proc * p[10];
    for (int i = 0; i < 10; i++) {
        p[i] = createRandomProcess();
        printProcess(p[i]);
    }


    return 0;
}