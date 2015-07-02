/*__________________________________________________
 * main.cpp
 *__________________________________________________
 */

#include <iostream>

#include "cube/cube.h"

int main(int argc, char* argv[])
{
    std::cout << "Hello !\n" ;

    int nGrid         = 32 ;
    int nParticles    = 10 ;
    double cubeLength = 100 ;

    cube::Cube c = cube::Cube(nGrid, nParticles, cubeLength) ;
    c.printParameters() ;
    c.printParticleList() ;
    return (0);
}

