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
    void display();
    Cell* midtop();
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
        oldnode->next=node;
        oldnode=node;
    }
}

Cell* Board::midtop(){
    Cell* cur1=head->head,*cur2=head->head;
    
    while(cur1 && cur1->right){
        cur1=cur1->right->right;
        cur2=cur2->right;
    }
    cur2=cur2->left->left;
    return cur2;

}

void Board::display() {

        Line* current = head;
        
        for(int i=0;i<height;i++) {
            current->display();
            current=current->next;
        }
        std::cout << std::endl;
    };

Board::~Board()
{
}



#endif // BOARD_CPP
