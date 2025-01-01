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

    void insert(int value) {
        //prazan
        if(size == 0) {
            data = new int[1];
        } else {
            //nije prazan = prosirenje
            int* newData = new int[size + 1];
            for(int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }

        data[size++] = value;
        heapify(size-1);
    }

    void printHeap() const {
        if (isEmpty()) {
            cout << "Heap is empty!" << endl;
            return;
        }
        cout << "Heap elements: ";
        for (int i = 1; i <= size; ++i) {
            cout << data[i-1] << " ";
        }
        cout << endl;
    }

private:
    int* data;
    int size;
    bool isMaxHeap;

    bool isEmpty() const {
        return size == 0;
    }

    void heapify(int index) {
        int parent = (index - 1) / 2;

        while(index > 0) {
            cout << "unos: " << data[index] << endl;
            cout << "njegov otac: " << data[parent] << endl;
            if(isMaxHeap) {
                if(data[index] > data[parent]) {
                    swap(data[index], data[parent]);
                    index = parent;
                    parent = (index - 1) / 2;
                } else {
                    break;
                }
            } else {
                if(data[index] < data[parent]) {
                    swap(data[index], data[parent]);
                    index = parent;
                    parent = (index - 1) / 2;
                } else {
                    break;
                }
            }
        }
    }
};

#endif // HEAP_H
