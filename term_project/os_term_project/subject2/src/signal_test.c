#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


int process_num = 1;
int first, second;

void handle_signal_terminate(int signum) {
    printf("Child Proeess %d is Killed by Parent!\n", process_num);
    exit(0);
}

void handle_signal_interrupt(int signum) {
    kill(first, SIGTERM);
    kill(second, SIGTERM);
    exit(0);
}

int main() {
    int first_child  = fork();
    int second_child = -1;

    if(first_child != 0) {
        second_child = fork();
    }

    if(first_child == 0 || second_child == 0) {
        if(second_child == 0) {
            process_num = 2;
        }
        signal(SIGTERM, handle_signal_terminate);
        signal(SIGINT, SIG_IGN);
    }else {
        first = first_child, second = second_child;
        signal(SIGINT, handle_signal_interrupt);
    }

    while(1);
    
    return 0;
}
