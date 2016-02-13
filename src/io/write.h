
/*__________________________________________________
 * write.h
 *__________________________________________________
 *
 * functions that write results into files
 *
 */

#ifndef WRITE_H 
#define WRITE_H

// string
#include <string>
// Fourier...
#include <fftw3.h>

namespace io
{

    int writeDensityField(const std::string &fileName, double *field, int nGrid) ;
    int writePotentialField(const std::string &fileName, fftw_complex *potentialField, int nGrid) ;

    int writeParticleList(const std::string &fileName, double *xvParticles, int nParticles) ;

}

#endif

