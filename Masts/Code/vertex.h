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
    private:
        unsigned id;
        double x;
        double y;
        unsigned distance;
        std::vector<Vertex*> neighbours;
        sf::CircleShape circle;

    public:
        Vertex(): id(0), x(0), y(0), distance(0)
        {
        }

        Vertex(unsigned id, double x, double y): id(id), x(x), y(y), distance(0)
        {
            circle.setRadius(10);
            circle.setPosition(x*8+200,y*8);
            circle.setOutlineThickness(2);
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineColor(sf::Color::White);
        }

        Vertex(unsigned id, double x, double y, unsigned distance): id(id), x(x), y(y), distance(distance)
        {
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

        void addNext(unsigned id, double x, double y, unsigned distance)
        {
            this->neighbours.push_back(new Vertex(id, x, y, distance));
        }

        unsigned getID(){ return id; }

        double getX(){ return x; }

        double getY(){ return y; }

        Vertex* getNeighbour(int index){ return neighbours.at(index); }

        int getNeighboursSize(){ return neighbours.size(); }

        sf::CircleShape getCircle(){ return circle; }

        void setOutlineColor(sf::Color color){ circle.setOutlineColor(color); }

/// /// /// /// /// /// /// /// Functions other than for Edge
/// /// Vertex functions
///
        unsigned getNeighbourID(unsigned index){ return neighbours.at(index)->getID(); }
///
/// ###
/// /// /// /// /// /// ###

};
