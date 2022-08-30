#include <stdlib.h>
#include "process_schedule.h"


queue_t* make_queue() {
    queue_t* ret = (queue_t*) malloc(sizeof(queue_t));

    ret->first = NULL;
    ret->last  = NULL;

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

