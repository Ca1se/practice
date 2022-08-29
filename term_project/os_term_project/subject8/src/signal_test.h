#ifndef SIGNAL_TEST_H
#define SIGNAL_TEST_H

typedef void (*instruction_t)();

typedef struct process {
    int ins_pointer;
    int ins_count;
    instruction_t ins[64];
} process_t;

typedef struct queue_node {
    process_t* proc;
    struct queue_node* next;
} queue_node_t;

typedef struct queue {
    queue_node_t* first;
    queue_node_t* last;
} queue_t;

typedef struct signal {
    int value;
    queue_t* wait_process;
} signal_t;

extern queue_t process_queue;

extern int skip_schedule;

signal_t* make_signal();

void queue_push(queue_t* queue, process_t* process);

void queue_push_node(queue_t* queue, queue_node_t* node);

process_t* queue_pop(queue_t* queue);

queue_node_t* queue_pop_node(queue_t* queue);

void msignal(signal_t* sig);

void mwait(signal_t* sig);

#endif
