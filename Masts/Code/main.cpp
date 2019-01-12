/**
* Name: main.cpp
* Purpose: main
*
* @version 0.1 05/12/2018
* @author Piotr Zawadka
*/

#include <cmath>
#include "interface.h"
#include "windows.h"

int main(int argc, char* argv[])
{
    unsigned m;
    std::pair<unsigned, std::pair<Vertex*, Vertex*>> result;
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;

    std::string algorithm;

    int pause=0;
    int frame=1;

    bool loaded = false;

    std::chrono::duration<double> elapsedSeconds;

    Algorithms algorithms;
    Files files;

    if(argc == 2){
        std::string str(argv[1]);
        files.setFile(str);
        m = 1;
    }
    else if(argc >= 3){
        std::string str(argv[1]);
        files.setFile(str);
        m = atoi(argv[2]);
    }

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Masts");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        if(Interface::events(window, algorithms, files, vertices, edges, algorithm, loaded, result, elapsedSeconds, m)){
            const char* errorVer = "Wrong amount of vertices! in file ";
            char* msg = new char[sizeof(errorVer)+files.getFile().size()];
            strcpy(msg, errorVer);
            strcat(msg, files.getFile().c_str());
            MessageBox(NULL, msg, "ERROR!", MB_ICONEXCLAMATION|MB_OK);
            return ERROR_VERTICES_AMOUNT;
        }
        Interface::draw(window, files, algorithm, frame, pause, loaded, vertices, edges, result, elapsedSeconds);
    }
    return 0;
}

