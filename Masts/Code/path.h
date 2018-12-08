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
    public:
        std::vector<Edge*> path;

        Path()
        {
        }

        void addEdge(unsigned id, Vertex* start, Vertex* fin, unsigned scale)
        {
            path.push_back(new Edge(id, start, fin, scale));
        }

        void clean()
        {
            for(int i=0; i<path.size(); i++)
                path.at(i)->zero();
        }
};
