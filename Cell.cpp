

class Cell
{
private:
        Cell* top;
        Cell* right;
        Cell* left;
        Cell* down;
        int item;
public:
    Cell(int value){
        item=value;
        top=nullptr;
        right=nullptr;
        left=nullptr;
        down=nullptr;

    }
    ~Cell();
};


