#ifndef _QUEUE_H_
#define _QUEUE_H_

template<typename T>
class Queue {
private:
    T* data;
    int Maxsize;
    int front;
    int rear;
public:
    Queue(int initialLength = 200): data(nullptr), Maxsize(initialLength), front(Maxsize - 1), rear(Maxsize - 1) {
        data = new T[Maxsize];
    }
    void push(const T& elem)  {
        if((rear+1)%Maxsize==front) {
            throw "上溢";
        }
        rear=(rear+1)%Maxsize;
        data[rear]=elem;
    }

    void pop() {
        if(rear==front) {
            throw "下溢";
        }
        front=(front+1)%Maxsize;
    }
    T& front_data() {
        if(rear==front) {
            throw "下溢";
        }

        return data[(front+1)%Maxsize];
    }
    int empty() const {
        return front == rear ? 1 : 0;
    }
};
#endif
