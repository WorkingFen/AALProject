/**
* Name: graphs.cpp
* Purpose: Implementation of namespace Graphs
*
* @version 1.03a 14/05/2017
* @author Piotr Zawadka
*/
#include <fstream>
#include <sstream>
#include <windows.h>
#include "graphs.h"

///Wpisywanie nazwy pliku i zamykanie okna
void Graphs::events(sf::Window &window, Instructions &instructions, std::vector<Vertex*> &vertices, std::vector<Edge*> &edges,
                           unsigned &idStart, unsigned &idFinish, std::string &algorithm, std::vector<Edge*> &floydsEdges,
                           bool &loaded, Path &path, unsigned &cost,
                           unsigned &displayed, std::vector<Path*> &floydsPaths, std::vector<unsigned> &costs){
    sf::Event event;
    while (window.pollEvent(event)){
        switch (event.type){
            case sf::Event::Closed:                     ///Pierwszy przypadek: Event::Closed
                window.close();
                break;
            case sf::Event::KeyReleased:
                switch(event.key.code){
                    case sf::Keyboard::A:
                        instructions.file.push_back('A');
                        break;
                    case sf::Keyboard::B:
                        instructions.file.push_back('B');
                        break;
                    case sf::Keyboard::C:
                        instructions.file.push_back('C');
                        break;
                    case sf::Keyboard::D:
                        instructions.file.push_back('D');
                        break;
                    case sf::Keyboard::E:
                        instructions.file.push_back('E');
                        break;
                    case sf::Keyboard::F:
                        instructions.file.push_back('F');
                        break;
                    case sf::Keyboard::G:
                        instructions.file.push_back('G');
                        break;
                    case sf::Keyboard::H:
                        instructions.file.push_back('H');
                        break;
                    case sf::Keyboard::I:
                        instructions.file.push_back('I');
                        break;
                    case sf::Keyboard::J:
                        instructions.file.push_back('J');
                        break;
                    case sf::Keyboard::K:
                        instructions.file.push_back('K');
                        break;
                    case sf::Keyboard::L:
                        instructions.file.push_back('L');
                        break;
                    case sf::Keyboard::M:
                        instructions.file.push_back('M');
                        break;
                    case sf::Keyboard::N:
                        instructions.file.push_back('N');
                        break;
                    case sf::Keyboard::O:
                        instructions.file.push_back('O');
                        break;
                    case sf::Keyboard::P:
                        instructions.file.push_back('P');
                        break;
                    case sf::Keyboard::Q:
                        instructions.file.push_back('Q');
                        break;
                    case sf::Keyboard::R:
                        instructions.file.push_back('R');
                        break;
                    case sf::Keyboard::S:
                        instructions.file.push_back('S');
                        break;
                    case sf::Keyboard::T:
                        instructions.file.push_back('T');
                        break;
                    case sf::Keyboard::U:
                        instructions.file.push_back('U');
                        break;
                    case sf::Keyboard::V:
                        instructions.file.push_back('V');
                        break;
                    case sf::Keyboard::W:
                        instructions.file.push_back('W');
                        break;
                    case sf::Keyboard::X:
                        instructions.file.push_back('X');
                        break;
                    case sf::Keyboard::Y:
                        instructions.file.push_back('Y');
                        break;
                    case sf::Keyboard::Z:
                        instructions.file.push_back('Z');
                        break;
                    case sf::Keyboard::Space:
                        instructions.file.push_back('_');
                        break;
                    case sf::Keyboard::Num0:
                        instructions.file.push_back('0');
                        break;
                    case sf::Keyboard::Num1:
                        instructions.file.push_back('1');
                        break;
                    case sf::Keyboard::Num2:
                        instructions.file.push_back('2');
                        break;
                    case sf::Keyboard::Num3:
                        instructions.file.push_back('3');
                        break;
                    case sf::Keyboard::Num4:
                        instructions.file.push_back('4');
                        break;
                    case sf::Keyboard::Num5:
                        instructions.file.push_back('5');
                        break;
                    case sf::Keyboard::Num6:
                        instructions.file.push_back('6');
                        break;
                    case sf::Keyboard::Num7:
                        instructions.file.push_back('7');
                        break;
                    case sf::Keyboard::Num8:
                        instructions.file.push_back('8');
                        break;
                    case sf::Keyboard::Num9:
                        instructions.file.push_back('9');
                        break;
                    case sf::Keyboard::Numpad0:
                        instructions.file.push_back('0');
                        break;
                    case sf::Keyboard::Numpad1:
                        instructions.file.push_back('1');
                        break;
                    case sf::Keyboard::Numpad2:
                        instructions.file.push_back('2');
                        break;
                    case sf::Keyboard::Numpad3:
                        instructions.file.push_back('3');
                        break;
                    case sf::Keyboard::Numpad4:
                        instructions.file.push_back('4');
                        break;
                    case sf::Keyboard::Numpad5:
                        instructions.file.push_back('5');
                        break;
                    case sf::Keyboard::Numpad6:
                        instructions.file.push_back('6');
                        break;
                    case sf::Keyboard::Numpad7:
                        instructions.file.push_back('7');
                        break;
                    case sf::Keyboard::Numpad8:
                        instructions.file.push_back('8');
                        break;
                    case sf::Keyboard::Numpad9:
                        instructions.file.push_back('9');
                        break;
                    case sf::Keyboard::Return:
                        try{
                            vertices.clear();
                            edges.clear();
                            path.path.clear();
                            instructions.read(vertices, edges, idStart, idFinish, algorithm, floydsEdges, loaded);
                            if(algorithm == "PATH")
                                cost = instructions.dijkstrasAlgorithm(vertices, edges, path, idStart, idFinish);
                            else if(algorithm == "MST")
                                cost = instructions.primsAlgorithm(vertices, edges, path);
                            else if(algorithm == "FLOYD")
                                instructions.floydsAlgorithm(vertices, edges, floydsEdges, floydsPaths, costs);
                            else if(algorithm == "STEINER")
                                cost = instructions.steinersAlgorithm(vertices, edges, path);
                        }
                        catch(...){
                            std::string msg = "Fatal error while loading from file " + instructions.file + " No file or directory";
                            MessageBox(NULL, msg.c_str(), NULL, MB_OK | MB_ICONEXCLAMATION);
                            exit(20);
                        }
                        instructions.file = "";
                        break;
                    case sf::Keyboard::Left:
                        if(algorithm == "FLOYD")
                        {
                            if(displayed==0)
                                displayed=floydsEdges.size()-1;
                            else
                                --displayed;
                        }
                        break;
                    case sf::Keyboard::Right:
                        if(algorithm == "FLOYD")
                        {
                            if(displayed==floydsEdges.size()-1)
                                displayed=0;
                            else
                                displayed++;
                        }
                        break;
                    case sf::Keyboard::BackSpace:
                        if(instructions.file != "")
                            instructions.file.pop_back();
                        break;
                    default:
                        break;
                }
            case sf::Event::MouseButtonPressed:         ///Drugi przypadek: Event::MouseButtonPressed
                switch (event.mouseButton.button){
                    case sf::Mouse::Middle:             ///Srodkowy przycisk
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
} //Function

///Wypisz to co chce
void Graphs::write(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y,
                  sf::Color color, unsigned size){
    sf::Font font;
    font.loadFromFile("MunroNarrow.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString(msg);
    text.setCharacterSize(size);
    text.setColor(color);
    text.setPosition(x, y);

    window.draw(text);
}

///Narysuj to co chce
void Graphs::draw(sf::RenderWindow &window, Instructions &instructions, const std::string algorithm,
                   int &frame, int &pause, bool loaded,
                   std::vector<Vertex*> vertices, std::vector<Edge*> edges, std::vector<Edge*> floydsEdges,
                   Path path, unsigned &cost, unsigned displayed,
                   std::vector<Path*> floydsPaths, std::vector<unsigned> costs)
{
    if(!pause)                                                       ///Mrugajaca strzalka
        frame++;
    if(frame==20)
        frame=0;
    if(!frame)
        pause++;
    if(pause==20)
        pause=0;

    window.clear(sf::Color(8,8,16));                                ///Okno ma pewien wyznaczony kolor

    Graphs::write(window, ">", (1366 / 2) - 598, 65, sf::Color::White, 32);
    if(!frame)
        Graphs::write(window, "_", (1366 / 2) - 583, 65, sf::Color::White, 32);
    Graphs::write(window, instructions.file.c_str() , (1366 / 2) - 563, 65, sf::Color::White, 32); ///Wyswietlanie wpisywanego tekstu

    Graphs::write(window, "> "+algorithm,(1366 / 2) - 578, 100);  ///Wyswietlanie nazwy algorytmu

    if(algorithm == "FLOYD")
        cost = costs.at(displayed);
    std::stringstream a;
    a << cost;
    std::string koszty = a.str();
    std::string tekst = "Koszt grafu ";
    Graphs::write(window, "> "+tekst+koszty,(1366 / 2) - 578, 130);      ///Wyswietlanie kosztu grafu

    if(algorithm == "FLOYD")
    {
        std::stringstream a;
        a << edges_floyda.at(displayed)->w_id[0];
        std::string id = a.str();
        std::stringstream b;
        b << edges_floyda.at(displayed)->w_id[1];
        std::string id2 = b.str();
        Graphs::write(window, "> "+id+" "+id2,(1366 / 2) - 578, 160);
    }

    if(zaladowane)
    {
        for(int i = 0; i< vertices.size(); i++)                        ///Rysowanie wierzcholkow
        {
            window.draw(vertices.at(i)->kolko);
            std::stringstream a;
            a << (i+1);
            std::string s = a.str();
            Graphs::write(window, s, vertices.at(i)->x*8+190, vertices.at(i)->y*8-20);
        }

        for(int i = 0; i< edges.size(); i++)                        ///Rysowanie polaczen
        {
            window.draw(edges.at(i)->linia);
            std::stringstream a;
            a << edges.at(i)->waga;
            std::string s = a.str();
            Graphs::write(window, s,
                         (edges.at(i)->wierzcholki[0]->x +edges.at(i)->wierzcholki[1]->x)*4+200,
                         (edges.at(i)->wierzcholki[0]->y +edges.at(i)->wierzcholki[1]->y)*4-8, sf::Color::White, 14);
        }

        if(algorithm == "MST" || algorithm == "SCIEZKA" || algorithm == "STEINER")
            for(int i = 0; i< sciezka.sciezka.size(); i++)              ///Rysowanie sciezki dla MST i SCIEZKA
            {
                sciezka.sciezka.at(i)->linia[0].color = sf::Color(154,68,234);
                sciezka.sciezka.at(i)->linia[1].color = sf::Color(4,249,160);
                sciezka.sciezka.at(i)->wierzcholki[0]->kolko.setOutlineColor(sf::Color(154,68,234));
                sciezka.sciezka.at(i)->wierzcholki[1]->kolko.setOutlineColor(sf::Color(154,68,234));
                window.draw(sciezka.sciezka.at(i)->linia);
                window.draw(sciezka.sciezka.at(i)->wierzcholki[0]->kolko);
                window.draw(sciezka.sciezka.at(i)->wierzcholki[1]->kolko);
            }
        else if(algorithm == "FLOYD")
            for(int i = 0; i<sciezki_floyda.at(displayed)->sciezka.size(); i++) ///Rysowanie sciezki dla FLOYD
            {
                sciezki_floyda.at(displayed)->sciezka.at(i)->linia[0].color = sf::Color(154,68,234);
                sciezki_floyda.at(displayed)->sciezka.at(i)->linia[1].color = sf::Color(4,249,160);
                sciezki_floyda.at(displayed)->sciezka.at(i)->wierzcholki[0]->kolko.setOutlineColor(sf::Color(154,68,234));
                sciezki_floyda.at(displayed)->sciezka.at(i)->wierzcholki[1]->kolko.setOutlineColor(sf::Color(154,68,234));
                window.draw(sciezki_floyda.at(displayed)->sciezka.at(i)->linia);
                window.draw(sciezki_floyda.at(displayed)->sciezka.at(i)->wierzcholki[0]->kolko);
                window.draw(sciezki_floyda.at(displayed)->sciezka.at(i)->wierzcholki[1]->kolko);
            }

        ///Tutaj dopisywac nowe window.draw();
    }
    window.display();
}
