/**
* Name: path.h
* Purpose: Declaration of path
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/
#pragma once

#include <iostream>
#include "edge.h"

class Path{
    private:
        std::vector<Edge*> path;

    public:
        Path()
        {
        }

        ~Path()
        {
        }

        void addEdge(unsigned id, Vertex* start, Vertex* fin, unsigned scale)
        {
            path.push_back(new Edge(id, start, fin, scale));
        }

        void clean()
        {
            for(unsigned i=0; i<path.size(); i++)
                path.at(i)->zero();
        }

        Edge* getPath(unsigned index){ return path.at(index); }

        void clearPath(){ path.clear(); }

        unsigned getPathSize(){ return path.size(); }

/// /// /// /// /// /// /// /// Functions other than for Path
/// /// Edge functions
///
        void changeEdgeColor(unsigned index, sf::Color color){ path.at(index)->changeLineColor(color); }
///
        void changeEdgeColor(unsigned index, sf::Color color, sf::Color color2){ path.at(index)->changeLineColor(color, color2); }
///
        sf::VertexArray getLine(unsigned index){ return path.at(index)->getLine(); }
///
/// ###
/// /// Vertex functions
///
        void changeVertexColor(unsigned index, unsigned idVer, sf::Color color){ path.at(index)->changeVertexColor(idVer, color); }
///
        sf::CircleShape getVertexCircle(unsigned index, unsigned idVer){ return path.at(index)->getVertexCircle(idVer); }
///
/// ###
/// /// /// /// /// /// ###

};
