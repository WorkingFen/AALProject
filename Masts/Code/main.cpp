/**
* Name: main.cpp
* Purpose: main
*
* @version 0.01 18/11/2017
*/

#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "graphs.h"
#include "Instrukcje.h"
#include <cmath>

int main()
{
    std::vector<Wezel*> wezly;
    std::vector<Lacze*> lacza;
    std::vector<Lacze*> lacza_floyda;
    std::vector<Sciezka*> sciezki_floyda;
    std::vector<unsigned> koszta;

    unsigned id_start;
    unsigned id_koniec;
    unsigned koszt = 0;
    unsigned wyswietlane = 0;

    std::string algorytm;

    int pauza=0;
    int klatka=1;

    bool zaladowane = false;

    Instrukcje instrukcje;
    Sciezka sciezka;

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1366, 768), "Grafy");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        Graphs::zdarzenia(window, instrukcje, wezly, lacza, id_start, id_koniec, algorytm,
                        lacza_floyda, zaladowane, sciezka, koszt, wyswietlane, sciezki_floyda, koszta);
        Graphs::rysuj(window, instrukcje, algorytm, klatka, pauza, zaladowane, wezly, lacza,
                        lacza_floyda, sciezka, koszt, wyswietlane, sciezki_floyda, koszta);
    }
}

