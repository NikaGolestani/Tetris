#include "Cell.h"
#include <iostream>

#ifndef TETRIMO_H
#define TETRIMO_H

class Tetrimo {
private:
    int arr[4][4] = {{0}};
    bool end=false;
public:
    Cell* orjin;
    Tetrimo(int color, int type, Cell* o);
    bool check(Cell* o, int brr[4][4]) const;
    bool move(char a);
    void lockT();
    void display(sf::RenderWindow& window,int start,sf::Color a[5] );
    void deleteFromBoard();
    bool addToBoard();
    bool rotate(int r);
    friend class Next;
    ~Tetrimo();
};

Tetrimo::Tetrimo(int color, int type, Cell* o) {
    orjin = o;
    switch (type) {
        case 0://L
            arr[0][0] = arr[1][1] = arr[1][2] = arr[1][0] = color;
            break;
        case 1://corner
            arr[0][0] = arr[1][0] = arr[1][1] = color;
            break;
        case 2://line
            arr[1][0] = arr[1][1] = arr[1][2]  = color;
            break;
        case 3://square
            arr[1][0] = arr[0][0] = arr[0][1] = arr[1][1] = color;
            break;
        case 4://step/zigzag
            arr[2][0] = arr[2][1] = arr[1][2] = arr[1][1] = color;
            break;
        case 5://plus
        arr[0][1] = arr[1][0] = arr[1][1] = arr[1][2] = arr[2][1] = color;
            break;
        case 6://pyramid
            arr[0][0] = arr[1][0] = arr[2][0] = arr[1][1] = color;
                break;
        case 7://U
            arr[1][0] = arr[0][0] = arr[0][1] = arr[0][2] = arr[1][2] = color;
            break;
        case 8://arrow
            arr[1][0] = arr[0][0] = arr[1][1] = arr[0][2] = arr[1][2] = arr[2][1] = color;
            break;
        case 9://long zigzag
            arr[2][0] = arr[2][1] = arr[0][2] = arr[1][1] = arr[0][1] = color;
            break;
        default://square
            arr[1][0] = arr[0][0] = arr[0][1] = arr[1][1] = color;
            break;
    }

}

bool Tetrimo::check(Cell* o, int brr[4][4]) const {
    Cell* temp = o;
    Cell* temp2;
    int is_zero = 0;
    int x=0;
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
    temp2=o;
    while(temp2){
        temp2=temp2->right;
        x++;
    }
    if((brr[0][x]||brr[1][x]||brr[2][x]||brr[3][x])&& x<4)return false;
    return true;
}

bool Tetrimo::move(char a) {
    Cell* temp;

    switch (a) {
        case 'l':
            temp = orjin->left;
            if(!temp)return false;
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
        case 's':
            if (!orjin->down->down) {lockT();return false;}
            else temp = orjin->down;
            break;
        default:
            return false;  // invalid input
    }

    if (check(temp, arr)) {
        
        deleteFromBoard();
        orjin = temp;
        addToBoard();
        return true;
    } else {if(a=='s')lockT();
        return false;
    }
}

void Tetrimo::lockT(){
    Cell* temp = orjin;
    Cell* temp2;
    int i;
    for ( i = 0; i < 4 && temp; i++) {
        temp2 = temp;
        for (int j = 0; j < 4 && temp2; j++) {
            if (temp2->item)
            temp2->lock = 1;
            temp2 = temp2->right;
        }
        temp = temp->top;
        
    }
    end=(!temp && i!=4&& (arr[i][0]||arr[i][1]||arr[i][2]||arr[i][3]));

}

void Tetrimo::display(sf::RenderWindow& window, int start, sf::Color a[5]) {
    int x = 450;

    for (int i = 3; i >= 0; i--) {
        for (int j = 0; j < 4; j++) {
            sf::RectangleShape cellRect(sf::Vector2f(15, 15));
            cellRect.setPosition(x, start);

            // Set color based on the integer value
           if (arr [i][j]) {
            cellRect.setFillColor(a[arr[i][j]]);

            window.draw(cellRect);}
            x += 16;
        }

        start += 16;
        x = 450; // Reset x for the next row
    }
}

void Tetrimo::deleteFromBoard() {
    Cell* temp = orjin;
    Cell* temp2;

    for (int i = 0; i < 4 && temp; i++) {
        temp2 = temp;
        for (int j = 0; j < 4 && temp2; j++) {
            if (!temp2->lock)
            temp2->item = 0;
            temp2 = temp2->right;
        }
        temp = temp->top;
    }
}

bool Tetrimo::addToBoard() {
    Cell* temp = orjin;
    Cell* temp2 = orjin;
    int is_zero = 0;

    for (int i = 0; i < 4 && temp; i++) {
        temp2 = temp;
        for (int j = 0; j < 4 && temp2; j++) {
            if (arr[i][j] != 0){
                if (temp2->lock)return false;
                temp2->item = arr[i][j];}
            temp2 = temp2->right;
            if (arr[i][j]) is_zero = 1;
        }
        if (is_zero) temp = temp->top;
    }return true;
}

bool Tetrimo::rotate(int r) {
    int brr[4][4];
    int crr[4][4]={{0}};
    int zerocolcounter=0;
    Cell* ptr = orjin;
    int jch = -(2 - r);
    int ich = 2 - r;
    int ja, ia;
    (jch == -1) ? ja = 3 : ja = 0;
    (ich == -1) ? ia = 3 : ia = 0;
    int x = 0;
    bool c=false;
    int counter = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            brr[ja + (jch * j)][ia + (ich * i)] = arr[i][j];
        }
    }
    for (int i = 0; i < 4; i++) {

    if(brr[0][i]==brr[1][i] && brr[1][i]==brr[2][i] && brr[2][i]==brr[3][i] && brr[0][i]==0)
        counter++;
    else
        break;
}

        for (int i = 0; i < 4; i++) {
            for (int j = counter; j < 4; j++) {
                
                crr[i][j-counter] = brr[i][j];
                
            }    
        }
        

    c= check(ptr, crr);

   while (!c && x != 3 && ptr->right) {
        ptr = ptr->right;
        c= check(ptr, crr);
        x++;

    }
    if(!c){x=0;ptr=orjin;}
    while (!c && x != 3 && ptr->left) {
        ptr = ptr->left;
        c= check(ptr, crr);
        x++;
    }
    if (c) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                arr[i][j] = crr[i][j];
            }
        }
        deleteFromBoard();
        orjin = ptr;
        addToBoard();
    }

    return c;  
}

Tetrimo::~Tetrimo() {
    
}

#endif  // TETRIMO_H
