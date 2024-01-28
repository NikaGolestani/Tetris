#include "Board.h"
#include "Tetrimo.h"
#include "Next.h"
#include <iostream>
#include <random>
#include <SFML/Audio.hpp> 
#include <SFML/Graphics.hpp>
#include "ScoreBoard.h"
//g++ main.cpp -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -o test

std::string mytxt="";
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
        float timer=1;
    Board* board;
     ScoreBoard scoreboard;
    Next* queue;
    Tetrimo* test ;
    int point = 0;
    int tetrimocounter=5;
    int oldpoint = 0;
    int combo = 0;
    int rotate=5;
    bool start[6] = {false,false,false,false,false,false};
    int switcher=0;
    bool pause=false;
    int diff=1;
    sf::SoundBuffer buff[8];
    sf::Sound valid[2];
    sf::Sound other[6];
    bool nametaker=false;
    int xcp=0;
    int ycp=0;
int main() {
    sf::Music bgmusic;
    board=new Board(10,20);
    queue=new Next(board->midtop());
    queue->addCostumPiece();
    test=queue->gethead();
    sf::Clock clock;
    float t1 = clock.getElapsedTime().asSeconds();
    float t2 = 0.0f;
    sf::Font font;
    sf::Text text[21];
    
    bgmusic.openFromFile("bgmusic.ogg");
    buff[0].loadFromFile("oops.ogg");
    buff[1].loadFromFile("move.ogg");
    buff[2].loadFromFile("pop.ogg");
    buff[3].loadFromFile("lvlup.ogg");
    buff[4].loadFromFile("lock.ogg");
    buff[5].loadFromFile("gameover.ogg");
    buff[6].loadFromFile("select.ogg");
    buff[7].loadFromFile("s.ogg");

    valid[0].setBuffer(buff[0]);
    valid[1].setBuffer(buff[1]);
    other[0].setBuffer(buff[2]);
    other[1].setBuffer(buff[3]);
    other[2].setBuffer(buff[4]);
    other[3].setBuffer(buff[5]);
    other[4].setBuffer(buff[6]);
    other[5].setBuffer(buff[7]);
    bgmusic.setLoop(true);
    bgmusic.setVolume(25);
    bgmusic.play();
    if (!font.loadFromFile("FontFile.ttf")) {
        std::cout << "Error loading file" << std::endl;
        return EXIT_FAILURE;
    }

    text[2].setFont(font);text[2].setString("Next:");text[2].setCharacterSize(22);text[2].setPosition(450, 170);text[2].setFillColor(a[color][3]);text[2].setStyle(sf::Text::Style::Italic);text[2].setOutlineThickness(10);
    text[0].setFont(font);text[0].setString("GAME OVER");text[0].setCharacterSize(200);text[0].setPosition(0, 0);text[0].setFillColor(a[color][4]);text[0].setStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);text[0].setOutlineThickness(10);
    text[1].setFont(font);text[1].setCharacterSize(50);text[1].setPosition(400, 60);text[1].setFillColor(a[color][1]);text[1].setStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);text[1].setOutlineThickness(10);text[1].setString("point: " + std::to_string(point));
    text[3].setFont(font);text[3].setString("Start");text[3].setCharacterSize(50);text[3].setPosition(200, 200);text[3].setFillColor(a[color][3]);text[3].setStyle(sf::Text::Style::Italic);text[3].setOutlineThickness(10);
    text[4].setFont(font);text[4].setString("Themes");text[4].setCharacterSize(50);text[4].setPosition(200, 300);text[4].setFillColor(a[color][4]);text[4].setStyle(sf::Text::Style::Italic);text[4].setOutlineThickness(10);
    text[5].setFont(font);text[5].setString("Hold:");text[5].setCharacterSize(22);text[5].setPosition(450, 410);text[5].setFillColor(a[color][3]);text[5].setStyle(sf::Text::Style::Italic);text[5].setOutlineThickness(10);
    text[6].setFont(font);text[6].setCharacterSize(50);text[6].setPosition(400, 500);text[6].setFillColor(a[color][6]);text[6].setStyle(sf::Text::Style::Bold );text[6].setOutlineThickness(10);
    text[7].setFont(font);text[7].setString("||");text[7].setCharacterSize(200);text[7].setPosition(900, 400);text[7].setFillColor(a[color][4]);text[7].setStyle(sf::Text::Style::Bold );text[7].setOutlineThickness(20);
    text[8].setFont(font);text[8].setString("LeaderBoard");text[8].setCharacterSize(50);text[8].setPosition(200, 400);text[8].setFillColor(a[color][8]);text[8].setStyle(sf::Text::Style::Italic);text[8].setOutlineThickness(10);
    text[9].setFont(font);text[9].setString("Quite");text[9].setCharacterSize(50);text[9].setPosition(200, 700);text[9].setFillColor(a[color][9]);text[9].setStyle(sf::Text::Style::Italic);text[9].setOutlineThickness(10);
    text[10].setFont(font);text[10].setString("");text[10].setCharacterSize(50);text[10].setPosition(200, 800);text[10].setFillColor(sf::Color::White);text[10].setStyle(sf::Text::Style::Italic);text[10].setOutlineThickness(10);
    text[11].setFont(font);text[11].setString("Type Your Name:");text[11].setCharacterSize(50);text[11].setPosition(200, 600);text[11].setFillColor(a[color][1]);text[11].setStyle(sf::Text::Style::Italic);text[11].setOutlineThickness(10);
    text[12].setFont(font);text[12].setString("Press Tab to change theme ");text[12].setCharacterSize(50);text[12].setPosition(500, 900);text[12].setFillColor(a[color][1]);text[12].setStyle(sf::Text::Style::Italic);text[12].setOutlineThickness(10);
    text[13].setFont(font);text[13].setString("Press B to go back to main menu ");text[13].setCharacterSize(50);text[13].setPosition(500, 800);text[13].setFillColor(a[color][1]);text[13].setStyle(sf::Text::Style::Italic);text[13].setOutlineThickness(10);
    text[14].setFont(font);text[14].setString("Difficulty");text[14].setCharacterSize(50);text[14].setPosition(200, 500);text[14].setFillColor(a[color][4]);text[14].setStyle(sf::Text::Style::Italic);text[14].setOutlineThickness(10);
    text[15].setFont(font);text[15].setString("Easy");text[15].setCharacterSize(50);text[15].setPosition(200, 200);text[15].setFillColor(a[color][3]);text[15].setStyle(sf::Text::Style::Italic);text[15].setOutlineThickness(10);
    text[16].setFont(font);text[16].setString("Medium");text[16].setCharacterSize(50);text[16].setPosition(200, 350);text[16].setFillColor(a[color][2]);text[16].setStyle(sf::Text::Style::Italic);text[16].setOutlineThickness(10);
    text[17].setFont(font);text[17].setString("Hard");text[17].setCharacterSize(50);text[17].setPosition(200, 500);text[17].setFillColor(a[color][8]);text[17].setStyle(sf::Text::Style::Italic);text[17].setOutlineThickness(10);
    text[18].setFont(font);text[18].setString("Custom Pieces");text[18].setCharacterSize(50);text[18].setPosition(200, 600);text[18].setFillColor(a[color][5]);text[18].setStyle(sf::Text::Style::Italic);text[18].setOutlineThickness(10);
    text[19].setFont(font);text[19].setString("Press C to available Custom Piece ");text[19].setCharacterSize(50);text[19].setPosition(500, 900);text[19].setFillColor(a[color][1]);text[19].setStyle(sf::Text::Style::Italic);text[19].setOutlineThickness(10);
    text[20].setFont(font);text[20].setString("Press S to change cell");text[20].setCharacterSize(50);text[20].setPosition(500, 900);text[20].setFillColor(a[color][1]);text[20].setStyle(sf::Text::Style::Italic);text[20].setOutlineThickness(10);


    while (window.isOpen()) {
        sf::Event event;
        if (start[5])window.close();

        if (start[0]  && !pause) {
            t1 = clock.getElapsedTime().asSeconds();
            if (t1 - t2 >= timer && test) {
                if (combo)combo=0;
                if (!test->move('s')) {
                    other[2].play();
                    point += 5*(diff+1);
                    rotate=5;
                    combo = board->check_pop();
                    point += combo * 20*(diff+1);
                    tetrimocounter++;
                    text[1].setString("point: " + std::to_string(point));
                    text[6].setString("X  " +std::to_string(combo));
                    if (point - oldpoint > 300 && point<2100) {
                        oldpoint += 300;
                        timer*=0.8;
                        board->shrink();
                        board->deleteTop();
                        combo = board->check_pop();
                        other[1].play();
                    }
                    if(combo)other[0].play();
                    test = queue->addnextone(board->midtop());
                }t2 = t1;
                if(!test){
                    other[3].play();
                    nametaker=true;
                }
            }
            
        }
        while (window.pollEvent(event)) {
            
                handleKeyPress(event, test, color, text, board);
        }

    sf::RectangleShape selector(sf::Vector2f(10,10));
    selector.setPosition(175,switcher*100+225);
    selector.setFillColor(sf::Color::White);
    sf::RectangleShape diffselector(sf::Vector2f(10,10));
    diffselector.setPosition(175,diff*150+225);
    diffselector.setFillColor(sf::Color::White);
    sf::RectangleShape cpselector(sf::Vector2f(2,2));
    cpselector.setPosition(204+(xcp*16),204+(ycp*16)+(ycp/4)*30);
    cpselector.setFillColor(sf::Color::Red);

        window.clear(sf::Color(20, 20, 20));
        if (!start[0]&& !start[1]&&!start[2]&&!start[3]&&!start[4]) {
            window.draw(selector);
            window.draw(text[3]);
            window.draw(text[4]);
            window.draw(text[8]);
            window.draw(text[9]);
            window.draw(text[14]);
            window.draw(text[18]);
        } else{ if(!nametaker)window.draw(text[13]);
            if(start[0]) {
            if (test) {
                window.draw(text[1]);
                window.draw(text[2]);
                window.draw(text[5]);
                if(pause){window.draw(text[7]);
                window.draw(text[19]);
                }
                if (combo)window.draw(text[6]);
                queue->display(window, a[color]);
                board->display(window, a[color]);
            } else {
                text[10].setString(mytxt);
                if(nametaker)
                window.draw(text[11]);
                window.draw(text[10]);
                window.draw(text[0]);
            }
        }else if(start[1]){
            window.draw(text[12]);
            displayTheme(color);
        }else if(start[2])scoreboard.display(window);
        else if(start[3]){
            window.draw(diffselector);
            window.draw(text[15]);
            window.draw(text[16]);
            window.draw(text[17]);

        }else if(start[4]){queue->displaycp(window);window.draw(cpselector);window.draw(text[20]);}
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
    if (!start[0] && !start[1] && !start[2] && !start[3] && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        start[switcher] = true;
        other[4].play();
    }

    if (event.key.code == sf::Keyboard::Backspace && nametaker) {
        if (!mytxt.empty())
            mytxt.pop_back();
    }

    if (nametaker && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 13) {  // Check for Enter key
            nametaker = false;
            scoreboard.insert(mytxt, point, scoreboard.root);
            std::ofstream outFile("score.txt");
            scoreboard.save(outFile, scoreboard.root);
            outFile.close();
            mytxt = "";
        } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
            mytxt += static_cast<char>(event.text.unicode);
        }
    }
    if (event.type == sf::Event::KeyPressed && !nametaker) {
        switch (event.key.code) {
            case sf::Keyboard::Right:
                if (test && !pause && start[0]) valid[test->move('r')].play();
                else if(start[4]){xcp++;xcp%=4;}
                break;
            case sf::Keyboard::Left:
                if (test && !pause && start[0]) valid[test->move('l')].play();
                else if(start[4]){xcp--;xcp+=4;xcp%=4;}
                break;
            case sf::Keyboard::Down:
                if(start[3]){
                    diff++;
                    diff%=3;
                    timer=1.25-(diff*0.25);
                }
                if (test && !pause && start[0]) valid[test->move('d')].play();
                if(!start[0]&&!start[1]&&!start[2]&&!start[3]&&!start[4]){
                    switcher++;
                    switcher%=6;
                }else if(start[4]){ycp++;ycp%=12;}
                break;
            case sf::Keyboard::Up:
                if(start[3]){
                    diff--;
                    diff+=3;
                    diff%=3;
                    timer=1.25-(diff*0.25);
                }else if(start[4]){ycp--;ycp+=12;ycp%=12;}
                if (test && !pause && rotate && start[0]){valid[test->rotate(1)].play();rotate--;} else valid[0].play();
                if(!start[0]&&!start[1]&&!start[2]&&!start[3]&&!start[4]){
                    switcher--;
                    switcher+=6;
                    switcher%=6;
                }
                break;
            case sf::Keyboard::LAlt:
                if (test && !pause && rotate && start[0]) {valid[test->rotate(1)].play();rotate--;} else valid[0].play();
                break;
            case sf::Keyboard::R:
                board->restart(10,20);
                test=queue->restart(board->midtop());
                point=0;
                oldpoint=0;
                timer=1.25-(diff*0.25);
                break;
            case sf::Keyboard::H:
                if (tetrimocounter>=5 && start[0]){
                    valid[(tetrimocounter>=5)].play();
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
                start[switcher]=false;
                break;
            case sf::Keyboard::C:
            if (pause)
                queue->cpasked=!queue->cpasked;
            if(queue->cpasked)text[19].setString("Press C to disable Custom Piece ");else text[19].setString("Press C to available Custom Piece ");
                break;
            case sf::Keyboard::P:
                if(start[0])
                pause=!pause;
                break;
            case sf::Keyboard::Enter:
            if (nametaker){
                nametaker=false;
            scoreboard.insert(mytxt,point,scoreboard.root);
            std::ofstream outFile("score.txt");
            scoreboard.save(outFile, scoreboard.root);
            outFile.close();
            mytxt="";
            }
            break;
            case sf::Keyboard::S:
                if(start[4]){
                queue->cp[ycp/4][ycp%4][xcp]=!queue->cp[ycp/4][ycp%4][xcp];
                queue->saveCP();
                queue->cpcheck();
                }
                break;
            default:
                break;
        }
    }
}

