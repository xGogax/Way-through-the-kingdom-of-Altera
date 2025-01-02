#include "BinomialHeap.h"

BinomialNode* BinomialHeap::mergeTrees(BinomialNode* b1, BinomialNode* b2) {
    if (b1->key > b2->key)
        swap(b1, b2);
    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;

    return b1;
}

void BinomialHeap::merge(BinomialHeap& other) {
    BinomialNode* newHead = nullptr;
    BinomialNode** curr = &newHead;
    BinomialNode* h1 = head;
    BinomialNode* h2 = other.head;

    while (h1 != nullptr && h2 != nullptr) {
        if (h1->degree <= h2->degree) {
            *curr = h1;
            h1 = h1->sibling;
        } else {
            *curr = h2;
            h2 = h2->sibling;
        }
        curr = &((*curr)->sibling);
    }

    if (h1 != nullptr) *curr = h1;
    if (h2 != nullptr) *curr = h2;

    head = newHead;

    consolidate();

    other.head = nullptr;
}

void BinomialHeap::insert(int key) {
    BinomialHeap newHeap;
    newHeap.head = new BinomialNode(key);

    merge(newHeap);
}

void BinomialHeap::consolidate() {
    vector<BinomialNode*> trees(64, nullptr);

    BinomialNode* current = head;
    head = nullptr;

    while (current != nullptr) {
        BinomialNode* next = current->sibling;
        current->sibling = nullptr;

        int degree = current->degree;
        while (trees[degree] != nullptr) {
            current = mergeTrees(current, trees[degree]);
            trees[degree] = nullptr;
            degree++;
        }
        trees[degree] = current;
        current = next;
    }

    for (BinomialNode* tree : trees) {
        if (tree != nullptr) {
            tree->sibling = head;
            head = tree;
        }
    }
}

void BinomialHeap::printHeap() {
    BinomialNode* current = head;
    while (current != nullptr) {
        cout << "B" << current->degree << ": ";
        printTree(current);
        cout << endl;
        current = current->sibling;
    }
}

void BinomialHeap::printTree(BinomialNode* root) {
    cout << root->key << " ";
    BinomialNode* child = root->child;
    while (child != nullptr) {
        printTree(child);
        child = child->sibling;
    }
}