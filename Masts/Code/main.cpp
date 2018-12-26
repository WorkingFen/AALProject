/**
* Name: main.cpp
* Purpose: main
*
* @version 0.1 05/12/2018
* @author Piotr Zawadka
*/

#include <cmath>
#include "interface.h"

int main(int argc, char* argv[])
{
    std::pair<unsigned, std::pair<Vertex*, Vertex*>> result;
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;

    std::string algorithm;

    int pause=0;
    int frame=1;

    bool loaded = false;

    Algorithms algorithms;
    Files files;

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Masts");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        if(argc == 1)
            Interface::events(window, algorithms, files, vertices, edges, algorithm, loaded, result);
        Interface::draw(window, files, algorithm, frame, pause, loaded, vertices, edges, result);
    }
}

