
/*__________________________________________________
 * indexing.cpp
 *__________________________________________________
 *
 * implementation of the functions to compute the 1d index in a 3d table 
 *
 */

#ifndef INDEXING_CPP
#define INDEXING_CPP

#include "indexing.h"
// modulus
#include "../patch/modulus.h"

namespace utils
{

    int flatIndexM3d(int i, int j, int k, int iMax, int jMax, int kMax)
    {
        return ( patch::modulus(i, iMax) * kMax * jMax +
                 patch::modulus(j, jMax) * kMax        +
                 patch::modulus(k, kMax)               ) ;
    }

    int indexMRealField(int i, int j, int k, int nGrid)
    {
        return ( patch::modulus(i, nGrid) * nGrid * nGrid +
                 patch::modulus(j, nGrid) * nGrid         +
                 patch::modulus(k, nGrid)                 ) ;
    }

    int indexMComplexField(int i, int j, int k, int nGrid)
    {
        return ( patch::modulus(i, nGrid)         * ( nGrid / 2 + 1 ) * nGrid +
                 patch::modulus(j, nGrid)         * ( nGrid / 2 + 1 )         +
                 patch::modulus(k, nGrid / 2 + 1)                             ) ;
    }

    int flatIndex3d(int i, int j, int k, int iMax, int jMax, int kMax)
    {
        return ( i * kMax * jMax +
                 j * kMax        +
                 k               ) ;
    }

    int indexRealField(int i, int j, int k, int nGrid)
    {
        return ( i * nGrid * nGrid +
                 j * nGrid         +
                 k                 ) ;
    }

    int indexComplexField(int i, int j, int k, int nGrid)
    {
        return ( i * ( nGrid / 2 + 1 ) * nGrid +
                 j * ( nGrid / 2 + 1 )         +
                 k                             ) ;
    }

}

#endif

