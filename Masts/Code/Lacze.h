/**
* Name: Lacze.h
* Purpose: Deklaracja lacza
*
* @version 0.01 18/11/2017
*/
#pragma once

#include <iostream>
#include <math.h>
#include "Wezel.h"
#include <ctime>

class Lacze{
    public:
        unsigned id;
        Wezel* wierzcholki[2];
        unsigned w_id[2];
        unsigned waga;
        sf::VertexArray linia;

        Lacze(): id(0), waga(0)
        {
            wierzcholki[0] = nullptr;
            wierzcholki[1] = nullptr;
            w_id[0] = 0;
            w_id[1] = 0;
        }

        Lacze(unsigned id, Wezel* start, Wezel* koniec)
        {
            this->id = id;
            wierzcholki[0] = start;
            wierzcholki[1] = koniec;
            w_id[0] = start->id;
            w_id[1] = koniec->id;
            //waga = sqrt((koniec->x - start->x)*(koniec->x - start->x)+(koniec->y - start->y)*(koniec->y - start->y));
            waga = (std::rand() % 50) + 1;
            linia = sf::VertexArray(sf::Lines, 2);
            linia[0].position = sf::Vector2f(start->x*8 + 210, start->y*8+10);
            linia[1].position = sf::Vector2f(koniec->x*8 + 210, koniec->y*8+10);
            linia[0].color = sf::Color::White;
            linia[1].color = sf::Color::White;
        }

        Lacze(unsigned id, Wezel* start, Wezel* koniec, unsigned waga)
        {
            this->id = id;
            wierzcholki[0] = start;
            wierzcholki[1] = koniec;
            w_id[0] = start->id;
            w_id[1] = koniec->id;
            //waga = sqrt((koniec->x - start->x)*(koniec->x - start->x)+(koniec->y - start->y)*(koniec->y - start->y));
            this->waga = waga;
            linia = sf::VertexArray(sf::Lines, 2);
            linia[0].position = sf::Vector2f(start->x*8 + 210, start->y*8+10);
            linia[1].position = sf::Vector2f(koniec->x*8 + 210, koniec->y*8+10);
            linia[0].color = sf::Color::White;
            linia[1].color = sf::Color::White;
        }

        void zeruj()
        {
            waga = 0;
        }

        unsigned koszt()
        {
            return waga;
        }

        ~Lacze()
        {
        }

};
