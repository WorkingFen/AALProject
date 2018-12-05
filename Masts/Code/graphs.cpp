/**
* Name: graphs.cpp
* Purpose: Implementacja namespace Graphs
*
* @version 1.03a 14/05/2017
*/
#include <fstream>
#include <sstream>
#include "graphs.h"
#include <windows.h>

///Wpisywanie nazwy pliku i zamykanie okna
void Graphs::zdarzenia(sf::Window &window, Instrukcje &instrukcje, std::vector<Wezel*> &wezly, std::vector<Lacze*> &lacza,
                           unsigned &id_start, unsigned &id_koniec, std::string &algorytm, std::vector<Lacze*> &lacza_floyda,
                           bool &zaladowane, Sciezka &sciezka, unsigned &koszt,
                           unsigned &wyswietlane, std::vector<Sciezka*> &sciezki_floyda, std::vector<unsigned> &koszta){
    sf::Event event;
    while (window.pollEvent(event)){
        switch (event.type){
            case sf::Event::Closed:                     ///Pierwszy przypadek: Event::Closed
                window.close();
                break;
            case sf::Event::KeyReleased:
                switch(event.key.code){
                    case sf::Keyboard::A:
                        instrukcje.plik.push_back('A');
                        break;
                    case sf::Keyboard::B:
                        instrukcje.plik.push_back('B');
                        break;
                    case sf::Keyboard::C:
                        instrukcje.plik.push_back('C');
                        break;
                    case sf::Keyboard::D:
                        instrukcje.plik.push_back('D');
                        break;
                    case sf::Keyboard::E:
                        instrukcje.plik.push_back('E');
                        break;
                    case sf::Keyboard::F:
                        instrukcje.plik.push_back('F');
                        break;
                    case sf::Keyboard::G:
                        instrukcje.plik.push_back('G');
                        break;
                    case sf::Keyboard::H:
                        instrukcje.plik.push_back('H');
                        break;
                    case sf::Keyboard::I:
                        instrukcje.plik.push_back('I');
                        break;
                    case sf::Keyboard::J:
                        instrukcje.plik.push_back('J');
                        break;
                    case sf::Keyboard::K:
                        instrukcje.plik.push_back('K');
                        break;
                    case sf::Keyboard::L:
                        instrukcje.plik.push_back('L');
                        break;
                    case sf::Keyboard::M:
                        instrukcje.plik.push_back('M');
                        break;
                    case sf::Keyboard::N:
                        instrukcje.plik.push_back('N');
                        break;
                    case sf::Keyboard::O:
                        instrukcje.plik.push_back('O');
                        break;
                    case sf::Keyboard::P:
                        instrukcje.plik.push_back('P');
                        break;
                    case sf::Keyboard::Q:
                        instrukcje.plik.push_back('Q');
                        break;
                    case sf::Keyboard::R:
                        instrukcje.plik.push_back('R');
                        break;
                    case sf::Keyboard::S:
                        instrukcje.plik.push_back('S');
                        break;
                    case sf::Keyboard::T:
                        instrukcje.plik.push_back('T');
                        break;
                    case sf::Keyboard::U:
                        instrukcje.plik.push_back('U');
                        break;
                    case sf::Keyboard::V:
                        instrukcje.plik.push_back('V');
                        break;
                    case sf::Keyboard::W:
                        instrukcje.plik.push_back('W');
                        break;
                    case sf::Keyboard::X:
                        instrukcje.plik.push_back('X');
                        break;
                    case sf::Keyboard::Y:
                        instrukcje.plik.push_back('Y');
                        break;
                    case sf::Keyboard::Z:
                        instrukcje.plik.push_back('Z');
                        break;
                    case sf::Keyboard::Space:
                        instrukcje.plik.push_back('_');
                        break;
                    case sf::Keyboard::Num0:
                        instrukcje.plik.push_back('0');
                        break;
                    case sf::Keyboard::Num1:
                        instrukcje.plik.push_back('1');
                        break;
                    case sf::Keyboard::Num2:
                        instrukcje.plik.push_back('2');
                        break;
                    case sf::Keyboard::Num3:
                        instrukcje.plik.push_back('3');
                        break;
                    case sf::Keyboard::Num4:
                        instrukcje.plik.push_back('4');
                        break;
                    case sf::Keyboard::Num5:
                        instrukcje.plik.push_back('5');
                        break;
                    case sf::Keyboard::Num6:
                        instrukcje.plik.push_back('6');
                        break;
                    case sf::Keyboard::Num7:
                        instrukcje.plik.push_back('7');
                        break;
                    case sf::Keyboard::Num8:
                        instrukcje.plik.push_back('8');
                        break;
                    case sf::Keyboard::Num9:
                        instrukcje.plik.push_back('9');
                        break;
                    case sf::Keyboard::Numpad0:
                        instrukcje.plik.push_back('0');
                        break;
                    case sf::Keyboard::Numpad1:
                        instrukcje.plik.push_back('1');
                        break;
                    case sf::Keyboard::Numpad2:
                        instrukcje.plik.push_back('2');
                        break;
                    case sf::Keyboard::Numpad3:
                        instrukcje.plik.push_back('3');
                        break;
                    case sf::Keyboard::Numpad4:
                        instrukcje.plik.push_back('4');
                        break;
                    case sf::Keyboard::Numpad5:
                        instrukcje.plik.push_back('5');
                        break;
                    case sf::Keyboard::Numpad6:
                        instrukcje.plik.push_back('6');
                        break;
                    case sf::Keyboard::Numpad7:
                        instrukcje.plik.push_back('7');
                        break;
                    case sf::Keyboard::Numpad8:
                        instrukcje.plik.push_back('8');
                        break;
                    case sf::Keyboard::Numpad9:
                        instrukcje.plik.push_back('9');
                        break;
                    case sf::Keyboard::Return:
                        try{
                            wezly.clear();
                            lacza.clear();
                            sciezka.sciezka.clear();
                            instrukcje.odczyt(wezly, lacza, id_start, id_koniec, algorytm, lacza_floyda, zaladowane);
                            if(algorytm == "SCIEZKA")
                                koszt = instrukcje.algorytm_dijkstry(wezly, lacza, sciezka, id_start, id_koniec);
                                //koszt = instrukcje.algorytm_usun(wezly, lacza, sciezka, id_start, id_koniec);
                            else if(algorytm == "MST")
                                //koszt = instrukcje.algorytm_prima(wezly, lacza, sciezka);
                                koszt = instrukcje.algorytm_drzewo(wezly, lacza, sciezka);
                                //koszt = instrukcje.algorytm_delta(wezly, lacza, sciezka);
                                //koszt = instrukcje.algorytm_dodaj(wezly, lacza, sciezka);
                            else if(algorytm == "FLOYD")
                                instrukcje.algorytm_floyda(wezly, lacza, lacza_floyda, sciezki_floyda, koszta);
                            else if(algorytm == "STEINER")
                                koszt=instrukcje.algorytm_steinera(wezly, lacza, sciezka);
                        }
                        catch(...){
                            std::string msg = "Fatal error while loading from file " + instrukcje.plik + " No file or directory";
                            MessageBox(NULL, msg.c_str(), NULL, MB_OK | MB_ICONEXCLAMATION);
                            exit(20);
                        }
                        instrukcje.plik = "";
                        break;
                    case sf::Keyboard::Left:
                        if(algorytm == "FLOYD")
                        {
                            if(wyswietlane==0)
                                wyswietlane=lacza_floyda.size()-1;
                            else
                                --wyswietlane;
                        }
                        break;
                    case sf::Keyboard::Right:
                        if(algorytm == "FLOYD")
                        {
                            if(wyswietlane==lacza_floyda.size()-1)
                                wyswietlane=0;
                            else
                                wyswietlane++;
                        }
                        break;
                    case sf::Keyboard::BackSpace:
                        if(instrukcje.plik != "")
                            instrukcje.plik.pop_back();
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
void Graphs::pisz(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y,
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
void Graphs::rysuj(sf::RenderWindow &window, Instrukcje &instrukcje, const std::string algorytm,
                   int &klatka, int &pauza, bool zaladowane,
                   std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, std::vector<Lacze*> lacza_floyda,
                   Sciezka sciezka, unsigned &koszt, unsigned wyswietlane,
                   std::vector<Sciezka*> sciezki_floyda, std::vector<unsigned> koszta)
{
    if(!pauza)                                                       ///Mrugajaca strzalka
        klatka++;
    if(klatka==20)
        klatka=0;
    if(!klatka)
        pauza++;
    if(pauza==20)
        pauza=0;

    window.clear(sf::Color(8,8,16));                                ///Okno ma pewien wyznaczony kolor

    Graphs::pisz(window, ">", (1366 / 2) - 598, 65, sf::Color::White, 32);
    if(!klatka)
        Graphs::pisz(window, "_", (1366 / 2) - 583, 65, sf::Color::White, 32);
    Graphs::pisz(window, instrukcje.plik.c_str() , (1366 / 2) - 563, 65, sf::Color::White, 32); ///Wyswietlanie wpisywanego tekstu

    Graphs::pisz(window, "> "+algorytm,(1366 / 2) - 578, 100);  ///Wyswietlanie nazwy algorytmu

    if(algorytm == "FLOYD")
        koszt = koszta.at(wyswietlane);
    std::stringstream a;
    a << koszt;
    std::string koszty = a.str();
    std::string tekst = "Koszt grafu ";
    Graphs::pisz(window, "> "+tekst+koszty,(1366 / 2) - 578, 130);      ///Wyswietlanie kosztu grafu

    if(algorytm == "FLOYD")
    {
        std::stringstream a;
        a << lacza_floyda.at(wyswietlane)->w_id[0];
        std::string id = a.str();
        std::stringstream b;
        b << lacza_floyda.at(wyswietlane)->w_id[1];
        std::string id2 = b.str();
        Graphs::pisz(window, "> "+id+" "+id2,(1366 / 2) - 578, 160);
    }

    if(zaladowane)
    {
        for(int i = 0; i< wezly.size(); i++)                        ///Rysowanie wierzcholkow
        {
            window.draw(wezly.at(i)->kolko);
            std::stringstream a;
            a << (i+1);
            std::string s = a.str();
            Graphs::pisz(window, s, wezly.at(i)->x*8+190, wezly.at(i)->y*8-20);
        }

        for(int i = 0; i< lacza.size(); i++)                        ///Rysowanie polaczen
        {
            window.draw(lacza.at(i)->linia);
            std::stringstream a;
            a << lacza.at(i)->waga;
            std::string s = a.str();
            Graphs::pisz(window, s,
                         (lacza.at(i)->wierzcholki[0]->x +lacza.at(i)->wierzcholki[1]->x)*4+200,
                         (lacza.at(i)->wierzcholki[0]->y +lacza.at(i)->wierzcholki[1]->y)*4-8, sf::Color::White, 14);
        }

        if(algorytm == "MST" || algorytm == "SCIEZKA" || algorytm == "STEINER")
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
        else if(algorytm == "FLOYD")
            for(int i = 0; i<sciezki_floyda.at(wyswietlane)->sciezka.size(); i++) ///Rysowanie sciezki dla FLOYD
            {
                sciezki_floyda.at(wyswietlane)->sciezka.at(i)->linia[0].color = sf::Color(154,68,234);
                sciezki_floyda.at(wyswietlane)->sciezka.at(i)->linia[1].color = sf::Color(4,249,160);
                sciezki_floyda.at(wyswietlane)->sciezka.at(i)->wierzcholki[0]->kolko.setOutlineColor(sf::Color(154,68,234));
                sciezki_floyda.at(wyswietlane)->sciezka.at(i)->wierzcholki[1]->kolko.setOutlineColor(sf::Color(154,68,234));
                window.draw(sciezki_floyda.at(wyswietlane)->sciezka.at(i)->linia);
                window.draw(sciezki_floyda.at(wyswietlane)->sciezka.at(i)->wierzcholki[0]->kolko);
                window.draw(sciezki_floyda.at(wyswietlane)->sciezka.at(i)->wierzcholki[1]->kolko);
            }

        ///Tutaj dopisywac nowe window.draw();
    }
    window.display();
}
