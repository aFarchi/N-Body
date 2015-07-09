
/*__________________________________________________
 * cube.cpp
 *__________________________________________________
 *
 * implementation of class Cube
 *
 */

#ifndef CUBE_CPP
#define CUBE_CPP

#include "cube.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "../patch/toString.cpp"

namespace cube
{
    template <typename DensityBuilder>
    Cube<DensityBuilder>::Cube(int nGrid, int nParticles, double cubeLength, const std::string &log) :
        _densityBuilder(nGrid, cubeLength),
        _log(log),
        _nGrid(nGrid),
        _nParticles(nParticles),
        _cubeLength(cubeLength)
    {
        _log.separator() ;
        _log.printMessage(std::string("Initializing cube..."), true) ;
        
        // initializes random seed
        srand(time(NULL)) ;
        
        // allocate xv particles array
        _xvParticles = new double[6*nParticles] ;

        // initializes xv particles array
        initializeRandomParticles() ;

        _log.printMessage(std::string("Preparing Fourier Transformations..."), true) ;
        
        // Allocate Fields array
        int realSize = _nGrid * _nGrid * _nGrid ;
        int complexSize = _nGrid * _nGrid * ( _nGrid/2 + 1 ) ;
        _realField = (double*) fftw_malloc(sizeof(double) * realSize) ;
        _complexField = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * complexSize ) ;

        // Prepare Fourier Transformations
        unsigned flags = FFTW_MEASURE ;
        _forwardFT  = fftw_plan_dft_r2c_3d(_nGrid, _nGrid, _nGrid, _realField, _complexField, flags) ;
        _backwardFT = fftw_plan_dft_c2r_3d(_nGrid, _nGrid, _nGrid, _complexField, _realField, flags) ;
        _log.separator() ;
    }

    template <typename DensityBuilder>
    Cube<DensityBuilder>::~Cube()
    {
        _log.separator(50, '=', true) ;
        _log.printMessage(std::string("Destroying cube..."), true) ;
        // free xv particles array
        delete _xvParticles ;

        // free FFTW plans
        fftw_destroy_plan(_forwardFT) ;
        fftw_destroy_plan(_backwardFT) ;

        // free fields array 
        fftw_free(_realField) ;
        fftw_free(_complexField) ;
        _log.separator() ;
    }

    template <typename DensityBuilder>
    void Cube<DensityBuilder>::printParameters()
    {
        _log.separator() ;
        _log.printMessage(std::string("Cube with parameters :"), true) ;
        _log.printMessage(std::string("nGrid      = ")+patch::to_string(_nGrid), true) ;
        _log.printMessage(std::string("nParticles = ")+patch::to_string(_nParticles), true) ;
        _log.printMessage(std::string("cubeLength = ")+patch::to_string(_cubeLength), true) ;
    }

    template <typename DensityBuilder>
    void Cube<DensityBuilder>::printParticleList()
    {
        for ( int np = 0 ; np < _nParticles ; np++ )
        {
            _log.separator() ;
            _log.printMessage(std::string("particule #")+patch::to_string(np), true) ; 
            _log.printMessage(std::string("x  = ")+patch::to_string(_xvParticles[6*np]), true) ;
            _log.printMessage(std::string("y  = ")+patch::to_string(_xvParticles[6*np+1]), true) ;
            _log.printMessage(std::string("z  = ")+patch::to_string(_xvParticles[6*np+2]), true) ;
            _log.printMessage(std::string("vx = ")+patch::to_string(_xvParticles[6*np+3]), true) ;
            _log.printMessage(std::string("vy = ")+patch::to_string(_xvParticles[6*np+4]), true) ;
            _log.printMessage(std::string("vz = ")+patch::to_string(_xvParticles[6*np+5]), true) ;
        }
    }

    template <typename DensityBuilder>
    int Cube<DensityBuilder>::writeParticleList(const char *fileName)
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

    template <typename DensityBuilder>
    int Cube<DensityBuilder>::writeParticleList(const std::string &fileName)
    {
        return writeParticleList(fileName.c_str()) ;
    }

    template <typename DensityBuilder>
    void Cube<DensityBuilder>::initializeRandomParticles()
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

    template <typename DensityBuilder>
    int Cube<DensityBuilder>::writeDensityField(const char *fileName)
    {
        FILE *file ;
        file = fopen(fileName, "wb") ;

        if (!file)
        {
            _log.printMessage(std::string("Could not open file ")+std::string(fileName), true) ;
            return EXIT_FAILURE ;
        }

        // write nGrid
        int  written       = fwrite(&_nGrid, sizeof(int), 1, file) ;
        bool correctOutput = ( written == 1 ) ;

        // write density field
        written            = fwrite(_realField, sizeof(double), _nGrid*_nGrid*_nGrid, file) ;
        correctOutput     &= ( written == _nGrid*_nGrid*_nGrid ) ;

        if (!correctOutput)
        {
            _log.printMessage(std::string("Could not write to file ")+std::string(fileName), true) ;
            return EXIT_FAILURE ;
        }

        fclose(file) ;
        _log.printMessage(std::string("Written file ")+std::string(fileName), true) ;
        return EXIT_SUCCESS ;
    }

    template <typename DensityBuilder>
    int Cube<DensityBuilder>::writeDensityField(const std::string &fileName)
    {
        return writeDensityField(fileName.c_str()) ;
    }

    template <typename DensityBuilder>
    void Cube<DensityBuilder>::computeDensityField()
    {
        _densityBuilder.computeDensityField(_xvParticles, _realField, _nParticles) ;
    }
}

#endif

