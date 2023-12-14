//each Line contains n cells and should be conected to lower one line is a linked list
#include "Cell.h"
#include <iostream>
#ifndef LINE_CPP
#define  LINE_CPP

class Line
{
private:
    
    int max;
public:
    Cell* head;
    Line(int n, Cell* prev);
    ~Line();
    void display();
};

Line::Line(int n,Cell* prev)
{
    max=n;
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
    void Line::display() {

        Cell* current = head;
        while (current != nullptr) {
            std::cout << current->item << " ";
            current = current->right;
        }
        std::cout << std::endl;
    };

Line::~Line()
{
}

#endif // LINE_CPP
