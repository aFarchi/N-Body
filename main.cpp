/*__________________________________________________
 * main.cpp
 *__________________________________________________
 */

#include <iostream>
#include <string>
//#include "cube/cube.cpp"
//#include "patch/toString.cpp"

//#ifdef DDEN_NGP
//#include "cube/density/ngp.h"
//#else
//#include "cube/density/cic.h"
//#endif

#include "cube/run.h"

int main(int argc, char* argv[])
{
    std::cout << "Hello !\n" ;

    int    nGrid      = 32 ;
    int    nParticles = 20 ;
    double cubeLength = 100 ;
    double factor     = 0.0001 ;

    int    ntSteps    = 100 ;

    std::string outputDir = "/Users/Alban/Desktop/test-nbody/" ; 
    std::string logFile   = "screen" ;
    std::string prefixPL  = outputDir + "xvp" ;
    std::string suffixPL  = ".bin" ;

    return cube::runSimulation(nGrid, nParticles, cubeLength, factor, ntSteps,
            outputDir, logFile, prefixPL, suffixPL) ;

//#ifdef DDEN_NGP
//    cube::Cube<cube::NGPDensity> c(nGrid, nParticles, cubeLength, logFile) ;
//#else
//    cube::Cube<cube::CICDensity> c(nGrid, nParticles, cubeLength, logFile) ;
//#endif

//    c.printParameters() ;
//    for ( int t = 0 ; t < ntSteps ; t++ )
//    {
//        c.writeParticleList(prefixPL+patch::to_string(t)+suffixPL) ;
//        c.timeStep(factor) ;
//    }
    
//    c.writeParticleList(prefixPL+patch::to_string(ntSteps)+suffixPL) ;
//    return (0);
}

