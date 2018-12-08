/**
* Name: vertex.h
* Purpose: Declaration of vertex
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/
#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

///Vertex class
class Vertex{
    public:
        unsigned id;
        double x;
        double y;
        std::vector<Vertex*> neighbours;

        sf::CircleShape circle;

        Vertex(): id(0), x(0), y(0)
        {
        }

        Vertex(unsigned id, double x, double y)
        {
            this->id = id;
            this->x = x;
            this->y = y;
            circle.setRadius(10);
            circle.setPosition(x*8+200,y*8);
            circle.setOutlineThickness(2);
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineColor(sf::Color::White);
        }

        ~Vertex()
        {
        }

        void addNeighbour(unsigned id, double x, double y)
        {
            this->neighbours.push_back(new Vertex(id, x, y));
        }

};
