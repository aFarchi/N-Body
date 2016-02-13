
/*__________________________________________________
 * indexing.h
 *__________________________________________________
 *
 * functions to compute the 1d index in a 3d table 
 *
 */

#ifndef INDEXING_H
#define INDEXING_H

namespace utils
{

    int flatIndexM3d(int i, int j, int k, int iMax, int jMax, int kMax) ;
    int indexMRealField(int i, int j, int k, int nGrid) ;
    int indexMComplexField(int i, int j, int k, int nGrid) ;

    int flatIndex3d(int i, int j, int k, int iMax, int jMax, int kMax) ;
    int indexRealField(int i, int j, int k, int nGrid) ;
    int indexComplexField(int i, int j, int k, int nGrid) ;
}

#endif

