/**
* Name: interface.h
* Purpose: Declaration of namespace Interface
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/
#pragma once

#include "algorithms.h"
#include "files.h"

#define WIDTH 1366
#define HEIGHT 768
#define BACKGROUND sf::Color(8,8,16)

///Namespace with interface logic
namespace Interface
{
    char SFMLtoASCII(sf::Keyboard::Key code);

    void events(sf::Window &window, Algorithms &algorithms, Files &files, std::vector<Vertex*> &vertices,
                    std::vector<Edge*> &edges, std::string &algorithm,
                    bool &loaded, std::pair<unsigned, std::pair<Vertex*, Vertex*>> &result);

    void write(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y,
                    sf::Color color = sf::Color::White, unsigned size = 24);

    void draw(sf::RenderWindow &window, Files &files, const std::string algorithm, int &frame,
                    int &pause, bool loaded, std::vector<Vertex*> vertices, std::vector<Edge*> edges,
                    std::pair<unsigned, std::pair<Vertex*, Vertex*>> &result);

}
