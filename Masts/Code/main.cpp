/**
* Name: main.cpp
* Purpose: main
*
* @version 0.1 05/12/2018
* @author Piotr Zawadka
*/

#include <iostream>
#include <ctime>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "graphs.h"
#include "instructions.h"

int main()
{
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;
    std::vector<Edge*> floydsEdges;
    std::vector<Path*> floydsPaths;
    std::vector<unsigned> costs;

    unsigned idStart;
    unsigned idFinish;
    unsigned cost = 0;
    unsigned displayed = 0;

    std::string algorithm;

    int pause=0;
    int frame=1;

    bool loaded = false;

    Instructions instructions;
    Path path;

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1366, 768), "Masts");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        Graphs::events(window, instructions, vertices, edges, idStart, idFinish, algorithm,
                        floydsEdges, loaded, path, cost, displayed, floydsPaths, costs);
        Graphs::draw(window, instructions, algorithm, frame, pause, loaded, vertices, edges,
                        floydsEdges, path, cost, displayed, floydsPaths, costs);
    }
}

