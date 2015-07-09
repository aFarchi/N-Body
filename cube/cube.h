
/*__________________________________________________
 * cube.h
 *__________________________________________________
 *
 * definition of class Cube
 *
 */

#ifndef CUBE_H
#define CUBE_H

#include <string>
#include "../log/logFile.h"
#include <fftw3.h>

namespace cube
{
    template <typename DensityBuilder>
    class Cube
    {
        public:
            Cube(int nGrid, int nParticles, double cubeLength, const std::string &log="screen") ;
            ~Cube() ;

            void printParameters() ;
            void printParticleList() ;

            int writeParticleList(const char *fileName) ;
            int writeParticleList(const std::string &fileName) ;

            int writeDensityField(const char *fileName) ;
            int writeDensityField(const std::string &fileName) ;

            void computeDensityField() ;

        private:
            void initializeRandomParticles() ;

            DensityBuilder  _densityBuilder ;
            output::LogFile _log ;
            const int       _nGrid ;
            const int       _nParticles ;
            double         *_xvParticles ;

            const double    _cubeLength ;

            double         *_realField ;
            fftw_complex   *_complexField ;
            fftw_plan       _forwardFT ;
            fftw_plan       _backwardFT ;
    } ;

}

#endif
