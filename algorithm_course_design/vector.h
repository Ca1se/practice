#ifndef _VECTOR_H_
#define _VECTOR_H_

#include<cstddef>
#include<cstring>
#include<iostream>

template<typename ElemType, int expandLength = 500> 
class Vector {
private:
    ElemType* _listHead; 
    size_t _capacity;
    size_t _size;

    void expand_capacity() {
        _capacity += expandLength;
        ElemType* t = new ElemType[_capacity];
        memcpy(t, _listHead, sizeof(ElemType) * _size);
        delete[] _listHead;
        _listHead = t;
    }
    
public:
    explicit Vector(size_t initialCapacity = 500): _listHead(nullptr), _capacity(initialCapacity), _size(0) {
        _listHead = new ElemType[initialCapacity];
    }

    Vector(const Vector& v): _listHead(nullptr), _capacity(v._capacity), _size(v._size) {
        _listHead = new ElemType[v._capacity];
        memcpy(_listHead, v._listHead, sizeof(ElemType) * v._size);
    }

    ~Vector() {
        if(_listHead) {
            delete[] _listHead;
            _listHead = nullptr;
        }
    }

    size_t size() const {
        return _size;
    }

    void push_back(const ElemType& elem) {
        if(_size == _capacity) {
            expand_capacity();
        }

        _listHead[_size++] = elem;
    }

    void pop_back() {
        if(_size) _size--;
    }

    ElemType& front() {
        if(_size == 0) throw "empty vector";
        return _listHead[0];
    }

    ElemType& back() {
        if(_size == 0) throw "empty vector";
        return _listHead[_size - 1];
    }

    ElemType& operator[] (size_t pos) {
        return _listHead[pos];
    }

    const ElemType& operator[] (size_t pos) const {
        return _listHead[pos];
    }

    const Vector<ElemType>& operator= (const Vector<ElemType>& rhs) {
        this->_size = rhs._size;
        if(this->_capacity < rhs._size) {
            ElemType* t = new ElemType[rhs._capacity];
            delete[] this->_listHead;
            _listHead = t;
        }
        memcpy(this->_listHead, rhs._listHead, sizeof(ElemType) * rhs._size);
        return *this;
    }
};

#endif
