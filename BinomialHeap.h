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

    BinomialNode* mergeTrees(BinomialNode* b1, BinomialNode* b2);
    void consolidate();

public:
    BinomialHeap() : head(nullptr) {}

    void insert(int key);
    void merge(BinomialHeap& other);
    void printHeap();
    void printTree(BinomialNode* root);
};

#endif