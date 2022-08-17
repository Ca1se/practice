#include <stdlib.h>
#include "thread_simu.h"

void init_pcb(pcb_t* pcb) {
    
}

pcb_t* create_thread() {
    pcb_t* ret = (pcb_t*) malloc(sizeof(pcb_t));

    init_pcb(ret);

    return ret;
}

void destroy_thread(pcb_t* pcb) {
    free(pcb);
}
