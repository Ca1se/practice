#ifndef _MIN_PRIORITY_QUEUE_H_
#define _MIN_PRIORITY_QUEUE_H_

#include <cstddef>
#include "my_vector.h"

template<typename ElemType>
class MinPriorityQueue {
private:
    my::vector<ElemType> _heap;
    
    void sink(size_t p) {
        size_t s = size();
        while(p * 2 <= s) {
            size_t k = p * 2;
            if(k + 1 <= s && _heap[k + 1] < _heap[k]) k++;
            if(_heap[p] <= _heap[k])  break;
            std::swap(_heap[p], _heap[k]);
            p = k;
        }
    }

    void swim(size_t p) {
        while(p / 2) {
            size_t k = p / 2;
            if(_heap[p] >= _heap[k]) break;
            std::swap(_heap[p], _heap[k]);
            p = k;
        }
    }

public:
    explicit MinPriorityQueue(): _heap() {
        _heap.push_back(ElemType());
    }

    MinPriorityQueue(const MinPriorityQueue& m): _heap(m.heap) {}

    ~MinPriorityQueue() {}

    const ElemType& top() const {
        return _heap[1];
    }

    void push(const ElemType& e) {
        _heap.push_back(e);
        swim(size());
    }

    void pop() {
        std::swap(_heap[1], _heap[size()]);
        _heap.pop_back();
        sink(1);
    }

    size_t size() const {
        return _heap.size() - 1;
    }

    size_t empty() const {
        return size() == 0;
    }
};

#endif
