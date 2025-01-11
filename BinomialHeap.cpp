#include "BinomialHeap.h"

#include <stack>

void BinomialHeap::removeTop() {
    if (head == nullptr) return;

    BinomialNode* maxOrMinNode = head;
    BinomialNode* prevMaxOrMinNode = nullptr;
    BinomialNode* curr = head;
    BinomialNode* prev = nullptr;

    while (curr != nullptr) {
        if ((isMaxHeap && curr->key > maxOrMinNode->key) || (!isMaxHeap && curr->key < maxOrMinNode->key)) {
            maxOrMinNode = curr;
            prevMaxOrMinNode = prev;
        }
        prev = curr;
        curr = curr->sibling;
    }

    if (prevMaxOrMinNode == nullptr) {
        head = maxOrMinNode->sibling;
    } else {
        prevMaxOrMinNode->sibling = maxOrMinNode->sibling;
    }

    BinomialNode* child = maxOrMinNode->child;
    while (child != nullptr) {
        BinomialNode* nextChild = child->sibling;
        child->sibling = head;
        child->parent = nullptr;
        head = child;
        child = nextChild;
    }

    delete maxOrMinNode;

    consolidate();
}


BinomialNode* BinomialHeap::mergeTrees(BinomialNode* b1, BinomialNode* b2) {
    if ((isMaxHeap && b1->key < b2->key) || (!isMaxHeap && b1->key > b2->key)) {
        swap(b1, b2);
    }

    // Dodajemo b2 kao dete b1
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
    BinomialHeap newHeap(isMaxHeap);
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

void BinomialHeap::printTree(BinomialNode* root) {
    using std::cout;
    using std::endl;

    if (root == nullptr) return;

    struct NodeInfo {
        BinomialNode* node;
        int depth;
        bool isLast;
    };

    vector<bool> flag(10, true);
    stack<NodeInfo> nodeStack;

    nodeStack.push({root, 0, true});

    while (!nodeStack.empty()) {
        NodeInfo current = nodeStack.top();
        nodeStack.pop();

        BinomialNode* node = current.node;
        int depth = current.depth;
        bool isLast = current.isLast;

        for (int i = 1; i < depth; ++i) {
            if (flag[i]) {
                cout << "\033[48;5;14m\033[1m|   ";
            } else {
                cout << "\033[48;5;14m\033[1m    ";
            }
        }

        if (depth == 0) {
            cout << "\033[1m\033[48;5;14m\033[97m"<<node->key;
            string x = to_string(node->key);
            for(int i = 0; i < 20 - (depth * 4) - x.length(); i++) {
                cout << " ";
            }
            cout << "\033[0m" << endl;
        } else if (isLast) {
            cout << "\033[1m\033[48;5;14m\033[97m+---" << node->key;
            flag[depth] = false;
            string x = to_string(node->key);
            for(int i = 0; i < 20 - (depth * 4) - x.length(); i++) {
                cout << " ";
            }
            cout << "\033[0m" << endl;
        } else {
            cout << "\033[1m\033[48;5;14m\033[97m|---" << node->key;
            string x = to_string(node->key);
            for(int i = 0; i < 20 - (depth * 4) - x.length(); i++) {
                cout << " ";
            }
            cout << "\033[0m" << endl;
        }

        BinomialNode* child = node->child;
        stack<BinomialNode*> childrenStack;
        while (child != nullptr) {
            childrenStack.push(child);
            child = child->sibling;
        }

        bool firstChild = true;
        while (!childrenStack.empty()) {
            BinomialNode* childNode = childrenStack.top();
            childrenStack.pop();
            nodeStack.push({childNode, depth + 1, firstChild});
            firstChild = false;
        }
    }
}

void BinomialHeap::printHeap() {
    if (head == nullptr && isMaxHeap == false) {
        std::cout << "\033[1m\033[31mHeap is empty.\033[0m" << std::endl;
        return;
    } else if(head == nullptr && isMaxHeap == true) {
        std::cout << "\033[1m\033[34mHeap is empty.\033[0m" << std::endl;
        return;
    }

    BinomialNode* current = head;
    while (current != nullptr) {
        std::cout << "\033[48;5;15m\033[30m\033[1mLEVEL " << current->degree << ":            \033[0m" << std::endl;
        printTree(current);
        std::cout << std::endl;
        current = current->sibling;
    }
}

void BinomialHeap::clearTree(BinomialNode *node) {
    if (node == nullptr) return;
    clearTree(node->child);
    clearTree(node->sibling);
    delete node;
}