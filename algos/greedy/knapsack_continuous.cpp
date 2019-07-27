#include <iostream>	// cin, cout
#include <ios>		// streamsize
#include <vector>	// vector
#include <fstream>	// ifstream
#include <limits>	// numeric_limits<streamsize>::max
#include <memory>
#include <unordered_map>


template <typename __Istream>
std::unordered_multimap<int, int> __input( __Istream&);

std::unordered_multimap<int, int> input( const char* fname = nullptr );

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
// max( 4/5, 9/3, 11/4, 2/6 ) = 11/4 = 2.75 ( $ / kg )
// so, buddy, take 4 kg of 3rd material
// 2. Since we have more space, we repeat 1st step.
// max( 4/5, 9/3, 2/6 ) = 9/3 = 3 ( $ / kg )
// take 3 kg of 2nd material
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
// ( 4 * 11 + 3 * 9 + 1 * 4 )
//-----------------------------------------------------------------------------


int main()
{
	auto materials = input();
	for( const auto& x : materials )
		std::cout << x.first << " " << x.second;
	std::cout << '\n';
	
	return 0;
}


template <typename __Istream>
std::unordered_multimap<int, int> __input( __Istream & in )
{
	int capacity, n, price, weight;
	std::unordered_multimap<int, int> materials;
	// in.ignore( std::numeric_limits<std::streamsize>::max, '\n' );

	in >> capacity >> n;

	while( n-- )
	{
		in >> price >> weight;
		materials.insert( std::make_pair( price, weight ) );
	}

	return materials;
}


std::unordered_multimap<int, int> input( const char* fname )
{
	if ( !fname )
	{
		return __input( std::cin );
	}
	else
	{
		std::ifstream ifs { fname, std::ofstream::in };
		std::unordered_multimap<int, int> text { __input( ifs ) };
		ifs.close();

		return text;
	}
}


template <typename __Ostream>
void __output( __Ostream & os, const std::string & encoded )
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
