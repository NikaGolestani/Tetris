#ifndef SCOREBOARD_CPP
#define SCOREBOARD_CPP

#include <iostream>
#include <fstream>
#include <string>
sf::Text text;
sf::Font font;
std::string mytext="";
bool txt=false;
int count=0;

struct TreeNode {
    int data;
    std::string name;
    TreeNode* left;
    TreeNode* right;

    TreeNode(std::string player, int value) : name(player), data(value), left(nullptr), right(nullptr) {}
};

class ScoreBoard {
private:
    int index = 0;
    int count=0;

public:
TreeNode* root;
    ScoreBoard();
    void inorderTraversal(TreeNode* root) ;
    void display( sf::RenderWindow& window);
    TreeNode* insert(std::string player, int value, TreeNode* root);
    void save(std::ofstream& outFile, TreeNode* root);
    ~ScoreBoard();
};

ScoreBoard::ScoreBoard() {
    std::ifstream file("score.txt");
    font.loadFromFile("FontFile.ttf");
    if (!file.is_open()) {
        std::cout << "Error opening file: " << std::endl;
        return;
    }

    int score;
    std::string player_name;

    while (file >> score >> player_name) {
        root = insert(player_name, score, root);
    }

    file.close();
}

TreeNode* ScoreBoard::insert(std::string player, int value, TreeNode* root) {
    index++;

    if (root == nullptr) {
        return new TreeNode(player, value);
    }


    if (value > root->data) {
        root->left = insert(player, value, root->left);
    }
  
    else if (value < root->data) {
        root->right = insert(player, value, root->right);
    }else{
        root->name+="||"+player;
    }


    return root;
}

void ScoreBoard::inorderTraversal(TreeNode* root) {

    if (root != nullptr ) {
        inorderTraversal(root->left);
        if(count<=5){
        mytext += std::to_string(root->data) + "  " + root->name + "\n";
        count++;
        }else return;
        inorderTraversal(root->right);
        
    }

   
}

void ScoreBoard::display( sf::RenderWindow& window){
    mytext="";
    count=0;
    inorderTraversal(root);
    text.setFont(font);
    text.setString(mytext);
    text.setCharacterSize(40);
    text.setPosition(200, 200);
    text.setFillColor(sf::Color(250, 200, 250));
    text.setStyle(sf::Text::Style::Italic);
    text.setOutlineThickness(10);
    window.draw(text);
}


void ScoreBoard::save(std::ofstream& outFile, TreeNode* root) {
    if (root != nullptr) {
        // Save the current node's data to the file
        outFile << root->data << " " << root->name << std::endl;

        // Recursive call for left and right subtrees
        save(outFile, root->left);
        save(outFile, root->right);
    }
}

ScoreBoard::~ScoreBoard() {}

#endif // SCOREBOARD_CPP
