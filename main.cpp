#include <fstream>

#include "BinomialHeap.h"

#include <iostream>
#include <string>;

using namespace std;

int countBlue;
int countRed;

void B(BinomialHeap* x) {
    delete x;
}

void D(string choice, BinomialHeap* blue) {
    cout << "You entered the cave" << endl;
    countBlue++;
    size_t start = choice.find('[') + 1;
    size_t end = choice.find(']');

    string brojStr = choice.substr(start, end - start);

    int broj = stoi(brojStr);

    cout << "You found " << broj << "\033[1m\033[34m diamonds\033[0m" << endl;
    blue->insert(broj);
}

void M(string choice, BinomialHeap* red) {
    countRed++;
    cout << "You entered the cave" << endl;
    size_t start = choice.find('[') + 1;
    size_t end = choice.find(']');

    string brojStr = choice.substr(start, end - start);

    int broj = stoi(brojStr);

    cout << "You found " << broj << "\033[1m\033[31m moissanite\033[0m" << endl;
    red->insert(broj);
}

void T(BinomialHeap* blue) {
    cout << "you can only get weapons for your most valuable \033[1m\033[34mdiamond\033[0m" << endl;
    countBlue--;
    blue->removeTop();
}

void P(BinomialHeap* red) {
    cout << "you can get some food for some \033[1m\033[31mmoissanite\033[0m" << endl;
    countRed--;
    red->removeTop();
}

void G(BinomialHeap* red, BinomialHeap* blue) {
    cout << "let's see what you have in your bags!\033[0m" << endl;
    cout << "\033[1;97;101m       RED BAG      \033[0m" << endl;
    red->printHeap();
    cout << "\033[1m\033[97;44m      BLUE BAG      \033[0m" << endl;
    blue->printHeap();
}

void L(BinomialHeap* red, BinomialHeap* blue) {
    cout << "You encountered a thief" << endl;
    if(countRed > countBlue) {
        red->merge(*blue);
    } else {
        blue->merge(*red);
    }
}

void R(string choice, BinomialHeap* blue) {
    cout << "You encountered rare merchant" << endl;
    size_t start = choice.find('[') + 1;
    size_t end = choice.find(']');

    string brojStr = choice.substr(start, end - start);

    int broj = stoi(brojStr);

    for (size_t i = 0; i < broj; i++) {
        countBlue--;
        blue->removeTop();
    }
}

void F(string fileName, BinomialHeap*& red, BinomialHeap*& blue, bool& flag) {
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cout << "Error: Unable to open file " << fileName << endl;
        return;
    }

    string choice;
    while (getline(inputFile, choice)) {
        cout << "------------------------------" << endl;
        if (choice == "V") {
            cout << "You bought \033[1m\033[31mred\033[0m and \033[1m\033[34mblue\033[0m bag." << endl;
            red = new BinomialHeap(false);
            blue = new BinomialHeap(true);
            flag = true;
        } else if (choice == "B" && flag) {
            cout << "You sold your \033[1m\033[31mred\033[0m and \033[1m\033[34mblue\033[0m bag." << endl;
            B(red);
            B(blue);
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
            L(red, blue);
        } else if (choice.find('R') != string::npos && flag) {
            R(choice, blue);
        } else {
            cout << "Invalid command or missing bags. Skipping: " << choice << endl;
        }
    }

    inputFile.close();
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
    string filename;

    printMenu();
    while(true) {
        cin >> choice;
        cout << "------------------------------" << endl;
        if(choice == "F") {
            cin >> filename;
            F(filename, red, blue, flag);
        } else if (choice == "V") {
            cout << "You bought \033[1m\033[31mred\033[0m and \033[1m\033[34mblue\033[0m bag." << endl;
            red = new BinomialHeap(false); blue = new BinomialHeap(true);
            flag = true;
        } else if (choice == "B" && flag) {
            cout << "You sold your \033[1m\033[31mred\033[0m and \033[1m\033[34mblue\033[0m bag." << endl;
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
            L(red, blue);
        } else if (choice.find('R') != string::npos && flag) {
            R(choice, blue);
        }
    }
    return 0;
}