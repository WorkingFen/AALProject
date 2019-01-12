/**
* Name: files.cpp
* Purpose: Implementation of actions on files
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/

#include "files.h"

int Files::read(std::vector<Vertex*> &vertices, std::string &algorithm, bool &loaded)
{
    std::string line;
    std::string response;
    std::string hollow;
    unsigned verticesNum, edgesNum;
    unsigned id, distance;

    this->loading.open("Resources/" + file + ".txt");
    if(loading.good())
    {
        while(loading >> response)
        {
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
                if(verticesNum <= 1) return ERROR_VERTICES_AMOUNT;
            }
            else if(response == "EDGES")
            {
                line = response;
                loading >> hollow;
                loading >> edgesNum;
            }
            else if(line == "VERTICES")
            {
                if(verticesNum <= 20){
                    if(algorithm == "BRUTE" || algorithm == "MASTS" || algorithm == "LINEAR"){
                        id = atoi(response.c_str());
                        loading >> hollow;
                        loading >> hollow;
                        loading >> distance;
                        vertices.push_back(new Vertex(id, distance));

                        for(unsigned i=1; i<verticesNum; i++)
                        {
                            loading >> id;
                            loading >> hollow;
                            loading >> hollow;
                            loading >> distance;
                            vertices.push_back(new Vertex(id, distance));
                        }
                    }
                }
                else{
                    if(algorithm == "BRUTE" || algorithm == "MASTS" || algorithm == "LINEAR"){
                        id = atoi(response.c_str());
                        loading >> distance;
                        vertices.push_back(new Vertex(id, distance));

                        for(unsigned i=1; i<verticesNum; i++)
                        {
                            loading >> id;
                            loading >> distance;
                            vertices.push_back(new Vertex(id, distance));
                        }
                    }
                }
            }
            else if(line == "EDGES"){}
        }
    }
    else
    {
        std::string msg = "An error occurred while loading from file " + file;
        throw msg;
    }
    this->loading.close();
    loaded = true;
    return 0;
}
