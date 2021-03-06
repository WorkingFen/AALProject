/**
* Name: files.h
* Purpose: Declaration of actions on files
*
* @version 0.1 06/12/2018
* @author Piotr Zawadka
*/
#pragma once

#include <fstream>
#include <string>
#include <cstdlib>
#include "vertex.h"

#define ERROR_VERTICES_AMOUNT 1

class Files{
    private:
        std::ifstream loading;
        std::string file;

    public:
        int read(std::vector<Vertex*> &vertices, std::string &algorithm, bool &loaded);

        std::string getFile(){ return file; }

        void setFile(std::string file){ this->file = file; }

        void popFile(){ file.pop_back(); }

        void pushFile(char letter){ file.push_back(letter); }

};
