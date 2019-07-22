#include <iostream>	// cin, cout
#include <ios>		// streamsize
#include <vector>	// vector
#include <fstream>	// ifstream
#include <limits>	// numeric_limits<streamsize>::max
#include <map>
#include <tuple>

struct Dims
{
	int rows;
	int cols;
};

template <typename __Istream>
std::vector<Dims> __input( __Istream&);

std::vector<Dims> input( const char* fname = nullptr );

template <typename __Ostream>
void __output( __Ostream&, int );

void output( int, const char* fname = nullptr );


// @Preface
// When multiplying matrices, you could change parentheses
// like this ( ( A1 * A2 ) * A3 ) = ( A1 * ( A2 * A3 ) )
// so that matrix multiplication becomes more efficient
//
// @Problem
// Change parentheses, so that multiplication became
// more efficient
//
// @Example
// A [ 5 x 10 ]
// B [ 10 x 20 ]
// C [ 20 x 5 ]
// Solution:
// ( A * B ) ~ 5 * 10 * 20 = 1000 mult.
// ( B * C ) ~ 10 * 20 * 5 = 1000 mult.
// ( A * ( B * C ) ) ~ 1250 multiplications
// ( ( A * B ) * C ) ~ 1500 multiplications
// Answer: 1250 multiplications
//
// @Input format
// 3
// 5 10
// 10 20
// 20 5


/**
 * Helper recursive function
 */
int __parenthesise(
    const std::vector<Dims>& mtr,
    std::map<std::pair<int, int>, int>& visited,
    // visited intervals of matrices
    // maps interval to minimal multiplication number
    int start,
    // interval start
    int end
    // interval end
)
{
	if ( visited.find( { start, end } ) != std::end( visited ) )
		// if we've already calculated minimal multiplications for this case
		return visited[ { start, end } ];

	int right_mult = __parenthesise( mtr, visited, start + 1, end );
	// A1 * ( A2 * ... * An )
	int left_mult  = __parenthesise( mtr, visited, start, end - 1 );
	// (A1 * ... * An-1 ) * An

	right_mult += mtr[ start ].rows *
	              mtr[ start ].cols *
	              mtr[ end   ].cols ;

	left_mult  += mtr[ start ].rows *
	              mtr[  end  ].rows *
	              mtr[  end  ].cols ;
    // now add appropriate matrix multiplication costs
    int min_mult = std::min( right_mult, left_mult );
    // and find minimal cost
	visited[ { start, end } ] = min_mult;
	// mark case as calculated
	return min_mult;
}

/**
 * Solution function
 */
int parenthesise( std::vector<Dims> mtr )
{
	std::map<std::pair<int, int>, int> visited;
	for ( int i = 1; i < mtr.size(); i++ )
		// initializing every pair of matrices
		visited[ { i - 1, i } ] = mtr[ i - 1 ].rows *
		                          mtr[ i - 1 ].cols *
		                          mtr[   i	 ].cols ;


	return __parenthesise( mtr, visited, 0, mtr.size() - 1 );
}


int main()
{
	std::vector<Dims> matrices { input() };
	int res { parenthesise( matrices ) };
	output( res );

	return 0;
}


template <typename __Istream>
std::vector<Dims> __input( __Istream& in )
{
	int n, rows, cols;
	std::vector<Dims> matrices;

	in >> n;
	// in.ignore( std::numeric_limits<std::streamsize>::max, '\n' );

	while ( n-- )
	{
		in >> rows >> cols;
		matrices.push_back( { rows, cols } );
	}

	return matrices;
}


std::vector<Dims> input( const char* fname )
{
	if ( !fname )
	{
		return __input( std::cin );
	}
	else
	{
		std::ifstream ifs { fname, std::ofstream::in };
		std::vector<Dims> matrices { __input( ifs ) };
		ifs.close();

		return matrices;
	}
}


template <typename __Ostream>
void __output( __Ostream& os, int res )
{
	os << res;
}


void output( int res, const char* fname )
{
	if ( !fname )
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