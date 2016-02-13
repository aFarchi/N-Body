
/*__________________________________________________
 * cube.cpp
 *__________________________________________________
 *
 */

#ifndef CUBE_CPP
#define CUBE_CPP

#include "cube.h"

// to_string
#include "../patch/toString.cpp"
// writeParticleList
#include "../io/write.h"

namespace cube
{

    template <typename Initializator, typename Step>
        Cube<Initializator, Step>::Cube() :
            _nParticles(0),
            _parameters()
        {
        }

    template <typename Initializator, typename Step>
        Cube<Initializator, Step>::Cube(int nParticles, int nGrid, double cubeLength, double deltaT, double pi, double G, unsigned flags) :
            _nParticles(nParticles),
            _parameters("Cube with parameters :\n")
        {
            int realSize    = nGrid * nGrid * nGrid ;
            int complexSize = nGrid * nGrid * ( nGrid / 2 + 1 ) ;

            _xvParticles    = new double[6*nParticles] ;
            _densityField   = (double*) fftw_malloc(sizeof(double)*realSize) ;
            _potentialField = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*complexSize) ;

            _initialize     = new Initializator(_xvParticles, nParticles, cubeLength) ;
            _stepFunction   = new Step(_xvParticles, nParticles, _densityField, _potentialField, nGrid, cubeLength, deltaT, pi, G, flags) ;

            _parameters    += std::string("nGrid      = ") + patch::to_string(nGrid)      + "\n" ;
            _parameters    += std::string("nParticles = ") + patch::to_string(nParticles) + "\n" ;
            _parameters    += std::string("cubeLength = ") + patch::to_string(cubeLength) + "\n" ;
            _parameters    += std::string("deltaT     = ") + patch::to_string(deltaT)     + "\n" ;
        }

    template <typename Initializator, typename Step>
        Cube<Initializator, Step>::~Cube()
        {
            fftw_free(_potentialField) ;
            fftw_free(_densityField) ;
            delete _xvParticles ;
            delete _initialize ;
            delete _stepFunction ;
        }

    template <typename Initializator, typename Step>
        void Cube<Initializator, Step>::initialize()
        {
            (*_initialize)() ;
        }

    template <typename Initializator, typename Step>
        void Cube<Initializator, Step>::stepForward()
        {
            (*_stepFunction)() ;
        }

    template <typename Initializator, typename Step>
        std::string Cube<Initializator, Step>::printParameters()
        {
            return _parameters ;
        }

    template <typename Initializator, typename Step>
        int Cube<Initializator, Step>::writeParticleList(const std::string &fileName)
        {
            return io::writeParticleList(fileName, _xvParticles, _nParticles) ; 
        }

}

#endif

