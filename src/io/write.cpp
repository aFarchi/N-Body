
/*__________________________________________________
 * write.cpp
 *__________________________________________________
 *
 * implementation of the io functions
 *
 */

#ifndef WRITE_CPP 
#define WRITE_CPP

#include "write.h"
// cout
#include <iostream>
// EXIT_FAILURE, EXIT_SUCCESS
#include <stdlib.h>

namespace io
{

    int writeDensityField(const std::string &fileName, double *field, int nGrid)
    {
        FILE *file ;
        file = fopen(fileName.c_str(), "wb") ;

        if (!file)
        {
            std::cout << "Could not open file " << fileName << std::endl ;
            return EXIT_FAILURE ;
        }

        // write nGrid
        int  written       = fwrite(&nGrid, sizeof(int), 1, file) ;
        bool correctOutput = ( written == 1 ) ;

        // write density field
        written            = fwrite(field, sizeof(double), nGrid*nGrid*nGrid, file) ;
        correctOutput     &= ( written == nGrid*nGrid*nGrid ) ;

        if (!correctOutput)
        {
            std::cout << "Could not write to file " << fileName << std::endl ;
            return EXIT_FAILURE ;
        }

        fclose(file) ;
        //std::cout << "Written file " << fileName << std::endl ;
        return EXIT_SUCCESS ;
    }

    int writePotentialField(const std::string &fileName, fftw_complex *potentialField, int nGrid)
    {
        FILE *file ;
        file = fopen(fileName.c_str(), "wb") ;

        if (!file)
        {
            std::cout << "Could not open file " << fileName << std::endl ;
            return EXIT_FAILURE ;
        }

        // write nGrid
        int  written       = fwrite(&nGrid, sizeof(int), 1, file) ;
        bool correctOutput = ( written == 1 ) ;

        // write potential field
        int complexSize    = nGrid * nGrid * ( nGrid / 2 + 1 ) ;
        written            = fwrite(potentialField, sizeof(fftw_complex), complexSize, file) ;
        correctOutput     &= ( written == complexSize ) ;

        if (!correctOutput)
        {
            std::cout << "Could not write to file " << fileName << std::endl ;
            return EXIT_FAILURE ;
        }

        fclose(file) ;
        //std::cout << "Written file " << fileName << std::endl ;
        return EXIT_SUCCESS ;
    }

    int writeParticleList(const std::string &fileName, double *xvParticles, int nParticles)
    {
        FILE *file ;
        file = fopen(fileName.c_str(), "wb") ;

        if (!file)
        {
            std::cout << "Could not open file " << fileName << std::endl ;
            return EXIT_FAILURE ;
        }

        // write nParticles
        int written        = fwrite(&nParticles, sizeof(int), 1, file) ;
        bool correctOutput = ( written == 1 ) ;

        // write particle list
        written            = fwrite(xvParticles, sizeof(double), 6 * nParticles, file) ;
        correctOutput      = ( written == 6 * nParticles ) ;

        if (!correctOutput)
        {
            std::cout << "Could not write to file " << fileName << std::endl ;
            return EXIT_FAILURE ;
        }

        fclose(file) ;
        //std::cout << "Written file " << fileName << std::endl ;
        return EXIT_SUCCESS ;
    }

}

#endif

