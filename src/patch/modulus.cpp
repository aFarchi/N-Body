
/*__________________________________________________
 * modulus.cpp
 *__________________________________________________
 *
 * implementation of the modulus functions
 *
 */

#ifndef MODULUS_CPP
#define MODULUS_CPP

#include "modulus.h"

namespace patch
{
    int modulus(int n, int p)
    {
        if ( p < 0 )
        {
            return modulus(n, -p) ;
        }
        else
        {
            int q = n % p ;
            if ( q < 0 )
            {
                q += p ;
            }

            return q ;
        }
    }

    double modulus(double n, double p)
    {
        if ( p < 0 )
        {
            return modulus(n, -p) ;
        }
        else
        {
            double q = n ;
            while ( q <= 0 )
            {
                q += p ;
            }
            while ( q > p )
            {
                q -= p ;
            }
            return q ;
        }
    }
}

#endif

