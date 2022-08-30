#ifndef SIGNAL_TEST_H
#define SIGNAL_TEST_H

typedef void (*instruction_t)();

typedef struct process {
    int             ins_pointer;
    int             ins_count;
    instruction_t   ins[64];
    struct process* next;
} process_t;

typedef struct queue {
    process_t* first;
    process_t* last;
} queue_t;

typedef struct signal {
    int         value;
    queue_t*    wait_process;
} signal_t;

extern queue_t process_queue;

extern int skip_schedule;

signal_t* make_signal();

void queue_push(queue_t* queue, process_t* process);

process_t* queue_pop(queue_t* queue);

void msignal(signal_t* sig);

void mwait(signal_t* sig);

#endif
