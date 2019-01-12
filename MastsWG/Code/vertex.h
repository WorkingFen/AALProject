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

///Vertex class
class Vertex{
    private:
        unsigned id;
        unsigned distance;

    public:
        Vertex(): id(0), distance(0)
        {
        }

        Vertex(unsigned id, unsigned distance): id(id), distance(distance)
        {
        }

        ~Vertex()
        {
        }

        unsigned getID(){ return id; }

        unsigned getDistance(){ return distance; }

};
