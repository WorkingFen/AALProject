/**
* Name: edge.h
* Purpose: Declaration of edge
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/
#pragma once

#include <ctime>
#include <math.h>
#include "vertex.h"

class Edge{
    private:
        unsigned id;
        Vertex* vertices[2];
        unsigned scale;
        sf::VertexArray line;

    public:
        Edge(): id(0), scale(0)
        {
            vertices[0] = nullptr;
            vertices[1] = nullptr;
        }

        Edge(unsigned id, Vertex* start, Vertex* fin): id(id)
        {
            vertices[0] = start;
            vertices[1] = fin;
            scale = (std::rand() % 50) + 1;
            line = sf::VertexArray(sf::Lines, 2);
            line[0].position = sf::Vector2f(WIDTH/2 + start->getX()*8 + 10 ,HEIGHT/2 - start->getY()*8 + 30);
            line[1].position = sf::Vector2f(WIDTH/2 + fin->getX()*8 + 10 ,HEIGHT/2 - fin->getY()*8 + 30);
            changeLineColor(sf::Color::White);
        }

        Edge(unsigned id, Vertex* start, Vertex* fin, unsigned scale): id(id), scale(scale)
        {
            vertices[0] = start;
            vertices[1] = fin;
            line = sf::VertexArray(sf::Lines, 2);
            line[0].position = sf::Vector2f(WIDTH/2 + start->getX()*8 + 10 ,HEIGHT/2 - start->getY()*8 + 30);
            line[1].position = sf::Vector2f(WIDTH/2 + fin->getX()*8 + 10 ,HEIGHT/2 - fin->getY()*8 + 30);
            changeLineColor(sf::Color::White);
        }

        ~Edge()
        {
        }

        void zero()
        {
            scale = 0;
        }

        unsigned getID(){ return id; }

        unsigned getScale(){ return scale; }

        Vertex* getVertex(unsigned index){ return vertices[index]; }

        unsigned getIDVer(unsigned index){ return vertices[index]->getID(); }

        sf::VertexArray getLine(){ return line; }

        void changeLineColor(sf::Color color){
             line[0].color = color;
             line[1].color = color;
        }

        void changeLineColor(sf::Color color, sf::Color color2){
             line[0].color = color;
             line[1].color = color2;
        }

/// /// /// /// /// /// /// /// Functions other than for Edge
/// /// Vertex functions
///
        double getVertexX(unsigned index){ return vertices[index]->getX(); }
///
        double getVertexY(unsigned index){ return vertices[index]->getY(); }
///
        void changeVertexColor(unsigned index, sf::Color color){ vertices[index]->setOutlineColor(color); }
///
        sf::CircleShape getVertexCircle(unsigned index){ return vertices[index]->getCircle(); }
///
/// ###
/// /// /// /// /// /// ###

};
