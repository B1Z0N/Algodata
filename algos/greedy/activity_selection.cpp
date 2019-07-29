#include <iostream>	// cin, cout
#include <ios>		// streamsize
#include <vector>	// vector
#include <fstream>	// ifstream
#include <limits>	// numeric_limits<streamsize>::max
#include <queue>
#include <tuple>
#include <algorithm>


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
	mutable std::size_t max_weight;

	mutable bool calculated { false };

	void sort()
	{
		std::sort( std::begin( quer ), std::end( quer ), 
			[] (const Activity& fst, const Activity& snd)
			{
				return fst.end < snd.end;
			}
		);
	}
public:
	ActivityQuery( ) = default;

	ActivityQuery( std::vector<std::size_t> start, std::vector<std::size_t> end, std::vector<std::size_t> weight )
	{
		for( int i = 0; i < start.size(); i++ )
			quer.push_back( { start[i], end[i], weight[i] } );

		sort();
	}

	ActivityQuery( const std::vector<Activity>& actvt )
	: quer{ actvt } { sort(); }

	std::vector<Activity> get_activities() const
	{
		return quer;
	}

	/**
	 * Returns max_weight
	 * Calculated only first time, then just returns the result
	 */
	std::size_t solve( ) const
	{
		if( !calculated )
		{
			__solve();
			calculated = true;
		}

		return max_weight;
	}

private:
	void __solve() const;
};

std::ostream& operator<<( std::ostream& os, const ActivityQuery& aq );
std::istream& operator>>( std::istream& is, ActivityQuery& aq );


int main( int argc, char* argv[] )
{
	std::ifstream ifile { argv[1] };

	ActivityQuery actq { };
	ifile >> actq;
	std::cout << actq << '\n';

	ifile.close();

	return 0;
}


/**
 * Algorithm of solution
 */
void ActivityQuery::__solve() const
{
	static auto left_activity_bsearch {
		[this] ( std::size_t index ) -> int
		{
			std::size_t lo = 0, hi = index - 1;
			while( lo <= hi )
			{
				std::size_t mid = ( lo + hi ) / 2;

				if( quer[ mid ].end <= quer[ index ].start )
				{
					if( quer[ mid + 1 ].end <= quer[ index ].start )
						lo = mid + 1;
					else
						return mid;
				}
				else
					hi = mid - 1;
			}

			return -1;
		}
	};

	std::vector<std::size_t> sol ( quer.size() );

	sol[0] = quer[0].weight;
	for( std::size_t i = 1; i < quer.size(); i++ )
	{
		std::size_t weight_with_current = quer[i].weight;
		int j = left_activity_bsearch( i );

		if( j != -1 ) weight_with_current += sol[j];

		if( sol[ i - 1 ] > weight_with_current )
		{
			sol[ i ] = sol[ i - 1 ];
		}
		else
		{
			sol[ i ] = weight_with_current;
		}
	}

	max_weight = sol.back();
}

std::istream& operator>>( std::istream& is, ActivityQuery& aq )
{
	std::vector<Activity> actvts;
	Activity temp;

	std::size_t n;
	is >> n;

	while( n-- )
	{
		is >> temp.start >> temp.end >> temp.weight;
		actvts.push_back( temp );
	}

	aq = ActivityQuery { actvts };

	return is;
}

std::ostream& operator<<( std::ostream& os, const ActivityQuery& aq)
{
	return os << aq.solve();
}

