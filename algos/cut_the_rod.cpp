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
	in.ignore( std::numeric_limits<std::streamsize>::max, '\n' );

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
		return __input( cin );
	}
	else
	{
		std::ofstream ifs { fname, std::ofstream::in };
		std::vector<int> costs { __input( ifs ) };
		ofs.close();

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
		__output( os, res );
	}
	else
	{
		std::ofstream ofs { fname };
		__output( ofs, res );
		ofs.close();
	}
}