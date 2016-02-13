
/*__________________________________________________
 * toString.cpp
 *__________________________________________________
 *
 * patch to correct the to_string function
 *
 */

#ifndef TOSTRING_CPP
#define TOSTRING_CPP

// string
#include <string>
// ostringstream
#include <sstream>

namespace patch
{
    template < typename T >
    std::string to_string(const T& n)
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

#endif

