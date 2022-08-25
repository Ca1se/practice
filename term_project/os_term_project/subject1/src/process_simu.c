#include <stdlib.h>
#include "process_simu.h"


pcb_list_t* get_pcb_list() {
    static pcb_list_t* list = NULL;

    if(list == NULL) {
        list = (pcb_list_t*) malloc(sizeof(pcb_list_t));
        list->first = list->last = NULL;
        list->size = 0;
    }

    return list;
}

pcb_tree_t* get_pcb_tree() {
    static pcb_tree_t* tree = NULL;

    if(tree == NULL) {
        tree = (pcb_tree_t*) malloc(sizeof(pcb_tree_t));
        tree->root = NULL;
    }

    return tree;
}

void add_pcb(pcb_t* pcb) {
    pcb_list_t* list = get_pcb_list();

    if(list->last != NULL) {
        list->last->control_info.next = pcb;
        list->last = pcb;
    }else {
        list->first = list->last = pcb;
    }

    list->size++;
}

void init_pcb(pcb_t* pcb, pcb_t* parent) {
    static uint32_t pcb_count = 0;

    pcb->pid = pcb_count++;
    pcb->uid = 0;
    if(parent != NULL) {
        pcb->ppid = parent->pid;
    }

    // initialize process status, process dispath information and process control information
    pcb->control_info.next = NULL;
}

pcb_t* create_pcb() {
     return (pcb_t*) malloc(sizeof(pcb_t));
}

void destroy_pcb(pcb_t* pcb) {
    free(pcb);
}

pcb_t* fork(pcb_t* parent) {
    pcb_t* ret = create_pcb();

    init_pcb(ret, parent);
    add_pcb(ret);

    return ret;
}
