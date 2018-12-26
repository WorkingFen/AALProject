/**
* Name: interface.cpp
* Purpose: Implementation of namespace Interface
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/

#include <sstream>
#include <windows.h>
#include "interface.h"

///SFML doesn't have proper transformation to ASCII, so I had to create my own
char Interface::SFMLtoASCII(sf::Keyboard::Key code){
    if(code == sf::Keyboard::A) return 'A';
    else if(code == sf::Keyboard::B) return 'B';
    else if(code == sf::Keyboard::C) return 'C';
    else if(code == sf::Keyboard::D) return 'D';
    else if(code == sf::Keyboard::E) return 'E';
    else if(code == sf::Keyboard::F) return 'F';
    else if(code == sf::Keyboard::G) return 'G';
    else if(code == sf::Keyboard::H) return 'H';
    else if(code == sf::Keyboard::I) return 'I';
    else if(code == sf::Keyboard::J) return 'J';
    else if(code == sf::Keyboard::K) return 'K';
    else if(code == sf::Keyboard::L) return 'L';
    else if(code == sf::Keyboard::M) return 'M';
    else if(code == sf::Keyboard::N) return 'N';
    else if(code == sf::Keyboard::O) return 'O';
    else if(code == sf::Keyboard::P) return 'P';
    else if(code == sf::Keyboard::Q) return 'Q';
    else if(code == sf::Keyboard::R) return 'R';
    else if(code == sf::Keyboard::S) return 'S';
    else if(code == sf::Keyboard::T) return 'T';
    else if(code == sf::Keyboard::U) return 'U';
    else if(code == sf::Keyboard::V) return 'V';
    else if(code == sf::Keyboard::W) return 'W';
    else if(code == sf::Keyboard::X) return 'X';
    else if(code == sf::Keyboard::Y) return 'Y';
    else if(code == sf::Keyboard::Z) return 'Z';
    else if(code == sf::Keyboard::Space) return '_';
    else if(code == sf::Keyboard::Num0) return '0';
    else if(code == sf::Keyboard::Num1) return '1';
    else if(code == sf::Keyboard::Num2) return '2';
    else if(code == sf::Keyboard::Num3) return '3';
    else if(code == sf::Keyboard::Num4) return '4';
    else if(code == sf::Keyboard::Num5) return '5';
    else if(code == sf::Keyboard::Num6) return '6';
    else if(code == sf::Keyboard::Num7) return '7';
    else if(code == sf::Keyboard::Num8) return '8';
    else if(code == sf::Keyboard::Num9) return '9';
    else if(code == sf::Keyboard::Numpad0) return '0';
    else if(code == sf::Keyboard::Numpad1) return '1';
    else if(code == sf::Keyboard::Numpad2) return '2';
    else if(code == sf::Keyboard::Numpad3) return '3';
    else if(code == sf::Keyboard::Numpad4) return '4';
    else if(code == sf::Keyboard::Numpad5) return '5';
    else if(code == sf::Keyboard::Numpad6) return '6';
    else if(code == sf::Keyboard::Numpad7) return '7';
    else if(code == sf::Keyboard::Numpad8) return '8';
    else if(code == sf::Keyboard::Numpad9) return '9';
    return '\0';
}

///Writing file's name and closing executable program
int Interface::events(sf::Window &window, Algorithms &algorithms, Files &files, std::vector<Vertex*> &vertices,
                           std::vector<Edge*> &edges, std::string &algorithm,
                           bool &loaded, std::pair<unsigned, std::pair<Vertex*, Vertex*>> &result){
    sf::Event event;
    while (window.pollEvent(event)){
        switch (event.type){
            case sf::Event::Closed:                                                                                                     ///Event::Closed
                window.close();
                break;
            case sf::Event::KeyReleased:                                                                                                ///Event::KeyReleased
                switch(event.key.code){
                    case sf::Keyboard::Return:
                        try{
                            vertices.clear();
                            edges.clear();
                            if(files.read(vertices, edges, algorithm, loaded)) return ERROR_VERTICES_AMOUNT;
                            if(algorithm == "BRUTE")
                                result = algorithms.bruteAlgorithm(vertices);
                            else if(algorithm == "MASTS")
                                result = algorithms.mastsAlgorithm(vertices);
                            else if(algorithm == "LINEAR")
                                result = algorithms.linearAlgorithm(vertices);
                        }
                        catch(...){
                            std::string msg = "Fatal error while loading from file " + files.getFile() + " No file or directory";
                            MessageBox(NULL, msg.c_str(), NULL, MB_OK | MB_ICONEXCLAMATION);
                            exit(20);
                        }
                        files.setFile("");
                        break;
                    case sf::Keyboard::BackSpace:
                        if(files.getFile() != "") files.popFile();
                        break;
                    default:
                        files.pushFile(SFMLtoASCII(event.key.code));
                        break;
                }
            case sf::Event::MouseButtonPressed:                                                                                         ///Event::MouseButtonPressed
                switch (event.mouseButton.button){
                    case sf::Mouse::Middle:
                        window.close();
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        } //switch[event.type]
    } //while
    return 0;
} //Function

///Writing function
void Interface::write(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y,
                  sf::Color color, unsigned size){
    sf::Font font;
    font.loadFromFile("Resources/MunroNarrow.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString(msg);
    text.setCharacterSize(size);
    text.setColor(color);
    text.setPosition(x, y);

    window.draw(text);
}

///Drawing function
void Interface::draw(sf::RenderWindow &window, Files &files, const std::string algorithm,
                   int &frame, int &pause, bool loaded, std::vector<Vertex*> vertices, std::vector<Edge*> edges,
                   std::pair<unsigned, std::pair<Vertex*, Vertex*>> &result)
{
    if(!pause)                                                                                                                          ///Mrugajaca strzalka
        frame++;
    if(frame==20)
        frame=0;
    if(!frame)
        pause++;
    if(pause==20)
        pause=0;

    window.clear(BACKGROUND);                                                                                                           ///Okno ma pewien wyznaczony kolor

    Interface::write(window, ">", (WIDTH / 2) - 598, 65, sf::Color::White, 32);
    if(!frame)
        Interface::write(window, "_", (WIDTH / 2) - 583, 65, sf::Color::White, 32);
    Interface::write(window, files.getFile().c_str() , (WIDTH / 2) - 563, 65, sf::Color::White, 32);                                     ///Wyswietlanie wpisywanego tekstu

    Interface::write(window, "> "+algorithm,(WIDTH / 2) - 578, 100);                                                                       ///Wyswietlanie nazwy algorytmu

    if(loaded)
    {
        if(vertices.size() <= 20){
            for(unsigned i = 0; i< vertices.size(); i++)                                                                                    ///Rysowanie wierzcholkow
            {
                window.draw(vertices.at(i)->getCircle());
                std::stringstream a;
                a << (i+1);
                std::string s = a.str();
                Interface::write(window, s, WIDTH/2 + vertices.at(i)->getX()*8 - 10, HEIGHT/2 - vertices.at(i)->getY()*8 - 25);
            }

            for(unsigned i = 0; i< edges.size(); i++)                                                                                       ///Rysowanie polaczen
            {
                window.draw(edges.at(i)->getLine());
                std::stringstream a;
                a << edges.at(i)->getScale();
                std::string s = a.str();
                Interface::write(window, s,
                             WIDTH/2 + (edges.at(i)->getVertexX(0)+edges.at(i)->getVertexX(1))*4 + 10,
                             HEIGHT/2 - (edges.at(i)->getVertexY(0)+edges.at(i)->getVertexY(1))*4 + 10, sf::Color::White, 16);
            }
        }

        if(algorithm == "BRUTE" || algorithm == "MASTS" || algorithm == "LINEAR"){
            Interface::write(window, "> Najwieksza odleglosc ", (WIDTH / 2) - 578, 130);
            std::stringstream dist;
            dist << result.first;
            std::stringstream id1;
            id1 << result.second.first->getID();
            std::stringstream id2;
            id2 << result.second.second->getID();
            Interface::write(window, dist.str(), (WIDTH / 2) - 560, 160);
            Interface::write(window, " miedzy "+id1.str(),(WIDTH / 2) - 540, 160);
            Interface::write(window, ", a "+id2.str(),(WIDTH / 2) - 460, 160);
        }
        ///Tutaj dopisywac nowe window.draw();
    }
    window.display();
}
