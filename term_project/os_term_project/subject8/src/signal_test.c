#include <stdlib.h>
#include "signal_test.h"


queue_t process_queue;
int     skip_schedule;

signal_t* make_signal(int resource_num) {
    signal_t* ret = (signal_t*) malloc(sizeof(signal_t));

    ret->value = resource_num;
    ret->wait_process = (queue_t*) malloc(sizeof(queue_t));
    ret->wait_process->first = NULL;

    return ret;
}

void queue_push(queue_t* queue, process_t* proc) {
    proc->next = NULL;

    if(queue->first == NULL) {
        queue->first = proc;
        queue->last  = proc;
    }else {
        queue->last->next = proc;
        queue->last = proc;
    }
}

process_t* queue_pop(queue_t* queue) {
    process_t* ret = NULL;

    if(queue->first != NULL) {
        ret = queue->first;
        queue->first = queue->first->next;
    }
    
    return ret;
}

void mwait(signal_t* sig) {
    sig->value--;
    if(sig->value < 0) {
        process_t* tmp = queue_pop(&process_queue);
        queue_push(sig->wait_process, tmp);
        skip_schedule = 1;
    }
}

void msignal(signal_t* sig) {
    sig->value++;
    if(sig->value <= 0) {
        process_t* tmp = queue_pop(sig->wait_process);
        queue_push(&process_queue, tmp);
    }
}
