/**
* Name: graphs.h
* Purpose: Deklaracja namespace Graphs
*
* @version 1.03 14/05/2017
*/
#pragma once

#include <SFML/Graphics.hpp>
#include "Instrukcje.h"
#include <string>

///Namespace z logika graphs
namespace Graphs
{
    void zdarzenia(sf::Window &window, Instrukcje &instrukcje, std::vector<Wezel*> &wezly, std::vector<Lacze*> &lacza,
                    unsigned &id_start, unsigned &id_koniec, std::string &algorytm, std::vector<Lacze*> &lacza_floyda,
                    bool &zaladowane, Sciezka &sciezka, unsigned &koszt,
                    unsigned &wyswietlane, std::vector<Sciezka*> &sciezki_floyda, std::vector<unsigned> &koszta);

    void pisz(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y,
                    sf::Color color = sf::Color::White, unsigned size = 24);

    void rysuj(sf::RenderWindow &window, Instrukcje &instrukcje, const std::string algorytm,
                    int &klatka, int &pauza, bool zaladowane,
                    std::vector<Wezel*> wezly, std::vector<Lacze*> lacza, std::vector<Lacze*> lacza_floyda,
                    Sciezka sciezka, unsigned &koszt, unsigned wyswietlane,
                    std::vector<Sciezka*> sciezki_floyda, std::vector<unsigned> koszta);

}
