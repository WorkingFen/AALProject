/**
* Name: Wezel.h
* Purpose: Deklaracja wezla
*
* @version 0.01 18/11/2017
*/
#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

///Klasa wezla
class Wezel{
    public:
        unsigned id;
        double x;
        double y;
        bool opcjonalne;
        std::vector<Wezel*> sasiedzi;

        sf::CircleShape kolko;

        /*Wezel(): id(0), x(0), y(0)//, opcjonalne(0)
        {
        }//// to git*/
        Wezel(): id(0), x(0), y(0), opcjonalne(0)
        {
        }

        /*Wezel(unsigned id, double x, double y)//, bool opcjonalne)
        {
            this->id = id;
            this->x = x;
            this->y = y;
            //this->opcjonalne = opcjonalne;
            kolko.setRadius(10);
            kolko.setPosition(x*8+200,y*8);
            kolko.setOutlineThickness(2);
            kolko.setFillColor(sf::Color::Transparent);
            kolko.setOutlineColor(sf::Color::White);
        }// to git*/

        Wezel(unsigned id, double x, double y, bool opcjonalne)
        {
            this->id = id;
            this->x = x;
            this->y = y;
            this->opcjonalne = opcjonalne;
            kolko.setRadius(10);
            kolko.setPosition(x*8+200,y*8);
            kolko.setOutlineThickness(2);
            kolko.setFillColor(sf::Color::Transparent);
            kolko.setOutlineColor(sf::Color::White);
        }

        ~Wezel()
        {
        }

        /*void dodaj_sasiada(unsigned id, double x, double y)//, bool opcjonalne = 0)
        {
            this->sasiedzi.push_back(new Wezel(id, x, y));//, opcjonalne));
        }// to git*/

        void dodaj_sasiada(unsigned id, double x, double y, bool opcjonalne)
        {
            this->sasiedzi.push_back(new Wezel(id, x, y, opcjonalne));
        }
};
