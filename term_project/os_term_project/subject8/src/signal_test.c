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

void queue_push_aux(queue_t* queue, queue_node_t* node) {
    if(queue->first == NULL) {
        queue->first = node;
        queue->last  = node;
    }else {
        queue->last->next = node;
        queue->last = node;
    }
}

void queue_push(queue_t* queue, process_t* process) {
    queue_node_t* node = (queue_node_t*) malloc(sizeof(queue_node_t));

    node->proc = process;
    node->next = NULL;

    queue_push_aux(queue, node);
}

void queue_push_node(queue_t* queue, queue_node_t* node) {
    node->next = NULL;
    queue_push_aux(queue, node);
}

process_t* queue_pop(queue_t* queue) {
    process_t* ret = NULL;

    if(queue->first != NULL) {
        ret = queue->first->proc;
        queue_node_t* tmp = queue->first;
        queue->first = queue->first->next;
        free(tmp);
    }

    return ret;
}

queue_node_t* queue_pop_node(queue_t* queue) {
    queue_node_t* ret = NULL;

    if(queue->first != NULL) {
        ret = queue->first;
        queue->first = queue->first->next;
    }

    return ret;
}

void msignal(signal_t* sig) {
    sig->value--;
    if(sig->value < 0) {
        queue_node_t* tmp = queue_pop_node(&process_queue);
        queue_push_node(sig->wait_process, tmp);
        skip_schedule = 1;
    }
}

void mwait(signal_t* sig) {
    sig->value++;
    if(sig->value <= 0) {
        queue_node_t* tmp = queue_pop_node(sig->wait_process);
        queue_push_node(&process_queue, tmp);
    }
}
