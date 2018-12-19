/**
* Name: files.cpp
* Purpose: Implementation of actions on files
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/

#include "files.h"

void Files::read(std::vector<Vertex*> &vertices, std::vector<Edge*> &edges, unsigned &idStart,
                        unsigned &idFinish, std::string &algorithm, std::vector<Edge*> &floydsEdges, bool &loaded)
{
    std::string line;
    std::string response;
    std::string hollow;
    unsigned verticesNum;
    unsigned edgesNum;
    unsigned id, idVer0, idVer1;
    unsigned forSwitch;
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
            else if(response == "ADDITIONAL")
            {
                line = response;
            }
            else if(line == "VERTICES")
            {
                if(algorithm == "BRUTE" || algorithm == "MASTS" || algorithm == "LINEAR"){
                    id = atoi(response.c_str());              ///Pierwsza liczba zostala juz pobrana; Usuwamy znak 0, by mieć liczbę;
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
                else{
                    id = atoi(response.c_str());              ///Pierwsza liczba zostala juz pobrana; Usuwamy znak 0, by mieć liczbę;
                    loading >> x;
                    loading >> y;
                    vertices.push_back(new Vertex(id, x, y));

                    for(unsigned i=1; i<verticesNum; i++)
                    {
                        loading >> id;
                        loading >> x;
                        loading >> y;
                        vertices.push_back(new Vertex(id, x, y));
                    }
                }
            }
            else if(line == "EDGES")
            {
                if(algorithm == "BRUTE" || algorithm == "MASTS" || algorithm == "LINEAR"){
                    id = atoi(response.c_str());                    ///Pierwsza liczba zostala juz pobrana; Usuwamy znak 0, by mieć liczbę;
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
                else{
                    id = atoi(response.c_str());                    ///Pierwsza liczba zostala juz pobrana; Usuwamy znak 0, by mieć liczbę;
                    loading >> idVer0;
                    loading >> idVer1;
                    vertices.at(idVer0-1)->addNeighbour(idVer1, vertices.at(idVer1-1)->getX(), vertices.at(idVer1-1)->getY());
                    vertices.at(idVer1-1)->addNeighbour(idVer0, vertices.at(idVer0-1)->getX(), vertices.at(idVer0-1)->getY());
                    edges.push_back(new Edge(id, vertices.at(idVer0-1), vertices.at(idVer1-1)));

                    for(unsigned i=1; i<edgesNum; i++)
                    {
                        loading >> id;
                        loading >> idVer0;
                        loading >> idVer1;
                        vertices.at(idVer0-1)->addNeighbour(idVer1, vertices.at(idVer1-1)->getX(), vertices.at(idVer1-1)->getY());
                        vertices.at(idVer1-1)->addNeighbour(idVer0, vertices.at(idVer0-1)->getX(), vertices.at(idVer0-1)->getY());
                        edges.push_back(new Edge(id, vertices.at(idVer0-1), vertices.at(idVer1-1)));
                    }
                }
            }
            else if(line == "ADDITIONAL")
            {
                if(algorithm == "PATH") forSwitch = 1;
                else if(algorithm == "FLOYD") forSwitch = 2;
                else forSwitch = 0;
                switch(forSwitch)
                {
                    case 1:
                        idStart = atoi(response.c_str());
                        loading >> idFinish;
                        break;
                    case 2:
                        idVer0 = atoi(response.c_str());            ///Pierwsza liczba zostala juz pobrana; Usuwamy znak 0, by mieć liczbę;
                        loading >> idVer1;
                        floydsEdges.push_back(new Edge(1, vertices.at(idVer0-1), vertices.at(idVer1-1)));
                        break;
                    default:
                        break;
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
