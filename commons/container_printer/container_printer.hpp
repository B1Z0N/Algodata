// code that looks common enough for me to write and post it here
// printing iterable of iterable/values of ... to ostream object
// works on any std conatiner and on any class that meets 
// the requirements of Container(named requirement)
#include <iostream>
#include <iterator>
#include <vector>

namespace cmns {
// commons

template <typename T>
std::ostream& __print_container(std::ostream& os, const T& val, 
                const char* separator = ", ",
                                const char *inscope = "[", 
                const char* outscope = "]", 
                bool end = false)
// prints single value
// end - tells if this the last element in the sequence
{
    os << val;
    if (!end)
    {
        // if this is not the end
        // print separator too
        os << separator;
    }

    return os;
}

template <
    typename T,
    template <typename> typename C
    >
std::ostream& __print_container(
    std::ostream& os, const C<T>& con, const char* separator = ", ", 
    const char *inscope = "[", const char* outscope = "]", bool end = false
    )
// prints iterable of iterbles/values of ...
// end - tells if this the last element in the sequence
{
    if (con.empty())
    {
        // if empty, just print empty parentheses
        return os << inscope << " " << outscope;
    }
    auto prev_end {std::rbegin(con)}; // reverse iterator to (end - 1) element

    os << inscope;

    for (auto it {std::begin(con)}; 
         it != std::prev(prev_end.base());  // convert reverse iterator to normal
         it++)              // iterate till the last element
    {
        __print_container(os, *it, separator, inscope, outscope);
        // recursive/polymorphic call to function
    }

    __print_container(os, *prev_end, separator, inscope, outscope, true);
     // but for the last element call it with (end = true)

    os << outscope;

    if (!end)
    {
        // if this is not the end
        // print separator too
        os << separator << std::endl;
    }

    return os;
}

template <
    typename T,
    template <typename> typename C
    >
std::ostream& print_container(std::ostream& os, const C<T>& con,
    const char* separator = ", ", const char *inscope = "[", const char* outscope = "]")
// wrapper for prettyness
{
    return __print_container(os, con, separator, inscope, outscope, false);
}


};  // namespace cmns