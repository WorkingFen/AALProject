/**
* Name: files.cpp
* Purpose: Implementation of actions on files
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/

#include "files.h"

void Files::read(std::vector<Vertex*> &vertices, std::vector<Edge*> &edges, std::string &algorithm, bool &loaded)
{
    std::string line;
    std::string response;
    std::string hollow;
    unsigned verticesNum;
    unsigned edgesNum;
    unsigned id, idVer0, idVer1;
    unsigned distance;
    double x, y;

    this->loading.open("Resources/" + file + ".txt");
    if(loading.good())
    {
        while(!loading.eof())
        {
            loading >> response;
            if(response == "#")
            {
                std::getline(loading, hollow);
                continue;
            }
            else if(response == "ALGORITHM")
            {
                loading >> hollow;
                loading >> algorithm;
            }
            else if(response == "VERTICES")
            {
                line = response;
                loading >> hollow;
                loading >> verticesNum;
            }
            else if(response == "EDGES")
            {
                line = response;
                loading >> hollow;
                loading >> edgesNum;
            }
            else if(line == "VERTICES")
            {
                if(algorithm == "BRUTE" || algorithm == "MASTS" || algorithm == "LINEAR"){
                    id = atoi(response.c_str());
                    loading >> x;
                    loading >> y;
                    loading >> distance;
                    vertices.push_back(new Vertex(id, x, y, distance));

                    for(unsigned i=1; i<verticesNum; i++)
                    {
                        loading >> id;
                        loading >> x;
                        loading >> y;
                        loading >> distance;
                        vertices.push_back(new Vertex(id, x, y, distance));
                    }
                }
            }
            else if(line == "EDGES")
            {
                if(algorithm == "BRUTE" || algorithm == "MASTS" || algorithm == "LINEAR"){
                    id = atoi(response.c_str());
                    loading >> idVer0;
                    loading >> idVer1;
                    vertices.at(idVer0-1)->addNeighbour(idVer1, vertices.at(idVer1-1)->getX(), vertices.at(idVer1-1)->getY());
                    vertices.at(idVer1-1)->addNeighbour(idVer0, vertices.at(idVer0-1)->getX(), vertices.at(idVer0-1)->getY());
                    edges.push_back(new Edge(id, vertices.at(idVer0-1), vertices.at(idVer1-1), vertices.at(idVer0-1)->getDistance()));

                    for(unsigned i=1; i<edgesNum; i++)
                    {
                        loading >> id;
                        loading >> idVer0;
                        loading >> idVer1;
                        vertices.at(idVer0-1)->addNeighbour(idVer1, vertices.at(idVer1-1)->getX(), vertices.at(idVer1-1)->getY());
                        vertices.at(idVer1-1)->addNeighbour(idVer0, vertices.at(idVer0-1)->getX(), vertices.at(idVer0-1)->getY());
                        edges.push_back(new Edge(id, vertices.at(idVer0-1), vertices.at(idVer1-1), vertices.at(idVer0-1)->getDistance()));
                    }
                }
            }
        }
    }
    else
    {
        std::string msg = "An error occurred while loading from file " + file;
        throw msg;
    }
    this->loading.close();
    loaded = true;
}
