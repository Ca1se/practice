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

void add_pcb(pcb_t* pcb, pcb_t* parent) {
    pcb_list_t* list = get_pcb_list();
    pcb_node_t* node = (pcb_node_t*) malloc(sizeof(pcb_node_t));

    node->child = node->sibling = NULL;
    node->pcb = pcb;

    pcb->control_info.next = NULL;
    pcb->node = node;

    if(list->last != NULL) {
        list->last->control_info.next = pcb;
        list->last = pcb;

        if(parent->node->child == NULL)
            parent->node->child = node;
        else {
            pcb_node_t* tmp = parent->node->child;

            while(tmp->sibling != NULL)
                tmp = tmp->sibling;
            tmp->sibling = node;
        }

    }else {
        list->first = list->last = pcb;

        get_pcb_tree()->root = node;
    }

    list->size++;
}

void init_pcb(pcb_t* pcb, pcb_t* parent) {
    static uint32_t pcb_count = 0;

    pcb->pid = pcb_count++;
    pcb->uid = 0;

    pcb->ppid = 0;
    if(parent != NULL) {
        pcb->ppid = parent->pid;
    }

    // initialize process status, process dispath information and process control information
}

pcb_t* search_pcb(int32_t pid) {
    if(pid == -1) return NULL;

    pcb_list_t* list = get_pcb_list();
    pcb_t* ret = NULL;

    pcb_t* tmp = list->first;
    while(tmp != NULL) {
        if(tmp->pid == pid) {
            ret = tmp;
            break;
        }
        tmp = tmp->control_info.next;
    }
    return ret;
}

int32_t fork(int32_t ppid) {
    pcb_t* pcb      = (pcb_t*) malloc(sizeof(pcb_t));
    pcb_t* parent   = search_pcb(ppid);

    init_pcb(pcb, parent);
    add_pcb(pcb, parent);

    return pcb->pid;
}

void terminate_all_aux(pcb_node_t* root) {
    pcb_node_t* tmp = root->child;

    while(tmp != NULL) {
        terminate_all_aux(tmp);
        tmp = tmp->sibling;
    }

    free(root);
}

void terminate_all() {
    pcb_tree_t* tree = get_pcb_tree();
    pcb_list_t* list = get_pcb_list();

    terminate_all_aux(tree->root);
    free(tree);
    free(list);
}
