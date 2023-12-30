#ifndef CELL_CPP
#define CELL_CPP

class Cell
{
private:
        Cell* top;
        Cell* right;
        Cell* left;
        Cell* down;
        int lock=0;
        int item;
public:
    Cell(int value){
        item=value;
        top=nullptr;
        right=nullptr;
        left=nullptr;
        down=nullptr;

    }
    friend class Line;
    friend class Board;
    friend class Tetrimo;
    friend class Next;
    ~Cell(){
        
    };
};

#endif // CELL_CPP
