#include <iostream>	// cin, cout
#include <ios>		// streamsize
#include <vector>	// vector
#include <fstream>	// ifstream
#include <limits>	// numeric_limits<streamsize>::max
#include <map>
#include <tuple>
#include <string>

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


/**
 * Solution function
 */
int edit_distance( std::string a, std::string b )
{

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