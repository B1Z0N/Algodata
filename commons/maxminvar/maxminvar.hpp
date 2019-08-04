// finding maximal element in variadic number of arguments

#ifndef MAX_MIN_VAR_HPP
#define MAX_MIN_VAR_HPP


namespace cmns {
// commons


// *************MAXIMAL*VALUE*FUNCTIONS****************


/**
 *  Recursion stop on oneelemnt sequence
 */
template <typename T>
T max( const T& elem );


/**
 * Recursive function to find maximal value in 
 * arguments passed
 */
template <typename T, typename... Args>
auto max( T fst, Args... args );


// *************MINIMAL*VALUE*FUNCTIONS****************


/**
 *  Recursion stop on oneelemnt sequence
 */
template <typename T>
T min( const T& elem );

/**
 * Recursive function to find minimal value in 
 * arguments passed
 */
template <typename T, typename... Args>
auto min( T fst, Args... args );


};


#endif