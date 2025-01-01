#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

class Heap {
public:
    Heap(bool isMaxHeap) {
        data = nullptr;
        size = 0;
        this->isMaxHeap = isMaxHeap;
    }

    ~Heap() {
        delete[] data;
    }

    void insert(int value);
    void printHeap() const;

private:
    int* data;
    int size;
    bool isMaxHeap;

    bool isEmpty() const {
        return size == 0;
    }

    void heapify(int index);
};

#endif // HEAP_H
