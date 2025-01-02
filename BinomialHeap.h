#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct BinomialNode {
    int key;
    int degree;
    BinomialNode* parent;
    BinomialNode* child;
    BinomialNode* sibling;

    BinomialNode(int k) : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

class BinomialHeap {
private:
    BinomialNode* head;
    bool isMaxHeap;  // Ovaj flag označava da li je heap Max-Heap ili Min-Heap

    BinomialNode* mergeTrees(BinomialNode* b1, BinomialNode* b2);
    void consolidate();
    void printTree(BinomialNode* node);
    void clearTree(BinomialNode* node);;
public:
    BinomialHeap(bool maxHeap = false) : head(nullptr), isMaxHeap(maxHeap) {}
    ~BinomialHeap() {
        clearTree(head);
    };

    void removeTop();
    void insert(int key);
    void merge(BinomialHeap& other);
    void printHeap();
};

#endif