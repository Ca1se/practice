#ifndef _QUICK_SORT_H_
#define _QUICK_SORT_H_
#include "my_vector.h"

template<typename T>
inline int Partition(my::vector<T>& a,int i,int j) {         //划分
    T sign=a[i];                          //记录标志位
    while(i!=j)                             //以标志位为基准进行划分
    {
        while(a[j]>=sign&&j>i)              
        {
            j--;
        }
        a[i]=a[j];
        while(a[i]<=sign&&i<j)
        {
            i++;
        }
        a[j]=a[i]; 
    }
    a[i]=sign;
    return i;
}

template<typename T>
inline void quicksort(my::vector<T>& a,int l,int r) {
    if(l<r)
    {
        int i=Partition(a,l,r);
        quicksort(a,l,i);
        quicksort(a,i+1,r);
    }
}

#endif
