//each Line contains n cells and should be conected to lower one line is a linked list
#include "Cell.h"
#include <iostream>
#ifndef LINE_CPP
#define  LINE_CPP
#include <SFML/Graphics.hpp>

class Line
{
private:
    Line* next;
    Cell* head;
public:
    Line(int n, Cell* prev);
    bool isfull();
    void pop(Line* prev);
    void makehead(Line* headb);
    void display(sf::RenderWindow& window,int start,sf::Color a[5] );
    void shrink();
    friend class Board;
    ~Line();
    
};

Line::Line(int n,Cell* prev)
{

     Cell* node=new Cell(0);
     head=node;
     Cell* cur=head;
     if (prev){ 
        head->top=prev;
        prev->down=head;}
     for(int i=1;i<n;i++){
        node = new Cell(0);
        cur->right = node;
        node->left = cur;
        cur = cur->right;
        
        if (prev){
            prev=prev->right;
            node->top=prev;
            prev->down=node;
            node->top=prev;
        }

     }
}
    void Line::display(sf::RenderWindow& window,int start,sf::Color a[5] ) {
        Cell* current = head;
        int x=60;
        
        while (current != nullptr) {
            sf::RectangleShape cellRect(sf::Vector2f(30, 30)); // Adjust size as needed
            cellRect.setPosition(x,start);
            
            // Set color based on the integer value
 
                cellRect.setFillColor(a[current->item]); 
            

            window.draw(cellRect);
            current = current->right;
            x+=32;
        }
    
    }
    bool Line::isfull(){
        Cell* current=head;
        while(current){
            if (current) {
        if (current->item == 0) {
            return false;
        }current=current->right;
} else {
    // Handle the case when 'current' is nullptr (e.g., print an error message).
    return false;
}
        }return true;
    }
    void Line::pop(Line* prev){
        Cell* cur=head;
        if (!prev)return;
        prev->next=next;
        Cell* curprev=prev->head;
        while(cur && next){
            curprev->down=cur->down;
            cur->down->top=curprev;
            cur=cur->right;
            curprev=curprev->right;
        }
        while(cur && !cur->down){
            curprev->down=cur->down;
            cur=cur->right;
            curprev=curprev->right;
        }
    }

    void Line::shrink(){
        Cell* temp=head;
        head=head->right;
        temp->right->left=nullptr;
        delete temp;
    }

    void Line::makehead(Line*headb){
        Cell* cur=head;
        Cell* curnext=headb->head;
        next=headb;
        while(cur){
            cur->top=nullptr;
            cur->down=curnext;
            curnext->top=cur;
            cur->item=0;
            cur->lock=0;
            cur=cur->right;
            curnext=curnext->right;
        }
    }

Line::~Line()
{
    // Iterate through each cell in the line and delete them
    Cell* current = head;
    while (current) {
        Cell* temp = current;
        current = current->right;  // Move to the next cell
        if (temp->down)
            temp->down->top = nullptr;
        delete temp; 
    }
    next=nullptr;
    head = nullptr;  
}

//g++ main.cpp -lsfml-system -lsfml-window -lsfml-graphics -o test
#endif // LINE_CPP
