#include "BinomialHeap.h"

#include <iostream>
#include <string>;

using namespace std;

void F() {

}

void B(BinomialHeap* x) {
    delete x;
}

void D(string choice, BinomialHeap* blue) {
    size_t start = choice.find('[') + 1;
    size_t end = choice.find(']');

    string brojStr = choice.substr(start, end - start);

    int broj = stoi(brojStr);

    blue->insert(broj);
}

void M(string choice, BinomialHeap* red) {
    size_t start = choice.find('[') + 1;
    size_t end = choice.find(']');

    string brojStr = choice.substr(start, end - start);

    int broj = stoi(brojStr);

    red->insert(broj);
}

void T(BinomialHeap* blue) {
    blue->removeTop();
}

void P(BinomialHeap* red) {
    red->removeTop();
}

void G(BinomialHeap* red, BinomialHeap* blue) {
    cout << "\033[1;97;101m       RED BAG      \033[0m" << endl;
    red->printHeap();
    cout << "\033[1m\033[97;44m      BLUE BAG      \033[0m" << endl;
    blue->printHeap();
}

void L() {

}

void R(string choice, BinomialHeap* blue) {
    size_t start = choice.find('[') + 1;
    size_t end = choice.find(']');

    string brojStr = choice.substr(start, end - start);

    int broj = stoi(brojStr);

    for (size_t i = 0; i < broj; i++) {
        blue->removeTop();
    }
}

void printMenu() {
    cout << "===================================================\n";
    cout << "|               THE WAY THROUGH THE               |\n";
    cout << "|                KINGDOM OF ALTERA                |\n";
    cout << "===================================================\n";
    cout << "| F.    | Read from file                          |\n";
    cout << "| V.    | Buy red and blue bag                    |\n";
    cout << "| B.    | Sell red and blue bag                   |\n";
    cout << "| D[x]. | Find x diamonds                         |\n";
    cout << "| M[x]. | Find x moissanite                       |\n";
    cout << "| T.    | Encountering a traveling arms dealer    |\n";
    cout << "| P.    | Encountering a traveling baker.         |\n";
    cout << "| G.    | Encountering the border crossing.       |\n";
    cout << "| L.    | Encountering a thief.                   |\n";
    cout << "| R[k]. | Encountering a rare merchant            |\n";
    cout << "===================================================\n";
}

int main() {
    string choice;
    BinomialHeap* red;
    BinomialHeap* blue;
    bool flag = false;

    printMenu();

    while(true) {
        cin >> choice;
        if(choice == "F") {

        } else if (choice == "V") {
            red = new BinomialHeap(false); blue = new BinomialHeap(true);
            flag = true;
        } else if (choice == "B" && flag) {
            B(red); B(blue);
            flag = false;
        } else if (choice.find('D') != string::npos && flag) {
            D(choice, blue);
        } else if (choice.find('M') != string::npos && flag) {
            M(choice, red);
        } else if (choice == "T" && flag) {
            T(blue);
        } else if (choice == "P" && flag) {
            P(red);
        } else if (choice == "G" && flag) {
            G(red, blue);
        } else if (choice == "L" && flag) {

        } else if (choice.find('R') != string::npos && flag) {
            R(choice, blue);
        }
    }
    return 0;
}