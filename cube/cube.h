
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
            Cube(int nGrid, int nParticles, double cubeLength, const std::string &log="screen", double pi=3.14159265) ;
            ~Cube() ;

            void printParameters() ;
            void printParticleList() ;

            int writeParticleList(const char *fileName) ;
            int writeParticleList(const std::string &fileName) ;

            int writeDensityField(const char *fileName) ;
            int writeDensityField(const std::string &fileName) ;

            void timeStep(double factor=1.0) ;

            void computeDensityField() ;

        private:
            void initializeRandomParticles() ;
            void initializeForceKernel() ;

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

            double         *_forceKernel ;
            double          _pi ;
            double         *_forceFieldX ;
            double         *_forceFieldY ;
            double         *_forceFieldZ ;
    } ;

}

#endif
