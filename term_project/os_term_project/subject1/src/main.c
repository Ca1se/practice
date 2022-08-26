#include <stdio.h>

#include "process_simu.h"

void print_tree(pcb_node_t* root) {
    printf("%u ", root->pcb->pid);

    pcb_node_t* tmp = root->child;
    while (tmp != NULL) {
        print_tree(tmp);
        tmp = tmp->sibling;
    }
}

int main() {
    int32_t process0 = fork(-1);
    int32_t process1 = fork(process0);
    int32_t process2 = fork(process0);
    int32_t process3 = fork(process0);
    int32_t process4 = fork(process1);
    int32_t process5 = fork(process1);
    int32_t process6 = fork(process5);
    int32_t process7 = fork(process2);
    int32_t process8 = fork(process7);
    int32_t process9 = fork(process7);
    int32_t process10 = fork(process7);

    print_tree(get_pcb_tree()->root);
    printf("\n");
    terminate_all();

    return 0;
}
