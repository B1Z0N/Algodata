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
	std::vector<bool>  included;

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
	auto values = knp.get_values();
	os << values.size() << '\n';
	for (const auto& val : values) {
		os << val << ' ';
	}
	return os;
}


std::istream& operator>>( std::istream& is, Knapsack& knp )
{
	is >> knp.capacity;

	std::size_t n, value = 0, weight;
	is >> n;

	while( n-- )
	{
		is >> weight;
		knp.values.push_back(value++);
		knp.weights.push_back(weight);
	}

	return is;
}	


class DynamicCondition {
	std::set<int> included;
	std::size_t sum;
public:

	DynamicCondition(std::set<int> included_, int sum_ = -1) 
		:included{included_}, sum{sum_}
	{
		if (sum == -1) 
			sum = std::accumulate(std::begin(included), std::end(included), 0);
	}

	DynamicCondition &operator+=(const DynamicCondition& other) {
		included.insert(other.included.begin(), other.included.end());	
		sum = std::accumulate(std::begin(included), std::end(included), 0); 
		return *this;
	}
	
	std::set<int> get_included() { return included; }
	std::size_t get_sum() { return sum };
};

/**
 * Algorithm implementation
 */
std::size_t Knapsack::solve()
{
	std::size_t size { values.size( ) };
	DynamicCondition remember[ size + 1 ][ capacity + 1 ];
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
				remember[ i ][ w ] = ;
			else if( weights[ i - 1 ] <= w )
			{
				int with = values[ i - 1 ] + remember[ i - 1 ][ w - weights[ i - 1 ] ];
				int without = remember[ i - 1 ][ w ]; 
				if (with > without) {
					remember[ i ][ w ] = with;
					included.insert(i);
				} else {
					remeber[ i ][ w ] = without;
					included.erase(i);
				} 
			}
			else
				remember[ i ][ w ] = remember[ i - 1 ][ w ];
		}
	}

	return remember[ size ][ capacity ];
}

int main() {
	Knapsack knp{};
	std::cin >> knp;
	std::cout << knp;

	return 0;
}
