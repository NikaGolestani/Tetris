#include "Line.h"
#ifndef BOARD_CPP
#define BOARD_CPP

class Board
{
private:
    Line* head;
    int width;
    int height;
public:
    Board(int a,int b);
    void Board::display();
    ~Board();
};

Board::Board(int a,int b)
{
    width=a;
    height=b;
    head=new Line(a,nullptr);
    Line *node,*oldnode=head;
    for (int i=0;i<b;i++){
        node=new Line(a,oldnode->head);
        oldnode=node;
    }
}
void Board::display() {

        Cell* current = head->head;
        Cell* current2;
        for(int i=0;i<height;i++) {
            current2=current;
            for(int j=0;j<width;j++){
            std::cout << current2->item << " ";
            current2=current2->right;
            }
            current=current->top;
        }
        std::cout << std::endl;
    };

Board::~Board()
{
}



#endif // BOARD_CPP
