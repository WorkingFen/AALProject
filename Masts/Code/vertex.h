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

#define WIDTH 1366
#define HEIGHT 768

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

        Vertex(unsigned id, unsigned distance): id(id), x(0), y(0), distance(distance)
        {
            circle.setRadius(10);
            circle.setPosition(WIDTH/2 + x*8 ,HEIGHT/2 - y*8 +20);
            circle.setOutlineThickness(2);
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineColor(sf::Color::White);
        }

        Vertex(unsigned id, double x, double y, unsigned distance): id(id), x(x), y(y), distance(distance)
        {
            circle.setRadius(10);
            circle.setPosition(WIDTH/2 + x*8 ,HEIGHT/2 - y*8 +20);
            circle.setOutlineThickness(2);
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineColor(sf::Color::White);
        }

        ~Vertex()
        {
        }

        void addNeighbour(unsigned id, unsigned distance)
        {
            this->neighbours.push_back(new Vertex(id, distance));
        }

        void addNeighbour(unsigned id, double x, double y, unsigned distance)
        {
            this->neighbours.push_back(new Vertex(id, x, y, distance));
        }

        unsigned getID(){ return id; }

        double getX(){ return x; }

        double getY(){ return y; }

        unsigned getDistance(){ return distance; }

        Vertex* getNeighbour(int index){ return neighbours.at(index); }

        int getNeighboursSize(){ return neighbours.size(); }

        sf::CircleShape getCircle(){ return circle; }

        void setOutlineColor(sf::Color color){ circle.setOutlineColor(color); }

/// /// /// /// /// /// /// /// Functions other than for this Vertex
/// /// Vertex functions
///
        unsigned getNeighbourID(unsigned index){ return neighbours.at(index)->getID(); }
///
/// ###
/// /// /// /// /// /// ###

};
