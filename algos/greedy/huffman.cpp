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

//------------------------------------------------------------------
// @Problem
// Encode and decode information with Huffman encoding
//
// You are given an array of elements with attributes 
// freq ( x.freq ) and val ( x.val )
//
// @Example
// 1. You are given a text, so you capture letter's frequencies
// and push it to the table
//
// 2. Buiding binary tree
// +------+-----+-----+-----+-----+
// | val  | 'a' | 'b' | 'c' | 'd' |
// +------+-----+-----+-----+-----+
// | freq |  14 |  5  |  9  |  7  |
// +------+-----+-----+-----+-----+
// 
// so lets build code tree:
// * Find two vals with minimal frequencies and push it to the tree,
//   root of this two nodes added to the table 
//   ( 0 is the least of two vals and 1 is another)
// 			
//  			 ''(12)
//				 /	 \
//			   0/	  \1
//	 	  'b'(5)	  'd'(7)
//
// * Repeat previous step with new data
// 		
// 				 ''(21)
// 				 /	 \
// 			   0/	  \1
// 			'c'(9)  ''(12)
// 					 /	 \
// 				   0/	  \1
// 			   'b'(5)	  'd'(7)
// 		
// * And again 
//		    
//		    	   ''(35)
//		    	   /  \
//		    	 0/	   \1
//		     'a'(14) ''(21)
//		    		 /	 \
//		    	   0/	  \1
//		    	'c'(9)  ''(12)
//		    			 /	 \
//		    		   0/	  \1
//		    	   'b'(5)	  'd'(7)
//
// the solution is binary ( not search ) tree mentioned above, 
// so, for example, code for 'a' is 0 and code for 'b' is 110
// code of 'cabad' is 10 0 110 0 111
//					   c a  b  a  d
//
// P. S. we should've been encoding our initial text, but it is to
// cumbersome to show it as an example, just use the same algorithm 
// to encode and decode( in 3rd item ) initial text
// 
// 3. Decoding
//
// let us decode this, we are given tree above and 
// a code mentioned above ( cabad )
// 
// we have code 1001100111
// * take 1, go right in the tree, take 0 go left and stop,
// because there are no way further, so we get 'c' as a first letter
//
// * in the same way we get 'a', 'b', 'a', and 'd', we can't have any
// ambiguity in letters, cause this is the property of a Huffman encoding
//
// @Input format
// cabad
//
// @Output
// 1001100111
//-----------------------------------------------------------------------------

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