/**
* Name: instructions.h
* Purpose: Declaration of instructions
*
* @version 0.01 18/11/2017
* @author Piotr Zawadka
*/
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "edge.h"
#include "vertex.h"
#include "path.h"

#define MX 500

class Instructions{
    private:
        std::ifstream loading;

    public:
        std::string file;
        void read(std::vector<Vertex*> &vertices, std::vector<Edge*> &edges, unsigned &idStart,
                    unsigned &idFinish, std::string &algorithm, std::vector<Edge*> &floydsEdges, bool &loaded);

        unsigned primsAlgorithm(std::vector<Vertex*> vertices, std::vector<Edge*> edges, Path &path);

        unsigned steinersAlgorithm(std::vector<Vertex*> vertices, std::vector<Edge*> edges, Path &path);

        unsigned dijkstrasAlgorithm(std::vector<Vertex*> vertices, std::vector<Edge*> edges, Path &path, unsigned idStart, unsigned idFinish);

        void floydsAlgorithm(std::vector<Vertex*> vertices, std::vector<Edge*> edges,
                                 std::vector<Edge*> floydsEdges, std::vector<Path*> &floydsPaths,
                                 std::vector<unsigned> &costs);
};
