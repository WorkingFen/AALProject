/**
* Name: main.cpp
* Purpose: main
*
* @version 0.1 05/12/2018
* @author Piotr Zawadka
*/

#include <cmath>
#include "interface.h"

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

    Algorithms algorithms;
    Files files;
    Path path;

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Masts");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        Interface::events(window, algorithms, files, vertices, edges, idStart, idFinish, algorithm,
                        floydsEdges, loaded, path, cost, displayed, floydsPaths, costs);
        Interface::draw(window, files, algorithm, frame, pause, loaded, vertices, edges,
                        floydsEdges, path, cost, displayed, floydsPaths, costs);
    }
}

