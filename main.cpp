/*__________________________________________________
 * main.cpp
 *__________________________________________________
 */

#include <iostream>
#include <string>
#include "cube/cube.cpp"
#include "cube/density/ngp.h"
#include "patch/toString.cpp"

int main(int argc, char* argv[])
{
    std::cout << "Hello !\n" ;

    int    nGrid      = 32 ;
    int    nParticles = 1000 ;
    double cubeLength = 100 ;
    double factor     = 0.01 ;

    int    ntSteps    = 1000 ;

    std::string outputDir = "/Users/Alban/Desktop/test-nbody/" ; 
    std::string logFile   = "screen" ;
    std::string prefixPL  = outputDir + "xvp" ;
    std::string suffixPL  = ".bin" ;

    cube::Cube<cube::NGPDensity> c(nGrid, nParticles, cubeLength, logFile) ;
    
    c.printParameters() ;
    for ( int t = 0 ; t < ntSteps ; t++ )
    {
        c.writeParticleList(prefixPL+patch::to_string(t)+suffixPL) ;
        c.timeStep(factor) ;
    }
    
    c.writeParticleList(prefixPL+patch::to_string(ntSteps)+suffixPL) ;
    return (0);
}

