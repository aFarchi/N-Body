
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
#include <math.h>

#include "../patch/toString.cpp"

namespace cube
{
    template <typename DensityBuilder>
    Cube<DensityBuilder>::Cube(int nGrid, int nParticles, double cubeLength, const std::string &log, double pi) :
        _densityBuilder(nGrid, cubeLength),
        _log(log),
        _nGrid(nGrid),
        _nParticles(nParticles),
        _cubeLength(cubeLength),
        _pi(pi)
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

        // Initialize force kernel
        _forceKernel = new double[complexSize] ;
        initializeForceKernel() ;

        // Allocate force field
        _forceFieldX = new double[realSize] ;
        _forceFieldY = new double[realSize] ;
        _forceFieldZ = new double[realSize] ;
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

        // free force kernel
        delete _forceKernel ;
        delete _forceFieldX ;
        delete _forceFieldY ;
        delete _forceFieldZ ;
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

    template <typename DensityBuilder>
    void Cube<DensityBuilder>::initializeForceKernel()
    {
        for ( int i = 0 ; i < _nGrid ; i++ )
        {
            for ( int j = 0 ; j < _nGrid ; j++ )
            {
                for ( int k = 0 ; k < ( _nGrid/2 + 1 ) ; k++ )
                {
                    double kI = -2.0 * ( 1.0 - cos( 2.0 * i * _pi / ( _nGrid + 1.0 ) ) ) ; 
                    double kJ = -2.0 * ( 1.0 - cos( 2.0 * j * _pi / ( _nGrid + 1.0 ) ) ) ; 
                    double kK = -2.0 * ( 1.0 - cos( 2.0 * k * _pi / ( _nGrid + 1.0 ) ) ) ; 
   
                    _forceKernel[i*_nGrid*(_nGrid/2+1)+j*(_nGrid/2+1)+k] = kI + kJ + kK ;
                }
            }
        }
        _forceKernel[0] = 1.0 ;
    }

    template <typename DensityBuilder>
    void Cube<DensityBuilder>::timeStep(double factor)
    {
        //_log.printMessage(std::string("Computing density field."), true) ;
        computeDensityField() ;
        //_log.printMessage(std::string("FFT Forward"), true) ;
        fftw_execute(_forwardFT) ;

        //_log.printMessage(std::string("Dividing by eigenvalues"), true) ;
        int complexSize = _nGrid * _nGrid * ( _nGrid/2 + 1 ) ;
        for ( int i = 0 ; i < complexSize ; i++ )
        {
            _complexField[i][0] /= _forceKernel[i] ;
            _complexField[i][1] /= _forceKernel[i] ;
        }

        //_log.printMessage(std::string("FFT Backward"), true) ;
        fftw_execute(_backwardFT) ;

        //_log.printMessage(std::string("Numerical gradient X"), true) ;
        for ( int j = 0 ; j < _nGrid ; j++ )
        {
            for ( int k = 0 ; k < _nGrid ; k++ )
            {
                _forceFieldX[j*_nGrid+k] = -0.5 * ( _realField[_nGrid*_nGrid+j*_nGrid+k] -
                                                    _realField[(_nGrid-1)*_nGrid*_nGrid+j*_nGrid+k] ) ;

                for ( int i = 1 ; i < _nGrid - 1 ; i++ )
                {
                    _forceFieldX[i*_nGrid*_nGrid+j*_nGrid+k] = -0.5 * ( _realField[(i+1)*_nGrid*_nGrid+j*_nGrid+k] -
                                                                        _realField[(i-1)*_nGrid*_nGrid+j*_nGrid+k] ) ; 
                }

                _forceFieldX[(_nGrid-1)*_nGrid*_nGrid+j*_nGrid+k] = -0.5 * ( _realField[j*_nGrid+k] -
                                                                             _realField[(_nGrid-2)*_nGrid*_nGrid+j*_nGrid+k] ) ;

            }
        }

        //_log.printMessage(std::string("Numerical gradient Y"), true) ;
        for ( int i = 0 ; i < _nGrid ; i++ )
        {
            for ( int k = 0 ; k < _nGrid ; k++ )
            {
                _forceFieldY[i*_nGrid*_nGrid+k] = -0.5 * ( _realField[i*_nGrid*_nGrid+_nGrid+k] -
                                                           _realField[i*_nGrid*_nGrid+(_nGrid-1)*_nGrid+k] ) ;

                for ( int j = 1 ; j < _nGrid - 1 ; j++ )
                {
                    _forceFieldY[i*_nGrid*_nGrid+j*_nGrid+k] = -0.5 * ( _realField[i*_nGrid*_nGrid+(j+1)*_nGrid+k] -
                                                                        _realField[i*_nGrid*_nGrid+(j-1)*_nGrid+k] ) ; 
                }

                _forceFieldY[i*_nGrid*_nGrid+(_nGrid-1)*_nGrid+k] = -0.5 * ( _realField[i*_nGrid*_nGrid+k] -
                                                                             _realField[i*_nGrid*_nGrid+(_nGrid-2)*_nGrid+k] ) ;

            }
        }

        //_log.printMessage(std::string("Numerical gradient Z"), true) ;
        for ( int i = 0 ; i < _nGrid ; i++ )
        {
            for ( int j = 0 ; j < _nGrid ; j++ )
            {
                _forceFieldZ[i*_nGrid*_nGrid+j*_nGrid] = -0.5 * ( _realField[i*_nGrid*_nGrid+j*_nGrid+1] -
                                                                  _realField[i*_nGrid*_nGrid+j*_nGrid+(_nGrid-1)] ) ;

                for ( int k = 1 ; k < _nGrid - 1 ; k++ )
                {
                    _forceFieldZ[i*_nGrid*_nGrid+j*_nGrid+k] = -0.5 * ( _realField[i*_nGrid*_nGrid+j*_nGrid+(k+1)] -
                                                                        _realField[i*_nGrid*_nGrid+j*_nGrid+(k-1)] ) ; 
                }

                _forceFieldZ[i*_nGrid*_nGrid+j*_nGrid+(_nGrid-1)] = -0.5 * ( _realField[i*_nGrid*_nGrid+j*_nGrid] -
                                                                             _realField[i*_nGrid*_nGrid+j*_nGrid+(_nGrid-2)] ) ;

            }
        }

        //_log.printMessage(std::string("Moving particles"), true) ;
        double scale = _nGrid / _cubeLength ;
        for ( int np = 0 ; np < _nParticles ; np++ )
        {
            int i = floor( _xvParticles[6*np  ] * scale ) ;
            int j = floor( _xvParticles[6*np+1] * scale ) ;
            int k = floor( _xvParticles[6*np+2] * scale ) ;
        
            _xvParticles[6*np+3] += _forceFieldX[i*_nGrid*_nGrid+j*_nGrid+k] ;
            _xvParticles[6*np+4] += _forceFieldY[i*_nGrid*_nGrid+j*_nGrid+k] ;
            _xvParticles[6*np+5] += _forceFieldZ[i*_nGrid*_nGrid+j*_nGrid+k] ;
        
            _xvParticles[6*np  ] += factor * _xvParticles[6*np+3] ; 
            _xvParticles[6*np+1] += factor * _xvParticles[6*np+4] ; 
            _xvParticles[6*np+2] += factor * _xvParticles[6*np+5] ; 
        }

        //_log.printMessage(std::string("Send particles"), true) ;
        for ( int np = 0 ; np < _nParticles ; np++ )
        {
            for ( int dim = 0 ; dim < 3 ; dim++ )
            {
                while ( _xvParticles[6*np+dim] < 0.0 )
                {
                    _xvParticles[6*np+dim] += _cubeLength ;
                }

                while ( _xvParticles[6*np+dim] >= _cubeLength )
                {
                    _xvParticles[6*np+dim] -= _cubeLength ;
                }
                /*
                if (  _xvParticles[6*np+dim] < 0.0 )
                {
                    _xvParticles[6*np+dim] += _cubeLength ;
                    _log.printMessage(std::string("Particle out of bounds :")+patch::to_string(_xvParticles[6*np+dim]), true) ;
                }
                else if ( _xvParticles[6*np+dim] > _cubeLength )
                {
                    _xvParticles[6*np+dim] -= _cubeLength ;
                }
                */
            }
        }
        //_log.printMessage(std::string("performed time step"), true) ;
    }
}

#endif

