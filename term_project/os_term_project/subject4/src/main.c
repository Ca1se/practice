#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "process_schedule.h"

queue_t process_queue[9];

int time_slice_len;
int log_count;

char buf[10240];
char fmt_buf[128];

int random_int32(int from, int to) { return rand() % (to - from + 1) + from; }

void schedule() {
    sprintf(fmt_buf,
            "---------------------Start Scheduling---------------------\n\n");
    strcat(buf, fmt_buf);

    for (int i = 0; i < 9; i++) {
        sprintf(fmt_buf, "Scheduling priority %d processes:\n", i);
        strcat(buf, fmt_buf);

        queue_t* que = &process_queue[i];
        while (que->first != NULL) {
            process_t* cur = queue_pop(que);

            sprintf(fmt_buf,
                    "%03d: Process %d is running. Time required to finish: %dms\n",
                    ++log_count, cur->pid, cur->time_req - cur->time_exe);
            strcat(buf, fmt_buf);

            cur->time_exe += time_slice_len;

            if (cur->time_exe >= cur->time_req) {
                sprintf(fmt_buf, "%03d: Process %d finished\n\n", ++log_count,
                        cur->pid);
                strcat(buf, fmt_buf);

                free(cur);
                continue;
            }

            queue_push(que, cur);
            sprintf(fmt_buf,
                    "%03d: Process %d has been suspended."
                    " Total running time: %dms\n\n",
                    ++log_count, cur->pid, cur->time_exe);
            strcat(buf, fmt_buf);
        }
    }

    sprintf(fmt_buf,
            "---------------------Stop Scheduling----------------------\n");
    strcat(buf, fmt_buf);

    FILE* fp = fopen(OUTPUT_FILE_DIR "/scheduling_info", "w+");
    fwrite(buf, strlen(buf), 1, fp);
    fclose(fp);
}

int main() {
    srand(time(NULL));

    time_slice_len = random_int32(4, 8) * 5;

    sprintf(fmt_buf, "Time slice length: %dms\n\n", time_slice_len);
    strcat(buf, fmt_buf);

    for (int i = 0; i < 20; i++) {
        process_t* tmp = (process_t*)malloc(sizeof(process_t));

        tmp->pid = i;
        tmp->time_req = random_int32(30, 100);
        tmp->time_exe = 0;
        tmp->priority = random_int32(0, 8);

        queue_push(&process_queue[tmp->priority], tmp);

        sprintf(fmt_buf,
                "pid: %d\n"
                "time required: %d\n"
                "priority: %d\n\n",
                tmp->pid, tmp->time_req, tmp->priority);

        strcat(buf, fmt_buf);
    }

    FILE* fp = fopen(OUTPUT_FILE_DIR "/process_info", "w+");
    fwrite(buf, strlen(buf), 1, fp);
    fclose(fp);

    buf[0] = 0;
    schedule();

    return 0;
}
