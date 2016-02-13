
/*__________________________________________________
 * gradient.cpp
 *__________________________________________________
 *
 *
 */

#ifndef GRADIENT_CPP
#define GRADIENT_CPP

#include "gradient.h"
// flatIndex3d
#include "indexing.h"

namespace utils
{

    void gradientX(double *field, double *gradient, int iMax, int jMax, int kMax, double factor)
    {
        for ( int i = 0 ; i < iMax - 1 ; i++ )
        {
            for ( int j = 0 ; j < jMax ; j++ )
            {
                for ( int k = 0 ; k < kMax ; k++ )
                {
                    gradient[flatIndex3d(i, j, k, iMax, jMax, kMax)] = field[flatIndex3d(i+1, j, k, iMax, jMax, kMax)] ;
                }
            }
        }

        for ( int j = 0 ; j < jMax ; j++ )
        {
            for ( int k = 0 ; k < kMax ; k++ )
            {
                gradient[flatIndex3d(iMax-1, j, k, iMax, jMax, kMax)] = field[flatIndex3d(0, j, k, iMax, jMax, kMax)] ;
            }
        }

        for ( int j = 0 ; j < jMax ; j++ )
        {
            for ( int k = 0 ; k < kMax ; k++ )
            {
                gradient[flatIndex3d(0, j, k, iMax, jMax, kMax)] -= field[flatIndex3d(iMax-1, j, k, iMax, jMax, kMax)] ;
            }
        }

        for ( int i = 1 ; i < iMax ; i++ )
        {
            for ( int j = 0 ; j < jMax ; j++ )
            {
                for ( int k = 0 ; k < kMax ; k++ )
                {
                    gradient[flatIndex3d(i, j, k, iMax, jMax, kMax)] -= field[flatIndex3d(i-1, j, k, iMax, jMax, kMax)] ;
                }
            }
        }

        factor *= 0.5 ;
        for ( int i = 0 ; i < iMax * jMax * kMax ; i++ )
        {
            gradient[i] *= factor ;
        }
    }

    void gradientY(double *field, double *gradient, int iMax, int jMax, int kMax, double factor)
    {
        for ( int i = 0 ; i < iMax ; i++ )
        {
            for ( int j = 0 ; j < jMax - 1 ; j++ )
            {
                for ( int k = 0 ; k < kMax ; k++ )
                {
                    gradient[flatIndex3d(i, j, k, iMax, jMax, kMax)] = field[flatIndex3d(i, j+1, k, iMax, jMax, kMax)] ;
                }
            }

            for ( int k = 0 ; k < kMax ; k++ )
            {
                gradient[flatIndex3d(i, jMax-1, k, iMax, jMax, kMax)] = field[flatIndex3d(i, 0, k, iMax, jMax, kMax)] ;
            }

            for ( int k = 0 ; k < kMax ; k++ )
            {
                gradient[flatIndex3d(i, 0, k, iMax, jMax, kMax)] -= field[flatIndex3d(i, jMax-1, k, iMax, jMax, kMax)] ;
            }

            for ( int j = 1 ; j < jMax ; j++ )
            {
                for ( int k = 0 ; k < kMax ; k++ )
                {
                    gradient[flatIndex3d(i, j, k, iMax, jMax, kMax)] -= field[flatIndex3d(i, j-1, k, iMax, jMax, kMax)] ;
                }
            }
        }

        factor *= 0.5 ;
        for ( int i = 0 ; i < iMax * jMax * kMax ; i++ )
        {
            gradient[i] *= factor ;
        }
    }

    void gradientZ(double *field, double *gradient, int iMax, int jMax, int kMax, double factor)
    {
        for ( int i = 0 ; i < iMax ; i++ )
        {
            for ( int j = 0 ; j < jMax ; j++ )
            {
                for ( int k = 0 ; k < kMax - 1 ; k++ )
                {
                    gradient[flatIndex3d(i, j, k, iMax, jMax, kMax)] = field[flatIndex3d(i, j, k+1, iMax, jMax, kMax)] ;
                }

                gradient[flatIndex3d(i, j, kMax-1, iMax, jMax, kMax)] = field[flatIndex3d(i, j, 0, iMax, jMax, kMax)] ;
                gradient[flatIndex3d(i, j, 0, iMax, jMax, kMax)] -= field[flatIndex3d(i, j, kMax-1, iMax, jMax, kMax)] ;

                for ( int k = 1 ; k < kMax ; k++ )
                {
                    gradient[flatIndex3d(i, j, k, iMax, jMax, kMax)] -= field[flatIndex3d(i, j, k-1, iMax, jMax, kMax)] ;
                }
            }
        }

        factor *= 0.5 ;
        for ( int i = 0 ; i < iMax * jMax * kMax ; i++ )
        {
            gradient[i] *= factor ;
        }
    }
}

#endif

