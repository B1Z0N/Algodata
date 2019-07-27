#include <iostream>	// cin, cout
#include <ios>		// streamsize
#include <vector>	// vector
#include <fstream>	// ifstream
#include <limits>	// numeric_limits<streamsize>::max
#include <queue>
#include <tuple>

struct Material;

template <typename __Istream>
std::pair<std::priority_queue<Material>, int> __input( __Istream&);

std::pair<std::priority_queue<Material>, int> input( const char* fname = nullptr );

template <typename __Ostream>
void __output( __Ostream&, int);

void output( int, const char* fname = nullptr );


//------------------------------------------------------------------
// @Problem
// Thief is stoling materials from storage.
// Different materials may have distinct price per kg.
// He can stole non-integral amount of the material.
// But his knapsack is of limited size and he can take
// only limited weight. Help him earn the most money.
// 
// @Example
// You are given the table:
// +--------+----+---+----+---+
// | price  | 4  | 9 | 11 | 2 |
// +--------+----+---+----+---+
// | weight | 5  | 3 |  4 | 6 |
// +--------+----+---+----+---+
// And maximal weight is 8
// Let's find the maximal sum of money that could be earned.
// 1. First, go take maximal price per weight and steal as much
// as you can.
// max( 4/5, 9/3, 2/6 ) = 9/3 = 3 ( $ / kg )
// so, buddy, take 3 kg of 2nd material
// 2. Since we have more space, we repeat 1st step.
// max( 4/5, 9/3, 11/4, 2/6 ) = 11/4 = 2.75 ( $ / kg )
// take 4 kg of 3rd material
// 3. Again
// max( 4/5, 2/6 ) = 4/5 = 0.8 ( $ / kg )
// finish this and take 1 kg of 1st material, 
// knapsack is full, get out of there as fast as you can!
//				+--------------+
//				| WE ARE RICH! |
//				+--------------+
//
// @Input format
// 8 4
// 4 5 9 3 11 4 2 6
//
// First line is:
// "knapsack-capacity" "number-of-different-materials"
// And second is:
// "price1" "weight1" ...
// 
// @Output
// 75
//
// ( 3 * 9 + 4 * 11 + 1 * 4 )
//-----------------------------------------------------------------------------


struct Material
{
	int price;
	int weight;

	friend bool operator < ( const Material& a, const Material& b )
	{ 
		return ( a.price / a.weight ) < ( b.price / b.weight );
	}
};

/**
 * Solution function
 */
int steal( std::pair<std::priority_queue<Material>, int> mat_and_capacity )
{
	auto& materials = mat_and_capacity.first;
	int capacity = mat_and_capacity.second;

	int sum { };
	while( capacity > 0 && !materials.empty() )
	{
		Material mt = materials.top(); materials.pop();
		
		sum += mt.price * 
				( capacity < mt.weight ? capacity : mt.weight);
		capacity -= mt.weight;
	}

	return sum;
}

int main()
{
	output( steal( input( ) ) );
	std::cout << '\n';

	return 0;
}


template <typename __Istream>
std::pair<std::priority_queue<Material>, int> __input( __Istream & in )
{
	int capacity, n, price, weight;
	std::priority_queue<Material> mtrls;
	// in.ignore( std::numeric_limits<std::streamsize>::max, '\n' );

	in >> capacity >> n;

	while( n-- )
	{
		in >> price >> weight;
		mtrls.push( { price, weight } );
	}

	return { mtrls, capacity };
}


std::pair<std::priority_queue<Material>, int> input( const char* fname )
{
	if ( !fname )
	{
		return __input( std::cin );
	}
	else
	{
		std::ifstream ifs { fname, std::ofstream::in };
		auto mat_and_capacity { __input( ifs ) };
		ifs.close();

		return mat_and_capacity;
	}
}


template <typename __Ostream>
void __output( __Ostream & os, int sum )
{
	os << sum;
}

void output( int sum, const char* fname )
{
	if ( !fname )
	{
		__output( std::cout, sum );
	}
	else
	{
		std::ofstream ofs { fname };
		__output( ofs, sum );
		ofs.close();
	}
}
