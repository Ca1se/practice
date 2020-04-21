#include<iostream>
#include<cstdlib>
using namespace std;
struct STACK
{
    int *top;
    int *base;
    int StackSize;
};

void InitAStack(STACK* sta,int initsize){
    sta->base=(int*)malloc(initsize*sizeof(int));
    if(!sta->base)  exit(0);
    sta->top=sta->base;
    sta->StackSize=initsize;
}

void Push(STACK* sta,int data){
    if(sta->top-sta->base>=sta->StackSize){
        sta->base=(int*)realloc(sta->base,(sta->StackSize+10)*sizeof(int));
        if(!sta->base)  exit(0);
        sta->top=sta->base+sta->StackSize;
        sta->StackSize+=10;
    }
    *(sta->top)=data;
    (sta->top)++;
}

int Pop(STACK* sta){
    if(sta->top==sta->base) return 0;
    int temp=*--(sta->top);
    return temp;
}

int StackSizeOf(STACK* sta){
    return sta->top-sta->base;
}

int main(){
    STACK astack;
    InitAStack(&astack,100);
    Push(&astack,10);
    Push(&astack,20);
    Push(&astack,30);
    cout << StackSizeOf(&astack) << endl;
    cout << Pop(&astack) << endl;
    cout << StackSizeOf(&astack) << endl;
}