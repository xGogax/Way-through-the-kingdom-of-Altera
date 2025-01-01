#include <iostream>

#include "Heap.h"

using namespace std;

int main() {
    Heap maxHeap(false);
    maxHeap.insert(89);
    maxHeap.insert(46);
    maxHeap.insert(50);
    maxHeap.insert(22);
    maxHeap.insert(24);
    maxHeap.insert(2);
    maxHeap.insert(93);
    maxHeap.printHeap();

    return 0;
}
