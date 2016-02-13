
/*__________________________________________________
 * cube.h
 *__________________________________________________
 *
 * cube class
 *
 */

#ifndef CUBE_H
#define CUBE_H

// Fourier...
#include <fftw3.h>
// string
#include <string>

namespace cube
{
    
    template <typename Initializator, typename Step>
        class Cube
        {
            public:
                Cube() ;
                Cube(int nParticles, int nGrid, double cubeLength, double deltaT, double pi = 3.141592, double G = 6.674e-11, unsigned flags = FFTW_MEASURE) ;
                ~Cube() ;
                void initialize() ;
                void stepForward() ;

                std::string printParameters() ; 
                int writeParticleList(const std::string &fileName) ;

            private:
                Initializator *_initialize ;
                Step          *_stepFunction ;

                double        *_xvParticles ;
                double        *_densityField ;
                fftw_complex  *_potentialField ;

                const int      _nParticles ;
                std::string    _parameters ;
        };

}

#endif

