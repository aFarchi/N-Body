
/*__________________________________________________
 * FDForce.h
 *__________________________________________________
 *
 */

#ifndef FDFORCE_H
#define FDFORCE_H

// Fourier...
#include <fftw3.h>

namespace force
{

    template <typename ParticleMover>
        class FDForce
        {
            public :
                FDForce() ;
                FDForce(double *potentialField, fftw_complex *potentialFourierField, int nGrid, double *xvParticles, 
                        int nParticles, double cubeLength, double deltaT, unsigned flags = FFTW_MEASURE) ;
                ~FDForce() ;

                void operator()() ;

            private :
                ParticleMover *_move ;

                double        *_potentialField ;
                double        *_forceField ;
                fftw_complex  *_potentialFourierField ;
                fftw_plan      _backwardFT ;

                const int      _nGrid ;

        };

}

#endif

