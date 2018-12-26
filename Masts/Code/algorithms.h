/**
* Name: algorithms.h
* Purpose: Declaration of algorithms
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/
#pragma once

#include <chrono>
#include <string>
#include <cstdlib>
#include "edge.h"

class Algorithms{
    public:
        std::pair<unsigned, std::pair<Vertex*, Vertex*>> linearAlgorithm(std::vector<Vertex*> vertices, std::chrono::duration<double> &elapsedSeconds);

        std::pair<unsigned, std::pair<Vertex*, Vertex*>> mastsAlgorithm(std::vector<Vertex*> vertices, std::chrono::duration<double> &elapsedSeconds);

        std::pair<unsigned, std::pair<Vertex*, Vertex*>> bruteAlgorithm(std::vector<Vertex*> vertices, std::chrono::duration<double> &elapsedSeconds);
};
