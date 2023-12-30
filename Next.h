#include "Tetrimo.h"
#include <random>

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 9);

class Next
{
private:
    Tetrimo* arr[5];    
public:
    Next(Cell* orjin);
    Tetrimo* gethead();
    Tetrimo* addnextone(Cell* o);
    Tetrimo* hold(Cell* o);
    void display(sf::RenderWindow& window,sf::Color a[5] );
    ~Next();
};

Next::Next(Cell* orjin)
{
    for(int i=0;i<4;i++){
        arr[i]=new Tetrimo(distribution(gen) % 4 + 1, distribution(gen), nullptr);
    }
    arr[0]->orjin=orjin;
    arr[0]->addToBoard();
}

Tetrimo* Next::addnextone(Cell* o){
    if (arr[0]->end||o->item)return nullptr;
    delete arr[0];
    for(int i=0;i<3;i++){
        arr[i]=arr[i+1];
    }
    arr[3]=new Tetrimo(distribution(gen) % 9 + 1, distribution(gen), nullptr);
    arr[0]->orjin=o;
    return arr[0];
}

Tetrimo* Next::gethead(){
    return arr[0];
}

void Next::display(sf::RenderWindow& window, sf::Color a[5]) {
    int y = 200;
    for (int i = 1; i < 4; i++) {
        arr[i]->display(window, y, a);
        y += 65;
    }
    if (arr[4])arr[4]->display(window, 450, a);
}

Tetrimo* Next::hold(Cell* o){
    arr[0]->deleteFromBoard();
    if (!arr[4]){
        arr[4]=arr[0];
        for (int i=0;i<3;i++){
            arr[i]=arr[i+1];
        }arr[3]=new Tetrimo(distribution(gen) % 9 + 1, distribution(gen), nullptr);
    }else{
        Tetrimo*temp=arr[0];
        arr[0]=arr[4];
        arr[4]=temp;
    }
    arr[0]->orjin=o;
    arr[0]->addToBoard();
    return arr[0];
}

Next::~Next()
{
    for(int i=0;i<4;i++){
        if(arr[i])delete arr[i];
    }
}
