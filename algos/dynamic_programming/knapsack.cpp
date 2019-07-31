#include <iostream>
#include <vector>
#include <cassert>


// @Problem
// Given a set of items, each with a weight and a value, 
// determine the number of each item to include in a collection 
// so that the total weight is less than or equal to a given limit 
// and the total value is as large as possible. 
// 
// @Algorithm
// Time complexity  - O(N*W), 
// where N is the number of items and 
// W is the capacity of the knapsack.
// Space complexity - O(N*W)
//
// @Example
//
// ╔════════╦════╦═════╦═════╗
// ║ value  ║ 60 ║ 100 ║ 120 ║
// ╠════════╬════╬═════╬═════╣
// ║ weight ║ 10 ║  20 ║  30 ║
// ╚════════╩════╩═════╩═════╝
// MAXW = 50
// 
// Weight = 10; Value = 60;
// Weight = 20; Value = 100;
// Weight = 30; Value = 120;
// Weight = 10 + 20; Value = 160;
// Weight = 10 + 30; Value = 180;
// Weight = 20 + 30; Value = 220;
// Weight = 30 + 20 + 10 > 50
//
// Answer: 220;
//
// @Input format
// 50 
// 3
// 60 10 100 20 120 30
//
// @Output format
// 220


/**
 * 0-1 knapsack solution class
 */
class Knapsack
{
	using size_t = std::size_t;

	size_t capacity;
	std::vector<size_t> values ;
	std::vector<size_t> weights;

	bool calculated { false };
	size_t result;

public:

	Knapsack() = default;
	Knapsack( size_t capacity, const std::vector<size_t>& values, const std::vector<size_t>& weights)
	: capacity{ capacity }, values{ values }, weights{ weights } { } 

	size_t get_capacity() { return capacity; }
	std::vector<size_t> get_values () { return values ; }
	std::vector<size_t> get_weights() { return weights; }

	/**
	 * Solved only first time, for others just use saved value
	 */
	size_t operator()() 
	{
		return calculated ? result : calculated = true, solve();
	}

	friend std::ostream& operator<<( std::ostream& os, Knapsack& knp );
	friend std::istream& operator>>( std::istream& is, Knapsack& knp );	

private:

	/**
	 * Algorithm implementation
	 */
	size_t solve();
};


std::ostream& operator<<( std::ostream& os, Knapsack& knp )
{
	return os << knp();
}


std::istream& operator>>( std::istream& is, Knapsack& knp )
{
	is >> knp.capacity;

	std::size_t n, value, weight;
	is >> n;

	while( n-- )
	{
		is >> value >> weight;

		knp.values.push_back(value);
		knp.weights.push_back(weight);
	}

	return is;
}	


/**
 * Algorithm implementation
 */
std::size_t Knapsack::solve()
{
	std::size_t size { values.size( ) };
	std::size_t remember[ size + 1 ][ capacity + 1 ];
	/**
	 * A row number i represents the set of all the items 
	 * from rows 1 to i. For instance, the values in row 3 assumes 
	 * that we only have items 1, 2, and 3.
	 *
	 * A column number j represents the weight capacity of our knapsack. 
	 * Therefore, the values in column 5, for example, assumes that our 
	 * knapsack can hold 5 weight units.
	 *
	 * Putting everything together, an entry in row i, column j represents 
	 * the maximum value that can be obtained with items 1, 2, 3 … i, in a 
	 * knapsack that can hold j weight units.
	 */

	for( int i = 0; i <= size; ++i )
	{
		for( int w = 0; w <= capacity; ++w )
		{
			if( i == 0 || w == 0 )
				// base case 
				remember[ i ][ w ] = 0;
			else if( weights[ i - 1 ] <= w )
				remember[ i ][ w ] = std::max( 
					values[ i - 1 ] + remember[ i - 1 ][ w - weights[ i - 1 ] ],	
					// include this item
					remember[ i - 1 ][ w ]	// or
					// don't include
				);
			else
				remember[ i ][ w ] = remember[ i - 1 ][ w ];
		}
	}

	return remember[ size ][ capacity ];
}


void test_knapsack( const std::vector<std::size_t>& values, 
			   	    const std::vector<std::size_t>& weights, 
			   		std::size_t capacity, std::size_t answer )
{
	assert( ( Knapsack { capacity, values, weights } )() == answer );
}


int main()
{
	// Base cases
	test_knapsack( { 60 }, { 10 }, 10, 60 );
	test_knapsack( { 60 }, { 10 }, 5,   0 );

	// Simple cases
	test_knapsack( { 60, 100, 120 }, { 10, 20, 30 }, 50, 220 );
	test_knapsack( { 25, 31, 15, 25, 4 }, { 43, 67, 25, 12, 36 }, 75, 50 );

	// Medium cases
	test_knapsack( { 17, 32, 33, 30, 10, 4, 21, 40, 42, 5, 29, 27, 10, 35, 
					 34, 33, 49, 47, 47, 28, 27, 5, 38, 47, 8, 9, 19,  10, 
					 6, 45, 10, 23, 31, 32, 14, 17, 31, 45, 21, 39, 19, 7,
					 36, 19, 44, 27, 20, 39, 45, 18 }, 
				   { 25, 35, 43, 33, 6, 23, 3, 5, 42, 45, 19, 21, 27,   2, 
				   	 11, 2, 6, 29, 32, 36, 21, 41, 37, 29, 15, 30, 19, 34, 
				   	 1, 12, 31, 20, 44, 37, 1, 17, 18, 34, 22, 23, 2,   3, 
				   	 30, 1, 7, 24, 39, 33, 14, 1 }, 22, 235 );

	std::cout << "All tests passed!\n";

	return 0;
}