#ifndef QUEUE_H
#define QUEUE_H

typedef struct process {
    int             pid;
    int             time_req;
    int             time_exe;
    int             priority;
    struct process* next;
} process_t;

typedef struct queue {
    process_t* first;
    process_t* last;
} queue_t;

queue_t* make_queue();

void queue_push(queue_t* queue, process_t* process);

process_t* queue_pop(queue_t* queue);

#endif
