#include "Heap.h"

void Heap::insert(int value) {
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

void Heap::printHeap() const {
    if (isEmpty()) {
        cout << "Heap is empty!" << endl;
        return;
    }


    cout << "Heap elements: ";
    for (int i = 0; i < size; ++i) {
        cout <<data[i] << " ";
    }
}

void Heap::heapify(int index) {
    int parent = (index - 1) / 2;

    while(index > 0) {
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
