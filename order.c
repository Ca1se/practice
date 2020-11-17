#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct StuInfo{
    char name[20];
    char ID[20];
    int score;
}StuInfo;
typedef struct List {
    StuInfo stu;
    struct List* next;
}List;
void InitAStuInfo(StuInfo* stu, const char* name, const char* ID, int score) {
    strcpy(stu->name, name);
    strcpy(stu->ID, ID);
    stu->score = score;
}
void AddStuInfo(List** h) {
    char name[20] = {0}, ID[20] = {0};
    int score = 0;
    printf("请输入学生的姓名: ");
    scanf("%s", name);
    printf("请输入学生的学号: ");
    scanf("%s", ID);
    printf("请输入学生的分数: ");
    scanf("%d", &score);

    List* stu = (List*)malloc(sizeof(StuInfo));
    InitAStuInfo(&(stu->stu), name, ID, score);
    
    stu->next = *h;
    *h = stu;
}
void PrintAllStuInfo(List* h) {
    List* target = h;
    while(target != NULL){
        printf("姓名:%s\n", target->stu.name);
        printf("学号:%s\n", target->stu.ID);
        printf("分数:%d\n", target->stu.score);
        target = target->next;
    }
}
void DeleteStuInfo(List** h) {
    char name[20] = {0}, ID[20] = {0};
    printf("请输入学生的姓名:");
    scanf("%s", name);
    printf("请输入学生的学号:");
    scanf("%s", ID);

    List* pre, *now;
    pre = now = *h;

    int hasIt = 0;
    while(now != NULL){
        if(!(strcmp(now->stu.name, name) || strcmp(now->stu.ID, ID))){
            hasIt = 1;
            break;
        }
        if(now != pre){
            pre = pre->next;
        }
        now = now->next;
    }

    if(hasIt){
        if(now == pre){
            *h = now->next;
            free(now);
        }else{
            pre->next = now->next;
            free(now);
        }
    }else{
        printf("查无此人\n");
    }
}
void ReleaseList(List* h) {
    List* t = h;
    while(h != NULL){
        h = h->next;
        free(t);
        t = h;
    }
}
int main() {
    List* head = NULL;
    int goon = 1;
    while(goon) {
        printf("欢迎使用学生信息管理系统, 输入 1: 添加学生信息, 输入 2: 查看所有学生信息, 输入 3: 删除学生信息, 输入 q: 退出系统\n");
        char ch;
        do{
            scanf("%c", &ch);
        }while(ch != '1' && ch != '2' && ch != '3' && ch != 'q');
        switch (ch){
            case '1':{
                AddStuInfo(&head);
                break;
            }
            case '2':{
                PrintAllStuInfo(head);
                break;
            }
            case '3':{
                DeleteStuInfo(&head);
                break;
            }
            default:{
                goon = 0;
                break;
            }
        }
    }
    ReleaseList(head);
    printf("退出系统\n");
    return 0;
}