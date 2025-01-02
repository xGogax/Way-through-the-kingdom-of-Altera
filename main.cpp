#include "BinomialHeap.h"

int main() {
    BinomialHeap heap;

    // Insert elements
    heap.insert(12);
    heap.insert(10);
    heap.insert(15);
    heap.insert(8);
    heap.insert(20);
    heap.insert(4);
    heap.insert(16);

    cout << "Binomial Heap after insertions:" << endl;
    heap.printHeap();

    return 0;
}