/**
* Name: edge.h
* Purpose: Declaration of edge
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/
#pragma once

#include <iostream>
#include <ctime>
#include <math.h>
#include "vertex.h"

class Edge{
    public:
        unsigned id;
        Vertex* vertices[2];
        unsigned idVer[2];
        unsigned scale;
        sf::VertexArray line;

        Edge(): id(0), scale(0)
        {
            vertices[0] = nullptr;
            vertices[1] = nullptr;
            idVer[0] = 0;
            idVer[1] = 0;
        }

        Edge(unsigned id, Vertex* start, Vertex* fin)
        {
            this->id = id;
            vertices[0] = start;
            vertices[1] = fin;
            idVer[0] = start->id;
            idVer[1] = fin->id;
            scale = (std::rand() % 50) + 1;
            line = sf::VertexArray(sf::Lines, 2);
            line[0].position = sf::Vector2f(start->x*8 + 210, start->y*8+10);
            line[1].position = sf::Vector2f(fin->x*8 + 210, fin->y*8+10);
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;
        }

        Edge(unsigned id, Vertex* start, Vertex* fin, unsigned scale)
        {
            this->id = id;
            vertices[0] = start;
            vertices[1] = fin;
            idVer[0] = start->id;
            idVer[1] = fin->id;
            this->scale = scale;
            line = sf::VertexArray(sf::Lines, 2);
            line[0].position = sf::Vector2f(start->x*8 + 210, start->y*8+10);
            line[1].position = sf::Vector2f(fin->x*8 + 210, fin->y*8+10);
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;
        }

        void zero()
        {
            scale = 0;
        }

        unsigned cost()
        {
            return scale;
        }

        ~Edge()
        {
        }

};
