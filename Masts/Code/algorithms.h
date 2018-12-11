/**
* Name: algorithms.h
* Purpose: Declaration of algorithms
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/
#pragma once

#include <string>
#include <cstdlib>
#include "path.h"

class Algorithms{
    public:
        unsigned primsAlgorithm(std::vector<Vertex*> vertices, std::vector<Edge*> edges, Path &path);

        unsigned dijkstrasAlgorithm(std::vector<Vertex*> vertices, std::vector<Edge*> edges, Path &path,
                                    unsigned idStart, unsigned idFinish);

        void floydsAlgorithm(std::vector<Vertex*> vertices, std::vector<Edge*> edges,
                                 std::vector<Edge*> floydsEdges, std::vector<Path*> &floydsPaths,
                                 std::vector<unsigned> &costs);

        std::pair<unsigned, std::pair<Vertex*, Vertex*>> mastsAlgorithm(std::vector<Vertex*> vertices);

        std::pair<unsigned, std::pair<Vertex*, Vertex*>> bruteAlgorithm(std::vector<Vertex*> vertices);
};
