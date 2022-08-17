#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdint.h>


typedef struct pcb pcb_t;

typedef struct thread_status {
    uint32_t    eax;
    uint32_t    ebx;
    uint32_t    ecx;
    uint32_t    edx;
    uint32_t    pc;
    uint16_t    psw;
    void*       user_stack;
} thread_status_t;

typedef struct thread_dispath_info {
    uint8_t     status;
    uint8_t     priority;
    uint32_t    wait_count;
    uint32_t    live_count;
    uint32_t    event;
} thread_dispath_info_t;

typedef struct thread_control_info {
    uint32_t    inner_addr;
    uint32_t    outer_addr;
    void*       resource_list;
    pcb_t*      next;
} thread_control_info_t;

struct pcb {
    uint32_t    pid;
    uint32_t    ppid;
    uint32_t    uid;

    thread_status_t         status;
    thread_dispath_info_t   dispath_info;
    thread_control_info_t   control_info;
};

pcb_t*  create_thread();

void    destroy_thread(pcb_t* pcb);

#endif // list.h
