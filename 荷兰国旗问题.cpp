//给定一个数组,一个数字,比给的数小的数放左边,比给的数大的数放右边,等于给的数数放中间,要求空间复杂度O(1),时间复杂度O(N)
#include<iostream>
using namespace std;
int main(){
    int arr[]={3,6,4,6,7,4,8,3,2,1,7,8,5,7,8,3,7};
    int less=-1,more=sizeof(arr)/4,num=5;
    for(int i=0;i<more;){
        int temp=arr[i];
        if(arr[i]<num){//小于
            arr[i++]=arr[++less];
            arr[less]=temp;
        }else if(arr[i]>num){//大于
            arr[i]=arr[--more];
            arr[more]=temp;
        }else{//等于
            i++;
        }
    }
    for(int i=0;i<(sizeof(arr)/4);i++){
        cout << arr[i] << endl;
    }
}