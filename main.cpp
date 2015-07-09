/*__________________________________________________
 * main.cpp
 *__________________________________________________
 */

#include <iostream>
#include <string>
#include "cube/cube.cpp"
#include "cube/density/ngp.h"

int main(int argc, char* argv[])
{
    std::cout << "Hello !\n" ;

    int nGrid         = 32 ;
    int nParticles    = 10000 ;
    double cubeLength = 100 ;

    std::string fileName   = "/Users/Alban/Desktop/test.bin" ;
    std::string logFile    = "/Users/Alban/Desktop/logTest.txt" ;
    std::string fN_den     = "/Users/Alban/Desktop/denTest.bin" ;

    cube::Cube<cube::NGPDensity> c(nGrid, nParticles, cubeLength, logFile) ;
    c.printParameters() ;
    c.printParticleList() ;
    c.writeParticleList(fileName) ;
    c.computeDensityField() ;
    c.writeDensityField(fN_den) ;

    return (0);
}

