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
                break;
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

    Interface::write(window, "Wpisz nazwe pliku z ktorego odczytane maja byc dane", (WIDTH / 4), 12, sf::Color::White, 36);

    Interface::write(window, ">", (WIDTH / 2) - 598, 75, sf::Color::White, 32);
    if(!frame)
        Interface::write(window, "_", (WIDTH / 2) - 583, 75, sf::Color::White, 32);
    Interface::write(window, files.getFile().c_str() , (WIDTH / 2) - 563, 75, sf::Color::White, 32);                                     ///Wyswietlanie wpisywanego tekstu

    if(loaded)
    {
        if(vertices.size() <= 20){
            for(unsigned i = 0; i< vertices.size(); i++)                                                                                    ///Rysowanie wierzcholkow
            {
                window.draw(vertices.at(i)->getCircle());
                std::stringstream a;
                a << (i+1);
                std::string s = a.str();
                double verSize = vertices.size();
                Interface::write(window, s, WIDTH/2 + std::round(verSize*(1.8-3/(2*verSize))*sin((2*i*PI)/verSize))*8 +56/verSize,
                                 HEIGHT/2 - std::round(verSize*(1.8-3/(2*verSize))*cos((2*i*PI)/verSize))*8 +(9*verSize)/8+ 56/verSize);
            }

            for(unsigned i = 0; i< edges.size(); i++)                                                                                       ///Rysowanie polaczen
            {
                window.draw(edges.at(i)->getLine());
                std::stringstream a;
                a << edges.at(i)->getScale();
                std::string s = a.str();
                Interface::write(window, s,
                             WIDTH/2 + (edges.at(i)->getVertexX(0)+edges.at(i)->getVertexX(1))*4.2 +5,
                             HEIGHT/2 - (edges.at(i)->getVertexY(0)+edges.at(i)->getVertexY(1))*4.2 +20, sf::Color::White, 16);
            }
        }
        else{
            Interface::write(window, "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB", WIDTH/2, HEIGHT/2 - 270, sf::Color::White, 18);
            Interface::write(window, "BNB------------------------------B B", WIDTH/2, HEIGHT/2 - 252, sf::Color::White, 18);
            Interface::write(window, "BBB------------------------------BBB", WIDTH/2, HEIGHT/2 - 234, sf::Color::White, 18);
            Interface::write(window, "BBB------------------------------BBB", WIDTH/2, HEIGHT/2 - 216, sf::Color::White, 18);
            Interface::write(window, "BBB------------------------------BBB", WIDTH/2, HEIGHT/2 - 198, sf::Color::White, 18);
            Interface::write(window, "BBB------------------------------BBB", WIDTH/2, HEIGHT/2 - 180, sf::Color::White, 18);
            Interface::write(window, "BBB------------------------------BBB", WIDTH/2, HEIGHT/2 - 162, sf::Color::White, 18);
            Interface::write(window, "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB", WIDTH/2, HEIGHT/2 - 144, sf::Color::White, 18);
            Interface::write(window, "BBBBB++++++++++++++++BBBBBB", WIDTH/2, HEIGHT/2 - 126, sf::Color::White, 18);
            Interface::write(window, "BBBBB++BBBBB+++++++++++BBBBBB", WIDTH/2, HEIGHT/2 - 108, sf::Color::White, 18);
            Interface::write(window, "BBBBB++BBBBB+++++++++++BBBBBB", WIDTH/2, HEIGHT/2 - 90, sf::Color::White, 18);
            Interface::write(window, "BBBBB++BBBBB+++++++++++BBBBBB", WIDTH/2, HEIGHT/2 - 72, sf::Color::White, 18);
            Interface::write(window, "BBBBB++++++++++++++++BBBBBB", WIDTH/2, HEIGHT/2 - 54, sf::Color::White, 18);
            Interface::write(window, "BBBBB++++++++++++++++BBBBBB", WIDTH/2, HEIGHT/2 - 36, sf::Color::White, 18);
            Interface::write(window, "BBBBB++++++++++++++++BBBBBB", WIDTH/2, HEIGHT/2 - 18, sf::Color::White, 18);

            Interface::write(window, "        z###ac              za###c", WIDTH/2, HEIGHT/2 + 36, sf::Color::White, 18);
            Interface::write(window, "            z###ac      za###c", WIDTH/2, HEIGHT/2 + 54, sf::Color::White, 18);
            Interface::write(window, "                z###NN###c", WIDTH/2, HEIGHT/2 + 72, sf::Color::White, 18);
            Interface::write(window, "            z###ac      za###c", WIDTH/2, HEIGHT/2 + 90, sf::Color::White, 18);
            Interface::write(window, "        z###ac              za###c", WIDTH/2, HEIGHT/2 + 108, sf::Color::White, 18);


            Interface::write(window, "Za duzo wierzcholkow, aby wyswietlic graf", WIDTH/2 - 220, HEIGHT/2 + 160, sf::Color::White, 48);
        }

        if(algorithm == "BRUTE" || algorithm == "MASTS" || algorithm == "LINEAR"){
            Interface::write(window, "> "+algorithm,(WIDTH / 2) - 598, 110);                                                                       ///Wyswietlanie nazwy algorytmu

            std::stringstream numVer;
            numVer << vertices.size();
            Interface::write(window, "> Ilosc wierzcholkow grafu: ", (WIDTH / 2) - 598, 140);
            Interface::write(window, numVer.str(), (WIDTH / 2) - 340, 140);

            std::stringstream dist;
            dist << result.first;
            unsigned sumDis = 0;
            for(auto tmp : vertices){
                sumDis += tmp->getDistance();
            }
            std::stringstream sumDist;
            sumDist << sumDis;
            Interface::write(window, "> Odleglosc/Suma odleglosci: ", (WIDTH / 2) - 598, 170);
            Interface::write(window, dist.str()+"/"+sumDist.str(), (WIDTH / 2) - 340, 170);

            std::stringstream id1;
            id1 << result.second.first->getID();
            Interface::write(window, "> Pierwszy wierzcholek: ", (WIDTH / 2) - 598, 200);
            Interface::write(window, id1.str(), (WIDTH / 2) - 340, 200);

            std::stringstream id2;
            id2 << result.second.second->getID();
            Interface::write(window, "> Drugi wierzcholek: ", (WIDTH / 2) - 598, 230);
            Interface::write(window, id2.str(), (WIDTH / 2) - 340, 230);

            Interface::write(window, "> Czas wykonania algorytmu: ", (WIDTH / 2) - 598, 260);
        }
        ///Tutaj dopisywac nowe window.draw();
    }
    window.display();
}
