#include <iostream>	// cin, cout
#include <ios>		// streamsize
#include <vector>	// vector
#include <fstream>	// ifstream
#include <limits>	// numeric_limits<streamsize>::max
#include <unordered_map>
#include <string>
#include <functional> // hash


template <typename __Istream>
std::string __input( __Istream&);

std::string input( const char* fname = nullptr );

template <typename __Ostream>
void __output( __Ostream&, int );

void output( int, const char* fname = nullptr );

// @Preface
// Editing distance is the number of operations to
// convert string x[1..n] to string y[1..m]
// Operations are:
// 1. Delete character x[i]
// 2. Insert character c after x[i]
// 3. Assign character c to x[i]
//
// @Problem
// Find edit distance on two strings
//
// @Example
// mohito
// motorola
//
// Solution:
//+------+------------+-----------+
//| Step |   String   | Operation |
//+------+------------+-----------+
//|  0.  | [mo]hito   | none      |
//|  1.  | [mot]ito   | assign    |
//|  2.  | [moto]to   | assign    |
//|  3.  | [motor]o   | assign    |
//|  3.  | [motoro]   | none      |
//|  4.  | [motorol]  | insert    |
//|  5.  | [motorola] | insert    |
//+------+------------+-----------+
// Answer: distance is five
//
// @Input format
// mohito
// motorola
// 
// @Output format
// 5

struct EditIntervals
// structure to denote substrings
// to find edit_distance of 
// a[0..end1] and b[0..end2]
{
	int end1;
	int end2;

	friend bool operator==( const EditIntervals& a, const EditIntervals& b)
	{
		return a.end1 == b.end1 && a.end2 == b.end2;
	}
};

class EditIntervalsHash
// hash functor for unordered_map
{
public:
	size_t operator()( const EditIntervals& ivls ) const
	{
		return std::hash<int>{}( ivls.end1 ) ^ std::hash<int>{}( ivls.end2 );
	}
};

int min( int a, int b, int c )
{
	return std::min( std::min( a, b ), c ); 
} 

/**
 * Recursive helper function
 */
int __edit_distance( const std::string& a, const std::string& b, 
	std::unordered_map<EditIntervals, int, EditIntervalsHash>& visited, 
	int enda, int endb )
{
	if( visited.find( { enda, endb } ) != std::end( visited ) )
		// if already calculated - return it
		return visited[ { enda, endb } ];

	if ( enda == 0 ) return endb;
	if ( endb == 0 ) return enda;

	if( a[ enda - 1 ] == b[ endb - 1 ] ) 
	{
		visited[ { enda, endb } ] = __edit_distance( a, b, visited, enda - 1, endb - 1 );

		return visited[ { enda, endb } ];
	}

	visited[ { enda, endb } ] = min( 
			__edit_distance( a, b, visited, enda 	, endb - 1 ), // insert
			__edit_distance( a, b, visited, enda - 1, endb     ), // remove
			__edit_distance( a, b, visited, enda - 1, endb - 1 )  // replace
		) + 1;

	return visited[ { enda, endb } ];
}

/**
 * Solution function
 */
int edit_distance( std::string a, std::string b )
{
	int cost = 0;
	std::unordered_map<EditIntervals, int, EditIntervalsHash> visited;

	return __edit_distance( a, b, visited, a.size(), b.size() );
}

int main()
{
	std::string a { input() };
	std::string b { input() };
	int res { edit_distance( a, b ) };
	output( res );

	return 0;
}


template <typename __Istream>
std::string __input( __Istream& in )
{
	std::string str;

	in >> str;
	// in.ignore( std::numeric_limits<std::streamsize>::max, '\n' );

	return str;
}


std::string input( const char* fname )
{
	if ( !fname )
	{
		return __input( std::cin );
	}
	else
	{
		std::ifstream ifs { fname, std::ofstream::in };
		std::string str { __input( ifs ) };
		ifs.close();

		return str;
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