#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

const char* const msg1 = "Message from Child 1!";
const char* const msg2 = "Message from Child 2!";
int pipefd[2];

void handle_signal_interrupt_1(int signum) {
    write(pipefd[1], msg1, strlen(msg1));
    exit(0);
}

void handle_signal_interrput_2(int signum) {
    write(pipefd[1], msg2, strlen(msg2));
    exit(0);
}

int main() {
    pipe(pipefd);

    int first_child  = fork();
    int second_child = -1;

    if(first_child != 0) {
        second_child = fork();
    }

    if(first_child == 0) {
        signal(SIGINT, handle_signal_interrupt_1);
    }else if(second_child == 0) {
        signal(SIGINT, handle_signal_interrput_2);
    }else {
        char buf[64] = {};
        sleep(1);

        kill(first_child, SIGINT);
        read(pipefd[0], buf, sizeof buf);
        printf("%s\n", buf);


        kill(second_child, SIGINT);
        read(pipefd[0], buf, sizeof buf);
        printf("%s\n", buf);

        exit(0);
    }

    while(1);

    return 0;
}
