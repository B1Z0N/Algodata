#include <iostream>	// cin, cout
#include <ios>		// streamsize
#include <vector>	// vector
#include <fstream>	// ifstream
#include <limits>	// numeric_limits<streamsize>::max

template <typename __Istream>
std::vector<int> __input( __Istream&);

std::vector<int> input( const char* fname = nullptr );

template <typename __Ostream>
void __output( __Ostream&, int );

void output( int, const char* fname = nullptr );


// @Problem
// You have a rod and you need to cut it on pieces
// of lengths, in a such way that it has the biggest
// summary cost.
//
// You are given length/cost table and initial rod length.
//
// @Example
// +--------+---+---+---+---+
// | length | 1 | 2 | 3 | 4 |
// +--------+---+---+---+---+
// | price  | 2 | 5 | 3 | 8 |
// +--------+---+---+---+---+
// initial rod length is 4
// the solution is 10 = 5 + 5 ( 2 pieces of length 2 )
//
// @Input format
// 4
// 2 5 3 8

/**
 * Recursive helper function
 */
int __cut_the_rod( const std::vector<int>& costs, std::vector<int>& visited, int len)
{
	if( len == 1 )
		// whole rod, can't delete
		return visited[0];

	int cost = costs[ len - 1 ];
	// try to sell it as is, not cutting
	int next_cost;

	for( int i = 1; i <= len / 2; i++ )
	// loop to check only half
	// because other half is symmetric
	{
		// try cutting 1, 2, 3 ...
		// and find optimal
		if( visited[ len - i - 1 ] != -1 )
			// if we already found - use it
			next_cost = visited[ len - i - 1 ];
		else
			// if no - go find it
			next_cost = __cut_the_rod( costs, visited, len - i );

		// plus cost of the pieace we are cutting
		next_cost += costs[ i - 1 ];

		if( cost < next_cost )
			// assign maximal value
			cost = next_cost;
	}

	// don't forget to set this
	// as visited
	visited[len - 1] = cost;
	return cost;
}
/**
 * Solution function
 */
int cut_the_rod( std::vector<int> costs )
{
	std::vector<int> visited ( costs.size() );
	// vector of already found optimal costs 
	for( auto& x : visited ) x = -1;
	visited[0] = costs[0];
	// rod of length 1 is optimally selled at cost of itself

	return __cut_the_rod( costs, visited, costs.size() );
}


int main()
{
	std::vector<int> costs { input() };
	int res { cut_the_rod( costs ) };
	output( res );

	return 0;
}


template <typename __Istream>
std::vector<int> __input( __Istream& in )
{
	int n;
	std::vector<int> costs;

	in >> n;
	// in.ignore( std::numeric_limits<std::streamsize>::max, '\n' );

	while( n-- )
	{
		int cost;
		in >> cost;
		costs.push_back( cost );
	}

	return costs;
}


std::vector<int> input( const char* fname )
{
	if( !fname )
	{
		return __input( std::cin );
	}
	else
	{
		std::ifstream ifs { fname, std::ofstream::in };
		std::vector<int> costs { __input( ifs ) };
		ifs.close();

		return costs; 
	}
} 


template <typename __Ostream>
void __output( __Ostream& os, int res )
{
	os << res;
}


void output( int res, const char* fname )
{
	if( !fname )
	{
		__output( std::cout, res );
	}
	else
	{
		std::ofstream ofs { fname };
		__output( ofs, res );
		ofs.close();
	}
}