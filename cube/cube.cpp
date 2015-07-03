
/*__________________________________________________
 * cube.cpp
 *__________________________________________________
 *
 * implementation of class Cube
 *
 */

#include "cube.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


namespace cube
{
    Cube::Cube(int nGrid, int nParticles, double cubeLength) :
        _nGrid(nGrid),
        _nParticles(nParticles),
        _cubeLength(cubeLength)
    {
        
        // initializes random seed
        srand(time(NULL)) ;
        
        // allocate xv particles array
        _xvParticles = new double[6*nParticles] ;

        // initializes xv particles array
        initializeRandomParticles() ;
    }

    Cube::~Cube()
    {
        // free xv particles array
        delete _xvParticles ;
    }

    void Cube::printParameters()
    {
        std::cout << "_________________________" << std::endl ;
        std::cout << "Cube with parameters :" << std::endl ;
        std::cout << "nGrid      = " << _nGrid << std::endl ;
        std::cout << "nParticles = " << _nParticles << std::endl ;
        std::cout << "cubeLength = " << _cubeLength << std::endl ;
    }

    void Cube::printParticleList()
    {
        for ( int np = 0 ; np < _nParticles ; np++ )
        {
            std::cout << "_________________________" << std::endl ;
            std::cout << "particule #" << np << std::endl ;
            std::cout << "x  = " << _xvParticles[6*np]   << std::endl ;
            std::cout << "y  = " << _xvParticles[6*np+1] << std::endl ;
            std::cout << "z  = " << _xvParticles[6*np+2] << std::endl ;
            std::cout << "vx = " << _xvParticles[6*np+3] << std::endl ;
            std::cout << "vy = " << _xvParticles[6*np+4] << std::endl ;
            std::cout << "vz = " << _xvParticles[6*np+5] << std::endl ;
        }
    }


    int Cube::writeParticleList(const char *fileName)
    {
        FILE *file ;
        file = fopen(fileName, "wb") ;

        if (!file)
        {
            std::cout << "Could not open file " << fileName << std::endl ;
            return EXIT_FAILURE ;
        }

        // write number of particles
        int written = fwrite(&_nParticles, sizeof(int), 1, file) ;
        bool correctOutput = ( written == 1 ) ;

        // write xv particles array
        written = fwrite(_xvParticles, sizeof(double), 6*_nParticles, file) ;
        correctOutput &= ( written == 6 * _nParticles ) ;

        if (!correctOutput)
        {
            std::cout << "Could not write to file " << fileName << std::endl ;
            return EXIT_FAILURE ;
        }

        fclose(file) ;
        std::cout << "Written file " << fileName << std::endl ;
        return EXIT_SUCCESS ;
    }

    int Cube::writeParticleList(const std::string &fileName)
    {
        return writeParticleList(fileName.c_str()) ;
    }

    void Cube::initializeRandomParticles()
    {
        for (int np = 0 ; np < _nParticles ; np++)
        {
            // gives random positions
            for (int dim = 0 ; dim < 3 ; dim++)
            {
                _xvParticles[6*np+dim] = _cubeLength * ((double) rand() / (RAND_MAX)) ;
            }

            // gives zero velocity
            for (int dim = 3 ; dim < 6 ; dim++)
            {
                _xvParticles[6*np+dim] = 0.0 ;
            }
        }
    }
}
