#include "Board.h"
#include "Tetrimo.h"
#include "Next.h"
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
sf::Color a[3][10] = {
        {sf::Color::Black, sf::Color(255, 85, 187), sf::Color(255, 211, 163), sf::Color(252, 255, 178), sf::Color(182, 234, 250),
         sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color(128, 0, 128)},
         
        {sf::Color(200, 200, 200), sf::Color::Blue, sf::Color::Green, sf::Color::Red, sf::Color::Yellow,
         sf::Color(255, 140, 0), sf::Color(0, 128, 0), sf::Color(128, 0, 0), sf::Color(255, 69, 0), sf::Color(128, 128, 0)},
         
        {sf::Color(18, 72, 107), sf::Color(65, 145, 151), sf::Color(120, 214, 198), sf::Color(245, 252, 205),
         sf::Color(245, 240, 187), sf::Color(219, 223, 170), sf::Color(179, 200, 144), sf::Color(241, 248, 100),
         sf::Color(188, 235, 60), sf::Color::Magenta}};

        sf::RenderWindow window(sf::VideoMode(2000, 1000), "SFML window", sf::Style::Fullscreen);

        void handleKeyPress(sf::Event& event, Tetrimo*& test, int& color, sf::Text text[], Board* board) ;
        void displayTheme(int cur);
        int color = 0;
        float timer=1.5;
    Board* board;
    Next* queue;
    Tetrimo* test ;
    int point = 0;
    int tetrimocounter=5;
    int oldpoint = 0;
    int combo = 0;
    int rotate=5;
    bool start[2] = {false,false};
    int switcher=0;
    bool restart=false;
    bool pause=false;
int main() {
    board=new Board(10,20);
    queue=new Next(board->midtop());
    test=queue->gethead();
    sf::Clock clock;
    float t1 = clock.getElapsedTime().asSeconds();
    float t2 = 0.0f;
    sf::Font font;
    sf::Text text[8];

    if (!font.loadFromFile("FontFile.ttf")) {
        std::cout << "Error loading file" << std::endl;
        return EXIT_FAILURE;
    }

    text[2].setFont(font);text[2].setString("Next:");text[2].setCharacterSize(22);text[2].setPosition(450, 170);text[2].setFillColor(a[color][3]);text[2].setStyle(sf::Text::Style::Italic);text[2].setOutlineThickness(10);
    text[0].setFont(font);text[0].setString("GAME OVER");text[0].setCharacterSize(200);text[0].setPosition(0, 0);text[0].setFillColor(a[color][4]);text[0].setStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);text[0].setOutlineThickness(10);
    text[1].setFont(font);text[1].setCharacterSize(50);text[1].setPosition(400, 60);text[1].setFillColor(a[color][1]);text[1].setStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);text[1].setOutlineThickness(10);text[1].setString("point: " + std::to_string(point));
    text[3].setFont(font);text[3].setString("Start");text[3].setCharacterSize(50);text[3].setPosition(200, 200);text[3].setFillColor(a[color][3]);text[3].setStyle(sf::Text::Style::Italic);text[3].setOutlineThickness(10);
    text[4].setFont(font);text[4].setString("Themes");text[4].setCharacterSize(50);text[4].setPosition(200, 400);text[4].setFillColor(a[color][4]);text[4].setStyle(sf::Text::Style::Italic);text[4].setOutlineThickness(10);
    text[5].setFont(font);text[5].setString("Hold:");text[5].setCharacterSize(22);text[5].setPosition(450, 410);text[5].setFillColor(a[color][3]);text[5].setStyle(sf::Text::Style::Italic);text[5].setOutlineThickness(10);
    text[6].setFont(font);text[6].setCharacterSize(50);text[6].setPosition(400, 500);text[6].setFillColor(a[color][6]);text[6].setStyle(sf::Text::Style::Bold );text[6].setOutlineThickness(10);
    text[7].setFont(font);text[7].setString("||");text[7].setCharacterSize(200);text[7].setPosition(900, 400);text[7].setFillColor(a[color][4]);text[7].setStyle(sf::Text::Style::Bold );text[7].setOutlineThickness(20);


    while (window.isOpen()) {
        sf::Event event;
        
       /* if (restart){
            Board*tempb=board;
            Next*tempq=queue;
            
            board= new Board(10,20); 
            queue=new Next(board->midtop());
            test=queue->gethead();
            point=0;
            oldpoint=0;
            restart=false;
            delete tempb;
            delete tempq ;
        }*/

        if (start[0] && !start[1] && !pause) {
            t1 = clock.getElapsedTime().asSeconds();
            if (t1 - t2 >= timer && test) {
                if (combo)combo=0;
                if (!test->move('s')) {
                    point += 5;
                    rotate=5;
                    combo = board->check_pop();
                    point += combo * 20;
                    tetrimocounter++;
                    text[1].setString("point: " + std::to_string(point));
                    text[6].setString("X  " +std::to_string(combo));
                    if (point - oldpoint > 100) {
                        oldpoint += 100;
                        timer*=0.8;
                        board->shrink();
                        board->deleteTop();
                        combo = board->check_pop();
                    }
                    test = queue->addnextone(board->midtop());
                }t2 = t1;
                
            }
        }
        while (window.pollEvent(event)) {
            if (!start[0] &&!start[1]&& event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                start[switcher]= true;
                
            }
                handleKeyPress(event, test, color, text, board);
            
        }

         sf::RectangleShape selector(sf::Vector2f(10,10));
    selector.setPosition(175,switcher*200+225);
    selector.setFillColor(sf::Color::White);

        window.clear(sf::Color(20, 20, 20));
        if (!start[0]&& !start[1]) {
            window.draw(selector);
            window.draw(text[3]);
            window.draw(text[4]);
        } else if(start[0]) {
            if (test) {
                window.draw(text[1]);
                window.draw(text[2]);
                window.draw(text[5]);
                if(pause)window.draw(text[7]);
                if (combo)window.draw(text[6]);
                queue->display(window, a[color]);
                board->display(window, a[color]);
            } else {
                window.draw(text[0]);
            }
        }else{
            displayTheme(color);
        }
        
        window.display();
    }

    return 0;
}

void displayTheme(int cur){
    const int boxSize = 30;
    const int spacing = 5;
    const int startX = 50;
    const int startY = 50;
    sf::RectangleShape selected(sf::Vector2f(360,40));
    selected.setPosition(45,45+cur*50);
    selected.setFillColor(sf::Color::White);
    window.draw(selected);
    for (int j=0;j<3;j++)
    for (int i = 0; i < 10; ++i) {
        sf::RectangleShape colorBox(sf::Vector2f(boxSize, boxSize));
        colorBox.setPosition(startX + i * (boxSize + spacing), startY*(j+1));
        colorBox.setFillColor(a[j][i]);
        window.draw(colorBox);
    }
}

void handleKeyPress(sf::Event& event, Tetrimo*& test, int& color, sf::Text text[], Board* board) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Right:
                if (test && !pause && start[0]) test->move('r');
                break;
            case sf::Keyboard::Left:
                if (test && !pause && start[0]) test->move('l');
                break;
            case sf::Keyboard::Down:
                if (test && !pause && start[0]) test->move('d');
                if(!start[0]&&!start[1]){
                    switcher++;
                    switcher%=2;
                }
                break;
            case sf::Keyboard::Up:
                if (test && !pause && rotate && start[0]){test->rotate(1);rotate--;} 
                if(!start[0]&&!start[1]){
                    switcher--;
                    switcher+=2;
                    switcher%=2;
                }
                break;
            case sf::Keyboard::LAlt:
                if (test && !pause && rotate && start[0]) {test->rotate(1);rotate--;} 
                break;
            case sf::Keyboard::H:
                if (tetrimocounter>=5 && start[0]){
                test=queue->hold(board->midtop());tetrimocounter=0;}
                break;    
            case sf::Keyboard::Tab:
                color += 1;
                color %= 3;
                text[1].setFillColor(a[color][1]);
                text[6].setFillColor(a[color][6]);
                break;
            case sf::Keyboard::Escape:
                window.close();
                break;
            case sf::Keyboard::B:
                start[0]=false;
                start[1]=0;
                break;
           /* case sf::Keyboard::R:
                if(start[0])
                restart=true;
                break;*/
            case sf::Keyboard::P:
                if(start[0])
                pause=!pause;
                break;
            default:
                break;
        }
    }
}

