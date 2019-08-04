// finding maximal element in variadic number of arguments

#include "maxminvar.hpp"

namespace cmns {
// commons


// *************MAXIMAL*VALUE*FUNCTIONS****************


/**
 *  Recursion stop on oneelemnt sequence
 */
template <typename T>
T max( const T& elem ) { return elem; }


/**
 * Recursive function to find maximal value in 
 * arguments passed
 */
template <typename T, typename... Args>
auto max( T fst, Args... args )
{
	auto max_elem { max( args... ) };
	return max_elem > fst ? max_elem : fst;
}


// *************MINIMAL*VALUE*FUNCTIONS****************


/**
 *  Recursion stop on oneelemnt sequence
 */
template <typename T>
T min( const T& elem ) { return elem; }

/**
 * Recursive function to find minimal value in 
 * arguments passed
 */
template <typename T, typename... Args>
auto min( T fst, Args... args )
{
	auto max_elem { min( args... ) };
	return max_elem < fst ? max_elem : fst;
}


};