
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

#include "../patch/toString.h"

namespace cube
{
    Cube::Cube(int nGrid, int nParticles, double cubeLength, const std::string &log) :
        _nGrid(nGrid),
        _nParticles(nParticles),
        _cubeLength(cubeLength),
        _log(log)
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
        _log.printMessage(std::string("_________________________"), true) ;
        _log.printMessage(std::string("Cube with parameters :"), true) ;
        _log.printMessage(std::string("nGrid      = ")+patch::to_string(_nGrid), true) ;
        _log.printMessage(std::string("nParticles = ")+patch::to_string(_nParticles), true) ;
        _log.printMessage(std::string("cubeLength = ")+patch::to_string(_cubeLength), true) ;
    }

    void Cube::printParticleList()
    {
        for ( int np = 0 ; np < _nParticles ; np++ )
        {
            _log.printMessage(std::string("_________________________"), true) ;
            _log.printMessage(std::string("particule #")+patch::to_string(np), true) ; 
            _log.printMessage(std::string("x  = ")+patch::to_string(_xvParticles[6*np]), true) ;
            _log.printMessage(std::string("y  = ")+patch::to_string(_xvParticles[6*np+1]), true) ;
            _log.printMessage(std::string("z  = ")+patch::to_string(_xvParticles[6*np+2]), true) ;
            _log.printMessage(std::string("vx = ")+patch::to_string(_xvParticles[6*np+3]), true) ;
            _log.printMessage(std::string("vy = ")+patch::to_string(_xvParticles[6*np+4]), true) ;
            _log.printMessage(std::string("vz = ")+patch::to_string(_xvParticles[6*np+5]), true) ;
        }
    }


    int Cube::writeParticleList(const char *fileName)
    {
        FILE *file ;
        file = fopen(fileName, "wb") ;

        if (!file)
        {
            _log.printMessage(std::string("Could not open file ")+std::string(fileName), true) ;
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
            _log.printMessage(std::string("Could not write to file ")+std::string(fileName), true) ;
            return EXIT_FAILURE ;
        }

        fclose(file) ;
        _log.printMessage(std::string("Written file ")+std::string(fileName), true) ;
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
