/**
* Name: main.cpp
* Purpose: main
*
* @version 0.1 05/12/2018
* @author Piotr Zawadka
*/

#include <cmath>
#include <chrono>
#include <sstream>
#include "windows.h"
#include "files.h"
#include "algorithms.h"

int main(int argc, char* argv[])
{
    unsigned m;
    std::pair<unsigned, std::pair<Vertex*, Vertex*>> result;
    std::vector<Vertex*> vertices;

    std::string algorithm;

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
    else return 0;

    try{
        if(files.read(vertices, algorithm, loaded)){
            const char* errorVer = "Wrong amount of vertices! in file ";
            char* msg = new char[sizeof(errorVer)+files.getFile().size()];
            strcpy(msg, errorVer);
            strcat(msg, files.getFile().c_str());
            MessageBox(NULL, msg, "ERROR!", MB_ICONEXCLAMATION|MB_OK);
            return ERROR_VERTICES_AMOUNT;
        }
        auto start = std::chrono::high_resolution_clock::now();
        for(unsigned i = 0; i < m; i++){
            if(algorithm == "BRUTE")
                result = algorithms.bruteAlgorithm(vertices);
            else if(algorithm == "MASTS")
                result = algorithms.mastsAlgorithm(vertices);
            else if(algorithm == "LINEAR")
                result = algorithms.linearAlgorithm(vertices);
        }
        auto end = std::chrono::high_resolution_clock::now();
        elapsedSeconds = end-start;
    }
    catch(...){
        std::string msg = "Fatal error while loading from file " + files.getFile() + " No file or directory";
        MessageBox(NULL, msg.c_str(), NULL, MB_OK | MB_ICONEXCLAMATION);
        exit(20);
    }
    std::cout << "File used: " << files.getFile() << std::endl;
    files.setFile("");

    std::cout << "Algorithm used: " << algorithm << std::endl;
    std::cout << "Amount of vertices: " << vertices.size() << std::endl;

    unsigned sumDis = 0;
    for(auto tmp : vertices){
        sumDis += tmp->getDistance();
    }
    std::cout << "Distance/Sum distance: " << result.first << "/" << sumDis << std::endl;
    std::cout << "First vertex: " << result.second.first->getID() << std::endl;
    std::cout << "Second vertex: " << result.second.second->getID() << std::endl;
    std::cout << "Time taken: " << elapsedSeconds.count() << std::endl;

    return 0;
}

