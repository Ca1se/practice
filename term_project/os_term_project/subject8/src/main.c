#include <stdlib.h>
#include <stdio.h>
#include "signal_test.h"


void instruction_nop();
void instruction_print_1();
void instruction_print_2();
void instruction_signal();
void instruction_wait();

extern queue_t process_queue;
extern int skip_schedule;

signal_t* sig = NULL;

void simulate() {
    while(process_queue.first != NULL) {
        process_t* cur = process_queue.first;
        
        // executing instruction
        cur->ins[cur->ins_pointer++]();

        if(cur->ins_pointer == cur->ins_count) {
            queue_pop(&process_queue);
            continue;
        }

        if(skip_schedule == 1) {
            skip_schedule = 0;
            continue;
        }

        // scheduling process
        process_t* tmp = queue_pop(&process_queue);
        queue_push(&process_queue, tmp);
    }
}

int main() {
    sig = make_signal();

    process_t* process1 = (process_t*) malloc(sizeof(process_t));
    process_t* process2 = (process_t*) malloc(sizeof(process_t));

    // initialize two processes
    process1->ins_count = 10;
    process1->ins_pointer = 0;
    process2->ins_count = 10;
    process2->ins_pointer = 0;

    for(int i = 0; i < 10; i++) {
        int tmp = i % 5;
        if(tmp != 0 && tmp != 4) {
            process1->ins[i] = instruction_print_1;
            process2->ins[i] = instruction_print_2;
        }else {
            process1->ins[i] = instruction_nop;
            process2->ins[i] = instruction_nop;
        }
    }

    queue_push(&process_queue, process1);
    queue_push(&process_queue, process2);

    printf("Simulate with semaphore disabled:\n");
    simulate();
    printf("\n");

    process1->ins_pointer = 0;
    process2->ins_pointer = 0;

    for(int i = 0; i < 10; i++) {
        int tmp = i % 5;
        if(tmp != 0 && tmp != 4) {
            process1->ins[i] = instruction_print_1;
            process2->ins[i] = instruction_print_2;
        }else if(i % 5 == 0) {
            process1->ins[i] = instruction_signal;
            process2->ins[i] = instruction_signal;
        }else {
            process1->ins[i] = instruction_wait;
            process2->ins[i] = instruction_wait;
        }
    }

    queue_push(&process_queue, process1);
    queue_push(&process_queue, process2);

    printf("Simulate with semaphore enabled:\n");
    simulate();
    printf("\n");

    free(process1);
    free(process2);

    return 0;
}

void instruction_nop() { }

void instruction_print_1() {
    printf("Hi! This is a message from process1!\n");
}

void instruction_print_2() {
    printf("Hi! This is a message from process2!\n");
}

void instruction_signal() {
    msignal(sig);
}

void instruction_wait() {
    mwait(sig);
}
