#include <sys/msg.h>
#include <stdio.h>


typedef struct mymsg {
    long type;
    char text[1024 + 1];
} mymsg_t;

int main() {
    FILE* fp = fopen(TEXT_FILE_PATH, "r");
    mymsg_t msg;
    
    fread(msg.text, 1024, 1, fp);
    fclose(fp);

    key_t key = ftok("/tmp", 66);
    int mq = msgget(key, IPC_CREAT | 0666);

    msg.type = 1;
    msgsnd(mq, &msg, 1024, 0);
    getchar();

    msgctl(mq, IPC_RMID, NULL);

    return 0;
}
