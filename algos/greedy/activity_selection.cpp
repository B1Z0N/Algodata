#include <iostream>	// cin, cout
#include <ios>		// streamsize
#include <vector>	// vector
#include <fstream>	// ifstream
#include <limits>	// numeric_limits<streamsize>::max
#include <queue>
#include <tuple>


//------------------------------------------------------------------------------------------
// @Problem
// Suppose we have a set S = { a1, a2, ... , an };
// of n proposed activities that wish to use a resource, such as a lecture hall, which
// can serve only one activity at a time. Each activity ai has a start time si and a finish
// time fi , where ( 0 <= si < fi < inf ). If selected, activity ai takes place during the
// half-open time interval [ si, fi ). Activities ai and aj are compatible if the intervals
// [ si, fi ) and [ sj, fj ) do not overlap. That is, ai and aj are compatible if si >= fj
// or sj >= fi. Each activity has it's weight value W( ai ), W -function that  maps 
// activity i to some nonegative number. In the activity-selection problem, we wish 
// to select a compatible subset of intervals, so that 
// ( W( ak ) + W( aj ) + ... + W( am ) ) is maximal.
// 
// @Example
// You are given the table:
// ╔════════╦═══╦════╦═══╦═══╦═══╦════╗
// ║   i    ║ 1 ║ 2  ║ 3 ║ 4 ║ 5 ║ 6  ║
// ╠════════╬═══╬════╬═══╬═══╬═══╬════╣
// ║ start  ║ 4 ║  9 ║ 2 ║ 3 ║ 5 ║  7 ║
// ║ finish ║ 5 ║ 11 ║ 6 ║ 7 ║ 6 ║ 10 ║
// ║ weight ║ 4 ║  2 ║ 8 ║ 1 ║ 6 ║ 11 ║
// ╚════════╩═══╩════╩═══╩═══╩═══╩════╝
// 
//
// @Input format
// 6
// 4 5 4
// 9 11 2
// 2 6 8
// 3 7 1
// 5 6 6
// 7 10 11
//
// @Output
// _
//
//--------------------------------------------------------------------------------------------


/**
 * Struct for single activity data
 */
struct Activity
{
	std::size_t start;
	std::size_t end;
	std::size_t weight;
};


/**
 * Class to solve activity selection problem
 */
class ActivityQuery
{
	std::vector<Activity> quer;
	mutable std::vector<std::size_t> selection;
	mutable std::size_t max_weight { -1 };

public:

	ActivityQuery( std::vector<std::size_t> start, std::vector<std::size_t> end, std::vector<std::size_t> weight ) noexcept;
	ActivityQuery( std::map<std::pair<std::size_t, std::size_t>, std::size_t> start_end_to_weight ) noexcept;
	ActivityQuery( std::vector<Activity> actvt ) noexcept;

	/**
	 * Returns pair of selected ranges and max_weight
	 * Calculated only first time, then just returns the result
	 */
	std::pair<std::vector<std::size_t>, std::size_t> solve( ) const;
};

std::ostream& operator<<( std::ostream& os, ActivityQuery& aq );
std::istream& operator>>( std::istream& is, ActivityQuery& aq );

int main()
{
	auto actq;
	std::cin >> actq;
	actq.solve();
	std::cout << actq << '\n';

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
