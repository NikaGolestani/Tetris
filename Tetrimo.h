#include "Cell.h"
#include <iostream>

#ifndef TETRIMO_H
#define TETRIMO_H

class Tetrimo {
private:
    int arr[4][4] = {{0}};
    Cell* orjin;

public:
    Tetrimo(int color, int type, Cell* o);
    bool move(char a);
    void display();
    void deleteFromBoard();
    void addToBoard();
    bool rotate(int r);
    bool check(Cell* o,int brr[4][4]) const;
    ~Tetrimo();
};

Tetrimo::Tetrimo(int color, int type, Cell* o) {
    orjin = o;
    switch (type) {
        case 0:
            arr[0][0] = arr[1][1] = arr[1][2] = arr[1][0] = color;
            break;
        case 1:
            arr[1][1] = arr[2][1] = arr[2][2] = arr[2][0] = color;
            break;
        case 2:
            arr[1][0] = arr[1][1] = arr[1][2] = arr[1][3] = color;
            break;
        case 3:
            arr[2][1] = arr[1][1] = arr[1][2] = arr[2][2] = color;
            break;
        case 4:
            arr[2][0] = arr[2][1] = arr[1][2] = arr[1][1] = color;
            break;
        default:
            arr[2][1] = arr[1][1] = arr[1][2] = arr[2][2] = color;
            break;
    }
    addToBoard();
}

bool Tetrimo::check(Cell* o, int brr[4][4]) const {
    Cell* temp = o;
    Cell* temp2;
    int is_zero = 0;

    for (int i = 0; i < 4 && temp; i++) {
        temp2 = temp;
        for (int j = 0; j < 4; j++) {
            if (brr[i][j] && (!temp2 || temp2->lock)) {
                return false;  // cannot pass
            }

            if (temp2) temp2 = temp2->right;

            if (brr[i][j]) is_zero = 1;
        }
        if (is_zero) temp = temp->top;
    }
    return true;
}

bool Tetrimo::move(char a) {
    Cell* temp;

    switch (a) {
        case 'l':
            temp = orjin->left;
            break;
        case 'r':
            temp = orjin->right;
            break;
        case 't':
            temp = orjin->top;
            break;
        case 'd':
            if (!orjin->down->down) return false;
            temp = orjin->down;
            break;
        default:
            return false;  // invalid input
    }

    if (check(temp, arr)) {
        deleteFromBoard();
        orjin = temp;
        addToBoard();
        return true;
    } else {
        return false;
    }
}

void Tetrimo::deleteFromBoard() {
    Cell* temp = orjin;
    Cell* temp2;

    for (int i = 0; i < 4 && temp; i++) {
        temp2 = temp;
        for (int j = 0; j < 4 && temp2; j++) {
            temp2->item = 0;
            temp2 = temp2->right;
        }
        temp = temp->top;
    }
}

void Tetrimo::addToBoard() {
    Cell* temp = orjin;
    Cell* temp2 = orjin;
    int is_zero = 0;

    for (int i = 0; i < 4 && temp; i++) {
        temp2 = temp;
        for (int j = 0; j < 4 && temp2; j++) {
            if (arr[i][j] != 0)
                temp2->item = arr[i][j];
            temp2 = temp2->right;
            if (arr[i][j]) is_zero = 1;
        }
        if (is_zero) temp = temp->top;
    }
}

bool Tetrimo::rotate(int r) {
    int brr[4][4];
    Cell* ptr = orjin->left;
    int jch = -(2 - r);
    int ich = 2 - r;
    int ja, ia;
    (jch == -1) ? ja = 3 : ja = 0;
    (ich == -1) ? ia = 3 : ia = 0;
    int x = 0;
    int counter = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            brr[ja + (jch * j)][ia + (ich * i)] = arr[i][j];
        }
    }

    while (!x && counter != 3) {
        ptr = ptr->right;
        x = check(ptr, brr);
        counter++;
    }
    if (x) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                arr[i][j] = brr[i][j];
            }
        }
        deleteFromBoard();
        orjin = ptr;
        addToBoard();
    }

    return x;  // Placeholder, modify as needed
}

Tetrimo::~Tetrimo() {}

#endif  // TETRIMO_H
