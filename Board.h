#include "Line.h"
#ifndef BOARD_CPP
#define BOARD_CPP
#include <SFML/Graphics.hpp>

class Board
{
private:
    Line* head;
    int width;
    int height;
public:
    Board(int a,int b);
    void display(sf::RenderWindow& window,sf::Color a[5] ) ;
    void shrink();
    int check_pop();
    void deleteTop();
    void restart(int a,int b);
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

int Board::check_pop(){
    Line*cur=head;
    Line*prev=nullptr;
    int x=0;
    while (cur){
       if(cur->isfull()){
        cur->pop(prev);
        cur->makehead(head);
        head=cur;
        x++;
       }
       prev=cur;
       cur=cur->next;
    }return x;
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

void Board::shrink(){
    if(width<=7)return;
    Line* cur=head;
    width--;
    while(cur){
        cur->shrink();
        cur=cur->next;
    }
}
void Board::deleteTop(){
    Line* temp=head;
    height--;
    head=head->next;
    delete temp;
}

    void Board::display(sf::RenderWindow& window,sf::Color a[5] ) {
        Line* current = head;
        int y=60;
        for (int i = 0; i < height; i++) {
            current->display(window,y,a);
            current = current->next;
            y+=32;
        }

        window.display();
    }
void Board::restart(int a, int b) {
    // Delete existing lines
    Line* temp = head;
    while (temp) {
        Line* temp2 = temp->next;
        delete temp;
        temp = temp2;
    }

    // Initialize the board with new dimensions
    width = a;
    height = b;
    head = new Line(a, nullptr);
    Line* oldnode = head;

    for (int i = 1; i < b; ++i) {
        Line* node = new Line(a, oldnode->head);
        oldnode->next = node;
        oldnode = node;
    }
}




Board::~Board()
{Line* temp=head;
    while (head){
        head=head->next;
        delete temp;
        temp=head;
    }
    
}



#endif // BOARD_CPP
