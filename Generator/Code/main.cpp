/**
* Name: main.cpp
* Purpose: main
*
* @version 0.1 05/12/2018
* @author Piotr Zawadka
*/

#include "generator.h"

int main(int argc, char* argv[])
{
    if(argc >= 2){
        std::string filename(argv[1]);
        Generator generator;

        srand(time(NULL));
        if(argc == 2) generator.write(filename);
        else{
            std::string algorithm(argv[2]);
            if(algorithm == "BRUTE" || algorithm == "MASTS" || algorithm == "LINEAR"){
                if(argc == 3) generator.write(filename, algorithm);
                else{
                    if(atoi(argv[3]) >= 2){
                        if(argc == 4) generator.write(filename, algorithm, atoi(argv[3]));
                        else{
                            std::string msg = "Too many arguments, check HELP for further informations";
                            std::cout << msg;
                        }
                    }
                    else{
                        std::string msg = "Wrong amount of vertices, there should be more than 1 vertex";
                        std::cout << msg;
                    }
                }
            }
            else{
                std::string msg = "Wrong type of algorithm, check HELP for further informations";
                std::cout << msg;
            }
        }
    }
    else{
        std::string msg = "Too little arguments, check HELP for further informations";
        std::cout << msg;
    }
    return 0;
}
