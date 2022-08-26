#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>


typedef struct mymsg {
    long type;
    char text[1024 + 1];
} mymsg_t;

int main() {
    key_t key = ftok("/tmp", 66);
    int mq = msgget(key, IPC_CREAT | 0666);

    mymsg_t msg;
    msgrcv(mq, &msg, 1024, 1, 0);
    msg.text[1024] = '\0';
    printf("Recive from sender:\n%s", msg.text);

    return 0;
}
