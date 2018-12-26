/**
* Name: algorithms.cpp
* Purpose: Implementation of algorithms
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/

#include "algorithms.h"

std::pair<unsigned, std::pair<Vertex*, Vertex*>> Algorithms::linearAlgorithm(std::vector<Vertex*> vertices, std::chrono::duration<double> &elapsedSeconds){
    auto start = std::chrono::system_clock::now();
    unsigned len = vertices.size();
    unsigned sumDis = 0;

    for(auto tmp : vertices){
        sumDis += tmp->getDistance();
    }

    unsigned averageDis = sumDis >> 1;
    unsigned prevDis = 0;
    unsigned actualDis = 0;

    unsigned bestDis = 0;
    std::pair<Vertex*, Vertex*> bestVer;
    std::pair<unsigned, std::pair<Vertex*, Vertex*>> result;

    unsigned backVertex = vertices.size();

    for(unsigned frontVertex = 0; backVertex != 0 ; frontVertex = (frontVertex+1)%len){
        if(actualDis >= averageDis){
            if(prevDis == averageDis || actualDis  == averageDis){
                bestVer.first = vertices.at(backVertex%len);
                if((prevDis-averageDis) == 0){
                    bestVer.second = vertices.at((!frontVertex)?(len-1):((frontVertex-1)%len));
                    result.first = prevDis;
                }
                else{
                    bestVer.second = vertices.at(frontVertex);
                    result.first = actualDis;
                }
                result.second = bestVer;
                return result;
            }
            else if(bestDis > averageDis && bestDis < actualDis){
                if((bestDis - averageDis) > (averageDis - prevDis)){
                    bestVer.first = vertices.at(backVertex%len);
                    bestVer.second = vertices.at((!frontVertex)?(len-1):((frontVertex-1)%len));
                    bestDis = prevDis;
                }
            }
            else if(bestDis < averageDis && bestDis > prevDis){
                if((averageDis - bestDis) > (actualDis - averageDis)){
                    bestVer.first = vertices.at(backVertex%len);
                    bestVer.second = vertices.at(frontVertex);
                    bestDis = actualDis;
                }
            }
            else if((bestDis < averageDis && bestDis < prevDis) || (bestDis > averageDis && bestDis > actualDis)){
                bestVer.first = vertices.at(backVertex%len);
                if((actualDis - averageDis) >= (averageDis - prevDis)){
                    bestVer.second = vertices.at((!frontVertex)?(len-1):((frontVertex-1)%len));
                    bestDis = prevDis;
                }
                else{
                    bestVer.second = vertices.at(frontVertex);
                    bestDis = actualDis;
                }
            }
            actualDis-=vertices.at(backVertex%len)->getDistance();
            prevDis-=vertices.at(backVertex%len)->getDistance();
            backVertex = (backVertex+1)%len;
            frontVertex = (!frontVertex)?(len-1):((frontVertex-1)%len);
            continue;
        }
        prevDis = actualDis;
        actualDis += vertices.at(frontVertex)->getDistance();
    }
    result.first = bestDis;
    result.second = bestVer;
    auto end = std::chrono::system_clock::now();
    elapsedSeconds = end-start;
    return result;
}

std::pair<unsigned, std::pair<Vertex*, Vertex*>> Algorithms::mastsAlgorithm(std::vector<Vertex*> vertices, std::chrono::duration<double> &elapsedSeconds){
    auto start = std::chrono::system_clock::now();
    unsigned len = vertices.size();
    unsigned sumDis = 0;

    for(auto tmp : vertices){
        sumDis += tmp->getDistance();
    }

    unsigned averageDis = sumDis >> 1;
    unsigned actualDis = 0;
    unsigned bestDis = 0;
    unsigned prevDis = 0;
    std::pair<Vertex*, Vertex*> bestVer;

    std::pair<unsigned, std::pair<Vertex*, Vertex*>> result;

    for(unsigned chosen = 0; chosen < len; chosen++){
        for(unsigned temp = chosen; temp != len; temp = (temp+1)%len){
            actualDis += vertices.at(temp)->getDistance();
            if(actualDis >= averageDis){
                if(prevDis == averageDis || actualDis  == averageDis){
                    bestVer.first = vertices.at(chosen);
                    if((prevDis-averageDis) == 0){
                        bestVer.second = vertices.at(temp);
                        result.first = prevDis;
                    }
                    else{
                        bestVer.second = vertices.at((temp+1)%len);
                        result.first = actualDis;
                    }
                    result.second = bestVer;
                    return result;
                }
                else if(bestDis > averageDis && bestDis < actualDis){
                    if((bestDis - averageDis) > (averageDis - prevDis)){
                        bestVer.first = vertices.at(chosen);
                        bestVer.second = vertices.at(temp);
                        bestDis = prevDis;
                    }
                }
                else if(bestDis < averageDis && bestDis > prevDis){
                    if((averageDis - bestDis) > (actualDis - averageDis)){
                        bestVer.first = vertices.at(chosen);
                        bestVer.second = vertices.at((temp+1)%len);
                        bestDis = actualDis;
                    }
                }
                else if((bestDis < averageDis && bestDis < prevDis) || (bestDis > averageDis && bestDis > actualDis)){
                    bestVer.first = vertices.at(chosen);
                    if((actualDis - averageDis) >= (averageDis - prevDis)){
                        bestVer.second = vertices.at(temp);
                        bestDis = prevDis;
                    }
                    else{
                        bestVer.second = vertices.at((temp+1)%len);
                        bestDis = actualDis;
                    }
                }
                break;
            }
            prevDis = actualDis;
        }
        prevDis = 0;
        actualDis = 0;
    }
    result.first = bestDis;
    result.second = bestVer;
    auto end = std::chrono::system_clock::now();
    elapsedSeconds = end-start;
    return result;
}

std::pair<unsigned, std::pair<Vertex*, Vertex*>> Algorithms::bruteAlgorithm(std::vector<Vertex*> vertices, std::chrono::duration<double> &elapsedSeconds){
    auto start = std::chrono::system_clock::now();
    unsigned len = vertices.size();
    unsigned sumDis = 0;

    for(auto tmp : vertices){
        sumDis += tmp->getDistance();
    }

    unsigned averageDis = sumDis >> 1;
    unsigned actualDis = 0;
    unsigned bestDis = 0;
    std::pair<Vertex*, Vertex*> bestVer;

    std::pair<unsigned, std::pair<Vertex*, Vertex*>> result;

    for(unsigned chosen = 0; chosen < len; chosen++){
        for(unsigned target = (chosen+1)%len; target != chosen; target = (target+1)%len){
            for(unsigned temp = chosen; temp != target; temp = (temp+1)%len)
                actualDis += vertices.at(temp)->getDistance();
            if(actualDis <= averageDis && actualDis > bestDis){
                bestVer.first = vertices.at(chosen);
                bestVer.second = vertices.at(target);
                bestDis = actualDis;
            }
            actualDis = 0;
        }
    }
    result.first = bestDis;
    result.second = bestVer;
    auto end = std::chrono::system_clock::now();
    elapsedSeconds = end-start;
    return result;
}
