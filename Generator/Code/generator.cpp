/**
* Name: generator.cpp
* Purpose: Implementation of generator actions on files
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/

#include "generator.h"
#define PI 3.141592

void Generator::write(std::string filename, std::string algorithm, unsigned vertices)
{
    this->saving.open("Out/" + filename + ".txt");
    if(saving.good())
    {
        saving << "# Every line that starts with # will be ignored\n";
        saving << "# Order of vertices is significant\n";
        saving << "# Algorithm, which will be called; [BRUTE, MASTS, LINEAR]\n";
        saving << "ALGORITHM = " << algorithm << "\n";
        saving << "# Number of vertices. Vertices has been numbered from 1\n";
        saving << "VERTICES = " << vertices << "\n";
        saving << "# Every vertex has two (ID, Distance[to next vertex]) or four atributes (ID, X coordinate, Y coordinate, Distance)\n";
        saving << "# It depends on number of vertices. If more than 20, then graph won't be created\n";
        if(vertices <= 20)
            for(unsigned temp = 0; temp != vertices; temp++)
                saving << temp+1 << " " << std::round(vertices*2*sin((2*temp*PI)/vertices)) << " " << std::round(vertices*2*cos((2*temp*PI)/vertices)) << " " << (std::rand() % 20) + 1 << "\n";
        else
            for(unsigned temp = 0; temp != vertices; temp++)
                saving << temp+1 << " " << (std::rand() % 20) + 1 << "\n";
        saving << "# Number of edges\n";
        saving << "EDGES = " << vertices << "\n";
        saving << "# Every edge has three atributes (ID, first vertex, last vertex)\n";
        for(unsigned temp = 0; temp != vertices; temp++)
            saving << temp+1 << " " << temp+1 << " " << ((temp+1)%vertices)+1 << "\n";
    }
    else
    {
        std::string msg = "An error occurred while saving to file " + filename;
        throw msg;
    }
    this->saving.close();
}
