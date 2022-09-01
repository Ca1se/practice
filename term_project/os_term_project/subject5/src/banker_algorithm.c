#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


int available[4] = { 10, 10, 10, 10 };
int max[4][4];
int allocation[4][4];
int need[4][4];
int request[4];
bool finish[4];

int seq[4];


bool ge(int* a, int* b) {
    bool judge = true;
    for(int i = 0; i < 4; i++) {
        if(a[i] < b[i]) {
            judge = false;
            break;
        }
    }
    return judge;
}

void add(int* a, int* b) {
    for(int i = 0; i < 4; i++)
        a[i] += b[i];
}

void sub(int* a, int* b) {
    for(int i = 0; i < 4; i++)
        a[i] -= b[i];
}

bool test_security_aux(int cnt) {
    bool flag = false;
    for(int i = 0; i < 4; i++) {
        if(!finish[i] && ge(available, need[i])) {
            if(cnt == 3) {
                seq[3] = i;
                return true;
            }
            finish[i] = true;
            seq[cnt] = i;

            add(available, allocation[i]);
            flag = test_security_aux(cnt + 1);
            sub(available, allocation[i]);

            finish[i] = false;
        }
        if(flag) return true;
    }

    return false;
}

bool test_security(int pid) {
    bool judge = true;

    do {

    if(!ge(need[pid], request) || !ge(available, request)) {
        judge = false;
        break;
    }

    add(allocation[pid], request);
    sub(need[pid], request);
    sub(available, request);

    if(!test_security_aux(0)) {
        sub(allocation[pid], request);
        add(need[pid], request);
        add(available, request);
        judge = false;
    }
    
    } while(false);

    return judge;
}

void print_status() {
    printf("pid\tmax\t\tallocation\tneed\n");
    for(int i = 0; i < 4; i++) {
        printf("%d\t", i);
        for(int k = 0; k < 4; k++)
            printf("%d ", max[i][k]);
        printf("\t");
        for(int k = 0; k < 4; k++)
            printf("%d ", allocation[i][k]);
        printf("\t");
        for(int k = 0; k < 4; k++)
            printf("%d ", need[i][k]);
        printf("\n");
    }
    printf("available: %d %d %d %d\n",
            available[0], available[1], available[2], available[3]);
}

int random_int32(int from, int to) { return rand() % (to - from + 1) + from; }

int main() {
    srand(time(NULL));
    for(int i = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
            max[i][k] = random_int32(2, 9);

    memcpy(need, max, sizeof max);
    print_status();

    char buf[64];
    int pid;

    do {
        scanf("%s", buf);
        if(!strcmp(buf, "quit")) break;
        else if(!strcmp(buf, "request")) {
            scanf("%d", &pid);
            for(int i = 0; i < 4; i++)
                scanf("%d", request + i);
            if(test_security(pid)) {
                printf("Found a viable process sequence:");
                for(int i = 0; i < 4; i++) printf(" %d", seq[i]);
                printf(", request accepted.\n");
            }else {
                printf("Request rejected.\n");
            }
        }else if(!strcmp(buf, "print"))
            print_status();
    } while(true);

    return 0;
}
