#include "Tetrimo.h"
#include <random>
#include <iostream>
#include <fstream>
#include <string>

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 12);
Tetrimo* arr[5];  
class Next
{
private:
      
    int count=0;
public:
    bool cpempty[3]={true,true,true};
    int cp[3][4][4];
    bool cpasked=false;
    Next(Cell* orjin);
    Tetrimo* gethead();
    void addCostumPiece();
    void displaycp(sf::RenderWindow& window);
    Tetrimo* addnextone(Cell* o);
    Tetrimo* hold(Cell* o);
    void display(sf::RenderWindow& window,sf::Color a[5] );
    void cpcheck();
    void saveCP();
    Tetrimo* restart(Cell* orjin);
    ~Next();
};

Next::Next(Cell* orjin)
{
    for(int i=0;i<4;i++){
        arr[i]=new Tetrimo(distribution(gen) % 4 + 1, distribution(gen)%4, nullptr);
    }
    arr[0]->orjin=orjin;
    arr[0]->addToBoard();
    cpcheck();
}

Tetrimo* Next::addnextone(Cell* o){
    count++;
    int randi=0;
    if (arr[0]->end||o->item)return nullptr;
    delete arr[0];
    for(int i=0;i<3;i++){
        arr[i]=arr[i+1];
    }
    randi=distribution(gen);
    if(randi<10 || cpempty[randi-10]||!cpasked)
    arr[3]=new Tetrimo(distribution(gen) % 9 + 1, randi%((count/4)+4), nullptr);
    else
    arr[3]=new Tetrimo(distribution(gen) % 9 + 1, cp[randi-10], nullptr);
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

Tetrimo* Next::restart(Cell* orjin){
    for(int i=0;i<4;i++){
        if(arr[i])delete arr[i];
    }
     for(int i=0;i<4;i++){
        arr[i]=new Tetrimo(distribution(gen) % 4 + 1, distribution(gen)%4, nullptr);
    }
    arr[0]->orjin=orjin;
    arr[0]->addToBoard();
    return arr[0];
}
void Next::addCostumPiece() {
    std::ifstream inputFile("Custom.txt");

    if (inputFile.is_open()) {
        for (int k = 0; k < 3; ++k) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (!(inputFile >> cp[k][i][j])) {
                        std::cerr << "Error reading from file.\n";
                        return;
                    }
                }
            }
        }
        inputFile.close();
        
    } 
}
void Next::cpcheck(){
   for (int k = 0; k < 3; k++) {
        cpempty[k] = true; // Assume empty until proven otherwise
        for (int i = 0; i < 4 && cpempty[k]; i++) {
            for (int j = 0; j < 4 && cpempty[k]; j++) {
                if (cp[k][i][j] != 0) {
                    cpempty[k] = false; // Found a non-zero element, mark as not empty
                }
            }
        }
    }
}

void Next::displaycp(sf::RenderWindow& window){
 int x = 200;
 int y=200;
    for (int k = 0; k <3; k++){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            sf::RectangleShape cellRect(sf::Vector2f(15, 15));
            cellRect.setPosition(x, y);
           if (cp [k][i][j]) 
            cellRect.setFillColor(sf::Color::White);
            else 
            cellRect.setFillColor(sf::Color(50,50,50));
            window.draw(cellRect);
            x += 16;
        }
        y += 16;
        x = 200; // Reset x for the next row
    }y+=30;
}}

void Next::saveCP() {
    std::ofstream outputFile("Custom.txt");

    if (outputFile.is_open()) {
        for (int k = 0; k < 3; ++k) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    outputFile << cp[k][i][j] << " ";
                }
                outputFile << std::endl;
            }
        }

        outputFile.close();
    } else {
        std::cerr << "Error opening file for writing.\n";
    }
}

Next::~Next()
{
    for(int i=0;i<4;i++){
        if(arr[i])delete arr[i];
    }
}
