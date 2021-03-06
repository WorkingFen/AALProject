/**
* Name: interface.h
* Purpose: Declaration of namespace Interface
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/
#pragma once

#include <chrono>
#include "algorithms.h"
#include "files.h"

#define BACKGROUND sf::Color(8,8,16)
#define PI 3.141592

///Namespace with interface logic
namespace Interface
{
    char SFMLtoASCII(sf::Keyboard::Key code);

    int events(sf::Window &window, Algorithms &algorithms, Files &files, std::vector<Vertex*> &vertices,
                    std::vector<Edge*> &edges, std::string &algorithm,
                    bool &loaded, std::pair<unsigned, std::pair<Vertex*, Vertex*>> &result, std::chrono::duration<double> &elapsedSeconds, unsigned &m);

    void write(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y,
                    sf::Color color = sf::Color::White, unsigned size = 24);

    void draw(sf::RenderWindow &window, Files &files, const std::string algorithm, int &frame,
                    int &pause, bool loaded, std::vector<Vertex*> vertices, std::vector<Edge*> edges,
                    std::pair<unsigned, std::pair<Vertex*, Vertex*>> &result, std::chrono::duration<double> &elapsedSeconds);

}
