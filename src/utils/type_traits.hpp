#pragma once

namespace ft{

    /* C++11 :  helper class */
    
    template <class Tp, Tp v>
    struct integral_constant
    {
        static const    Tp                 value = v;
        typedef         Tp                 value_type;
        typedef         integral_constant   type;
    };

    typedef integral_constant<bool, true>  true_type;
    typedef integral_constant<bool, false> false_type;

    /* enable if */

    template <bool, class Tp = void> 
    struct enable_if {};

    template <class Tp> 
    struct enable_if<true, Tp> {typedef Tp type;};

    /* is_integral */ 

    template <class Tp> 
    struct is_integral                     : public false_type {};
    
    template <>          
    struct is_integral<bool>               : public true_type {};
    
    template <>          
    struct is_integral<char>               : public true_type {};
    
    template <>          
    struct is_integral<signed char>        : public true_type {};
    
    template <>          
    struct is_integral<unsigned char>      : public true_type {};
    
    template <>          
    struct is_integral<wchar_t>            : public true_type {};
    
    template <>          
    struct is_integral<short>              : public true_type {};
    
    template <>          
    struct is_integral<unsigned short>     : public true_type {};
    
    template <>          
    struct is_integral<int>                : public true_type {};
    
    template <>          
    struct is_integral<unsigned int>       : public true_type {};
    
    template <>          
    struct is_integral<long>               : public true_type {};
    
    template <>          
    struct is_integral<unsigned long>      : public true_type {};
    
    template <>          
    struct is_integral<long long>          : public true_type {};
    
    template <>          
    struct is_integral<unsigned long long> : public true_type {};
}
