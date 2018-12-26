/**
* Name: generator.h
* Purpose: Declaration of generator actions on files
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>

#define PI 3.141592

class Generator{
    private:
        std::ofstream saving;

    public:
        void write(std::string filename, std::string algorithm = "LINEAR", unsigned vertices = 20);
};
