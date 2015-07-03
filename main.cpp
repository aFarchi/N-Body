/*__________________________________________________
 * main.cpp
 *__________________________________________________
 */

#include <iostream>
#include <string>
#include "cube/cube.h"

int main(int argc, char* argv[])
{
    std::cout << "Hello !\n" ;

    int nGrid         = 32 ;
    int nParticles    = 10 ;
    double cubeLength = 100 ;

    std::string fileName   = "/Users/Alban/Desktop/test.bin" ;

    cube::Cube c = cube::Cube(nGrid, nParticles, cubeLength) ;
    c.printParameters() ;
    c.printParticleList() ;
    c.writeParticleList(fileName) ;

    return (0);
}

